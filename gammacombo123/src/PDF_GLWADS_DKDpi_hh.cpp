/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 * Combine all 13 observables from the GLW/ADS measurement.
 *
 **/

#include "PDF_GLWADS_DKDpi_hh.h"

	PDF_GLWADS_DKDpi_hh::PDF_GLWADS_DKDpi_hh(config cObs, config cErr, config cCor, ParametersAbs* pars, TString d)
: PDF_Abs(13)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	name = "glwads-dkdpi-hh";
	this->dir = d;
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}

	PDF_GLWADS_DKDpi_hh::PDF_GLWADS_DKDpi_hh(ParametersAbs* pars, TString d, int nObs)
: PDF_Abs(nObs)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	this->dir = d;
}


PDF_GLWADS_DKDpi_hh::~PDF_GLWADS_DKDpi_hh(){}


void PDF_GLWADS_DKDpi_hh::initParameters()
{
	parameters = new RooArgList("parameters");
	parameters->add(*(p->get("r_dk")));
	parameters->add(*(p->get("d_dk")));
	parameters->add(*(p->get("r_dpi")));
	parameters->add(*(p->get("d_dpi")));
	parameters->add(*(p->get("g")));
	parameters->add(*(p->get("rD_kpi")));
	parameters->add(*(p->get("dD_kpi")));
	parameters->add(*(p->get("RBRdkdpi")));
	parameters->add(*(p->get("AcpDKK")));
	parameters->add(*(p->get("AcpDpipi")));
}


void PDF_GLWADS_DKDpi_hh::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	theory->add(*(new RooFormulaVar("rkp_kpi_th",      "rkp_kpi_th",      "RBRdkdpi*(1 + r_dk^2 * rD_kpi^2 + 2*r_dk*rD_kpi*cos(g)*cos(d_dk-dD_kpi))/(1 + r_dpi^2 * rD_kpi^2 + 2*r_dpi*rD_kpi*cos(g)*cos(d_dpi-dD_kpi))", *p)));
	theory->add(*(new RooFormulaVar("rkp_pipi_th",     "rkp_pipi_th",     "RBRdkdpi*(1 + r_dk^2 + 2*r_dk*cos(d_dk)*cos(g))/(1 + r_dpi^2 + 2*r_dpi*cos(d_dpi)*cos(g))", *p)));
	theory->add(*(new RooFormulaVar("rkp_kk_th",       "rkp_kk_th",       "RBRdkdpi*(1 + r_dk^2 + 2*r_dk*cos(d_dk)*cos(g))/(1 + r_dpi^2 + 2*r_dpi*cos(d_dpi)*cos(g))", *p)));
	theory->add(*(new RooFormulaVar("afav_dk_kpi_th",  "afav_dk_kpi_th",  "2*r_dk *rD_kpi*sin(g)*sin(d_dk -dD_kpi) / (1 + r_dk^2  * rD_kpi^2 + 2*r_dk *rD_kpi*cos(g)*cos(d_dk -dD_kpi))", *p)));
	theory->add(*(new RooFormulaVar("afav_dpi_kpi_th", "afav_dpi_kpi_th", "2*r_dpi*rD_kpi*sin(g)*sin(d_dpi-dD_kpi) / (1 + r_dpi^2 * rD_kpi^2 + 2*r_dpi*rD_kpi*cos(g)*cos(d_dpi-dD_kpi))", *p)));
	theory->add(*(new RooFormulaVar("acp_dk_kk_th",    "acp_dk_kk_th",    "2*r_dk *sin(d_dk) *sin(g) / (1 + r_dk^2  + 2*r_dk *cos(d_dk) *cos(g)) + AcpDKK", *p)));
	theory->add(*(new RooFormulaVar("acp_dk_pipi_th",  "acp_dk_pipi_th",  "2*r_dk *sin(d_dk) *sin(g) / (1 + r_dk^2  + 2*r_dk *cos(d_dk) *cos(g)) + AcpDpipi", *p)));
	theory->add(*(new RooFormulaVar("acp_dpi_kk_th",   "acp_dpi_kk_th",   "2*r_dpi*sin(d_dpi)*sin(g) / (1 + r_dpi^2 + 2*r_dpi*cos(d_dpi)*cos(g)) + AcpDKK", *p)));
	theory->add(*(new RooFormulaVar("acp_dpi_pipi_th", "acp_dpi_pipi_th", "2*r_dpi*sin(d_dpi)*sin(g) / (1 + r_dpi^2 + 2*r_dpi*cos(d_dpi)*cos(g)) + AcpDpipi", *p)));
	theory->add(*(new RooFormulaVar("rp_dk_kpi_th",    "rp_dk_kpi_th",    "(r_dk^2  + rD_kpi^2 + 2*r_dk *rD_kpi*cos( g+d_dk +dD_kpi)) / (1 + r_dk^2 *rD_kpi^2 + 2*r_dk *rD_kpi*cos( g +d_dk -dD_kpi))", *p)));
	theory->add(*(new RooFormulaVar("rm_dk_kpi_th",    "rm_dk_kpi_th",    "(r_dk^2  + rD_kpi^2 + 2*r_dk *rD_kpi*cos(-g+d_dk +dD_kpi)) / (1 + r_dk^2 *rD_kpi^2 + 2*r_dk *rD_kpi*cos(-g +d_dk -dD_kpi))", *p)));
	theory->add(*(new RooFormulaVar("rp_dpi_kpi_th",   "rp_dpi_kpi_th",   "(r_dpi^2 + rD_kpi^2 + 2*r_dpi*rD_kpi*cos( g+d_dpi+dD_kpi)) / (1 + r_dpi^2*rD_kpi^2 + 2*r_dpi*rD_kpi*cos( g +d_dpi-dD_kpi))", *p)));
	theory->add(*(new RooFormulaVar("rm_dpi_kpi_th",   "rm_dpi_kpi_th",   "(r_dpi^2 + rD_kpi^2 + 2*r_dpi*rD_kpi*cos(-g+d_dpi+dD_kpi)) / (1 + r_dpi^2*rD_kpi^2 + 2*r_dpi*rD_kpi*cos(-g +d_dpi-dD_kpi))", *p)));
}

