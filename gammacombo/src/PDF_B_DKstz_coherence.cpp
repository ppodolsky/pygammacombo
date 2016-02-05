/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Sep 2013
 *
 * B Coherence factor in B0 -> D0 K*0
 *
 **/

#include "PDF_B_DKstz_coherence.h"

	PDF_B_DKstz_coherence::PDF_B_DKstz_coherence(config cObs)
: PDF_Abs(1)
{
	name = "dkstzcoherence";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(hfag);
	setCorrelations(hfag);
	buildCov();
	buildPdf();
}


PDF_B_DKstz_coherence::~PDF_B_DKstz_coherence(){}


void PDF_B_DKstz_coherence::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("k_dkstz")));
}  


void PDF_B_DKstz_coherence::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	theory->add(*(new RooFormulaVar("k_dkstz_th", "k_dkstz_th", "k_dkstz", *p)));
}


void PDF_B_DKstz_coherence::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("k_dkstz_obs", "k_dkstz",       1, -1e4, 1e4)));
}


void PDF_B_DKstz_coherence::setObservables(config c)
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
		case hfag:
			obsValSource = "HFAG";
			setObservable("k_dkstz_obs",0.95);
			break;

		default:
			cout << "PDF_B_DKstz_coherence::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_B_DKstz_coherence::setUncertainties(config c)
{
	switch(c)
	{
		case hfag:
			obsErrSource = "HFAG";
			StatErr[0] = 0.03;
			SystErr[0] = 0.0;
			break;

		default: 
			cout << "PDF_B_DKstz_coherence::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_B_DKstz_coherence::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case hfag:
			corSource = "-";
			break;

		default: 
			cout << "PDF_B_DKstz_coherence::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);    
	}
}  


void PDF_B_DKstz_coherence::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
