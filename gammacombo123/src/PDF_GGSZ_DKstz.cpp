/**
 * Gamma Combination
 * Author: M. Kenzie and A. Vallier (matthew.kenzie@cern.ch, avallier@cern.ch)
 * Date: June 2015
 *
 **/

#include "PDF_GGSZ_DKstz.h"

	PDF_GGSZ_DKstz::PDF_GGSZ_DKstz(config cObs, config cErr, config cCor, ParametersAbs* pars)
: PDF_Abs(4)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	name = "ggsz_dkstz";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}

PDF_GGSZ_DKstz::~PDF_GGSZ_DKstz(){}


void PDF_GGSZ_DKstz::initParameters()
{
	parameters = new RooArgList("parameters");
	parameters->add(*(p->get("r_dkstz")));
	parameters->add(*(p->get("d_dkstz")));
	parameters->add(*(p->get("g")));
}


void PDF_GGSZ_DKstz::initRelations()
{
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	RooArgSet *p = (RooArgSet*)parameters;
	theory->add(*(new RooFormulaVar("xm_dkstz_th", "x- (DK*)", "r_dkstz*cos(d_dkstz-g)", *p)));
	theory->add(*(new RooFormulaVar("ym_dkstz_th", "y- (DK*)", "r_dkstz*sin(d_dkstz-g)", *p)));
	theory->add(*(new RooFormulaVar("xp_dkstz_th", "x+ (DK*)", "r_dkstz*cos(d_dkstz+g)", *p)));
	theory->add(*(new RooFormulaVar("yp_dkstz_th", "y+ (DK*)", "r_dkstz*sin(d_dkstz+g)", *p)));
}


void PDF_GGSZ_DKstz::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("xm_dkstz_obs", "x- (DK* GGSZ) obs", 0, -1.5, 1.5)));
	observables->add(*(new RooRealVar("ym_dkstz_obs", "y- (DK* GGSZ) obs", 0, -1.5, 1.5)));
	observables->add(*(new RooRealVar("xp_dkstz_obs", "x+ (DK* GGSZ) obs", 0, -1.5, 1.5)));
	observables->add(*(new RooRealVar("yp_dkstz_obs", "y+ (DK* GGSZ) obs", 0, -1.5, 1.5)));
}


void PDF_GGSZ_DKstz::setObservables(config c)
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
		case lumi3fb:{
						 obsValSource = "Alexis' estimate"; // pers. comm. 10/6/2015
						 setObservable("xm_dkstz_obs", -0.03);
						 setObservable("ym_dkstz_obs", -0.24);
						 setObservable("xp_dkstz_obs",0.16);
						 setObservable("yp_dkstz_obs",0.18);
						 break;
					 }
		default:{
					cout << "PDF_GGSZ_DKstz::setObservables() : ERROR : config not found: " << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}


void PDF_GGSZ_DKstz::setUncertainties(config c)
{
	switch(c)
	{
		case lumi3fb:{
						 obsErrSource = "Alexis' estimate"; // pers. comm. 10/6/2015
						 StatErr[0] = 0.15; // xm
						 StatErr[1] = 0.19; // ym
						 StatErr[2] = 0.16; // xp
						 StatErr[3] = 0.19; // yp
						 SystErr[0] = 0.052;// xm
						 SystErr[1] = 0.043;// ym
						 SystErr[2] = 0.045;// xp
						 SystErr[3] = 0.060;// yp
						 break;
						  }
		default:{
					cout << "PDF_GGSZ_DKstz::setUncertainties() : ERROR : config not found: " << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}


void PDF_GGSZ_DKstz::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
    case lumi3fb: {
							  corSource = "no correlations";
                break;
              }
    case lumi3fb_estimate:{
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


void PDF_GGSZ_DKstz::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
