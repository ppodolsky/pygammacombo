/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#include "PDF_Dmixing.h"

	PDF_Dmixing::PDF_Dmixing(config cObs, config cErr, config cCor, ParametersAbs* pars)
: PDF_Abs(3)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	name = "Dmixing";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_Dmixing::~PDF_Dmixing(){}


void PDF_Dmixing::initParameters()
{
	parameters = new RooArgList("parameters");
	parameters->add(*(p->get("xD")));
	parameters->add(*(p->get("yD")));
	parameters->add(*(p->get("rD_kpi")));
	parameters->add(*(p->get("dD_kpi")));
}


void PDF_Dmixing::initRelations()
{
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	theory->add(*(new RooFormulaVar("RD_th",       "RD (Dmixing)",      "rD_kpi^2",                          *(RooArgSet*)parameters)));
	theory->add(*(new RooFormulaVar("yprime_th",   "yD' (Dmixing)",     " xD*sin(dD_kpi)-yD*cos(dD_kpi)",    *(RooArgSet*)parameters)));
	theory->add(*(new RooFormulaVar("xprimesq_th", "xD'^{2} (Dmixing)", "(xD*cos(dD_kpi)+yD*sin(dD_kpi))^2", *(RooArgSet*)parameters)));
}


void PDF_Dmixing::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("RD_obs",       "RD  (Dmixing) obs", 0, -1, 1)));
	observables->add(*(new RooRealVar("yprime_obs",   "y'  (Dmixing) obs", 0, -1, 1)));
	observables->add(*(new RooRealVar("xprimesq_obs", "x^{'2} (Dmixing) obs", 0, -1, 1)));
}


void PDF_Dmixing::setObservables(config c)
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
		case lumi1fb:{
						 obsValSource = "1fb-1 LHCb-PAPER-2012-038";
						 setObservable("RD_obs",       3.52e-3);
						 setObservable("yprime_obs",   7.2e-3);
						 setObservable("xprimesq_obs",-0.09e-3);
						 break;
					 }
		default:{
					cout << "PDF_Dmixing::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_Dmixing::setUncertainties(config c)
{
	switch(c)
	{
		case lumi1fb:{
						 obsErrSource = "1fb-1 LHCb-PAPER-2012-038";
						 StatErr[0] = 0.15e-3; // RD
						 StatErr[1] = 2.4e-3;  // yprime
						 StatErr[2] = 0.13e-3; // xprimesq
						 SystErr[0] = 0; // RD
						 SystErr[1] = 0; // yprime
						 SystErr[2] = 0; // xprimesq
						 break;
					 }
		case lumi50fb:{
						  setUncertainties(lumi1fb);
						  obsErrSource = "50fb-1 estimate, scaled down from 1fb-1 from LHCb-PAPER-2012-038";
						  for ( int i=0; i<nObs; i++ ){
							  StatErr[i] /= sqrt(50.);
							  SystErr[i] /= sqrt(50.);
						  }
						  break;
					  }
		default:{
					cout << "PDF_Dmixing::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_Dmixing::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi1fb:{
						 corSource = "1fb-1 LHCb-PAPER-2012-038";
						 corStatMatrix[1][0] = -0.954; // RD, yprime
						 corStatMatrix[2][0] = +0.882; // RD, xprimesq
						 corStatMatrix[2][1] = -0.973; // yprime, xprimesq

						 corSystMatrix[1][0] = 0.;
						 corSystMatrix[2][0] = 0.;
						 corSystMatrix[2][1] = 0.;
						 break;
					 }
		default:{
					cout << "PDF_Dmixing::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_Dmixing::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
