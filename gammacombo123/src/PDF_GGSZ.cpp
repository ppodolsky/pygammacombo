/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#include "PDF_GGSZ.h"

	PDF_GGSZ::PDF_GGSZ(config cObs, config cErr, config cCor, ParametersAbs* pars)
: PDF_Abs(4)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	name = "ggsz";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}

PDF_GGSZ::~PDF_GGSZ(){}


void PDF_GGSZ::initParameters()
{
	parameters = new RooArgList("parameters");
	parameters->add(*(p->get("r_dk")));
	parameters->add(*(p->get("d_dk")));
	parameters->add(*(p->get("g")));
}


void PDF_GGSZ::initRelations()
{
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	RooArgSet *p = (RooArgSet*)parameters;
	theory->add(*(new RooFormulaVar("xm_dk_th", "x- (DK)", "r_dk*cos(d_dk-g)", *p)));
	theory->add(*(new RooFormulaVar("ym_dk_th", "y- (DK)", "r_dk*sin(d_dk-g)", *p)));
	theory->add(*(new RooFormulaVar("xp_dk_th", "x+ (DK)", "r_dk*cos(d_dk+g)", *p)));
	theory->add(*(new RooFormulaVar("yp_dk_th", "y+ (DK)", "r_dk*sin(d_dk+g)", *p)));
}


void PDF_GGSZ::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("xm_dk_obs", "x- (DK GGSZ) obs", 0, -1, 1)));
	observables->add(*(new RooRealVar("ym_dk_obs", "y- (DK GGSZ) obs", 0, -1, 1)));
	observables->add(*(new RooRealVar("xp_dk_obs", "x+ (DK GGSZ) obs", 0, -1, 1)));
	observables->add(*(new RooRealVar("yp_dk_obs", "y+ (DK GGSZ) obs", 0, -1, 1)));
}


void PDF_GGSZ::setObservables(config c)
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
		case lumi3fbDKstz:{
						 obsValSource = "Alexis' estimate";
						 setObservable("xm_dk_obs", -0.0076);
						 setObservable("ym_dk_obs", -0.22);
						 setObservable("xp_dk_obs",0.14);
						 setObservable("yp_dk_obs",0.17);
						 break;
					 }
		case lumi1fb:{
						 obsValSource = "1fb-1 LHCb-PAPER-2012-027";
						 setObservable("xm_dk_obs", 0.000);
						 setObservable("ym_dk_obs", 0.027);
						 setObservable("xp_dk_obs",-0.103);
						 setObservable("yp_dk_obs",-0.009);
						 break;
					 }
		case lumi2fb:{
						 obsValSource = "2fb-1 LHCb-CONF-2013-XXX";
						 setObservable("xm_dk_obs", 5.3e-2);
						 setObservable("ym_dk_obs", 9.9e-2);
						 setObservable("xp_dk_obs",-8.7e-2);
						 setObservable("yp_dk_obs", 0.1e-2);
						 break;
					 }
		case lumi3fb:{
						 obsValSource = "3fb-1 LHCb-CONF-2013-004 v0.2 (combined cart. coord.)";
						 setObservable("xm_dk_obs", 3.46e-2);
						 setObservable("ym_dk_obs", 7.91e-2);
						 setObservable("xp_dk_obs",-8.85e-2);
						 setObservable("yp_dk_obs",-0.12e-2);
						 break;
					 }
		case lumi3fbPaper:{
							  obsValSource = "3fb-1 LHCb-ANA-2014-040 June 11 Sect 11";
							  setObservable("xm_dk_obs", 2.5e-2);
							  setObservable("ym_dk_obs", 7.5e-2);
							  setObservable("xp_dk_obs",-7.7e-2);
							  setObservable("yp_dk_obs",-2.2e-2);
							  break;
						  }
		case highrb:{
						obsValSource = "values corresponding to rB=0.3, g=70, dB=114";
						setObservable("xm_dk_obs", 0.21364);
						setObservable("ym_dk_obs", 0.21061);
						setObservable("xp_dk_obs",-0.29904);
						setObservable("yp_dk_obs",-0.02402);
						break;
					}
		default:{
					cout << "PDF_GGSZ::setObservables() : ERROR : config not found: " << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}


