/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 * Combine the Dpi observables from the D->K3pi ADS measurement.
 *
 **/

#include "PDF_GLWADS_Dpi_K3pi.h"

PDF_GLWADS_Dpi_K3pi::PDF_GLWADS_Dpi_K3pi(config cObs, config cErr, config cCor, ParametersAbs* pars, TString d)
: PDF_GLWADS_DKDpi_K3pi(pars,d,3)
{
  name = "glwads-dpi-k3pi";
  this->dir = d;   
  initParameters();
  initRelations();
  initObservables();
  setObservables(cObs);
  setUncertainties(cErr);
  setCorrelations(cCor);
  buildCov();
  buildPdf();
}


PDF_GLWADS_Dpi_K3pi::~PDF_GLWADS_Dpi_K3pi(){}


void PDF_GLWADS_Dpi_K3pi::initParameters()
{
  parameters = new RooArgList("parameters");
  parameters->add(*(p->get("r_dpi"))); 
  parameters->add(*(p->get("d_dpi"))); 
  parameters->add(*(p->get("g")));
  parameters->add(*(p->get("rD_k3pi"))); 
  parameters->add(*(p->get("dD_k3pi"))); 
  parameters->add(*(p->get("kD_k3pi")));
}  


void PDF_GLWADS_Dpi_K3pi::initRelations()
{
  theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  RooArgSet *p = (RooArgSet*)parameters;
  theory->add(*(new RooFormulaVar("afav_dpi_k3pi_th", "afav_dpi_k3pi_th", "2*r_dpi*rD_k3pi*kD_k3pi*sin(g)*sin(d_dpi-dD_k3pi) / (1 + r_dpi^2 * rD_k3pi^2 + 2*r_dpi*rD_k3pi*kD_k3pi*cos(g)*cos(d_dpi-dD_k3pi))", *p)));
  theory->add(*(new RooFormulaVar("rp_dpi_k3pi_th",   "rp_dpi_k3pi_th",   "r_dpi^2 + rD_k3pi^2 + 2*r_dpi*rD_k3pi*kD_k3pi*cos( g+d_dpi+dD_k3pi)", *p)));
  theory->add(*(new RooFormulaVar("rm_dpi_k3pi_th",   "rm_dpi_k3pi_th",   "r_dpi^2 + rD_k3pi^2 + 2*r_dpi*rD_k3pi*kD_k3pi*cos(-g+d_dpi+dD_k3pi)", *p)));
}


void PDF_GLWADS_Dpi_K3pi::initObservables()
{
  observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
  observables->add(*(new RooRealVar("afav_dpi_k3pi_obs", "Afav (D#pi K3#pi)"  , 0, -1e4, 1e4)));
  observables->add(*(new RooRealVar("rp_dpi_k3pi_obs",   "R+ (D#pi K3#pi ADS)", 1, -1e4, 1e4)));
  observables->add(*(new RooRealVar("rm_dpi_k3pi_obs",   "R- (D#pi K3#pi ADS)", 1, -1e4, 1e4)));
}


void PDF_GLWADS_Dpi_K3pi::setUncertainties(config c)
{
  switch(c)
  {
    case lumi1fb:
    {
      obsErrSource = "1fb-1, ExpNll/sept2012K3PIResult.root";
      TString File = this->dir+"/ExpNll/sept2012K3PIResult.root";
      TFile *fr = TFile::Open(File);
      RooFitResult *r = (RooFitResult*)fr->Get("fitresult_model_reducedData_binned");
      assert(r);
      for ( int i=0; i<nObs; i++ )
      {
        RooRealVar* pObs = (RooRealVar*)((RooArgList*)observables)->at(i);
        RooRealVar* pRes = (RooRealVar*)r->floatParsFinal().find(obsTmkToMalcolm(pObs->GetName()));
        assert(pRes);
        StatErr[i] = pRes->getError();
      }    
      SystErr[0] = 0.010;   // afav_dpi_obs    
      SystErr[1] = 0.00011; // rp_dpi_obs      
      SystErr[2] = 0.00011; // rm_dpi_obs      
      fr->Close();
      delete r;
      delete fr;
      break;
    }
    default:
      cout << "PDF_GLWADS_Dpi_K3pi::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
  }
}
