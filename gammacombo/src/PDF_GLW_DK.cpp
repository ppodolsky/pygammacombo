/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#include "PDF_GLW_DK.h"

	PDF_GLW_DK::PDF_GLW_DK(config cObs, config cErr, config cCor)
: PDF_Abs(2)
{
	name = "glwdk";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_GLW_DK::~PDF_GLW_DK(){}


void PDF_GLW_DK::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("r_dk"))); 
	parameters->add(*(p.get("d_dk"))); 
	parameters->add(*(p.get("g")));
}


void PDF_GLW_DK::initRelations()
{
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	theory->add(*(new RooFormulaVar("acpp_dk_th", "Acp+ DK", "2.*r_dk*sin(d_dk)*sin(g)/(1. + r_dk^2 + 2.*r_dk*cos(d_dk)*cos(g))", *(RooArgSet*)parameters)));
	theory->add(*(new RooFormulaVar("rcpp_dk_th", "Rcp+ DK", "1. + r_dk^2 + 2.*r_dk*cos(d_dk)*cos(g)", *(RooArgSet*)parameters)));
}


void PDF_GLW_DK::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("acpp_dk_obs", "Acp+ (DK) obs",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rcpp_dk_obs", "Rcp+ (DK) obs",  1, -1e4, 1e4)));
}


void PDF_GLW_DK::setObservables(config c)
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
			obsValSource = "1fb-1 LHCb-PAPER-2012-001";
			setObservable("acpp_dk_obs",0.145);
			setObservable("rcpp_dk_obs",1.007);
			break;
		default:
			cout << "PDF_GLW_DK::setObservables : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DK::setUncertainties(config c)
{
	switch(c)
	{
		case lumi1fb:
			obsErrSource = "1fb-1 LHCb-PAPER-2012-001";
			StatErr[0] = 0.032; // acpp
			StatErr[1] = 0.038; // rcpp

			SystErr[0] = 0.010; // acpp
			SystErr[1] = 0.012; // rcpp
			break;

		default: 
			cout << "PDF_GLW_DK::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DK::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi1fb:
			corSource = "1fb-1 LHCb-PAPER-2012-001";
			corStatMatrix[1][0] = 0.;
			corSystMatrix[1][0] = 0.;
			break;

		case babar:
			corSource = "Babar";
			corStatMatrix[1][0] = -0.08;
			corSystMatrix[1][0] = -0.06;    
			break;

		default: 
			cout << "PDF_GLW_DK::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);    
	}
}  


void PDF_GLW_DK::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
