/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Dec 2013
 *
 **/

#include "PDF_GLWADS_Dhpipi_hh_Dmix.h"

PDF_GLWADS_Dhpipi_hh_Dmix::PDF_GLWADS_Dhpipi_hh_Dmix(config cObs, config cErr, config cCor, 
  double Mxy, ParametersAbs* pars, TString d)
: PDF_GLWADS_Dhpipi_hh(cObs,cErr,cCor,pars,d)
{
  name = "glwads-dhpipi-hh-dmix";
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


PDF_GLWADS_Dhpipi_hh_Dmix::~PDF_GLWADS_Dhpipi_hh_Dmix(){}


void PDF_GLWADS_Dhpipi_hh_Dmix::initParameters()
{
  parameters->add(*(p->get("xD")));
  parameters->add(*(p->get("yD")));
}  


void PDF_GLWADS_Dhpipi_hh_Dmix::initRelations()
{
  RooArgSet *p = (RooArgSet*)parameters;
  delete theory; theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  RooRealVar&  rbk    = *((RooRealVar*)p->find("r_dkpipi"));
  RooRealVar&  dbk    = *((RooRealVar*)p->find("d_dkpipi"));
  RooRealVar&  kbk    = *((RooRealVar*)p->find("k_dkpipi"));
  RooRealVar&  rbp    = *((RooRealVar*)p->find("r_dpipipi"));
  RooRealVar&  dbp    = *((RooRealVar*)p->find("d_dpipipi"));
  RooRealVar&  kbp    = *((RooRealVar*)p->find("k_dpipipi"));
  RooConstVar& kf     = RooConst(1);
  RooRealVar&  rf     = *((RooRealVar*)p->find("rD_kpi"));
  RooConstVar& rfGLW  = RooConst(1);
  RooConstVar& rfRCP  = RooConst(0);
  RooRealVar&  df     = *((RooRealVar*)p->find("dD_kpi"));
  RooConstVar& dfGLW  = RooConst(0);
  RooRealVar&  g      = *((RooRealVar*)p->find("g"));
  RooRealVar&  xD     = *((RooRealVar*)p->find("xD"));
  RooRealVar&  yD     = *((RooRealVar*)p->find("yD"));
  RooRealVar&  AcpDKK = *((RooRealVar*)p->find("AcpDKK"));
  RooRealVar&  AcpDpp = *((RooRealVar*)p->find("AcpDpipi"));
  RooConstVar& AcpD   = RooConst(0);
  
  // theory->add(*(new RooFormulaVar("rcp_dkpipi_th",       "rcp_dkpipi_th",       "1 + r_dkpipi^2 + 2*k_dkpipi*r_dkpipi*cos(d_dkpipi)*cos(g)", *p)));
  // theory->add(*(new RooFormulaVar("afav_dkpipi_kpi_th",  "afav_dkpipi_kpi_th",  "2*k_dkpipi *r_dkpipi *rD_kpi*sin(g)*sin(d_dkpipi -dD_kpi) / (1 + r_dkpipi^2  * rD_kpi^2 + 2*k_dkpipi *r_dkpipi *rD_kpi*cos(g)*cos(d_dkpipi -dD_kpi))", *p)));
  // theory->add(*(new RooFormulaVar("afav_dpipipi_kpi_th", "afav_dpipipi_kpi_th", "2*k_dpipipi*r_dpipipi*rD_kpi*sin(g)*sin(d_dpipipi-dD_kpi) / (1 + r_dpipipi^2 * rD_kpi^2 + 2*k_dpipipi*r_dpipipi*rD_kpi*cos(g)*cos(d_dpipipi-dD_kpi))", *p)));
  // theory->add(*(new RooFormulaVar("acp_dkpipi_kk_th",    "acp_dkpipi_kk_th",    "2*k_dkpipi *r_dkpipi *sin(d_dkpipi) *sin(g) / (1 + r_dkpipi^2  + 2*k_dkpipi *r_dkpipi *cos(d_dkpipi) *cos(g)) + AcpDKK", *p)));
  // theory->add(*(new RooFormulaVar("acp_dkpipi_pipi_th",  "acp_dkpipi_pipi_th",  "2*k_dkpipi *r_dkpipi *sin(d_dkpipi) *sin(g) / (1 + r_dkpipi^2  + 2*k_dkpipi *r_dkpipi *cos(d_dkpipi) *cos(g)) + AcpDpipi", *p)));
  // theory->add(*(new RooFormulaVar("acp_dpipipi_kk_th",   "acp_dpipipi_kk_th",   "2*k_dpipipi*r_dpipipi*sin(d_dpipipi)*sin(g) / (1 + r_dpipipi^2 + 2*k_dpipipi*r_dpipipi*cos(d_dpipipi)*cos(g)) + AcpDKK", *p)));
  // theory->add(*(new RooFormulaVar("acp_dpipipi_pipi_th", "acp_dpipipi_pipi_th", "2*k_dpipipi*r_dpipipi*sin(d_dpipipi)*sin(g) / (1 + r_dpipipi^2 + 2*k_dpipipi*r_dpipipi*cos(d_dpipipi)*cos(g)) + AcpDpipi", *p)));
  // theory->add(*(new RooFormulaVar("rp_dkpipi_th",        "rp_dkpipi_th",        "(r_dkpipi^2  + rD_kpi^2 + 2*k_dkpipi *r_dkpipi *rD_kpi*cos( g+d_dkpipi +dD_kpi)) / (1 + r_dkpipi^2 *rD_kpi^2 + 2*k_dkpipi *r_dkpipi *rD_kpi*cos( g +d_dkpipi -dD_kpi))", *p)));
  // theory->add(*(new RooFormulaVar("rm_dkpipi_th",        "rm_dkpipi_th",        "(r_dkpipi^2  + rD_kpi^2 + 2*k_dkpipi *r_dkpipi *rD_kpi*cos(-g+d_dkpipi +dD_kpi)) / (1 + r_dkpipi^2 *rD_kpi^2 + 2*k_dkpipi *r_dkpipi *rD_kpi*cos(-g +d_dkpipi -dD_kpi))", *p)));
  // theory->add(*(new RooFormulaVar("rp_dpipipi_th",       "rp_dpipipi_th",       "(r_dpipipi^2 + rD_kpi^2 + 2*k_dpipipi*r_dpipipi*rD_kpi*cos( g+d_dpipipi+dD_kpi)) / (1 + r_dpipipi^2*rD_kpi^2 + 2*k_dpipipi*r_dpipipi*rD_kpi*cos( g +d_dpipipi-dD_kpi))", *p)));
  // theory->add(*(new RooFormulaVar("rm_dpipipi_th",       "rm_dpipipi_th",       "(r_dpipipi^2 + rD_kpi^2 + 2*k_dpipipi*r_dpipipi*rD_kpi*cos(-g+d_dpipipi+dD_kpi)) / (1 + r_dpipipi^2*rD_kpi^2 + 2*k_dpipipi*r_dpipipi*rD_kpi*cos(-g +d_dpipipi-dD_kpi))", *p)));

  theory->add(*(new RooGLWADSDmixRcpVar("rcp_dkpipi_th",       "RooGLWADSDmixRcpVar", rbk,  dbk, kbk, rfRCP, dfGLW, kf, g, xD, yD, _Mxy)));
  theory->add(*(new RooGLWADSDmixAcpVar("afav_dkpipi_kpi_th",  "RooGLWADSDmixAcpVar", rbk,  dbk, kbk, rf,    df,    kf, g, xD, yD, _Mxy, AcpD)));
  theory->add(*(new RooGLWADSDmixAcpVar("afav_dpipipi_kpi_th", "RooGLWADSDmixAcpVar", rbp,  dbp, kbp, rf,    df,    kf, g, xD, yD, _Mxy, AcpD)));
  theory->add(*(new RooGLWADSDmixAcpVar("acp_dkpipi_kk_th",    "RooGLWADSDmixAcpVar", rbk,  dbk, kbk, rfGLW, dfGLW, kf, g, xD, yD, _Mxy, AcpDKK)));
  theory->add(*(new RooGLWADSDmixAcpVar("acp_dkpipi_pipi_th",  "RooGLWADSDmixAcpVar", rbk,  dbk, kbk, rfGLW, dfGLW, kf, g, xD, yD, _Mxy, AcpDpp)));
  theory->add(*(new RooGLWADSDmixAcpVar("acp_dpipipi_kk_th",   "RooGLWADSDmixAcpVar", rbp,  dbp, kbp, rfGLW, dfGLW, kf, g, xD, yD, _Mxy, AcpDKK)));
  theory->add(*(new RooGLWADSDmixAcpVar("acp_dpipipi_pipi_th", "RooGLWADSDmixAcpVar", rbp,  dbp, kbp, rfGLW, dfGLW, kf, g, xD, yD, _Mxy, AcpDpp)));
  theory->add(*(new RooGLWADSDmixRpmVar("rp_dkpipi_th",        "RooGLWADSDmixRpmVar", rbk,  dbk, kbk, rf,    df,    kf, g, xD, yD, _Mxy, "+")));
  theory->add(*(new RooGLWADSDmixRpmVar("rm_dkpipi_th",        "RooGLWADSDmixRpmVar", rbk,  dbk, kbk, rf,    df,    kf, g, xD, yD, _Mxy, "-")));
  theory->add(*(new RooGLWADSDmixRpmVar("rp_dpipipi_th",       "RooGLWADSDmixRpmVar", rbp,  dbp, kbp, rf,    df,    kf, g, xD, yD, _Mxy, "+")));
  theory->add(*(new RooGLWADSDmixRpmVar("rm_dpipipi_th",       "RooGLWADSDmixRpmVar", rbp,  dbp, kbp, rf,    df,    kf, g, xD, yD, _Mxy, "-")));
}
