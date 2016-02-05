/**
 * Gamma Combination
 * Author: Matthew Kenzie matthew.kenzie@cern.ch
 * Date: October 2015
 *
 **/

#include "PDF_GGSZ_DstK.h"

	PDF_GGSZ_DstK::PDF_GGSZ_DstK(config cObs, config cErr, config cCor, ParametersAbs* pars)
: PDF_Abs(4)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	name = "ggsz_dstk";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}

PDF_GGSZ_DstK::~PDF_GGSZ_DstK(){}


void PDF_GGSZ_DstK::initParameters()
{
	parameters = new RooArgList("parameters");
	parameters->add(*(p->get("r_dstk")));
	parameters->add(*(p->get("d_dstk")));
	parameters->add(*(p->get("g")));
}


void PDF_GGSZ_DstK::initRelations()
{
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	RooArgSet *p = (RooArgSet*)parameters;
	theory->add(*(new RooFormulaVar("xm_dstk_th", "x- (D*K)", "r_dstk*cos(d_dstk-g)", *p)));
	theory->add(*(new RooFormulaVar("ym_dstk_th", "y- (D*K)", "r_dstk*sin(d_dstk-g)", *p)));
	theory->add(*(new RooFormulaVar("xp_dstk_th", "x+ (D*K)", "r_dstk*cos(d_dstk+g)", *p)));
	theory->add(*(new RooFormulaVar("yp_dstk_th", "y+ (D*K)", "r_dstk*sin(d_dstk+g)", *p)));
}


void PDF_GGSZ_DstK::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("xm_dstk_obs", "x- (D*K GGSZ) obs", 0, -1, 1)));
	observables->add(*(new RooRealVar("ym_dstk_obs", "y- (D*K GGSZ) obs", 0, -1, 1)));
	observables->add(*(new RooRealVar("xp_dstk_obs", "x+ (D*K GGSZ) obs", 0, -1, 1)));
	observables->add(*(new RooRealVar("yp_dstk_obs", "y+ (D*K GGSZ) obs", 0, -1, 1)));
}


void PDF_GGSZ_DstK::setObservables(config c)
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
    // for HFAG average
		case babar:{
							  obsValSource = "PRL 105 (2010) 121801";
							  setObservable("xm_dstk_obs",-0.104);
							  setObservable("ym_dstk_obs",-0.052);
							  setObservable("xp_dstk_obs", 0.147);
							  setObservable("yp_dstk_obs",-0.032);
							  break;
						  }
		case belle:{
							  obsValSource = "PRD 81 (2010) 112002";
							  setObservable("xm_dstk_obs",-0.036);
							  setObservable("ym_dstk_obs",-0.249);
							  setObservable("xp_dstk_obs", 0.083);
							  setObservable("yp_dstk_obs", 0.157);
							  break;
						  }
		default:{
					cout << "PDF_GGSZ_DstK::setObservables() : ERROR : config not found: " << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}


void PDF_GGSZ_DstK::setUncertainties(config c)
{
	switch(c)
	{
		// for HFAG average
    case babar:{
							  obsErrSource = "PRL 105 (2010) 121801";
							  StatErr[0] = 0.051; // xm
							  StatErr[1] = 0.063; // ym
							  StatErr[2] = 0.053; // xp
							  StatErr[3] = 0.077; // yp
							  SystErr[0] = sqrt(sq(0.019)+sq(0.002)); // xm
							  SystErr[1] = sqrt(sq(0.009)+sq(0.007)); // ym
							  SystErr[2] = sqrt(sq(0.017)+sq(0.003)); // xp
							  SystErr[3] = sqrt(sq(0.008)+sq(0.006)); // yp
							  break;
						  }
    case belle:{
							  obsErrSource = "PRD 81 (2010) 112002";
							  StatErr[0] = 0.127; // xm
							  StatErr[1] = 0.118; // ym
							  StatErr[2] = 0.092; // xp
							  StatErr[3] = 0.109; // yp
							  SystErr[0] = 0.090; // xm
							  SystErr[1] = 0.049; // ym
							  SystErr[2] = 0.081; // xp
							  SystErr[3] = 0.063; // yp
							  break;
						  }
		default:{
					cout << "PDF_GGSZ_DstK::setUncertainties() : ERROR : config not found: " << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}


void PDF_GGSZ_DstK::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		// for HFAG average
    case babar:{
							  corSource = "HFAG";
							  // no syst correlation avaialble
                //                     xm      ym      xp      yp
							  double dataStat[]  = { 1.   , -0.010,  0.000,  0.000,		// xm
                                      -0.010,  1.   ,  0.000,  0.000,		// ym
                                       0.000,  0.000,  1.   , -0.030,		// xp
                                       0.000,  0.000, -0.030,  1.     };// yp
							  corStatMatrix = TMatrixDSym(nObs,dataStat);
							  //                     xm      ym      xp      yp
							  double dataSyst[]  = { 1.   , -0.020,  0.440, -0.500,		// xm
                                      -0.020,  1.   , -0.600,  0.190,		// ym
                                       0.440, -0.600,  1.   , -0.440,		// xp
                                      -0.500,  0.190, -0.440,  1.     };// yp
							  corSystMatrix = TMatrixDSym(nObs,dataSyst);
							  break;
						  }
    case belle:{
							  corSource = "HFAG";
							  // no syst correlation avaialble
                //                     xm      ym      xp      yp
							  double dataStat[]  = { 1.   ,  0.161,  0.000,  0.000,		// xm
                                       0.161,  1.   ,  0.000,  0.000,		// ym
                                       0.000,  0.000,  1.   , -0.010,		// xp
                                       0.000,  0.000, -0.010,  1.     };// yp
							  corStatMatrix = TMatrixDSym(nObs,dataStat);
							  //                     xm      ym      xp      yp
							  double dataSyst[]  = { 1. ,  0.0,  0.0,  0.0,   // xm
                                       0.0,  1. ,  0.0,  0.0,   // ym
                                       0.0,  0.0,  1. ,  0.0,   // xp
                                       0.0,  0.0,  0.0,  1.   };// yp
							  corSystMatrix = TMatrixDSym(nObs,dataSyst);
							  break;
						  }
		default:{
					cout << "PDF_GGSZ_DstK::setCorrelations() : ERROR : config not found: " << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}


void PDF_GGSZ_DstK::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
