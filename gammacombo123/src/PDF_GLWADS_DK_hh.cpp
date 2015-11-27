/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 * Combine only the DK observables from 13 observables from the
 * two body GLW/ADS measurement.
 *
 **/

#include "PDF_GLWADS_DK_hh.h"

	PDF_GLWADS_DK_hh::PDF_GLWADS_DK_hh(config cObs, config cErr, config cCor, ParametersAbs* pars, TString d)
: PDF_GLWADS_DKDpi_hh(pars,d,8)
{
	name = "glwads-dk-hh";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_GLWADS_DK_hh::~PDF_GLWADS_DK_hh(){}


void PDF_GLWADS_DK_hh::initParameters()
{
	parameters = new RooArgList("parameters");
	parameters->add(*(p->get("r_dk")));
	parameters->add(*(p->get("d_dk")));
	parameters->add(*(p->get("g")));
	parameters->add(*(p->get("rD_kpi")));
	parameters->add(*(p->get("dD_kpi")));
	parameters->add(*(p->get("RBRdkdpi")));
	parameters->add(*(p->get("AcpDKK")));
	parameters->add(*(p->get("AcpDpipi")));
}


void PDF_GLWADS_DK_hh::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	theory->add(*(new RooFormulaVar("rkp_kpi_th",      "rkp_kpi_th",      "RBRdkdpi*(1 + r_dk^2 * rD_kpi^2 + 2*r_dk*rD_kpi*cos(g)*cos(d_dk-dD_kpi))", *p)));
	theory->add(*(new RooFormulaVar("rkp_pipi_th",     "rkp_pipi_th",     "RBRdkdpi*(1 + r_dk^2 + 2*r_dk*cos(d_dk)*cos(g))", *p)));
	theory->add(*(new RooFormulaVar("rkp_kk_th",       "rkp_kk_th",       "RBRdkdpi*(1 + r_dk^2 + 2*r_dk*cos(d_dk)*cos(g))", *p)));
	theory->add(*(new RooFormulaVar("afav_dk_kpi_th",  "afav_dk_kpi_th",  "2*r_dk *rD_kpi*sin(g)*sin(d_dk -dD_kpi) / (1 + r_dk^2  * rD_kpi^2 + 2*r_dk *rD_kpi*cos(g)*cos(d_dk -dD_kpi))", *p)));
	theory->add(*(new RooFormulaVar("acp_dk_kk_th",    "acp_dk_kk_th",    "2*r_dk *sin(d_dk) *sin(g) / (1 + r_dk^2  + 2*r_dk *cos(d_dk) *cos(g)) + AcpDKK", *p)));
	theory->add(*(new RooFormulaVar("acp_dk_pipi_th",  "acp_dk_pipi_th",  "2*r_dk *sin(d_dk) *sin(g) / (1 + r_dk^2  + 2*r_dk *cos(d_dk) *cos(g)) + AcpDpipi", *p)));
	theory->add(*(new RooFormulaVar("rp_dk_kpi_th",    "rp_dk_kpi_th",    "(r_dk^2  + rD_kpi^2 + 2*r_dk *rD_kpi*cos( g+d_dk +dD_kpi)) / (1 + r_dk^2 *rD_kpi^2 + 2*r_dk *rD_kpi*cos( g +d_dk -dD_kpi))", *p)));
	theory->add(*(new RooFormulaVar("rm_dk_kpi_th",    "rm_dk_kpi_th",    "(r_dk^2  + rD_kpi^2 + 2*r_dk *rD_kpi*cos(-g+d_dk +dD_kpi)) / (1 + r_dk^2 *rD_kpi^2 + 2*r_dk *rD_kpi*cos(-g +d_dk -dD_kpi))", *p)));
}


