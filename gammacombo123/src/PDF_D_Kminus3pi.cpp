//
//  PDF_D_Kminus3pi.cpp
//
//
//  Created by Matthew Kenzie on 11/07/14.
//
//

#include "PDF_D_Kminus3pi.h"

PDF_D_Kminus3pi::PDF_D_Kminus3pi(config cObs, config cErr, config cCor):
	PDF_Abs(1)
{
	name = "dkminus3pi_cleo";
  initParameters();
  initRelations();
  initObservables();
  setObservables(cObs);
  setUncertainties(cErr);
  setCorrelations(cCor);
  buildCov();
  buildPdf();

}

PDF_D_Kminus3pi::~PDF_D_Kminus3pi(){}

void PDF_D_Kminus3pi::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("BR_D_Kminus3pi")));
}

void PDF_D_Kminus3pi::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory");
	theory->add(*(new RooFormulaVar("BR_D_Kminus3pi_th","BR_D_Kminus3pi_th","BR_D_Kminus3pi",*(RooArgSet*)p)));
}

void PDF_D_Kminus3pi::initObservables()
{
	observables = new RooArgList("observables");
	observables->add(*(new RooRealVar("BR_D_Kminus3pi_obs","BR (D^{0}#rightarrow K^{+}3#pi",0.5,0.,1.)));
}

void PDF_D_Kminus3pi::setObservables(config c)
{
	switch(c)
	{
		case truth:
			setObservablesTruth();
			break;

		case toy:
			setObservablesToy();
			break;

		case cleo2014:
			obsValSource = "arXiv:1312.6775 - CLEO 2013 ";
			setObservable("BR_D_Kminus3pi_obs",8.29e-2); // Cleo 2014
			break;

		default:
      cout << "PDF_D_Kminus3pi::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);

	}
}

void PDF_D_Kminus3pi::setUncertainties(config c)
{
	switch(c)
	{
		case cleo2014:
			obsErrSource = "arXiv:1312.6775 - CLEO 2013 ";
			StatErr[0] = 0.043e-2;
			SystErr[0] = 0.2e-2;
			break;

		default:
      cout << "PDF_D_Kminus3pi::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);

	}
}

void PDF_D_Kminus3pi::setCorrelations(config c)
{
  resetCorrelations();
  switch(c)
  {
    case cleo2014:
			corSource = "no correlations for 1 obs";
      break;
    default:
      cout << "PDF_D_Kminus3pi::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
  }
}

void PDF_D_Kminus3pi::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name,"pdf_"+name,*(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}

