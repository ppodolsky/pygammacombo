/**
 * Gamma Combination
 * Author: Matthew Kenzie matthew.kenzie@cern.ch
 * Date: October 2015
 *
 **/

#include "PDF_GGSZ_DKst.h"

	PDF_GGSZ_DKst::PDF_GGSZ_DKst(config cObs, config cErr, config cCor, ParametersAbs* pars)
: PDF_Abs(4)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	name = "ggsz_dkst";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}

PDF_GGSZ_DKst::~PDF_GGSZ_DKst(){}


void PDF_GGSZ_DKst::initParameters()
{
	parameters = new RooArgList("parameters");
	parameters->add(*(p->get("r_dkst")));
	parameters->add(*(p->get("d_dkst")));
	parameters->add(*(p->get("g")));
}


void PDF_GGSZ_DKst::initRelations()
{
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	RooArgSet *p = (RooArgSet*)parameters;
	theory->add(*(new RooFormulaVar("xm_dkst_th", "x- (DK*)", "r_dkst*cos(d_dkst-g)", *p)));
	theory->add(*(new RooFormulaVar("ym_dkst_th", "y- (DK*)", "r_dkst*sin(d_dkst-g)", *p)));
	theory->add(*(new RooFormulaVar("xp_dkst_th", "x+ (DK*)", "r_dkst*cos(d_dkst+g)", *p)));
	theory->add(*(new RooFormulaVar("yp_dkst_th", "y+ (DK*)", "r_dkst*sin(d_dkst+g)", *p)));
}


void PDF_GGSZ_DKst::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("xm_dkst_obs", "x- (DK* GGSZ) obs", 0, -1, 1)));
	observables->add(*(new RooRealVar("ym_dkst_obs", "y- (DK* GGSZ) obs", 0, -1, 1)));
	observables->add(*(new RooRealVar("xp_dkst_obs", "x+ (DK* GGSZ) obs", 0, -1, 1)));
	observables->add(*(new RooRealVar("yp_dkst_obs", "y+ (DK* GGSZ) obs", 0, -1, 1)));
}


void PDF_GGSZ_DKst::setObservables(config c)
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
							  setObservable("xm_dkst_obs", 0.075);
							  setObservable("ym_dkst_obs", 0.127);
							  setObservable("xp_dkst_obs",-0.151);
							  setObservable("yp_dkst_obs", 0.045);
							  break;
						  }
		case belle:{
							  obsValSource = "PRD 73 (2006) 112009";
							  setObservable("xm_dkst_obs",-0.784);
							  setObservable("ym_dkst_obs",-0.281);
							  setObservable("xp_dkst_obs",-0.105);
							  setObservable("yp_dkst_obs",-0.004);
							  break;
						  }
		default:{
					cout << "PDF_GGSZ_DKst::setObservables() : ERROR : config not found: " << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}


void PDF_GGSZ_DKst::setUncertainties(config c)
{
	switch(c)
	{
		// for HFAG average
    case babar:{
							  obsErrSource = "PRL 105 (2010) 121801";
							  StatErr[0] = 0.096; // xm
							  StatErr[1] = 0.095; // ym
							  StatErr[2] = 0.083; // xp
							  StatErr[3] = 0.106; // yp
							  SystErr[0] = sqrt(sq(0.029)+sq(0.007)); // xm
							  SystErr[1] = sqrt(sq(0.027)+sq(0.006)); // ym
							  SystErr[2] = sqrt(sq(0.029)+sq(0.006)); // xp
							  SystErr[3] = sqrt(sq(0.036)+sq(0.008)); // yp
							  break;
						  }
    case belle:{
							  obsErrSource = "PRD 73 (2006) 112009";
							  StatErr[0] = 0.272; // xm
							  StatErr[1] = 0.3375; // ym
							  StatErr[2] = 0.172; // xp
							  StatErr[3] = 0.160; // yp
							  SystErr[0] = sqrt(sq(0.029)+sq(0.097)); // xm
							  SystErr[1] = sqrt(sq(0.046)+sq(0.086)); // ym
							  SystErr[2] = sqrt(sq(0.006)+sq(0.088)); // xp
							  SystErr[3] = sqrt(sq(0.013)+sq(0.095)); // yp
							  break;
						  }
		default:{
					cout << "PDF_GGSZ_DKst::setUncertainties() : ERROR : config not found: " << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}


void PDF_GGSZ_DKst::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		// for HFAG average
    case babar:{
							  corSource = "HFAG";
							  // no syst correlation avaialble
                //                     xm      ym      xp      yp
							  double dataStat[]  = { 1.   , -0.200,  0.000,  0.000,		// xm
                                      -0.200,  1.   ,  0.000,  0.000,		// ym
                                       0.000,  0.000,  1.   ,  0.100,		// xp
                                       0.000,  0.000,  0.100,  1.     };// yp
							  corStatMatrix = TMatrixDSym(nObs,dataStat);
                //                     xm      ym      xp      yp
							  double dataSyst[]  = { 1.   ,  0.630,  0.730,  0.660,		// xm
                                       0.630,  1.   ,  0.650,  0.970,		// ym
                                       0.730,  0.650,  1.   ,  0.740,		// xp
                                       0.660,  0.970,  0.740,  1.     };// yp
							  corSystMatrix = TMatrixDSym(nObs,dataSyst);
							  break;
						  }
    case belle:{
							  corSource = "HFAG";
							  // no syst correlation avaialble
                //                     xm      ym      xp      yp
							  double dataStat[]  = { 1.   , -0.338,  0.000,  0.000,		// xm
                                      -0.338,  1.   ,  0.000,  0.000,		// ym
                                       0.000,  0.000,  1.   , -0.201,		// xp
                                       0.000,  0.000, -0.201,  1.     };// yp
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
					cout << "PDF_GGSZ_DKst::setCorrelations() : ERROR : config not found: " << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}


void PDF_GGSZ_DKst::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
