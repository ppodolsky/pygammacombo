//
//  PDF_D_KSKpi_RWS.cpp
//
//
//  Created by Matthew Kenzie on 04/01/16.
//
//

#include "PDF_D_KSKpi_RWS.h"

PDF_D_KSKpi_RWS::PDF_D_KSKpi_RWS(config cObs, config cErr, config cCor):
	PDF_Abs(1)
{
	name = "dkskpiRWS";
  initParameters();
  initRelations();
  initObservables();
  setObservables(cObs);
  setUncertainties(cErr);
  setCorrelations(cCor);
  buildCov();
  buildPdf();

}

PDF_D_KSKpi_RWS::~PDF_D_KSKpi_RWS(){}

void PDF_D_KSKpi_RWS::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
  parameters->add(*(p.get("rD_kskpi")));
	parameters->add(*(p.get("dD_kskpi")));
	parameters->add(*(p.get("kD_kskpi")));
	parameters->add(*(p.get("xD")));
	parameters->add(*(p.get("yD")));
}

void PDF_D_KSKpi_RWS::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory");
	theory->add(*(new RooFormulaVar("RD_kskpi_th", "RD_kskpi_th", "( rD_kskpi^2 - kD_kskpi*rD_kskpi*(yD*cos(dD_kskpi)-xD*sin(dD_kskpi)) ) / ( 1 - rD_kskpi*kD_kskpi*(yD*cos(dD_kskpi)+xD*sin(dD_kskpi)) ) ", *p)));
  //theory->add(*(new RooFormulaVar("kD_kskpi_th", "kD_kskpi_th", "kD_kskpi", *p)));
}

void PDF_D_KSKpi_RWS::initObservables()
{
	observables = new RooArgList("observables");
	observables->add(*(new RooRealVar("RD_kskpi_obs", "RD (D#rightarrowK_{S}K#pi)",       0, -1e4, 1e4)));
  //observables->add(*(new RooRealVar("kD_kskpi_obs", "kD (D#rightarrowK_{S}K#pi)",       1.,-1e4, 1e4)));
}

void PDF_D_KSKpi_RWS::setObservables(config c)
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
      cout << "PDF_D_KSKpi_RWS::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
		}
	}
}

void PDF_D_KSKpi_RWS::setUncertainties(config c)
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
      cout << "PDF_D_KSKpi_RWS::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
		}
	}
}

void PDF_D_KSKpi_RWS::setCorrelations(config c)
{
  resetCorrelations();
  switch(c)
  {
    case lhcb:{
			corSource = "no correlations";
      break;
		}
    default:{
      cout << "PDF_D_KSKpi_RWS::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
		}
  }
}

void PDF_D_KSKpi_RWS::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name,"pdf_"+name,*(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
