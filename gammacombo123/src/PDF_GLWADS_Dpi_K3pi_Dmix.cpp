/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 * Combine the Dpi observables from the D->K3pi ADS measurement.
 *
 **/

#include "PDF_GLWADS_Dpi_K3pi_Dmix.h"

PDF_GLWADS_Dpi_K3pi_Dmix::PDF_GLWADS_Dpi_K3pi_Dmix(config cObs, config cErr, config cCor, 
  double Mxy, ParametersAbs* pars, TString d)
: PDF_GLWADS_Dpi_K3pi(cObs,cErr,cCor,pars,d)
{
  name = "glwads-dpi-k3pi-dmix";
  _Mxy = Mxy;
  initParameters();
  initRelations();
  // initObservables();
  // setObservables(cObs);
  // setUncertainties(cErr);
  // setCorrelations(cCor);
  // buildCov();
	delete pdf; // it was built already by the super class constructor
  buildPdf();
}


PDF_GLWADS_Dpi_K3pi_Dmix::~PDF_GLWADS_Dpi_K3pi_Dmix(){}


void PDF_GLWADS_Dpi_K3pi_Dmix::initParameters()
{
  parameters->add(*(p->get("xD")));
  parameters->add(*(p->get("yD")));
}  


void PDF_GLWADS_Dpi_K3pi_Dmix::initRelations()
{
  RooArgSet *p = (RooArgSet*)parameters;
  delete theory; theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  RooRealVar& rbp = *((RooRealVar*)p->find("r_dpi"));
  RooRealVar& dbp = *((RooRealVar*)p->find("d_dpi"));
  RooConstVar& kbp = RooConst(1);
  RooRealVar& kf  = *((RooRealVar*)p->find("kD_k3pi"));
  RooRealVar& rf  = *((RooRealVar*)p->find("rD_k3pi"));
  RooRealVar& df  = *((RooRealVar*)p->find("dD_k3pi"));
  RooRealVar& g   = *((RooRealVar*)p->find("g"));
  RooRealVar& xD  = *((RooRealVar*)p->find("xD"));
  RooRealVar& yD  = *((RooRealVar*)p->find("yD"));
  RooConstVar& AcpD = RooConst(0);
  theory->add(*(new RooGLWADSDmixAcpVar("afav_dpi_k3pi_th", "RooGLWADSDmixAcpVar", rbp, dbp, kbp, rf, df, kf, g, xD, yD, _Mxy, AcpD)));
  theory->add(*(new RooGLWADSDmixRpmVar("rp_dpi_k3pi_th",   "RooGLWADSDmixRpmVar", rbp, dbp, kbp, rf, df, kf, g, xD, yD, _Mxy, "+")));
  theory->add(*(new RooGLWADSDmixRpmVar("rm_dpi_k3pi_th",   "RooGLWADSDmixRpmVar", rbp, dbp, kbp, rf, df, kf, g, xD, yD, _Mxy, "-")));
}
