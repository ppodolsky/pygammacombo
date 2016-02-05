/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#include "PDF_GLWADS_DKDpi_K3pi.h"

	PDF_GLWADS_DKDpi_K3pi::PDF_GLWADS_DKDpi_K3pi(config cObs, config cErr, config cCor, ParametersAbs* pars, TString d)
: PDF_Abs(7)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	name = "glwads-dkdpi-k3pi";
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

	PDF_GLWADS_DKDpi_K3pi::PDF_GLWADS_DKDpi_K3pi(ParametersAbs* pars, TString d, int nObs)
: PDF_Abs(nObs)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	this->dir = d;
}


PDF_GLWADS_DKDpi_K3pi::~PDF_GLWADS_DKDpi_K3pi(){}


void PDF_GLWADS_DKDpi_K3pi::initParameters()
{
	parameters = new RooArgList("parameters");
	parameters->add(*(p->get("r_dk")));
	parameters->add(*(p->get("d_dk")));
	parameters->add(*(p->get("r_dpi")));
	parameters->add(*(p->get("d_dpi")));
	parameters->add(*(p->get("g")));
	parameters->add(*(p->get("rD_k3pi")));
	parameters->add(*(p->get("dD_k3pi")));
	parameters->add(*(p->get("kD_k3pi")));
	parameters->add(*(p->get("RBRdkdpi")));
}


void PDF_GLWADS_DKDpi_K3pi::initRelations()
{
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	RooArgSet *p = (RooArgSet*)parameters;
	theory->add(*(new RooFormulaVar("rkp_k3pi_th",      "rkp_k3pi_th",      "RBRdkdpi*(1 + r_dk^2 * rD_k3pi^2 + 2*r_dk*rD_k3pi*kD_k3pi*cos(g)*cos(d_dk-dD_k3pi))/(1 + r_dpi^2 * rD_k3pi^2 + 2*r_dpi*rD_k3pi*kD_k3pi*cos(g)*cos(d_dpi-dD_k3pi))", *p)));
	theory->add(*(new RooFormulaVar("afav_dk_k3pi_th",  "afav_dk_k3pi_th",  "2*r_dk *rD_k3pi*kD_k3pi*sin(g)*sin(d_dk -dD_k3pi) / (1 + r_dk^2  * rD_k3pi^2 + 2*r_dk *rD_k3pi*kD_k3pi*cos(g)*cos(d_dk -dD_k3pi))", *p)));
	theory->add(*(new RooFormulaVar("afav_dpi_k3pi_th", "afav_dpi_k3pi_th", "2*r_dpi*rD_k3pi*kD_k3pi*sin(g)*sin(d_dpi-dD_k3pi) / (1 + r_dpi^2 * rD_k3pi^2 + 2*r_dpi*rD_k3pi*kD_k3pi*cos(g)*cos(d_dpi-dD_k3pi))", *p)));
	theory->add(*(new RooFormulaVar("rp_dk_k3pi_th",    "rp_dk_k3pi_th",    "r_dk^2  + rD_k3pi^2 + 2*r_dk *rD_k3pi*kD_k3pi*cos( g+d_dk +dD_k3pi)", *p)));
	theory->add(*(new RooFormulaVar("rm_dk_k3pi_th",    "rm_dk_k3pi_th",    "r_dk^2  + rD_k3pi^2 + 2*r_dk *rD_k3pi*kD_k3pi*cos(-g+d_dk +dD_k3pi)", *p)));
	theory->add(*(new RooFormulaVar("rp_dpi_k3pi_th",   "rp_dpi_k3pi_th",   "r_dpi^2 + rD_k3pi^2 + 2*r_dpi*rD_k3pi*kD_k3pi*cos( g+d_dpi+dD_k3pi)", *p)));
	theory->add(*(new RooFormulaVar("rm_dpi_k3pi_th",   "rm_dpi_k3pi_th",   "r_dpi^2 + rD_k3pi^2 + 2*r_dpi*rD_k3pi*kD_k3pi*cos(-g+d_dpi+dD_k3pi)", *p)));
}

///
/// TMK names are used in the GammaCombo code.
/// Malcolm names are used in GammaDini and the GLW/ADS RooFitResults.
///
TString PDF_GLWADS_DKDpi_K3pi::obsTmkToMalcolm(TString tmkObs)
{
	if ( tmkObs=="rkp_k3pi_obs"      ) return "R_dk_vs_dpi"            ;
	if ( tmkObs=="afav_dk_k3pi_obs"  ) return "A_FAV_b2dk_d2kpipipi"   ;
	if ( tmkObs=="afav_dpi_k3pi_obs" ) return "A_FAV_b2dpi_d2kpipipi"  ;
	if ( tmkObs=="rp_dk_k3pi_obs"    ) return "R_plus_b2dk_d2pikpipi"  ;
	if ( tmkObs=="rm_dk_k3pi_obs"    ) return "R_minus_b2dk_d2pikpipi" ;
	if ( tmkObs=="rp_dpi_k3pi_obs"   ) return "R_plus_b2dpi_d2pikpipi" ;
	if ( tmkObs=="rm_dpi_k3pi_obs"   ) return "R_minus_b2dpi_d2pikpipi";
	assert(0);
}


