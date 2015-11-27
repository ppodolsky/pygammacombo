/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Set 2014
 *
 **/

#include "PDF_D_KstK_DCPV.h"

PDF_D_KstK_DCPV::PDF_D_KstK_DCPV(config cObs, config cErr, config cCor)
: PDF_Abs(2)
{
  name = "DKstKDCPV";
  initParameters();
  initRelations();
  initObservables();
  setObservables(cObs);
  setUncertainties(cErr);
  setCorrelations(cCor);
  buildCov();
  buildPdf();
}


PDF_D_KstK_DCPV::~PDF_D_KstK_DCPV(){}


void PDF_D_KstK_DCPV::initParameters()
{
  ParametersGammaCombo p;
  parameters = new RooArgList("parameters");
  parameters->add(*(p.get("AcpDzKstpKm")));
  parameters->add(*(p.get("AcpDzKstmKp")));
}  


void PDF_D_KstK_DCPV::initRelations()
{
  RooArgSet *p = (RooArgSet*)parameters;
  theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  theory->add(*(new RooFormulaVar("AcpDzKstpKm_th", "AcpDzKstpKm_th", "AcpDzKstpKm", *p)));
  theory->add(*(new RooFormulaVar("AcpDzKstmKp_th", "AcpDzKstmKp_th", "AcpDzKstmKp", *p)));
}


void PDF_D_KstK_DCPV::initObservables()
{
  observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("AcpDzKstpKm_obs", "AcpDKst+K-",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("AcpDzKstmKp_obs", "AcpDKst-K+",  0, -1e4, 1e4)));
}


void PDF_D_KstK_DCPV::setObservables(config c)
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
    case babar2008:{
      // obsValSource = "Babar 2008 0802.4035: Tab2, col5/(2*col2) (different sign than PDG)";
			obsValSource = "Babar 2008 0802.4035: Tab2, -col5/(2*col2)";
      setObservable("AcpDzKstpKm_obs",-0.009);
      setObservable("AcpDzKstmKp_obs",-0.053);
      break;
    }
    default:{
      cout << "PDF_D_KstK_DCPV::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
    }
  }
}


void PDF_D_KstK_DCPV::setUncertainties(config c)
{
  switch(c)
  {
    case babar2008:{
      obsErrSource = "Babar 2008 0802.4035";
      StatErr[0] = 0.013;
      StatErr[1] = 0.043;
      SystErr[0] = 0.0;
      SystErr[1] = 0.0;
      break;
    }
    default:{ 
      cout << "PDF_D_KstK_DCPV::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
    }
  }
}


void PDF_D_KstK_DCPV::setCorrelations(config c)
{
  resetCorrelations();
  switch(c)
  {
    case babar2008:{
      corSource = "Babar 2008 0802.4035";
      corStatMatrix[1][0] = 0.0;
      corSystMatrix[1][0] = 0.0;
      break;
    }
    default:{
      cout << "PDF_D_KstK_DCPV::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
    }    
  }
}  


void PDF_D_KstK_DCPV::buildPdf()
{
  pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
