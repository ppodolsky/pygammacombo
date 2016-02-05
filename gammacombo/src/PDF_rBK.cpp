/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: October 2013
 *
 * A constraint on rB for cartesian coordinates.
 *
 **/

#include "PDF_rBK.h"

	PDF_rBK::PDF_rBK(config cObs, config cErr, config cCor)
: PDF_Abs(1)
{
	name = "rBK";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_rBK::~PDF_rBK(){}


void PDF_rBK::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("xm_dk"))); 
	parameters->add(*(p.get("ym_dk")));
	parameters->add(*(p.get("xp_dk"))); 
	parameters->add(*(p.get("yp_dk")));
}


void PDF_rBK::initRelations()
{
	theory = new RooArgList("theory");
	// it's not so clear how rb depends on x and y - it should be the average
	// of x-,y, and x+,y+ - but we can't just put a factor 1/2 in there, else
	// the educational example breaks down: a constraint on rb=0.09 will not appear
	// at radius 0.09 in the x-,y- plot.
	theory->add(*(new RooFormulaVar("r_dk_th", "r_dk_th", "sqrt((xm_dk^2+ym_dk^2+xp_dk^2+yp_dk^2))", *(RooArgSet*)parameters)));
}


void PDF_rBK::initObservables()
{
	observables = new RooArgList("observables");
	observables->add(*(new RooRealVar("r_dk_obs", "r_dk_obs",  0.1, -1e4, 1e4)));
}


void PDF_rBK::setObservables(config c)
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
				setObservable("r_dk_obs",0.09);
				break;
			}
		default:
			{
				cout << "PDF_rBK::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}
	}
}


void PDF_rBK::setUncertainties(config c)
{
	switch(c)
	{
		case lumi1fb:
			{
				obsErrSource = "mock up";
				StatErr[0] = 0.005; // x
				SystErr[0] = 0; // x
				break;
			}
		default:
			{
				cout << "PDF_rBK::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}
	}
}


void PDF_rBK::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi1fb:
			corSource = "no correlations for 1 obs";
			break;
		default: 
			cout << "PDF_rBK::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);    
	}
}


void PDF_rBK::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
