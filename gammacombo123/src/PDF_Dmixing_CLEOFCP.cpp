///
///  PDF_Dmixing_CLEOFCP.cpp
///
///
///  Created by Matthew Kenzie on 11/07/14.
///
#include "PDF_Dmixing_CLEOFCP.h"

PDF_Dmixing_CLEOFCP::PDF_Dmixing_CLEOFCP(config cObs, config cErr, config cCor, config cType, TString d):
	PDF_Abs(1)
{
	name = "d4pi_dmixing_cleo";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();

}

PDF_Dmixing_CLEOFCP::~PDF_Dmixing_CLEOFCP(){}

void PDF_Dmixing_CLEOFCP::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	//parameters->add(*(p.get("F_kkpi0")));
	//parameters->add(*(p.get("F_pipipi0")));
	parameters->add(*(p.get("F_pipipipi")));
}

void PDF_Dmixing_CLEOFCP::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory");
	//theory->add(*(new RooFormulaVar("F_kkpi0_th", "F_kkpi0_th", "F_kkpi0", *p)));
	//theory->add(*(new RooFormulaVar("F_pipipi0_th", "F_pipipi0_th", "F_pipipi0", *p)));
	theory->add(*(new RooFormulaVar("F_pipipipi_th", "F_pipipipi_th", "F_pipipipi", *p)));

}

void PDF_Dmixing_CLEOFCP::initObservables()
{
	observables = new RooArgList("observables");
	//observables->add(*(new RooRealVar("F_kkpi0_obs", "F_{D#rightarrowKK#pi^{0}}", 0, -1.e4, 1.e4)));
	//observables->add(*(new RooRealVar("F_pipipi0_obs", "F_{D#rightarrow#pi#pi#pi^{0}}", 0, -1.e4, 1.e4)));
	observables->add(*(new RooRealVar("F_pipipipi_obs", "F_{D#rightarrow4#pi}", 0, -1.e4, 1.e4)));
}

void PDF_Dmixing_CLEOFCP::setObservables(config c)
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
		case cleo2015:{
					 obsValSource = "arXiv:1504.05878 - CLEO-c CP content of D decays";
					 //setObservable("F_kkpi0_obs"   , 0.732);
					 //setObservable("F_pipipi0_obs" , 0.973);
					 setObservable("F_pipipipi_obs", 0.737);
					 break;
				 }
		default:{
					cout << "PDF_Dmixing_CLEOFCP::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}

void PDF_Dmixing_CLEOFCP::setUncertainties(config c)
{
	switch(c)
	{
		case cleo2015:{
					 obsErrSource = "arXiv:1504.05878 - CLEO-c CP content of D decays";
					 //StatErr[0] = 0.055; // F_kkpi0
					 //StatErr[1] = 0.017; // F_pipipi0
					 //StatErr[2] = 0.028; // F_pipipipi
					 //SystErr[0] = 0.; // F_kkpi0
					 //SystErr[1] = 0.; // F_pipipi0
					 //SystErr[2] = 0.; // F_pipipipi
					 StatErr[0] = 0.028;
					 SystErr[0] = 0.;
					 break;
				 }
		default:{
					cout << "PDF_Dmixing_CLEOFCP::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}

void PDF_Dmixing_CLEOFCP::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case cleo2015:{
						  corSource = "No correlations";
						  break;
					  }
		default:{
					cout << "PDF_Dmixing_CLEOFCP::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}

void PDF_Dmixing_CLEOFCP::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
