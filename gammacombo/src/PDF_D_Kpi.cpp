/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#include "PDF_D_Kpi.h"

PDF_D_Kpi::PDF_D_Kpi(config cObs, config cErr, config cCor)
: PDF_Abs(2)
{
  name = "dkpi";
  initParameters();
  initRelations();
  initObservables();
  setObservables(cObs);
  setUncertainties(cErr);
  setCorrelations(cCor);
  buildCov();
  buildPdf();
}


PDF_D_Kpi::~PDF_D_Kpi(){}


void PDF_D_Kpi::initParameters()
{
  ParametersGammaCombo p;
  parameters = new RooArgList("parameters");
  parameters->add(*(p.get("rD_kpi"))); 
  parameters->add(*(p.get("dD_kpi")));
}  


void PDF_D_Kpi::initRelations()
{
  RooArgSet *p = (RooArgSet*)parameters;
  theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  theory->add(*(new RooFormulaVar("RD_kpi_th", "RD_kpi_th", "rD_kpi^2", *p)));
  theory->add(*(new RooFormulaVar("dD_kpi_th", "dD_kpi_th", "dD_kpi", *p)));
}


void PDF_D_Kpi::initObservables()
{
  observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("RD_kpi_obs", "RD (D#rightarrowK#pi)",       0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("dD_kpi_obs", "#deltaD (D#rightarrowK#pi)",  0, -1e4, 1e4)));
}


void PDF_D_Kpi::setObservables(config c)
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
    case hfagLP2011:{
      obsValSource = "HFAG LP2011 http://www.slac.stanford.edu/xorg/hfag/charm/LP11/results_mix+cpv.html";
      setObservable("RD_kpi_obs",0.003311);
      setObservable("dD_kpi_obs",DegToRad(22.4 + 180.0));
      // setObservable("RD_kpi_obs",0.00372);   // hunt down 2nd minimum
      // setObservable("dD_kpi_obs",DegToRad(26.4 + 180.0)); // hunt down 2nd minimum
      break;
    }
    case hfagFP2014:{
      obsValSource = "HFAG FP2014 http://www.slac.stanford.edu/xorg/hfag/charm/FPCP14/results_mix+cpv.html";
      setObservable("rD_kpi_obs",0.00349);
      setObservable("dD_kpi_obs",DegToRad(7.3 + 180.0));
      break;
    }
    default:{
      cout << "PDF_D_Kpi::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
    }
  }
}


void PDF_D_Kpi::setUncertainties(config c)
{
  switch(c)
  {
    case hfagLP2011:{
      obsErrSource = "HFAG LP2011 http://www.slac.stanford.edu/xorg/hfag/charm/LP11/results_mix+cpv.html";
      StatErr[0] = 0.000081; // RD 
      StatErr[1] = DegToRad(11); // dD
      // StatErr[0] = 0.000075; // RD   // hunt down 2nd minimum
      // StatErr[1] = DegToRad(8.8); // dD  // hunt down 2nd minimum
      SystErr[0] = 0.0; // RD
      SystErr[1] = 0.0; // dD
      break;
    }
    case hfagFP2014:{
      obsErrSource = "HFAG FP2014 http://www.slac.stanford.edu/xorg/hfag/charm/FPCP14/results_mix+cpv.html";
      StatErr[0] = 0.00004; // RD
      StatErr[1] = DegToRad(11.5); // dD
      SystErr[0] = 0.0; // RD
      SystErr[1] = 0.0; // dD
      break;
    }
    default:{ 
      cout << "PDF_D_Kpi::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
    }
  }
}


void PDF_D_Kpi::setCorrelations(config c)
{
  resetCorrelations();
  switch(c)
  {
    case hfagLP2011:{
      corSource = "HFAG LP2011 http://www.slac.stanford.edu/xorg/hfag/charm/LP11/results_mix+cpv.html";
      corStatMatrix[1][0] = 0.394;
      // corStatMatrix[1][0] = 0.0; // hunt down 2nd minimum
      corSystMatrix[1][0] = 0.0;
      break;
    }
    case hfagFP2014:{
      corSource = "HFAG FP2014 http://www.slac.stanford.edu/xorg/hfag/charm/FPCP14/results_mix+cpv.html";
      corStatMatrix[1][0] = 0.404;
      corSystMatrix[1][0] = 0.0;
      break;
    }
    default:{
      cout << "PDF_D_Kpi::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
    }    
  }
}  


void PDF_D_Kpi::buildPdf()
{
  pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
