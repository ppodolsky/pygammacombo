//
//  PDF_Dmixing_K3pi.cpp
//
//
//  Created by Sam Harnew on 10/08/15.
//
//

#include "PDF_Dmixing_K3pi.h"

PDF_Dmixing_K3pi::PDF_Dmixing_K3pi(config cObs, config cErr, config cCor):
	PDF_Abs(3)
{
  name = "Dmixing_K3pi";
  initParameters();
  initRelations();
  initObservables();
  setObservables(cObs);
  setUncertainties(cErr);
  setCorrelations(cCor);
  buildCov();
  buildPdf();

}

PDF_Dmixing_K3pi::~PDF_Dmixing_K3pi(){}

void PDF_Dmixing_K3pi::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
    parameters->add(*(p.get("rD_k3pi")));
    parameters->add(*(p.get("dD_k3pi")));
    parameters->add(*(p.get("kD_k3pi")));
	parameters->add(*(p.get("xD")));
	parameters->add(*(p.get("yD")));

}

void PDF_Dmixing_K3pi::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory");
	theory->add(*(new RooFormulaVar("Dmixing_K3pi_rD_th","rD_k3pi",*(RooArgSet*)p)));
    theory->add(*(new RooFormulaVar("Dmixing_K3pi_b_th","kD_k3pi*(yD*cos(dD_k3pi)-xD*sin(dD_k3pi))",*(RooArgSet*)p)));
	theory->add(*(new RooFormulaVar("Dmixing_K3pi_c_th","0.25*(xD*xD + yD*yD)",*(RooArgSet*)p)));


}

void PDF_Dmixing_K3pi::initObservables()
{
	observables = new RooArgList("observables");
	observables->add(*(new RooRealVar("Dmixing_K3pi_rD_obs","r_D(D^{0}#rightarrow K^{+}3#pi)",0.5,0.,1.)));
  observables->add(*(new RooRealVar("Dmixing_K3pi_b_obs","b(D^{0}#rightarrow K^{+}3#pi)",0.5,-1.,1.)));
	observables->add(*(new RooRealVar("Dmixing_K3pi_c_obs","c(D^{0}#rightarrow K^{+}3#pi)",0.5,-1.,1.)));
}

void PDF_Dmixing_K3pi::setObservables(config c)
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
		case lhcb2012:{
			obsValSource = "LHCb 2015 Preliminary";
			setObservable("Dmixing_K3pi_rD_obs",0.0573);
			setObservable("Dmixing_K3pi_b_obs" ,0.0002);
			setObservable("Dmixing_K3pi_c_obs" ,0.000048);
			break;
		}
		default:{
      cout << "PDF_Dmixing_K3pi::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
		}
	}
}

void PDF_Dmixing_K3pi::setUncertainties(config c)
{
	switch(c)
	{
		case lhcb2012:{
			obsErrSource = "LHCb 2015 Preliminary";
			StatErr[0] = 0.0012;
			SystErr[0] = 0.0;
			StatErr[1] = 0.0019;
			SystErr[1] = 0.0;
			StatErr[2] = 0.000018;
			SystErr[2] = 0.0;
			break;
		}
		default:{
      cout << "PDF_Dmixing_K3pi::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
		}
	}
}

void PDF_Dmixing_K3pi::setCorrelations(config c)
{
  resetCorrelations();
  switch(c)
  {
    case lhcb2012:{
		corSource = "LHCb 2015 Preliminary";
		corStatMatrix[0][1] = 0.93;
		corStatMatrix[0][2] = 0.83;
		corStatMatrix[1][2] = 0.95;
		corStatMatrix[1][0] = 0.93;
		corStatMatrix[2][0] = 0.83;
		corStatMatrix[2][1] = 0.95;
		break;
      break;
		}
    default:{
      cout << "PDF_Dmixing_K3pi::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
		}
  }
}

void PDF_Dmixing_K3pi::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name,"pdf_"+name,*(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