///
/// TMK names are used in the GammaCombo code.
/// Malcolm names are used in GammaDini and the GLW/ADS RooFitResults.
///
TString PDF_GLWADS_DKDpi_hh::obsTmkToMalcolm(TString tmkObs)
{
	if ( tmkObs=="rkp_kpi_obs"          ) return "R_dk_vs_dpi_d2kpi"  ;
	if ( tmkObs=="rkp_pipi_obs"         ) return "R_dk_vs_dpi_d2pipi" ;
	if ( tmkObs=="rkp_kk_obs"           ) return "R_dk_vs_dpi_d2kk"   ;
	if ( tmkObs=="afav_dk_kpi_obs"      ) return "A_FAV_b2dk_d2kpi"   ;
	if ( tmkObs=="afav_dpi_kpi_obs"     ) return "A_FAV_b2dpi_d2kpi"  ;
	if ( tmkObs=="acp_dk_kk_obs"        ) return "A_CPP_b2dk_d2kk"    ;
	if ( tmkObs=="acp_dk_pipi_obs"      ) return "A_CPP_b2dk_d2pipi"  ;
	if ( tmkObs=="acp_dpi_kk_obs"       ) return "A_CPP_b2dpi_d2kk"   ;
	if ( tmkObs=="acp_dpi_pipi_obs"     ) return "A_CPP_b2dpi_d2pipi" ;
	if ( tmkObs=="rp_dk_kpi_obs"        ) return "R_plus_b2dk_d2pik"  ;
	if ( tmkObs=="rm_dk_kpi_obs"        ) return "R_minus_b2dk_d2pik" ;
	if ( tmkObs=="rp_dpi_kpi_obs"       ) return "R_plus_b2dpi_d2pik" ;
	if ( tmkObs=="rm_dpi_kpi_obs"       ) return "R_minus_b2dpi_d2pik";
	cout << "PDF_GLWADS_DKDpi_hh::obsTmkToMalcolm() : ERROR : not found : " << tmkObs << endl;
	assert(0);
}


