//
//  PDF_D_Kplus3pi.cpp
//
//
//  Created by Matthew Kenzie on 11/07/14.
//
//

#include "PDF_D_Kplus3pi.h"

PDF_D_Kplus3pi::PDF_D_Kplus3pi(config cObs, config cErr, config cCor):
	PDF_Abs(1)
{
	name = "dkplus3pi_belle";
  initParameters();
  initRelations();
  initObservables();
  setObservables(cObs);
  setUncertainties(cErr);
  setCorrelations(cCor);
  buildCov();
  buildPdf();

}

PDF_D_Kplus3pi::~PDF_D_Kplus3pi(){}

void PDF_D_Kplus3pi::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
  parameters->add(*(p.get("rD_k3pi")));
  parameters->add(*(p.get("dD_k3pi")));
  parameters->add(*(p.get("kD_k3pi")));
	parameters->add(*(p.get("BR_D_Kminus3pi")));
	parameters->add(*(p.get("xD")));
	parameters->add(*(p.get("yD")));
}

void PDF_D_Kplus3pi::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory");
	// using Eq.1 from arXiv:1307:5935 and the relation x'^2 + y'^2 = x^2 + y^2
	// add a pi phase?
	theory->add(*(new RooFormulaVar("BR_D_Kplus3pi_th","BR_D_Kplus3pi_th","BR_D_Kminus3pi*(rD_k3pi^2 - kD_k3pi*rD_k3pi*(yD*cos(dD_k3pi)-xD*sin(dD_k3pi)) + 0.5*(xD^2 + yD^2))",*(RooArgSet*)p)));
}

void PDF_D_Kplus3pi::initObservables()
{
	observables = new RooArgList("observables");
	observables->add(*(new RooRealVar("BR_D_Kplus3pi_obs","BR (D^{0}#rightarrow K^{+}3#pi",0.5,0.,1.)));
}

void PDF_D_Kplus3pi::setObservables(config c)
{
	switch(c)
	{
		case truth:
			setObservablesTruth();
			break;

		case toy:
			setObservablesToy();
			break;

		case belle2013:
			obsValSource = "arXiv:1307.5935 - Belle 2013 ";
			setObservable("BR_D_Kplus3pi_obs",2.61e-4); // Belle 2013
			break;

		default:
      cout << "PDF_D_Kplus3pi::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);

	}
}

void PDF_D_Kplus3pi::setUncertainties(config c)
{
	switch(c)
	{
		case belle2013:
			obsErrSource = "arXiv:1307.5935 - Belle 2013 ";
			StatErr[0] = 0.06e-4;
			SystErr[0] = 0.085e-4;
			break;

		default:
      cout << "PDF_D_Kplus3pi::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);

	}
}

void PDF_D_Kplus3pi::setCorrelations(config c)
{
  resetCorrelations();
  switch(c)
  {
    case belle2013:
			corSource = "no correlations for 1 obs";
      break;
    default:
      cout << "PDF_D_Kplus3pi::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
  }
}

void PDF_D_Kplus3pi::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name,"pdf_"+name,*(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
