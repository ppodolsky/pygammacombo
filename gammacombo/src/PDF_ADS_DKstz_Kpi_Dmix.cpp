/**
 * Gamma Combination
 * Author: Matthew Kenzie matthew.kenzie@cern.ch
 * Date: November 2015
 *
 **/

///
/// The B0 -> D0 K*0 ADS measurement only, added D-mixing
///

#include "PDF_ADS_DKstz_Kpi_Dmix.h"

PDF_ADS_DKstz_Kpi_Dmix::PDF_ADS_DKstz_Kpi_Dmix(config cObs, config cErr, config cCor,
  double Mxy, ParametersAbs* pars, TString d)
: PDF_ADS_DKstz_Kpi(cObs,cErr,cCor,pars,d)
{
  name = "ads-dkstz-kpi-dmix";
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


PDF_ADS_DKstz_Kpi_Dmix::~PDF_ADS_DKstz_Kpi_Dmix(){}


void PDF_ADS_DKstz_Kpi_Dmix::initParameters()
{
  parameters->add(*(p->get("xD")));
  parameters->add(*(p->get("yD")));
}


void PDF_ADS_DKstz_Kpi_Dmix::initRelations()
{
  RooArgSet *p = (RooArgSet*)parameters;
  delete theory; theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  RooRealVar&  rbkpi      = *((RooRealVar*)p->find("r_dkstz"));
  RooRealVar&  dbkpi      = *((RooRealVar*)p->find("d_dkstz"));
  RooRealVar&  Rbkstz     = *((RooRealVar*)p->find("R_dkstz"));
  RooRealVar&  deltadkstz = *((RooRealVar*)p->find("delta_dkstz"));
  RooFormulaVar *rbk  = new RooFormulaVar("r_dkstz_f", "r_dkstz_f", "r_dkstz*R_dkstz", *p);
  RooFormulaVar *dbk  = new RooFormulaVar("d_dkstz_f", "d_dkstz_f", "d_dkstz+delta_dkstz", *p);
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

  theory->add(*(new RooGLWADSDmixAcpVar("afav_dkstz_kpi_th", "RooGLWADSDmixAcpVar", *rbk,  *dbk, kbk, rf,   df,   kf, g, xD, yD, _Mxy, AcpD)));
  theory->add(*(new RooGLWADSDmixRpmVar("rp_dkstz_th",       "RooGLWADSDmixRpmVar", *rbk,  *dbk, kbk, rf,   df,   kf, g, xD, yD, _Mxy, "+")));
  theory->add(*(new RooGLWADSDmixRpmVar("rm_dkstz_th",       "RooGLWADSDmixRpmVar", *rbk,  *dbk, kbk, rf,   df,   kf, g, xD, yD, _Mxy, "-")));
}
