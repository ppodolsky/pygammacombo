/**
 * Gamma Combination
 * Author: Matthew Kenzie, matthew.kenzie@cern.ch
 * Date: January 2016
 *
 *
 **/

#include "PDF_rDk3pi.h"

	PDF_rDk3pi::PDF_rDk3pi(config cObs, config cErr, config cCor)
: PDF_Abs(1)
{
	name = "rDk3pi";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_rDk3pi::~PDF_rDk3pi(){}


void PDF_rDk3pi::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("rD_k3pi")));
}


void PDF_rDk3pi::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory");
	theory->add(*(new RooFormulaVar("rD_k3pi_th", "rD_k3pi_th", "rD_k3pi", *(RooArgSet*)p)));
}


void PDF_rDk3pi::initObservables()
{
	observables = new RooArgList("observables");
	observables->add(*(new RooRealVar("rD_k3pi_obs", "rD_k3pi_obs",  0.5, -1e4, 1e4)));
}


void PDF_rDk3pi::setObservables(config c)
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
		case lhcb:
			{
				obsValSource = "LHCb 2015 Harnew";
				setObservable("rD_k3pi_obs",0.0573);
				break;
			}
		default:
			{
				cout << "PDF_rDk3pi::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}
	}
}


void PDF_rDk3pi::setUncertainties(config c)
{
	switch(c)
	{
		case lhcb:
			{
				obsErrSource = "Harnew";
				StatErr[0] = 0.0012; //
				SystErr[0] = 0.0; //
				break;
			}
		default:
			{
				cout << "PDF_rDk3pi::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}
	}
}


void PDF_rDk3pi::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lhcb:
			corSource = "no correlations for 1 obs";
			break;
		default:
			cout << "PDF_rDk3pi::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_rDk3pi::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
