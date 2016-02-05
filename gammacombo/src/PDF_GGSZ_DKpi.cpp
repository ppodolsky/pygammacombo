/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#include "PDF_GGSZ_DKpi.h"

	PDF_GGSZ_DKpi::PDF_GGSZ_DKpi(config cObs, config cErr, config cCor, ParametersAbs* pars)
: PDF_Abs(4)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	name = "ggsz_dkpi";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}

PDF_GGSZ_DKpi::~PDF_GGSZ_DKpi(){}


void PDF_GGSZ_DKpi::initParameters()
{
	parameters = new RooArgList("parameters");
	parameters->add(*(p->get("r_dkstz")));
	parameters->add(*(p->get("d_dkstz")));
	parameters->add(*(p->get("g")));
}


void PDF_GGSZ_DKpi::initRelations()
{
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	RooArgSet *p = (RooArgSet*)parameters;
	theory->add(*(new RooFormulaVar("xm_dkpi_th", "x- (DK)", "r_dkstz*cos(d_dkstz-g)", *p)));
	theory->add(*(new RooFormulaVar("ym_dkpi_th", "y- (DK)", "r_dkstz*sin(d_dkstz-g)", *p)));
	theory->add(*(new RooFormulaVar("xp_dkpi_th", "x+ (DK)", "r_dkstz*cos(d_dkstz+g)", *p)));
	theory->add(*(new RooFormulaVar("yp_dkpi_th", "y+ (DK)", "r_dkstz*sin(d_dkstz+g)", *p)));
}


void PDF_GGSZ_DKpi::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("xm_dkpi_obs", "x- (DKpi) obs", 0, -1, 1)));
	observables->add(*(new RooRealVar("ym_dkpi_obs", "y- (DKpi) obs", 0, -1, 1)));
	observables->add(*(new RooRealVar("xp_dkpi_obs", "x+ (DKpi) obs", 0, -1, 1)));
	observables->add(*(new RooRealVar("yp_dkpi_obs", "y+ (DKpi) obs", 0, -1, 1)));
}


void PDF_GGSZ_DKpi::setObservables(config c)
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
						 obsValSource = "Email from Mark 20/11/15";
						 setObservable("xm_dkpi_obs", -0.014);
						 setObservable("ym_dkpi_obs", -0.298);
						 setObservable("xp_dkpi_obs",  0.047);
						 setObservable("yp_dkpi_obs", -0.475);
						 break;
					 }
		default:{
					cout << "PDF_GGSZ_DKpi::setObservables() : ERROR : config not found: " << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}


void PDF_GGSZ_DKpi::setUncertainties(config c)
{
	switch(c)
	{
		case lumi3fb:{
						 obsErrSource = "Email from Mark 20/11/15";
						 StatErr[0] = 0.127; // xm
						 StatErr[1] = 0.256; // ym
						 StatErr[2] = 0.160; // xp
						 StatErr[3] = 0.278; // yp

             SystErr[0] = 0.139; // xm
						 SystErr[1] = 0.408; // ym
						 SystErr[2] = 0.112; // xp
						 SystErr[3] = 0.220; // yp
						 break;
					 }
		default:{
					cout << "PDF_GGSZ_DKpi::setUncertainties() : ERROR : config not found: " << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}


void PDF_GGSZ_DKpi::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi3fb:{
						 corSource = "Email from Mark 20/11/15";

             double dataStat[] = {  1.000,  0.341,  0.104,  0.130,
                                    0.341,  1.000,  0.054,  0.154,
                                    0.104,  0.054,  1.000,  0.501,
                                    0.130,  0.154,  0.501,  1.000 };

             corStatMatrix = TMatrixDSym(nObs,dataStat);

             double dataSyst[] = {  1.000,  0.813,  0.312,  0.379,
                                    0.813,  1.000,  0.263,  0.393,
                                    0.312,  0.263,  1.000,  0.698,
                                    0.379,  0.393,  0.698,  1.000 };

             corSystMatrix = TMatrixDSym(nObs, dataSyst);

						 break;
					 }
		default:{
					cout << "PDF_GGSZ_DKpi::setCorrelations() : ERROR : config not found: " << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}


void PDF_GGSZ_DKpi::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