void PDF_GGSZ::setUncertainties(config c)
{
	switch(c)
	{
		case lumi3fbDKstz:{
						 obsErrSource = "Alexis' estimate";
						 StatErr[0] = 0.15; // xm
						 StatErr[1] = 0.2; // ym
						 StatErr[2] = 0.15; // xp
						 StatErr[3] = 0.2; // yp
						 SystErr[0] = 0.0;
						 SystErr[1] = 0.0;
						 SystErr[2] = 0.0;
						 SystErr[3] = 0.0;
						 break;
						  }
		case lumi1fb:{
						 obsErrSource = "1fb-1 LHCb-PAPER-2012-027";
						 StatErr[0] = 0.043; // xm
						 StatErr[1] = 0.052; // ym
						 StatErr[2] = 0.045; // xp
						 StatErr[3] = 0.037; // yp
						 SystErr[0] = sqrt(sq(0.015)+sq(0.006)); // xm
						 SystErr[1] = sqrt(sq(0.008)+sq(0.023)); // ym
						 SystErr[2] = sqrt(sq(0.018)+sq(0.014)); // xp
						 SystErr[3] = sqrt(sq(0.008)+sq(0.030)); // yp
						 break;
					 }
		case lumi2fb:{
						 obsErrSource = "2fb-1 LHCb-CONF-2013-XXX";
						 StatErr[0] = 0.032; // xm
						 StatErr[1] = 0.036; // ym
						 StatErr[2] = 0.031; // xp
						 StatErr[3] = 0.037; // yp
						 SystErr[0] = sqrt(sq(0.012)+sq(0.009)); // xm
						 SystErr[1] = sqrt(sq(0.022)+sq(0.016)); // ym
						 SystErr[2] = sqrt(sq(0.017)+sq(0.006)); // xp
						 SystErr[3] = sqrt(sq(0.023)+sq(0.019)); // yp
						 break;
					 }
		case lumi3fb:{
						 obsErrSource = "3fb-1 LHCb-CONF-2013-004 v0.2 (combined cart. coord.)";
						 StatErr[0] = 2.89e-2/5; // xm
						 StatErr[1] = 3.83e-2; // ym
						 StatErr[2] = 3.12e-2; // xp
						 StatErr[3] = 3.65e-2; // yp
						 // a quick test of by how much we are limited by model errors: model errors only
						 // StatErr[0] = 0.9e-2; // xm
						 // StatErr[1] = 1.6e-2; // ym
						 // StatErr[2] = 0.6e-2; // xp
						 // StatErr[3] = 1.9e-2; // yp
						 SystErr[0] = 0.0; // xm
						 SystErr[1] = 0.0; // ym
						 SystErr[2] = 0.0; // xp
						 SystErr[3] = 0.0; // yp
						 break;
					 }
		case lumi3fbPaper:{
							  obsErrSource = "3fb-1 LHCb-ANA-2014-040 June 11 Sect 11";
							  StatErr[0] = 0.025; // xm
							  StatErr[1] = 0.029; // ym
							  StatErr[2] = 0.024; // xp
							  StatErr[3] = 0.025; // yp
							  SystErr[0] = sqrt(sq(0.010)+sq(0.005)); // xm
							  SystErr[1] = sqrt(sq(0.005)+sq(0.014)); // ym
							  SystErr[2] = sqrt(sq(0.010)+sq(0.004)); // xp
							  SystErr[3] = sqrt(sq(0.004)+sq(0.010)); // yp
							  break;
						  }
		case lumi9fb:{
						 setUncertainties(lumi3fbPaper);
						 obsErrSource = "9fb-1 errors obtained from scaling down the 3fb-1 errors (lumi3fbPaper)";
						 for ( int i=0; i<nObs; i++ ){
							 StatErr[i] /= (sqrt(2.7));
							 SystErr[i] /= (sqrt(2.7));
						 }
						 break;
					 }
		default:{
					cout << "PDF_GGSZ::setUncertainties() : ERROR : config not found: " << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}


void PDF_GGSZ::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi1fb:{
						 corSource = "1fb-1 LHCb-PAPER-2012-027";
						 corStatMatrix[1][0] = -0.11; // ym, xm
						 corStatMatrix[2][0] =  0.;   // xp, xm
						 corStatMatrix[2][1] =  0.;   // xp, ym
						 corStatMatrix[3][0] =  0.;   // yp, xm
						 corStatMatrix[3][1] =  0.;   // yp, ym
						 corStatMatrix[3][2] =  0.17; // yp, xp

						 corSystMatrix[1][0] = -0.05; // ym, xm
						 corSystMatrix[2][0] =  0.;   // xp, xm
						 corSystMatrix[2][1] =  0.;   // xp, ym
						 corSystMatrix[3][0] =  0.;   // yp, xm
						 corSystMatrix[3][1] =  0.;   // yp, ym
						 corSystMatrix[3][2] = +0.36; // yp, xp
						 break;
					 }
		case lumi2fb:{
						 corSource = "1fb-1 LHCb-PAPER-2012-027";
						 corStatMatrix[1][0] = -0.11; // ym, xm
						 corStatMatrix[2][0] =  0.;   // xp, xm
						 corStatMatrix[2][1] =  0.;   // xp, ym
						 corStatMatrix[3][0] =  0.;   // yp, xm
						 corStatMatrix[3][1] =  0.;   // yp, ym
						 corStatMatrix[3][2] =  0.17; // yp, xp

						 corSystMatrix[1][0] = -0.05; // ym, xm
						 corSystMatrix[2][0] =  0.;   // xp, xm
						 corSystMatrix[2][1] =  0.;   // xp, ym
						 corSystMatrix[3][0] =  0.;   // yp, xm
						 corSystMatrix[3][1] =  0.;   // yp, ym
						 corSystMatrix[3][2] = +0.36; // yp, xp
						 break;
					 }
		case lumi3fb:{
						 corSource = "3fb-1 LHCb-CONF-2013-004 v0.2 (combined cart. coord.)";
						 corStatMatrix[1][0] = -0.053; // ym, xm
						 corStatMatrix[2][0] = -0.136; // xp, xm
						 corStatMatrix[2][1] = -0.186; // xp, ym
						 corStatMatrix[3][0] = -0.031; // yp, xm
						 corStatMatrix[3][1] = -0.074; // yp, ym
						 corStatMatrix[3][2] =  0.106; // yp, xp

						 corSystMatrix[1][0] =  0.; // ym, xm
						 corSystMatrix[2][0] =  0.; // xp, xm
						 corSystMatrix[2][1] =  0.; // xp, ym
						 corSystMatrix[3][0] =  0.; // yp, xm
						 corSystMatrix[3][1] =  0.; // yp, ym
						 corSystMatrix[3][2] =  0.; // yp, xp
						 break;
					 }
		case lumi3fbPaper:{
							  corSource = "OtherFiles/compute3fbGGSZcorrelations.py with inputs from LHCb-ANA-2014-040-v7 as of 26.6.2014";
							  //                     xm      ym      xp      yp
							  double dataStat[]  = { 1.   , -0.247,  0.038, -0.003,		// xm
								  -0.247,  1.   , -0.011,  0.012,		// ym
								  0.038, -0.011,  1.   ,  0.002,		// xp
								  -0.003,  0.012,  0.002,  1.     };// yp
							  corStatMatrix = TMatrixDSym(nObs,dataStat);
							  //                     xm      ym      xp      yp
							  double dataSyst[]  = { 1.   ,  0.005, -0.025,  0.070,   // xm
								  0.005,  1.   ,  0.009, -0.141,   // ym
								  -0.025,  0.009,  1.   ,  0.008,   // xp
								  0.070, -0.141,  0.008,  1.     };// yp
							  corSystMatrix = TMatrixDSym(nObs,dataSyst);
							  break;
						  }
		case lumi3fbDKstz:{
							  corSource = "estimate";
							  //                     xm      ym      xp      yp
							  double dataStat[]  = { 1.   , -0.247,  0.038, -0.003,		// xm
								  -0.247,  1.   , -0.011,  0.012,		// ym
								  0.038, -0.011,  1.   ,  0.002,		// xp
								  -0.003,  0.012,  0.002,  1.     };// yp
							  corStatMatrix = TMatrixDSym(nObs,dataStat);
							  //                     xm      ym      xp      yp
							  double dataSyst[]  = { 1.   ,  0.005, -0.025,  0.070,   // xm
								  0.005,  1.   ,  0.009, -0.141,   // ym
								  -0.025,  0.009,  1.   ,  0.008,   // xp
								  0.070, -0.141,  0.008,  1.     };// yp
							  corSystMatrix = TMatrixDSym(nObs,dataSyst);
							  break;
						  }
		default:{
					cout << "PDF_GGSZ::setCorrelations() : ERROR : config not found: " << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}


void PDF_GGSZ::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
