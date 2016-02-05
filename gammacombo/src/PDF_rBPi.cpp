/**
 * Gamma Combination
 * Author: Matt Kenzie
 * Date: September 2015
 *
 * A constraint on rBPi from Niels
 *
 **/

#include "PDF_rBPi.h"

	PDF_rBPi::PDF_rBPi(config cObs, config cErr, config cCor)
: PDF_Abs(1)
{
	name = "rBPi";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_rBPi::~PDF_rBPi(){}


void PDF_rBPi::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("r_dpi")));
}


void PDF_rBPi::initRelations()
{
	theory = new RooArgList("theory");
	// it's not so clear how rb depends on x and y - it should be the average
	// of x-,y, and x+,y+ - but we can't just put a factor 1/2 in there, else
	// the educational example breaks down: a constraint on rb=0.09 will not appear
	// at radius 0.09 in the x-,y- plot.
	theory->add(*(new RooFormulaVar("r_dpi_th", "r_dpi_th", "r_dpi", *(RooArgSet*)parameters)));
}


void PDF_rBPi::initObservables()
{
	observables = new RooArgList("observables");
	observables->add(*(new RooRealVar("r_dpi_obs", "r_dpi_obs",  0.1, -1e4, 1e4)));
}


void PDF_rBPi::setObservables(config c)
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
		case manual:
			{
				obsValSource = "niels";
				setObservable("r_dpi_obs",0.0077);
				break;
			}
		default:
			{
				cout << "PDF_rBPi::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}
	}
}


void PDF_rBPi::setUncertainties(config c)
{
	switch(c)
	{
		case manual:
			{
				obsErrSource = "niels";
				StatErr[0] = 0.0035; //
        SystErr[0] = 0.;
				break;
			}
		case test1:
			{
				obsErrSource = "test1";
				StatErr[0] = 0.007; //
        SystErr[0] = 0.;
				break;
			}
		case test2:
			{
				obsErrSource = "test2";
				StatErr[0] = 0.0105; //
        SystErr[0] = 0.;
				break;
			}
		case test3:
			{
				obsErrSource = "test3";
				StatErr[0] = 0.014; //
        SystErr[0] = 0.;
				break;
			}
		case test4:
			{
				obsErrSource = "test4";
				StatErr[0] = 0.028; //
        SystErr[0] = 0.;
				break;
			}
		default:
			{
				cout << "PDF_rBPi::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}
	}
}


void PDF_rBPi::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case manual:
			corSource = "no correlations for 1 obs";
			break;
		default:
			cout << "PDF_rBPi::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_rBPi::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
