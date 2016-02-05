//
//  PDF_D_KSKpi_RWS_noDmix.cpp
//
//
//  Created by Matthew Kenzie on 04/01/16.
//
//

#include "PDF_D_KSKpi_RWS_noDmix.h"

PDF_D_KSKpi_RWS_noDmix::PDF_D_KSKpi_RWS_noDmix(config cObs, config cErr, config cCor):
	PDF_Abs(1)
{
	name = "dkskpiRWS_noDmix";
  initParameters();
  initRelations();
  initObservables();
  setObservables(cObs);
  setUncertainties(cErr);
  setCorrelations(cCor);
  buildCov();
  buildPdf();

}

PDF_D_KSKpi_RWS_noDmix::~PDF_D_KSKpi_RWS_noDmix(){}

void PDF_D_KSKpi_RWS_noDmix::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
  parameters->add(*(p.get("rD_kskpi")));
	parameters->add(*(p.get("dD_kskpi")));
	parameters->add(*(p.get("kD_kskpi")));
}

void PDF_D_KSKpi_RWS_noDmix::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory");
	theory->add(*(new RooFormulaVar("RD_kskpi_th", "RD_kskpi_th", "rD_kskpi^2", *p)));
  //theory->add(*(new RooFormulaVar("kD_kskpi_th", "kD_kskpi_th", "kD_kskpi", *p)));
}

void PDF_D_KSKpi_RWS_noDmix::initObservables()
{
	observables = new RooArgList("observables");
	observables->add(*(new RooRealVar("RD_kskpi_obs", "RD (D#rightarrowK_{S}K#pi)",       0, -1e4, 1e4)));
  //observables->add(*(new RooRealVar("kD_kskpi_obs", "kD (D#rightarrowK_{S}K#pi)",       1.,-1e4, 1e4)));
}

void PDF_D_KSKpi_RWS_noDmix::setObservables(config c)
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
		case lhcb:{
			obsValSource = "arXiv:1509.06628";
			setObservable("RD_kskpi_obs",0.370);
      //setObservable("kD_kskpi_obs",0.571);
			break;
		}
		default:{
      cout << "PDF_D_KSKpi_RWS_noDmix::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
		}
	}
}

void PDF_D_KSKpi_RWS_noDmix::setUncertainties(config c)
{
	switch(c)
	{
		case lhcb:{
			obsErrSource = "arXiv:1509.06628";
			StatErr[0] = 0.003;
			SystErr[0] = 0.012;
			//StatErr[1] = 0.005;
			//SystErr[1] = 0.019;
			break;
		}
		default:{
      cout << "PDF_D_KSKpi_RWS_noDmix::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
		}
	}
}

void PDF_D_KSKpi_RWS_noDmix::setCorrelations(config c)
{
  resetCorrelations();
  switch(c)
  {
    case lhcb:{
			corSource = "no correlations";
      break;
		}
    default:{
      cout << "PDF_D_KSKpi_RWS_noDmix::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
		}
  }
}

void PDF_D_KSKpi_RWS_noDmix::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name,"pdf_"+name,*(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