void PDF_GLWADS_DK_hh::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("rkp_kpi_obs",      "R_{K/#pi} (K#pi)",   1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rkp_pipi_obs",     "R_{K/#pi} (#pi#pi)", 1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rkp_kk_obs",       "R_{K/#pi} (KK)",     1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("afav_dk_kpi_obs",  "Afav (DK K#pi)",     0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dk_kk_obs",    "ACP (DK KK)",        0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dk_pipi_obs",  "ACP (DK #pi#pi)",    0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rp_dk_kpi_obs",    "R+ (DK K#pi)",       1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rm_dk_kpi_obs",    "R- (DK K#pi)",       1, -1e4, 1e4)));
}


void PDF_GLWADS_DK_hh::setUncertainties(config c)
{
	switch(c)
	{
		case lumi1fb: {
						  obsErrSource = "1fb-1 LHCb-PAPER-2012-001, ExpNll/winter2012ADSGLWResult.root";
						  TString File = this->dir+"/ExpNll/winter2012ADSGLWResult.root";
						  if ( !FileExists(File) ){cout << "PDF_GLWADS_DK_hh::setUncertainties : ERROR : File not found : " << File << endl; exit(1);}
						  TFile *fr = TFile::Open(File);
						  RooFitResult *r = (RooFitResult*)fr->Get("fitresult_model_reducedData_binned");
						  assert(r);
						  for ( int i=0; i<nObs; i++ ) {
							  RooRealVar* pObs = (RooRealVar*)((RooArgList*)observables)->at(i);
							  RooRealVar* pRes = (RooRealVar*)r->floatParsFinal().find(obsTmkToMalcolm(pObs->GetName())); assert(pRes);
							  StatErr[i] = pRes->getError();
						  }
						  SystErr[ 0] = 0.0018;  // rkp_kpi_obs
						  SystErr[ 1] = 0.0017;  // rkp_pipi_obs
						  SystErr[ 2] = 0.0018;  // rkp_kk_obs
						  SystErr[ 3] = 0.0174;  // afav_dk_obs
						  SystErr[ 4] = 0.010;   // acp_dk_kk_obs
						  SystErr[ 5] = 0.010;   // acp_dk_pipi_obs
						  SystErr[ 6] = 0.0007;  // rp_dk_obs
						  SystErr[ 7] = 0.0004;  // rm_dk_obs
						  fr->Close();
						  delete r;
						  delete fr;
						  break;
					  }
		case lumi3fb:{
						 // This has been copied over from PDF_GLWADS_DKDpi_hh
						 obsErrSource = "3fb-1 ANA v7 unblind"; // https://twiki.cern.ch/twiki/pub/LHCbPhysics/B2D0K/LHCb-ANA-2014-071-v7.pdf (see Vavas email 04/08/15)
						 // these get transformed over from the new inputs using ExpNll/transportGLWADS_new_to_old.py
						 //
						 // in the case of the DK only (robust) combination some of the observables don't exist
						 // usemap as the temp store
						 std::map< TString, double > stat_errs;
						 stat_errs["rkp_kpi_obs"]      = 0.0006;
						 stat_errs["rkp_pipi_obs"]     = 0.003173;
						 stat_errs["rkp_kk_obs"]       = 0.001810;
						 stat_errs["afav_dk_kpi_obs"]  = 0.0072;
						 stat_errs["acp_dk_kk_obs"]    = 0.0202;
						 stat_errs["acp_dk_pipi_obs"]  = 0.0370;
						 stat_errs["rp_dk_kpi_obs"]    = 0.001868;
						 stat_errs["rm_dk_kpi_obs"]    = 0.001241;

						 for ( int i=0; i<nObs; i++ )
						 {
							 RooRealVar* pObs = (RooRealVar*)((RooArgList*)observables)->at(i);
							 StatErr[i] = stat_errs[pObs->GetName()];
						 }
						 stat_errs.clear();

						 std::map< TString, double > syst_errs;
						 syst_errs["rkp_kpi_obs"]      = 0.0019;
						 syst_errs["rkp_pipi_obs"]     = 0.00278;
						 syst_errs["rkp_kk_obs"]       = 0.002461;
						 syst_errs["afav_dk_kpi_obs"]  = 0.0060;
						 syst_errs["acp_dk_kk_obs"]    = 0.0081;
						 syst_errs["acp_dk_pipi_obs"]  = 0.0120;
						 syst_errs["rp_dk_kpi_obs"]    = 0.001417;
						 syst_errs["rm_dk_kpi_obs"]    = 0.000629;

						 for ( int i=0; i<nObs; i++ )
						 {
							 RooRealVar* pObs = (RooRealVar*)((RooArgList*)observables)->at(i);
							 SystErr[i] = syst_errs[pObs->GetName()];
						 }
						 syst_errs.clear();

						 break;
					 }
		default: {
					 cout << "PDF_GLWADS_DK_hh::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					 exit(1);
				 }
	}
}