void PDF_GLWADS_DKDpi_K3pi::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("rkp_k3pi_obs",      "R_{K/#pi} (K3#pi)"  , 1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("afav_dk_k3pi_obs",  "Afav (DK K3#pi)"    , 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("afav_dpi_k3pi_obs", "Afav (D#pi K3#pi)"  , 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rp_dk_k3pi_obs",    "R+ (DK K3#pi ADS)"  , 1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rm_dk_k3pi_obs",    "R- (DK K3#pi ADS)"  , 1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rp_dpi_k3pi_obs",   "R+ (D#pi K3#pi ADS)", 1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rm_dpi_k3pi_obs",   "R- (D#pi K3#pi ADS)", 1, -1e4, 1e4)));
}


void PDF_GLWADS_DKDpi_K3pi::setObservables(config c)
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
						 obsValSource = "1fb-1, ExpNll/sept2012K3PIResult.root";
						 TString File = this->dir+"/ExpNll/sept2012K3PIResult.root";
						 TFile *fr = TFile::Open(File);
						 RooFitResult *r = (RooFitResult*)fr->Get("fitresult_model_reducedData_binned");
						 assert(r);
						 TIterator* it = observables->createIterator();
						 while ( RooRealVar* pObs = (RooRealVar*)it->Next() )
						 {
							 RooRealVar* pRes = (RooRealVar*)r->floatParsFinal().find(obsTmkToMalcolm(pObs->GetName()));
							 pObs->setVal(pRes->getVal());
						 }
						 fr->Close();
						 delete r;
						 delete fr;
						 break;
					 }
		case lumi3fb:{
						 obsValSource = "3fb-1 ANA v7 unblind"; // https://twiki.cern.ch/twiki/pub/LHCbPhysics/B2D0K/LHCb-ANA-2014-071-v7.pdf (see Vavas email 04/08/15)

						 // these get transformed over from the new inputs using ExpNll/transportGLWADS_new_to_old.py
						 // in the case of the DK only (robust) combination some of the observables don't exist
						 // usemap as the temp store
						 std::map< TString, double > vals;
						 vals["rkp_k3pi_obs"]      =  0.0793;
						 vals["afav_dk_k3pi_obs"]  =  -0.0004;
						 vals["afav_dpi_k3pi_obs"] =  0.0;
						 vals["rp_dk_k3pi_obs"]    =  0.018369;
						 vals["rm_dk_k3pi_obs"]    =  0.009611;
						 vals["rp_dpi_k3pi_obs"]   =  0.003683;
						 vals["rm_dpi_k3pi_obs"]   =  0.003857;

						 // now can loop the observables and set the values
						 TIterator* it = observables->createIterator();
						 while ( RooRealVar* pObs = (RooRealVar*)it->Next() ){
							 pObs->setVal(vals[pObs->GetName()]);
						 }

						 vals.clear();
						 break;
				}
		default:{
					cout << "PDF_GLWADS_DKDpi_K3pi::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_GLWADS_DKDpi_K3pi::setUncertainties(config c)
{
	switch(c)
	{
		case lumi1fb:{
						 obsErrSource = "1fb-1, ExpNll/sept2012K3PIResult.root";
						 TString File = this->dir+"/ExpNll/sept2012K3PIResult.root";
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
						 SystErr[0] = 0.0026;  // rkp_k3pi_obs
						 SystErr[1] = 0.018;   // afav_dk_obs
						 SystErr[2] = 0.010;   // afav_dpi_obs
						 SystErr[3] = 0.0010;  // rp_dk_obs
						 SystErr[4] = 0.0008;  // rm_dk_obs
						 SystErr[5] = 0.00011; // rp_dpi_obs
						 SystErr[6] = 0.00011; // rm_dpi_obs
						 fr->Close();
						 delete r;
						 delete fr;
						 break;
					 }
		case lumi3fb:{
						 obsErrSource = "3fb-1 ANA v7 unblind"; // https://twiki.cern.ch/twiki/pub/LHCbPhysics/B2D0K/LHCb-ANA-2014-071-v7.pdf (see Vavas email 04/08/15)

						 // these get transformed over from the new inputs using ExpNll/transportGLWADS_new_to_old.py
						 // in the case of the DK only (robust) combination some of the observables don't exist
						 // usemap as the temp store
						 std::map< TString, double > stat_errs;
						 stat_errs["rkp_k3pi_obs"]      =  0.0010;  // rkp_k3pi_obs
						 stat_errs["afav_dk_k3pi_obs"]  =  0.0119;    // afav_dk_obs
						 stat_errs["afav_dpi_k3pi_obs"] =  0.1;   // afav_dpi_obs // now Aprod, large error to disable it
						 stat_errs["rp_dk_k3pi_obs"]    =  0.002421;  // rp_dk_obs
						 stat_errs["rm_dk_k3pi_obs"]    =  0.001756;  // rm_dk_obs
						 stat_errs["rp_dpi_k3pi_obs"]   =  0.000252; // rp_dpi_obs
						 stat_errs["rm_dpi_k3pi_obs"]   =  0.000258; // rm_dpi_obs

						 for ( int i=0; i<nObs; i++ )
						 {
							 RooRealVar* pObs = (RooRealVar*)((RooArgList*)observables)->at(i);
							 StatErr[i] = stat_errs[pObs->GetName()];
						 }
						 stat_errs.clear();

						 std::map< TString, double > syst_errs;
						 syst_errs["rkp_k3pi_obs"]      = 0.0170;   // rkp_k3pi_obs
						 syst_errs["afav_dk_k3pi_obs"]  = 0.0019;     // afav_dk_obs
						 syst_errs["afav_dpi_k3pi_obs"] = 0.1;   //  afav_dpi_obs // now Aprod, large error to disable it
						 syst_errs["rp_dk_k3pi_obs"]    = 0.000950;   // rp_dk_obs
						 syst_errs["rm_dk_k3pi_obs"]    = 0.000673;   // rm_dk_obs
						 syst_errs["rp_dpi_k3pi_obs"]   = 0.000061;  // rp_dpi_obs
						 syst_errs["rm_dpi_k3pi_obs"]   = 0.000064;  // rm_dpi_obs

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
							 StatErr[i] /= (sqrt(2.7));
							 SystErr[i] /= (sqrt(2.7));
						 }
						 break;
					 }
		default:{
					cout << "PDF_GLWADS_DKDpi_K3pi::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_GLWADS_DKDpi_K3pi::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi1fb:{
						 corSource = "1fb-1, ExpNll/sept2012K3PIResult.root";
						 TString File = this->dir+"/ExpNll/sept2012K3PIResult.root";
						 if ( !FileExists(File) ){cout << "PDF_GLWADS_DKDpi_K3pi::setCorrelations : ERROR : File not found : " << File << endl; exit(1);}
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
		case lumi1fbSystCor:{
								corSource = "1fb-1, ExpNll/sept2012K3PIResult.root, Malcolm's toys";
								TString File = this->dir+"/ExpNll/sept2012K3PIResult.root";
								if ( !FileExists(File) ){cout << "PDF_GLWADS_DKDpi_K3pi::setCorrelations : ERROR : File not found : " << File << endl; exit(1);}
								TFile *fr = TFile::Open(File);
								RooFitResult *r = (RooFitResult*)fr->Get("fitresult_model_reducedData_binned");
								assert(r);
								for ( int i=0; i<nObs; i++ )
									for ( int j=0; j<nObs; j++ ){
										RooRealVar* pObs1 = (RooRealVar*)((RooArgList*)observables)->at(i);
										RooRealVar* pObs2 = (RooRealVar*)((RooArgList*)observables)->at(j);
										corStatMatrix[i][j] = r->correlation(obsTmkToMalcolm(pObs1->GetName()),obsTmkToMalcolm(pObs2->GetName()));
									}
								// systematics correlations
								SystCor_K3pi mySystCor;
								for ( int i=0; i<nObs; i++ )
									for ( int j=0; j<nObs; j++ ){
										RooRealVar* tmkObs1 = (RooRealVar*)((RooArgList*)observables)->at(i);
										RooRealVar* tmkObs2 = (RooRealVar*)((RooArgList*)observables)->at(j);
										corSystMatrix[i][j] = mySystCor.getCor(obsTmkToMalcolm(tmkObs1->GetName()), obsTmkToMalcolm(tmkObs2->GetName()));
									}
								fr->Close();
								delete r;
								delete fr;
								break;
							}
		case zero:{
					  corSource = "zero";
					  break;
				  }
		default:{
					cout << "PDF_GLWADS_DKDpi_K3pi::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_GLWADS_DKDpi_K3pi::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
