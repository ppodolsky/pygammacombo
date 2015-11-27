/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Jun 2014
 *
 **/

#include "PDF_GLWADS_DKstz_hh_Dmix.h"

PDF_GLWADS_DKstz_hh_Dmix::PDF_GLWADS_DKstz_hh_Dmix(config cObs, config cErr, config cCor, 
  double Mxy, ParametersAbs* pars, TString d)
: PDF_GLWADS_DKstz_hh(cObs,cErr,cCor,pars,d)
{
  name = "glwads-dkstz-hh-dmix";
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


PDF_GLWADS_DKstz_hh_Dmix::~PDF_GLWADS_DKstz_hh_Dmix(){}


void PDF_GLWADS_DKstz_hh_Dmix::initParameters()
{
  parameters->add(*(p->get("xD")));
  parameters->add(*(p->get("yD")));
}  


void PDF_GLWADS_DKstz_hh_Dmix::initRelations()
{
  RooArgSet *p = (RooArgSet*)parameters;
  delete theory; theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  RooRealVar&  rbk    = *((RooRealVar*)p->find("r_dkstz"));
  RooRealVar&  dbk    = *((RooRealVar*)p->find("d_dkstz"));
  RooRealVar&  kbk    = *((RooRealVar*)p->find("k_dkstz"));
  RooRealVar&  rf     = *((RooRealVar*)p->find("rD_kpi"));
  RooRealVar&  df     = *((RooRealVar*)p->find("dD_kpi"));
  RooConstVar& kf     = RooConst(1);
  RooRealVar&  g      = *((RooRealVar*)p->find("g"));
  RooRealVar&  xD     = *((RooRealVar*)p->find("xD"));
  RooRealVar&  yD     = *((RooRealVar*)p->find("yD"));
  RooRealVar&  AcpDKK = *((RooRealVar*)p->find("AcpDKK"));
  RooRealVar&  AcpDpp = *((RooRealVar*)p->find("AcpDpipi"));
  RooConstVar& AcpD   = RooConst(0);
  RooConstVar& rfCP   = RooConst(1);
  RooConstVar& dfCP   = RooConst(0);
    
  // theory->add(*(new RooFormulaVar("acp_dkstz_kk_th",    "acp_dkstz_kk",    "2*k_dkstz*r_dkstz *sin(d_dkstz) *sin(g) / (1 + r_dkstz^2  + 2*k_dkstz*r_dkstz *cos(d_dkstz) *cos(g)) + AcpDKK", *p)));
  // theory->add(*(new RooFormulaVar("afav_dkstz_kpi_th",  "afav_dkstz_kpi",  "2*k_dkstz*r_dkstz*rD_kpi *sin(d_dkstz-dD_kpi) *sin(g) / (1 + r_dkstz^2*rD_kpi^2  + 2*k_dkstz*r_dkstz*rD_kpi *cos(d_dkstz-dD_kpi) *cos(g))", *p)));
  // theory->add(*(new RooFormulaVar("rcp_dkstz_kk_th",    "rcp_dkstz_kk",    "(1 + r_dkstz^2  + 2*k_dkstz*r_dkstz *cos(d_dkstz) *cos(g))/(1 + r_dkstz^2*rD_kpi^2  + 2*k_dkstz*r_dkstz*rD_kpi *cos(d_dkstz-dD_kpi) *cos(g))", *p)));
  // theory->add(*(new RooFormulaVar("acp_dkstz_pipi_th",  "acp_dkstz_pipi",  "2*k_dkstz*r_dkstz *sin(d_dkstz) *sin(g) / (1 + r_dkstz^2  + 2*k_dkstz*r_dkstz *cos(d_dkstz) *cos(g)) + AcpDpipi", *p)));
  // theory->add(*(new RooFormulaVar("rcp_dkstz_pipi_th",  "rcp_dkstz_pipi",  "(1 + r_dkstz^2  + 2*k_dkstz*r_dkstz *cos(d_dkstz) *cos(g))/(1 + r_dkstz^2*rD_kpi^2  + 2*k_dkstz*r_dkstz*rD_kpi *cos(d_dkstz-dD_kpi) *cos(g))", *p)));
  // theory->add(*(new RooFormulaVar("rp_dkstz_th",        "rp_dkstz_th",     "(r_dkstz^2  + rD_kpi^2 + 2*k_dkstz *r_dkstz *rD_kpi*cos( g+d_dkstz +dD_kpi)) / (1 + r_dkstz^2 *rD_kpi^2 + 2*k_dkstz *r_dkstz *rD_kpi*cos( g +d_dkstz -dD_kpi))", *p)));
  // theory->add(*(new RooFormulaVar("rm_dkstz_th",        "rm_dkstz_th",     "(r_dkstz^2  + rD_kpi^2 + 2*k_dkstz *r_dkstz *rD_kpi*cos(-g+d_dkstz +dD_kpi)) / (1 + r_dkstz^2 *rD_kpi^2 + 2*k_dkstz *r_dkstz *rD_kpi*cos(-g +d_dkstz -dD_kpi))", *p)));
  
  theory->add(*(new RooGLWADSDmixAcpVar("acp_dkstz_kk_th",   "RooGLWADSDmixAcpVar", rbk,  dbk, kbk, rfCP, dfCP, kf, g, xD, yD, _Mxy, AcpDKK)));
  theory->add(*(new RooGLWADSDmixAcpVar("afav_dkstz_kpi_th", "RooGLWADSDmixAcpVar", rbk,  dbk, kbk, rf,   df,   kf, g, xD, yD, _Mxy, AcpD)));
  theory->add(*(new RooGLWADSDmixRcpVar("rcp_dkstz_kk_th",   "RooGLWADSDmixRcpVar", rbk,  dbk, kbk, rf,   df,   kf, g, xD, yD, _Mxy)));
  theory->add(*(new RooGLWADSDmixAcpVar("acp_dkstz_pipi_th", "RooGLWADSDmixAcpVar", rbk,  dbk, kbk, rfCP, dfCP, kf, g, xD, yD, _Mxy, AcpDpp)));
  theory->add(*(new RooGLWADSDmixRcpVar("rcp_dkstz_pipi_th", "RooGLWADSDmixRcpVar", rbk,  dbk, kbk, rf,   df,   kf, g, xD, yD, _Mxy)));
  theory->add(*(new RooGLWADSDmixRpmVar("rp_dkstz_th",       "RooGLWADSDmixRpmVar", rbk,  dbk, kbk, rf,   df,   kf, g, xD, yD, _Mxy, "+")));
  theory->add(*(new RooGLWADSDmixRpmVar("rm_dkstz_th",       "RooGLWADSDmixRpmVar", rbk,  dbk, kbk, rf,   df,   kf, g, xD, yD, _Mxy, "-")));
}
