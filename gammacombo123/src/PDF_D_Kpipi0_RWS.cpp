//
//  PDF_D_Kpipi0_RWS.cpp
//
//
//  Created by Moritz Karbach on 19/08/14.
//
//

#include "PDF_D_Kpipi0_RWS.h"

PDF_D_Kpipi0_RWS::PDF_D_Kpipi0_RWS(config cObs, config cErr, config cCor):
	PDF_Abs(1)
{
	name = "dkpipi0RWS";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();

}

PDF_D_Kpipi0_RWS::~PDF_D_Kpipi0_RWS(){}

void PDF_D_Kpipi0_RWS::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("rD_kpipi0")));
	parameters->add(*(p.get("dD_kpipi0")));
	parameters->add(*(p.get("kD_kpipi0")));
	parameters->add(*(p.get("xD")));
	parameters->add(*(p.get("yD")));
}

void PDF_D_Kpipi0_RWS::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory");
	// using Eq.1 from arXiv:1307:5935 and the relation x'^2 + y'^2 = x^2 + y^2
	theory->add(*(new RooFormulaVar("RWS_Kpipi0_th","RWS_Kpipi0_th","rD_kpipi0^2 - kD_kpipi0*rD_kpipi0*(yD*cos(dD_kpipi0)-xD*sin(dD_kpipi0)) + 0.5*(xD^2 + yD^2)",*(RooArgSet*)p)));
}

void PDF_D_Kpipi0_RWS::initObservables()
{
	observables = new RooArgList("observables");
	observables->add(*(new RooRealVar("RWS_Kpipi0_obs","R_{WS}(D^{0}#rightarrow K#pi#pi^{0})",0.5,0.,1.)));
}

void PDF_D_Kpipi0_RWS::setObservables(config c)
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
		case cleo2014:{
						  obsValSource = "OtherFiles/RWS_Kpipi0_errorpropagation.py";
						  setObservable("RWS_Kpipi0_obs",0.00219251336898);
						  break;
					  }
    case pdg: {
              obsValSource = "PDG - actually lifted from gammadini";
              setObservable("RWS_Kpipi0_obs", 0.00220);
              break;
            }
		default:{
					cout << "PDF_D_Kpipi0_RWS::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}

void PDF_D_Kpipi0_RWS::setUncertainties(config c)
{
	switch(c)
	{
		case cleo2014:{
						  obsErrSource = "OtherFiles/RWS_Kpipi0_errorpropagation.py";
						  StatErr[0] = 0.00014;
						  SystErr[0] = 0.0;
						  break;
					  }
    case pdg: {
              obsErrSource = "PDG - actually lifted from gammadini";
						  StatErr[0] = 0.00010;
						  SystErr[0] = 0.0;
              break;
            }
		default:{
					cout << "PDF_D_Kpipi0_RWS::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}

void PDF_D_Kpipi0_RWS::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case cleo2014:{
						  corSource = "no correlations for 1 obs";
						  break;
					  }
		case pdg:{
						  corSource = "no correlations for 1 obs";
						  break;
					  }
		default:{
					cout << "PDF_D_Kpipi0_RWS::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}

void PDF_D_Kpipi0_RWS::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name,"pdf_"+name,*(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
