/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Jan 2015
 *
 **/

#include "PDF_D_hhpi0_dilution.h"

	PDF_D_hhpi0_dilution::PDF_D_hhpi0_dilution(config cObs, config cErr, config cCor)
: PDF_Abs(2)
{
	name = "CleoDhhpi0Dilution";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_D_hhpi0_dilution::~PDF_D_hhpi0_dilution(){}


void PDF_D_hhpi0_dilution::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("F_pipipi0")));
	parameters->add(*(p.get("F_kkpi0")));
}


void PDF_D_hhpi0_dilution::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	theory->add(*(new RooFormulaVar("F_pipipi0_th", "F_pipipi0_th", "F_pipipi0", *p)));
	theory->add(*(new RooFormulaVar("F_kkpi0_th",   "F_kkpi0_th",   "F_kkpi0",   *p)));
}


void PDF_D_hhpi0_dilution::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("F_pipipi0_obs", "F_pipipi0",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("F_kkpi0_obs",   "F_kkpi0",    0, -1e4, 1e4)));
}


void PDF_D_hhpi0_dilution::setObservables(config c)
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
		case cleo:{
							obsValSource = "1410.3964";
							setObservable("F_pipipi0_obs", 0.968);
							setObservable("F_kkpi0_obs",   0.731);
							break;
						}
		case cleo2015:{
							obsValSource = "1504.05878";
							setObservable("F_pipipi0_obs", 0.973);
							setObservable("F_kkpi0_obs",   0.732);
							break;
						}
		default:{
					cout << "PDF_D_hhpi0_dilution::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_D_hhpi0_dilution::setUncertainties(config c)
{
	switch(c)
	{
		case cleo:{
							obsErrSource = "1410.3964";
							StatErr[0] = 0.017; // F_pipipi0
							StatErr[1] = 0.058; // F_kkpi0
							SystErr[0] = 0.006; // F_pipipi0
							SystErr[1] = 0.021; // F_kkpi0
							break;
						}
		case cleo2015:{
							obsErrSource = "1504.05878";
							StatErr[0] = 0.017; // F_pipipi0
							StatErr[1] = 0.055; // F_kkpi0
							SystErr[0] = 0.000; // F_pipipi0
							SystErr[1] = 0.000; // F_kkpi0
							break;
						}
		default:{
					cout << "PDF_D_hhpi0_dilution::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_D_hhpi0_dilution::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case cleo:{
							corSource = "1410.3964";
							break;
						}
		case cleo2015:{
							corSource = "1504.05878";
							break;
						}
		default:{
					cout << "PDF_D_hhpi0_dilution::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_D_hhpi0_dilution::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
