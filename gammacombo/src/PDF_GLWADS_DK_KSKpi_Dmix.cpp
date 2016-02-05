/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: July 2014
 *
 **/

#include "PDF_GLWADS_DK_KSKpi_Dmix.h"

PDF_GLWADS_DK_KSKpi_Dmix::PDF_GLWADS_DK_KSKpi_Dmix(config cObs, config cErr, config cCor, 
  double Mxy, ParametersAbs* pars, TString d)
: PDF_GLWADS_DK_KSKpi(cObs,cErr,cCor,pars,d)
{
  name = "glwads-dk-kskpi-dmix";
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


PDF_GLWADS_DK_KSKpi_Dmix::~PDF_GLWADS_DK_KSKpi_Dmix(){}


void PDF_GLWADS_DK_KSKpi_Dmix::initParameters()
{
  parameters->add(*(p->get("xD")));
  parameters->add(*(p->get("yD")));
}  


void PDF_GLWADS_DK_KSKpi_Dmix::initRelations()
{
  RooArgSet *p = (RooArgSet*)parameters;
  delete theory; theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  RooRealVar& rbk = *((RooRealVar*)p->find("r_dk"));
  RooRealVar& dbk = *((RooRealVar*)p->find("d_dk"));
  RooConstVar& kbk = RooConst(1);
  RooRealVar& kf  = *((RooRealVar*)p->find("kD_kskpi"));
  RooRealVar& rf  = *((RooRealVar*)p->find("rD_kskpi"));
  RooRealVar& df  = *((RooRealVar*)p->find("dD_kskpi"));
  RooRealVar& g   = *((RooRealVar*)p->find("g"));
  RooRealVar& xD  = *((RooRealVar*)p->find("xD"));
  RooRealVar& yD  = *((RooRealVar*)p->find("yD"));
  RooRealVar& Rcab = *((RooRealVar*)p->find("RBRdkdpi"));
  RooConstVar& AcpD = RooConst(0);
  
  // theory->add(*(new RooFormulaVar("rfavsup_dk_kskpi_th",  "rfavsup_dk_kskpi_th",  "(1 + r_dk^2*rD_kskpi^2  + 2*r_dk *rD_kskpi*kD_kskpi*cos(g)*cos(d_dk -dD_kskpi))/(r_dk^2 + rD_kskpi^2    + 2*r_dk *rD_kskpi*kD_kskpi*cos(g)*cos(d_dk +dD_kskpi))", *p)));  
  // theory->add(*(new RooFormulaVar("afav_dk_kskpi_th",     "afav_dk_kskpi_th",     "2*r_dk *rD_kskpi*kD_kskpi*sin(g)*sin(d_dk -dD_kskpi) / (1 + r_dk^2  * rD_kskpi^2 + 2*r_dk *rD_kskpi*kD_kskpi*cos(g)*cos(d_dk -dD_kskpi))", *p)));
  // theory->add(*(new RooFormulaVar("asup_dk_kskpi_th",     "asup_dk_kskpi_th",     "2*r_dk *rD_kskpi*kD_kskpi*sin(g)*sin(d_dk +dD_kskpi) / (r_dk^2  + rD_kskpi^2 + 2*r_dk *rD_kskpi*kD_kskpi*cos(g)*cos(d_dk +dD_kskpi))", *p)));
  
  theory->add(*(new RooGLWADSDmixRADSVar(  "rfavsup_dk_kskpi_th",  "RooGLWADSDmixRADSVar (inverse)", rbk, dbk, kbk, rf, df, kf, g, xD, yD, _Mxy, "inverse")));
  theory->add(*(new RooGLWADSDmixAcpVar(   "afav_dk_kskpi_th",     "RooGLWADSDmixAcpVar",    rbk, dbk, kbk, rf, df, kf, g, xD, yD, _Mxy, AcpD)));
  theory->add(*(new RooGLWADSDmixAcpADSVar("asup_dk_kskpi_th",     "RooGLWADSDmixAcpADSVar", rbk, dbk, kbk, rf, df, kf, g, xD, yD, _Mxy, AcpD)));
}
