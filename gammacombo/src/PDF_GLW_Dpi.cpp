/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#include "PDF_GLW_Dpi.h"

PDF_GLW_Dpi::PDF_GLW_Dpi(config cObs, config cErr, config cCor)
: PDF_Abs(2)
{
  name = "glwdpi";
  initParameters();
  initRelations();
  initObservables();
  setObservables(cObs);
  setUncertainties(cErr);
  setCorrelations(cCor);
  buildCov();
  buildPdf();
}


PDF_GLW_Dpi::~PDF_GLW_Dpi(){}


void PDF_GLW_Dpi::initParameters()
{
  ParametersGammaCombo p;
  parameters = new RooArgList("parameters");
  parameters->add(*(p.get("r_dpi"))); 
  parameters->add(*(p.get("d_dpi"))); 
  parameters->add(*(p.get("g")));
}


void PDF_GLW_Dpi::initRelations()
{
  theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	theory->add(*(new RooFormulaVar("acpp_dpi_kk_th", "Acp+ (KK, D#pi GLW)", "2.*r_dpi*sin(d_dpi)*sin(g)/(1. + r_dpi^2 + 2.*r_dpi*cos(d_dpi)*cos(g))", *(RooArgSet*)parameters)));
	theory->add(*(new RooFormulaVar("acpp_dpi_pipi_th", "Acp+ (#pi#pi, D#pi GLW)", "2.*r_dpi*sin(d_dpi)*sin(g)/(1. + r_dpi^2 + 2.*r_dpi*cos(d_dpi)*cos(g))", *(RooArgSet*)parameters)));
}


void PDF_GLW_Dpi::initObservables()
{
  observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("acpp_dpi_kk_obs", "Acp+ (KK, D#pi GLW)",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acpp_dpi_pipi_obs", "Acp+ (#pi#pi, D#pi GLW)",  0, -1e4, 1e4)));
}


void PDF_GLW_Dpi::setObservables(config c)
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
      obsValSource = "1fb-1 paper LHCb-PAPER-2012-001";
      setObservable("acpp_dpi_kk_obs",-0.020);
      setObservable("acpp_dpi_pipi_obs",-0.001);
      break;
    default:
      cout << "PDF_GLW_DzKstz::setObservables : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
  }
}


void PDF_GLW_Dpi::setUncertainties(config c)
{
  switch(c)
  {
    case lumi1fb:
    {
      obsErrSource = "1fb-1 paper LHCb-PAPER-2012-001";
      StatErr[0] = 0.009; // acpp kk
      StatErr[1] = 0.017; // acpp pipi
      SystErr[0] = 0.012; // acpp kk
      SystErr[1] = 0.010; // acpp pipi
      break;
    }
    default: 
      cout << "PDF_GLW_Dpi::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
  }
}


void PDF_GLW_Dpi::setCorrelations(config c)
{
  resetCorrelations();
  switch(c)
  {
    case lumi1fb:
      // no correlations
      break;
    default: 
      cout << "PDF_GLW_Dpi::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);    
  }
}  


void PDF_GLW_Dpi::buildPdf()
{
  pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
