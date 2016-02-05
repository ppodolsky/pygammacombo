/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Nov 2014
 *
 **/

#include "PDF_gamma.h"

	PDF_gamma::PDF_gamma(config cObs, config cErr, config cCor)
: PDF_Abs(1)
{
	name = "gamma";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_gamma::~PDF_gamma(){}


void PDF_gamma::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("g")));
}


void PDF_gamma::initRelations()
{
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	theory->add(*(new RooFormulaVar("g_th", "g_th", "g", *(RooArgSet*)parameters)));
}


void PDF_gamma::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("g_obs", "g_obs",  0, -1e4, 1e4)));
}


void PDF_gamma::setObservables(config c)
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
		case year2014:{
				      obsValSource = "year2014";
				      setObservable("g_obs",70.0/57.3);
				      break;
			      }
		default:{
				cout << "PDF_gamma::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}
	}
}


void PDF_gamma::setUncertainties(config c)
{
	switch(c)
	{
		case year2014:{
				      obsErrSource = "year2014";
				      StatErr[0] = 9./57.3; // g
				      SystErr[0] = 0; // g
				      break;
			      }
		default:{
				cout << "PDF_gamma::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}
	}
}


void PDF_gamma::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case year2014:{
				      corSource = "no correlations for 1 obs";
				      break;
			      }
		default:{ 
				cout << "PDF_gamma::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}    
	}
}


void PDF_gamma::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