void PDF_GLWADS_DKDpi_hh::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("rkp_kpi_obs",      "R_{K/#pi} (K#pi)",   1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rkp_pipi_obs",     "R_{K/#pi} (#pi#pi)", 1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rkp_kk_obs",       "R_{K/#pi} (KK)",     1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("afav_dk_kpi_obs",  "Afav (DK K#pi)",     0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("afav_dpi_kpi_obs", "Afav (D#pi K#pi)",   0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dk_kk_obs",    "ACP (DK KK)",        0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dk_pipi_obs",  "ACP (DK #pi#pi)",    0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dpi_kk_obs",   "ACP (D#pi KK)",      0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dpi_pipi_obs", "ACP (D#pi #pi#pi)",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rp_dk_kpi_obs",    "R+ (DK K#pi)",       1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rm_dk_kpi_obs",    "R- (DK K#pi)",       1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rp_dpi_kpi_obs",   "R+ (D#pi K#pi)",     1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rm_dpi_kpi_obs",   "R- (D#pi K#pi)",     1, -1e4, 1e4)));
}


void PDF_GLWADS_DKDpi_hh::setObservables(config c)
{
	switch(c)
	{
		case truth:{
					   setObservablesTruth();
					   break;
				   }
		case toy:{
					 setObservablesToy();
					 break;
				 }
		case lumi1fb:{
						 obsValSource = "1fb-1 LHCb-PAPER-2012-001, ExpNll/winter2012ADSGLWResult.root";
						 TString File = this->dir+"/ExpNll/winter2012ADSGLWResult.root";
						 if ( !FileExists(File) ){cout << "PDF_GLWADS_DKDpi_hh::setObservables : ERROR : File not found : " << File << endl; exit(1);}
						 TFile *fr = TFile::Open(File);
						 RooFitResult *r = (RooFitResult*)fr->Get("fitresult_model_reducedData_binned");
						 assert(r);
						 TIterator* it = observables->createIterator();
						 while ( RooRealVar* pObs = (RooRealVar*)it->Next() ){
							 RooRealVar* pRes = (RooRealVar*)r->floatParsFinal().find(obsTmkToMalcolm(pObs->GetName()));
							 pObs->setVal(pRes->getVal());
						 }
						 fr->Close();
						 delete it;
						 delete r;
						 delete fr;
						 break;
					 }
		case lumi3fb:{
						 obsValSource = "3fb-1 ANA v7 unblind"; // https://twiki.cern.ch/twiki/pub/LHCbPhysics/B2D0K/LHCb-ANA-2014-071-v7.pdf (see Vavas email 04/08/15)

						 // these get transformed over from the new inputs using ExpNll/transportGLWADS_new_to_old.py
						 //
						 // in the case of the DK only (robust) combination some of the observables don't exist
						 // usemap as the temp store
						 std::map< TString, double > vals;
						 vals["rkp_kpi_obs"] =       0.0779;
						 vals["rkp_pipi_obs"] =      0.078056;
						 vals["rkp_kk_obs"] =        0.075407;
						 vals["afav_dk_kpi_obs"] =   -0.0194;
						 vals["afav_dpi_kpi_obs"] =  0.0;			// now Aprod
						 vals["acp_dk_kk_obs"] =     0.0866;
						 vals["acp_dk_pipi_obs"] =   0.128;
						 vals["acp_dpi_kk_obs"] =    -0.0145;
						 vals["acp_dpi_pipi_obs"] =  0.00430;
						 vals["rp_dk_kpi_obs"] =     0.026376;
						 vals["rm_dk_kpi_obs"] =     0.011224;
						 vals["rp_dpi_kpi_obs"] =    0.003240;
						 vals["rm_dpi_kpi_obs"] =    0.00396;

						 // now can loop the observables and set the values
						 TIterator* it = observables->createIterator();
						 while ( RooRealVar* pObs = (RooRealVar*)it->Next() ){
							 pObs->setVal(vals[pObs->GetName()]);
						 }

						 vals.clear();
						 break;
					 }
		default:{
					cout << "PDF_GLWADS_DKDpi_hh::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_GLWADS_DKDpi_hh::setUncertainties(config c)
{
	switch(c){
		case lumi1fb:{
						 obsErrSource = "1fb-1 LHCb-PAPER-2012-001, ExpNll/winter2012ADSGLWResult.root";
						 TString File = this->dir+"/ExpNll/winter2012ADSGLWResult.root";
						 if ( !FileExists(File) ){cout << "PDF_GLWADS_DKDpi_hh::setUncertainties : ERROR : File not found : " << File << endl; exit(1);}
						 TFile *fr = TFile::Open(File);
						 RooFitResult *r = (RooFitResult*)fr->Get("fitresult_model_reducedData_binned");
						 assert(r);
						 for ( int i=0; i<nObs; i++ )
						 {
							 RooRealVar* pObs = (RooRealVar*)((RooArgList*)observables)->at(i);
							 RooRealVar* pRes = (RooRealVar*)r->floatParsFinal().find(obsTmkToMalcolm(pObs->GetName()));
							 assert(pRes);
							 StatErr[i] = pRes->getError();
						 }
						 SystErr[ 0] = 0.0018;  // rkp_kpi_obs
						 SystErr[ 1] = 0.0017;  // rkp_pipi_obs
						 SystErr[ 2] = 0.0018;  // rkp_kk_obs
						 SystErr[ 3] = 0.0174;  // afav_dk_obs
						 SystErr[ 4] = 0.0095;  // afav_dpi_obs
						 SystErr[ 5] = 0.010;   // acp_dk_kk_obs
						 SystErr[ 6] = 0.010;   // acp_dk_pipi_obs
						 SystErr[ 7] = 0.012;   // acp_dpi_kk_obs
						 SystErr[ 8] = 0.010;   // acp_dpi_pipi_obs
						 SystErr[ 9] = 0.0007;  // rp_dk_obs
						 SystErr[10] = 0.0004;  // rm_dk_obs
						 SystErr[11] = 0.00007; // rp_dpi_obs
						 SystErr[12] = 0.00008; // rm_dpi_obs
						 fr->Close();
						 delete r;
						 delete fr;
						 break;
					 }
					 // case lumi3fb:{
					 // 	setUncertainties(lumi1fb);
					 // 	obsErrSource = "3fb-1 errors obtained from scaling down the 1fb-1 errors";
					 // 	for ( int i=0; i<nObs; i++ ){
					 // 		StatErr[i] /= sqrt(5.);
					 // 		// SystErr[i] /= sqrt(3.);
					 // 	}
					 // 	break;
					 // }
		case lumi3fb:{
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
						 stat_errs["afav_dpi_kpi_obs"] = 0.1;     	// now Aprod, large error to disable it
						 stat_errs["acp_dk_kk_obs"]    = 0.0202;
						 stat_errs["acp_dk_pipi_obs"]  = 0.0370;
						 stat_errs["acp_dpi_kk_obs"]   = 0.0050;
						 stat_errs["acp_dpi_pipi_obs"] = 0.0086;
						 stat_errs["rp_dk_kpi_obs"]    = 0.001868;
						 stat_errs["rm_dk_kpi_obs"]    = 0.001241;
						 stat_errs["rp_dpi_kpi_obs"]   = 0.000156;
						 stat_errs["rm_dpi_kpi_obs"]   = 0.000174;

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
						 syst_errs["afav_dpi_kpi_obs"] = 0.1;      // now Aprod, large error to disable it
						 syst_errs["acp_dk_kk_obs"]    = 0.0081;
						 syst_errs["acp_dk_pipi_obs"]  = 0.0120;
						 syst_errs["acp_dpi_kk_obs"]   = 0.0017;
						 syst_errs["acp_dpi_pipi_obs"] = 0.00309;
						 syst_errs["rp_dk_kpi_obs"]    = 0.001417;
						 syst_errs["rm_dk_kpi_obs"]    = 0.000629;
						 syst_errs["rp_dpi_kpi_obs"]   = 0.000088;
						 syst_errs["rm_dpi_kpi_obs"]   = 0.000105;

						 for ( int i=0; i<nObs; i++ )
						 {
							 RooRealVar* pObs = (RooRealVar*)((RooArgList*)observables)->at(i);
							 SystErr[i] = syst_errs[pObs->GetName()];
						 }
						 syst_errs.clear();

						 break;
					 }
		case lumi9fb:{
						 setUncertainties(lumi3fb);
						 obsErrSource = "9fb-1 errors obtained from scaling down the 3fb-1 errors (lumi3fb)";
						 for ( int i=0; i<nObs; i++ ){
							 StatErr[i] /= (1.2 * sqrt(2.7));
							 SystErr[i] /= (1.2 * sqrt(2.7));
						 }
						 break;
					 }
		default:{
					cout << "PDF_GLWADS_DKDpi_hh::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_GLWADS_DKDpi_hh::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi1fb:
			{
				corSource = "1fb-1 LHCb-PAPER-2012-001, ExpNll/winter2012ADSGLWResult.root";
				TString File = this->dir+"/ExpNll/winter2012ADSGLWResult.root";
				if ( !FileExists(File) ){cout << "PDF_GLWADS_DKDpi_hh::setCorrelations : ERROR : File not found : " << File << endl; exit(1);}
				TFile *fr = TFile::Open(File);
				RooFitResult *r = (RooFitResult*)fr->Get("fitresult_model_reducedData_binned");
				assert(r);
				for ( int i=0; i<nObs; i++ )
					for ( int j=0; j<nObs; j++ )
					{
						RooRealVar* pObs1 = (RooRealVar*)((RooArgList*)observables)->at(i);
						RooRealVar* pObs2 = (RooRealVar*)((RooArgList*)observables)->at(j);
						corStatMatrix[i][j] = r->correlation(obsTmkToMalcolm(pObs1->GetName()),obsTmkToMalcolm(pObs2->GetName()));
					}
				// no systematics correlation
				fr->Close();
				delete r;
				delete fr;
				break;
			}
		case lumi1fbSystCor:
			{
				corSource = "1fb-1 LHCb-PAPER-2012-001, ExpNll/winter2012ADSGLWResult.root, Malcolm's toys";
				// statistical correlations
				TString File = this->dir+"/ExpNll/winter2012ADSGLWResult.root";
				TFile *fr = TFile::Open(File);
				RooFitResult *r = (RooFitResult*)fr->Get("fitresult_model_reducedData_binned");
				assert(r);
				for ( int i=0; i<nObs; i++ )
					for ( int j=0; j<nObs; j++ )
					{
						RooRealVar* tmkObs1 = (RooRealVar*)((RooArgList*)observables)->at(i);
						RooRealVar* tmkObs2 = (RooRealVar*)((RooArgList*)observables)->at(j);
						corStatMatrix[i][j] = r->correlation(obsTmkToMalcolm(tmkObs1->GetName()),obsTmkToMalcolm(tmkObs2->GetName()));
					}
				// systematics correlations
				SystCor_Kpi mySystCor;
				for ( int i=0; i<nObs; i++ )
					for ( int j=0; j<nObs; j++ )
					{
						RooRealVar* tmkObs1 = (RooRealVar*)((RooArgList*)observables)->at(i);
						RooRealVar* tmkObs2 = (RooRealVar*)((RooArgList*)observables)->at(j);
						corSystMatrix[i][j] = mySystCor.getCor(obsTmkToMalcolm(tmkObs1->GetName()), obsTmkToMalcolm(tmkObs2->GetName()));
					}
				fr->Close();
				delete r;
				delete fr;
				break;
			}
		default:
			cout << "PDF_GLWADS_DKDpi_hh::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLWADS_DKDpi_hh::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
	TIterator* it = theory->createIterator();
}
