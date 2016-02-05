/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#include "PDF_GGSZ_cartesian.h"

	PDF_GGSZ_cartesian::PDF_GGSZ_cartesian(config cObs, config cErr, config cCor, ParametersAbs* pars)
: PDF_Abs(4)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	name = "ggszcart";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}

PDF_GGSZ_cartesian::~PDF_GGSZ_cartesian(){}


void PDF_GGSZ_cartesian::initParameters()
{
	parameters = new RooArgList("parameters");
	parameters->add(*(p->get("xm_dk"))); 
	parameters->add(*(p->get("ym_dk")));
	parameters->add(*(p->get("xp_dk"))); 
	parameters->add(*(p->get("yp_dk")));
}  


void PDF_GGSZ_cartesian::initRelations()
{
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	RooArgSet *p = (RooArgSet*)parameters;
	theory->add(*(new RooFormulaVar("xm_dk_th", "x- (DK)", "xm_dk", *p)));
	theory->add(*(new RooFormulaVar("ym_dk_th", "y- (DK)", "ym_dk", *p)));
	theory->add(*(new RooFormulaVar("xp_dk_th", "x+ (DK)", "xp_dk", *p)));
	theory->add(*(new RooFormulaVar("yp_dk_th", "y+ (DK)", "yp_dk", *p)));
}


void PDF_GGSZ_cartesian::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("xm_dk_obs", "x- (DK GGSZ) obs", 0, -1, 1)));
	observables->add(*(new RooRealVar("ym_dk_obs", "y- (DK GGSZ) obs", 0, -1, 1)));
	observables->add(*(new RooRealVar("xp_dk_obs", "x+ (DK GGSZ) obs", 0, -1, 1)));
	observables->add(*(new RooRealVar("yp_dk_obs", "y+ (DK GGSZ) obs", 0, -1, 1)));
}


void PDF_GGSZ_cartesian::setObservables(config c)
{
	switch(c)
	{
		case truth:
			{
				setObservablesTruth();
				break;
			}
		case toy:
			{ 
				setObservablesToy();
				break;
			}
		case lumi1fb:
			{
				obsValSource = "mock up";
				setObservable("xm_dk_obs", 0.00);
				setObservable("ym_dk_obs", 0.14);
				setObservable("xp_dk_obs",-0.00);
				setObservable("yp_dk_obs",-0.00);
				break;
			}
		default:
			{
				cout << "PDF_GGSZ_cartesian::setObservables() : ERROR : config not found: " << ConfigToTString(c) << endl;
				exit(1);
			}
	}
}


void PDF_GGSZ_cartesian::setUncertainties(config c)
{
	switch(c)
	{
		case lumi1fb:
			{
				obsErrSource = "mock up";
				StatErr[0] = 0.03; // xm
				StatErr[1] = 0.03; // ym
				StatErr[2] = 0.03; // xp
				StatErr[3] = 0.03; // yp
				SystErr[0] = 0.0; // xm
				SystErr[1] = 0.0; // ym
				SystErr[2] = 0.0; // xp
				SystErr[3] = 0.0; // yp
				break;
			}
		default:
			{
				cout << "PDF_GGSZ_cartesian::setUncertainties() : ERROR : config not found: " << ConfigToTString(c) << endl;
				exit(1);
			}
	}
}


void PDF_GGSZ_cartesian::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi1fb:
			{
				corSource = "mock up";
				break;
			}     
		default:
			{
				cout << "PDF_GGSZ_cartesian::setCorrelations() : ERROR : config not found: " << ConfigToTString(c) << endl;
				exit(1);
			}
	}
}  


void PDF_GGSZ_cartesian::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
