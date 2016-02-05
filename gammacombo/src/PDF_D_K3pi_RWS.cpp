//
//  PDF_D_K3pi_RWS.cpp
//
//
//  Created by Moritz Karbach on 28/07/14.
//
//

#include "PDF_D_K3pi_RWS.h"

PDF_D_K3pi_RWS::PDF_D_K3pi_RWS(config cObs, config cErr, config cCor):
	PDF_Abs(1)
{
	name = "dk3piRWS";
  initParameters();
  initRelations();
  initObservables();
  setObservables(cObs);
  setUncertainties(cErr);
  setCorrelations(cCor);
  buildCov();
  buildPdf();

}

PDF_D_K3pi_RWS::~PDF_D_K3pi_RWS(){}

void PDF_D_K3pi_RWS::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
  parameters->add(*(p.get("rD_k3pi")));
  parameters->add(*(p.get("dD_k3pi")));
  parameters->add(*(p.get("kD_k3pi")));
	parameters->add(*(p.get("xD")));
	parameters->add(*(p.get("yD")));
}

void PDF_D_K3pi_RWS::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory");
	// using Eq.1 from arXiv:1307:5935 and the relation x'^2 + y'^2 = x^2 + y^2
	theory->add(*(new RooFormulaVar("RWS_K3pi_th","RWS_K3pi_th","rD_k3pi^2 - kD_k3pi*rD_k3pi*(yD*cos(dD_k3pi)-xD*sin(dD_k3pi)) + 0.5*(xD^2 + yD^2)",*(RooArgSet*)p)));
}

void PDF_D_K3pi_RWS::initObservables()
{
	observables = new RooArgList("observables");
	observables->add(*(new RooRealVar("RWS_K3pi_obs","R_{WS}(D^{0}#rightarrow K^{+}3#pi",0.5,0.,1.)));
}

void PDF_D_K3pi_RWS::setObservables(config c)
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
		case ckm2014:{
			//obsValSource = "arXiv:1307.5935 (Belle 2013), arXiv:1312.6775 (CLEO 2013); OtherFiles/RWS_K3pi_errorpropagation.py";
			obsErrSource = "PDG"; // see Guy's email 13/08/15
			setObservable("RWS_K3pi_obs",0.324e-02);
			break;
		}
		default:{
      cout << "PDF_D_K3pi_RWS::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
		}
	}
}

void PDF_D_K3pi_RWS::setUncertainties(config c)
{
	switch(c)
	{
		case ckm2014:{
			 //obsErrSource = "arXiv:1307.5935 (Belle 2013), arXiv:1312.6775 (CLEO 2013); OtherFiles/RWS_K3pi_errorpropagation.py";
			obsErrSource = "PDG"; // see Guy's email 13/08/15
			StatErr[0] = 0.008e-2;
			SystErr[0] = 0.007e-2;
			break;
		}
		default:{
      cout << "PDF_D_K3pi_RWS::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
		}
	}
}

void PDF_D_K3pi_RWS::setCorrelations(config c)
{
  resetCorrelations();
  switch(c)
  {
    case ckm2014:{
			corSource = "no correlations for 1 obs";
      break;
		}
    default:{
      cout << "PDF_D_K3pi_RWS::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
		}
  }
}

void PDF_D_K3pi_RWS::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name,"pdf_"+name,*(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
