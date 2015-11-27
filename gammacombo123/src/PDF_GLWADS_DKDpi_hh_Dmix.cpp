/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#include "PDF_GLWADS_DKDpi_hh_Dmix.h"

PDF_GLWADS_DKDpi_hh_Dmix::PDF_GLWADS_DKDpi_hh_Dmix(config cObs, config cErr, config cCor,
		double Mxy, ParametersAbs* pars, TString d)
: PDF_GLWADS_DKDpi_hh(cObs,cErr,cCor,pars,d)
{
	name = "glwads-dkdpi-hh-dmix";
	_Mxy = Mxy;
	initParameters();
	initRelations();
	delete pdf; // it was built already by the super class constructor
	buildPdf();
}


PDF_GLWADS_DKDpi_hh_Dmix::~PDF_GLWADS_DKDpi_hh_Dmix(){}


void PDF_GLWADS_DKDpi_hh_Dmix::initParameters()
{
	parameters->add(*(p->get("xD")));
	parameters->add(*(p->get("yD")));
}


void PDF_GLWADS_DKDpi_hh_Dmix::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	delete theory; theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	RooRealVar&  Rcab   = *((RooRealVar*)p->find("RBRdkdpi"));
	RooRealVar&  rbk    = *((RooRealVar*)p->find("r_dk"));
	RooRealVar&  dbk    = *((RooRealVar*)p->find("d_dk"));
	RooConstVar& kbk    = RooConst(1);
	RooRealVar&  rbp    = *((RooRealVar*)p->find("r_dpi"));
	RooRealVar&  dbp    = *((RooRealVar*)p->find("d_dpi"));
	RooConstVar& kbp    = RooConst(1);
	RooConstVar& kf     = RooConst(1);
	RooRealVar&  rf     = *((RooRealVar*)p->find("rD_kpi"));
	RooConstVar& rfGLW  = RooConst(1);
	RooRealVar&  df     = *((RooRealVar*)p->find("dD_kpi"));
	RooConstVar& dfGLW  = RooConst(0);
	RooRealVar&  g      = *((RooRealVar*)p->find("g"));
	RooRealVar&  xD     = *((RooRealVar*)p->find("xD"));
	RooRealVar&  yD     = *((RooRealVar*)p->find("yD"));
	RooRealVar&  AcpDKK = *((RooRealVar*)p->find("AcpDKK"));
	RooRealVar&  AcpDpp = *((RooRealVar*)p->find("AcpDpipi"));
	RooConstVar& AcpD   = RooConst(0);

	// theory->add(*(new RooFormulaVar("rkp_kpi_th",          "rkp_kpi",      "RBRdkdpi*(1 + r_dk^2 * rD_kpi^2 + 2*r_dk*rD_kpi*cos(g)*cos(d_dk-dD_kpi))/(1 + r_dpi^2 * rD_kpi^2 + 2*r_dpi*rD_kpi*cos(g)*cos(d_dpi-dD_kpi))", *p)));
	// theory->add(*(new RooFormulaVar("rkp_pipi_kpi_th",     "rkp_pipi",     "RBRdkdpi*(1 + r_dk^2 + 2*r_dk*cos(d_dk)*cos(g))/(1 + r_dpi^2 + 2*r_dpi*cos(d_dpi)*cos(g))", *p)));
	// theory->add(*(new RooFormulaVar("rkp_kk_kpi_th",       "rkp_kk",       "RBRdkdpi*(1 + r_dk^2 + 2*r_dk*cos(d_dk)*cos(g))/(1 + r_dpi^2 + 2*r_dpi*cos(d_dpi)*cos(g))", *p)));
	// theory->add(*(new RooFormulaVar("afav_dk_kpi_th",      "afav_dk",      "2*r_dk *rD_kpi*sin(g)*sin(d_dk -dD_kpi) / (1 + r_dk^2  * rD_kpi^2 + 2*r_dk *rD_kpi*cos(g)*cos(d_dk -dD_kpi))", *p)));
	// theory->add(*(new RooFormulaVar("afav_dpi_kpi_th",     "afav_dpi",     "2*r_dpi*rD_kpi*sin(g)*sin(d_dpi-dD_kpi) / (1 + r_dpi^2 * rD_kpi^2 + 2*r_dpi*rD_kpi*cos(g)*cos(d_dpi-dD_kpi))", *p)));
	// theory->add(*(new RooFormulaVar("acp_dk_kk_kpi_th",    "acp_dk_kk",    "2*r_dk *sin(d_dk) *sin(g) / (1 + r_dk^2  + 2*r_dk *cos(d_dk) *cos(g)) + AcpDKK", *p)));
	// theory->add(*(new RooFormulaVar("acp_dk_pipi_kpi_th",  "acp_dk_pipi",  "2*r_dk *sin(d_dk) *sin(g) / (1 + r_dk^2  + 2*r_dk *cos(d_dk) *cos(g)) + AcpDpipi", *p)));
	// theory->add(*(new RooFormulaVar("acp_dpi_kk_kpi_th",   "acp_dpi_kk",   "2*r_dpi*sin(d_dpi)*sin(g) / (1 + r_dpi^2 + 2*r_dpi*cos(d_dpi)*cos(g)) + AcpDKK", *p)));
	// theory->add(*(new RooFormulaVar("acp_dpi_pipi_kpi_th", "acp_dpi_pipi", "2*r_dpi*sin(d_dpi)*sin(g) / (1 + r_dpi^2 + 2*r_dpi*cos(d_dpi)*cos(g)) + AcpDpipi", *p)));
	// theory->add(*(new RooFormulaVar("rp_dk_kpi_th",        "rp_dk",        "(r_dk^2  + rD_kpi^2 + 2*r_dk *rD_kpi*cos( g+d_dk +dD_kpi)) / (1 + r_dk^2 *rD_kpi^2 + 2*r_dk *rD_kpi*cos( g +d_dk -dD_kpi))", *p)));
	// theory->add(*(new RooFormulaVar("rm_dk_kpi_th",        "rm_dk",        "(r_dk^2  + rD_kpi^2 + 2*r_dk *rD_kpi*cos(-g+d_dk +dD_kpi)) / (1 + r_dk^2 *rD_kpi^2 + 2*r_dk *rD_kpi*cos(-g +d_dk -dD_kpi))", *p)));
	// theory->add(*(new RooFormulaVar("rp_dpi_kpi_th",       "rp_dpi",       "(r_dpi^2 + rD_kpi^2 + 2*r_dpi*rD_kpi*cos( g+d_dpi+dD_kpi)) / (1 + r_dpi^2*rD_kpi^2 + 2*r_dpi*rD_kpi*cos( g +d_dpi-dD_kpi))", *p)));
	// theory->add(*(new RooFormulaVar("rm_dpi_kpi_th",       "rm_dpi",       "(r_dpi^2 + rD_kpi^2 + 2*r_dpi*rD_kpi*cos(-g+d_dpi+dD_kpi)) / (1 + r_dpi^2*rD_kpi^2 + 2*r_dpi*rD_kpi*cos(-g +d_dpi-dD_kpi))", *p)));

	theory->add(*(new RooGLWADSDmixRkpVar("rkp_kpi_th",          "RooGLWADSDmixRkpVar", Rcab, rbk, dbk, kbk, rbp, dbp, kbp, rf,    df,    kf, g, xD, yD, _Mxy, "fav")));
	theory->add(*(new RooGLWADSDmixRkpVar("rkp_pipi_th",         "RooGLWADSDmixRkpVar", Rcab, rbk, dbk, kbk, rbp, dbp, kbp, rfGLW, dfGLW, kf, g, xD, yD, _Mxy, "fav")));
	theory->add(*(new RooGLWADSDmixRkpVar("rkp_kk_th",           "RooGLWADSDmixRkpVar", Rcab, rbk, dbk, kbk, rbp, dbp, kbp, rfGLW, dfGLW, kf, g, xD, yD, _Mxy, "fav")));
	theory->add(*(new RooGLWADSDmixAcpVar("afav_dk_kpi_th",      "RooGLWADSDmixAcpVar", rbk,  dbk, kbk, rf,    df,    kf, g, xD, yD, _Mxy, AcpD)));
	theory->add(*(new RooGLWADSDmixAcpVar("afav_dpi_kpi_th",     "RooGLWADSDmixAcpVar", rbp,  dbp, kbp, rf,    df,    kf, g, xD, yD, _Mxy, AcpD)));
	theory->add(*(new RooGLWADSDmixAcpVar("acp_dk_kk_th",        "RooGLWADSDmixAcpVar", rbk,  dbk, kbk, rfGLW, dfGLW, kf, g, xD, yD, _Mxy, AcpDKK)));
	theory->add(*(new RooGLWADSDmixAcpVar("acp_dk_pipi_th",      "RooGLWADSDmixAcpVar", rbk,  dbk, kbk, rfGLW, dfGLW, kf, g, xD, yD, _Mxy, AcpDpp)));
	theory->add(*(new RooGLWADSDmixAcpVar("acp_dpi_kk_th",       "RooGLWADSDmixAcpVar", rbp,  dbp, kbp, rfGLW, dfGLW, kf, g, xD, yD, _Mxy, AcpDKK)));
	theory->add(*(new RooGLWADSDmixAcpVar("acp_dpi_pipi_th",     "RooGLWADSDmixAcpVar", rbp,  dbp, kbp, rfGLW, dfGLW, kf, g, xD, yD, _Mxy, AcpDpp)));
	theory->add(*(new RooGLWADSDmixRpmVar("rp_dk_kpi_th",        "RooGLWADSDmixRpmVar", rbk,  dbk, kbk, rf,    df,    kf, g, xD, yD, _Mxy, "+")));
	theory->add(*(new RooGLWADSDmixRpmVar("rm_dk_kpi_th",        "RooGLWADSDmixRpmVar", rbk,  dbk, kbk, rf,    df,    kf, g, xD, yD, _Mxy, "-")));
	theory->add(*(new RooGLWADSDmixRpmVar("rp_dpi_kpi_th",       "RooGLWADSDmixRpmVar", rbp,  dbp, kbp, rf,    df,    kf, g, xD, yD, _Mxy, "+")));
	theory->add(*(new RooGLWADSDmixRpmVar("rm_dpi_kpi_th",       "RooGLWADSDmixRpmVar", rbp,  dbp, kbp, rf,    df,    kf, g, xD, yD, _Mxy, "-")));
}
