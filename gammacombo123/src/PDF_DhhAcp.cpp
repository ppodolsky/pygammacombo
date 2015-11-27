/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: December 2012
 *
 **/

#include "PDF_DhhAcp.h"

PDF_DhhAcp::PDF_DhhAcp(config cObs, ParametersAbs* pars)
: PDF_Abs(2)
{
  if ( pars ) p = pars;
  else p = new ParametersGammaCombo();
  name = "DhhAcp";
  initParameters();
  initRelations();
  initObservables();
  setObservables(cObs);
  setUncertainties(hfag);
  setCorrelations(hfag);
  buildCov();
  buildPdf();
}


PDF_DhhAcp::~PDF_DhhAcp(){}


void PDF_DhhAcp::initParameters()
{
  parameters = new RooArgList("parameters");
  parameters->add(*(p->get("AcpDKK"))); 
  parameters->add(*(p->get("AcpDpipi")));
}


void PDF_DhhAcp::initRelations()
{
  RooArgSet *p = (RooArgSet*)parameters;
  theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  theory->add(*(new RooFormulaVar("AcpDKK_th", "AcpDKK_th", "AcpDKK", *p)));
  theory->add(*(new RooFormulaVar("AcpDpipi_th", "AcpDpipi_th", "AcpDpipi", *p)));
}


void PDF_DhhAcp::initObservables()
{
  observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("AcpDKK_obs", "Acp(D#rightarrowKK)",       0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("AcpDpipi_obs", "Acp(D#rightarrow#pi#pi)",  0, -1e4, 1e4)));
}


void PDF_DhhAcp::setObservables(config c)
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
    case hfag:{
      obsValSource = "March 12 http://www.slac.stanford.edu/xorg/hfag/charm/March12/results_mix+cpv.html";
      setObservable("AcpDKK_obs",-0.0031);
      setObservable("AcpDpipi_obs",+0.0036);
      break;
    }
    case zero:{
      obsValSource = "zero";
      setObservable("AcpDKK_obs",0.);
      setObservable("AcpDpipi_obs",0.);
      break;
    }
    default:{
      cout << "PDF_Dmixing::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
    } 
  }
}


void PDF_DhhAcp::setUncertainties(config c)
{
  switch(c)
  {
    case hfag:{
      obsErrSource = "March 12 http://www.slac.stanford.edu/xorg/hfag/charm/March12/results_mix+cpv.html";
      StatErr[0] = 0.0024; // AcpDKK_obs
      StatErr[1] = 0.0025; // AcpDpipi_obs
      SystErr[0] = 0;      // AcpDKK_obs
      SystErr[1] = 0;      // AcpDpipi_obs
      break;
    }
    case zero:{
      obsErrSource = "zero";
      StatErr[0] = 0.0001; // AcpDKK_obs
      StatErr[1] = 0.0;    // AcpDpipi_obs
      SystErr[0] = 0.0001; // AcpDKK_obs
      SystErr[1] = 0;      // AcpDpipi_obs
      break;
    }
    default:{
      cout << "PDF_DhhAcp::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
    }
  }
}


void PDF_DhhAcp::setCorrelations(config c)
{
  resetCorrelations();
  switch(c)
  {
    case hfag:{
      corSource = "March 12 http://www.slac.stanford.edu/xorg/hfag/charm/March12/results_mix+cpv.html";
      corStatMatrix[1][0] = 0.798;
      corSystMatrix[1][0] = 0.;
      break;
    }
    default:{
      cout << "PDF_DhhAcp::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
    }
  }
}  


void PDF_DhhAcp::buildPdf()
{
  pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
