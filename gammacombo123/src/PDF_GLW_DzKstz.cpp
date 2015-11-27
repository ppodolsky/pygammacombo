/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#include "PDF_GLW_DzKstz.h"

	PDF_GLW_DzKstz::PDF_GLW_DzKstz(config cObs, config cErr, config cCor)
: PDF_Abs(3)
{
	name = "glwdzkstz";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_GLW_DzKstz::~PDF_GLW_DzKstz(){}


void PDF_GLW_DzKstz::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("r_dzkstz"))); 
	parameters->add(*(p.get("d_dzkstz"))); 
	parameters->add(*(p.get("k_dzkstz")));
	parameters->add(*(p.get("rD_kpi"))); 
	parameters->add(*(p.get("dD_kpi"))); 
	parameters->add(*(p.get("g")));
}


void PDF_GLW_DzKstz::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	theory->add(*(new RooFormulaVar("acpp_dzkstz", "Acp+ (D0Kst0)", "2.*k_dzkstz*r_dzkstz*sin(d_dzkstz)*sin(g)/(1. + r_dzkstz^2 + 2.*k_dzkstz*r_dzkstz*cos(d_dzkstz)*cos(g))", *p)));
	theory->add(*(new RooFormulaVar("rcpp_dzkstz", "Rcp+ (D0Kst0)", "(1. + r_dzkstz^2 + 2.*k_dzkstz*r_dzkstz*cos(d_dzkstz)*cos(g))", *p)));
	theory->add(*(new RooFormulaVar("k_dzkstz_th", "k_dzkstz_th", "k_dzkstz", *p)));
}


void PDF_GLW_DzKstz::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("acpp_dzkstz_obs", "Acp+ (D0Kst0) obs",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rcpp_dzkstz_obs", "Rcp+ (D0Kst0) obs",  1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("k_dzkstz_obs", "#kappa_{B} (D0Kst0) obs",  0.95, -1e4, 1e4)));
}


void PDF_GLW_DzKstz::setObservables(config c)
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
			obsValSource = "1fb-1 paper LHCb-CONF-2012-024";
			setObservable("acpp_dzkstz_obs",-0.47);
			setObservable("rcpp_dzkstz_obs",1.42);
			setObservable("k_dzkstz_obs",0.95);
			break;
		default:
			cout << "PDF_GLW_DzKstz::setObservables : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DzKstz::setUncertainties(config c)
{
	switch(c)
	{
		case lumi1fb:
			{
				StatErr[0] = 0.25; // acpp
				StatErr[1] = 0.41; // rcpp
				StatErr[2] = 0.0;  // kB

				SystErr[0] = 0.02; // acpp
				SystErr[1] = 0.07; // rcpp
				SystErr[2] = 0.025; // kB
				break;
			}
		default: 
			cout << "PDF_GLW_DzKstz::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DzKstz::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi1fb:
			// no correlations
			break;
		default: 
			cout << "PDF_GLW_DzKstz::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);    
	}
} 


void PDF_GLW_DzKstz::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
