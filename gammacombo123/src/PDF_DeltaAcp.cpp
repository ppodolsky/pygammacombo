/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#include "PDF_DeltaAcp.h"

PDF_DeltaAcp::PDF_DeltaAcp(config cObs)
: PDF_Abs(1)
{
  name = "deltaAcp";
  initParameters();
  initRelations();
  initObservables();
  setObservables(cObs);
  setUncertainties(hfag);
  setCorrelations(hfag);
  buildCov();
  buildPdf();
}


PDF_DeltaAcp::~PDF_DeltaAcp(){}


void PDF_DeltaAcp::initParameters()
{
  ParametersGammaCombo p;
  parameters = new RooArgList("parameters");
  parameters->add(*(p.get("AcpDKK"))); 
  parameters->add(*(p.get("AcpDpipi")));
}


void PDF_DeltaAcp::initRelations()
{
  theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  theory->add(*(new RooFormulaVar("deltaAcp_th", "deltaAcp_th", "AcpDKK-AcpDpipi", *(RooArgSet*)parameters)));
}


void PDF_DeltaAcp::initObservables()
{
  observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("deltaAcp_obs", "#Deltaa_{CP}^{dir}",  0, -1e4, 1e4)));
}


void PDF_DeltaAcp::setObservables(config c)
{
  switch(c)
  {
    case truth:
    {
      setObservablesTruth();
      break;
    }
    case toy:
    { 
      setObservablesToy();
      break;
    }
    case lumi1fb:
    {
      obsValSource = "private communication";
      setObservable("deltaAcp_obs",-0.645/100.);
      break;
    }
    case lumi1fbsl:
    {
      obsValSource = "arXiv:1303.2614";
      setObservable("deltaAcp_obs",0.49/100.);
      break;
    }
    case hfag:
    {
      obsValSource = "HFAG (arXiv:1207.1158)";
      setObservable("deltaAcp_obs",-0.656/100.);
      break;
    }
    case zero:
    {
      obsValSource = "zero";
      setObservable("deltaAcp_obs",0/100.);
      break;
    }
    default:
    {
      cout << "PDF_DeltaAcp::setObservables() : ERROR : config not found: " << ConfigToTString(c) << endl;
      exit(1);
    }
  }
}


void PDF_DeltaAcp::setUncertainties(config c)
{
  switch(c)
  {
    case lumi1fb:
    {
      obsErrSource = "private communication";
      StatErr[0] = 0.180/100; // deltaAcp
      SystErr[0] = 0; // deltaAcp
      break;
    }
    case lumi1fbsl:
    {
      obsErrSource = "arXiv:1303.2614";
      StatErr[0] = 0.30/100; // deltaAcp
      SystErr[0] = 0.14/100; // deltaAcp
      break;
    }
    case hfag:
    {
      obsErrSource = "HFAG (arXiv:1207.1158)";
      StatErr[0] = 0.154/100.;  // deltaAcp
      SystErr[0] = 0;           // deltaAcp
      break;
    }
    case zero:
    {
      obsErrSource = "zero";
      StatErr[0] = 0.001/100; // deltaAcp
      SystErr[0] = 0; // deltaAcp
      break;
    }
    default:
    {
      cout << "PDF_DeltaAcp::setUncertainties() : ERROR : config not found: " << ConfigToTString(c) << endl;
      exit(1);
    }
  }
}


void PDF_DeltaAcp::setCorrelations(config c)
{
  resetCorrelations();
  // no correlation for 1 observable
}  


void PDF_DeltaAcp::buildPdf()
{
  pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
