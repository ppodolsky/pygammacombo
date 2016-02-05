/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Jul 2014
 *
 * The B->DKpipi, D->hh, GLW/ADS measurement: B->DKpipi, with D->Kpi, piK, pipi, KK,
 * 6 observables, including D mixing.
 **/

#include "PDF_GLWADS_DKpipi_hh_Dmix.h"

PDF_GLWADS_DKpipi_hh_Dmix::PDF_GLWADS_DKpipi_hh_Dmix(config cObs, config cErr, config cCor,
		double Mxy)
: PDF_GLWADS_DKpipi_hh(cObs,cErr,cCor)
{
	name = "GLWADS-Dkpipi-hh-dmix";
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


PDF_GLWADS_DKpipi_hh_Dmix::~PDF_GLWADS_DKpipi_hh_Dmix(){}


void PDF_GLWADS_DKpipi_hh_Dmix::initParameters()
{
	parameters->add(*(p->get("xD")));
	parameters->add(*(p->get("yD")));
}


void PDF_GLWADS_DKpipi_hh_Dmix::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	delete theory; theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	RooRealVar&  rbk    = *((RooRealVar*)p->find("r_dkpipi"));
	RooRealVar&  dbk    = *((RooRealVar*)p->find("d_dkpipi"));
	RooRealVar&  kbk    = *((RooRealVar*)p->find("k_dkpipi"));
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
	// theory->add(*(new RooFormulaVar("acp_dkpipi_kk_th",    "acp_dkpipi_kk_th",    "2*k_dkpipi *r_dkpipi *sin(d_dkpipi) *sin(g) / (1 + r_dkpipi^2  + 2*k_dkpipi *r_dkpipi *cos(d_dkpipi) *cos(g)) + AcpDKK", *p)));
	// theory->add(*(new RooFormulaVar("acp_dkpipi_pipi_th",  "acp_dkpipi_pipi_th",  "2*k_dkpipi *r_dkpipi *sin(d_dkpipi) *sin(g) / (1 + r_dkpipi^2  + 2*k_dkpipi *r_dkpipi *cos(d_dkpipi) *cos(g)) + AcpDpipi", *p)));
	// theory->add(*(new RooFormulaVar("rp_dkpipi_th",        "rp_dkpipi_th",        "(r_dkpipi^2  + rD_kpi^2 + 2*k_dkpipi *r_dkpipi *rD_kpi*cos( g+d_dkpipi +dD_kpi)) / (1 + r_dkpipi^2 *rD_kpi^2 + 2*k_dkpipi *r_dkpipi *rD_kpi*cos( g +d_dkpipi -dD_kpi))", *p)));
	// theory->add(*(new RooFormulaVar("rm_dkpipi_th",        "rm_dkpipi_th",        "(r_dkpipi^2  + rD_kpi^2 + 2*k_dkpipi *r_dkpipi *rD_kpi*cos(-g+d_dkpipi +dD_kpi)) / (1 + r_dkpipi^2 *rD_kpi^2 + 2*k_dkpipi *r_dkpipi *rD_kpi*cos(-g +d_dkpipi -dD_kpi))", *p)));

	theory->add(*(new RooGLWADSDmixRcpVar("rcp_dkpipi_th",       "RooGLWADSDmixRcpVar", rbk,  dbk, kbk, rfRCP, dfGLW, kf, g, xD, yD, _Mxy)));
	theory->add(*(new RooGLWADSDmixAcpVar("afav_dkpipi_kpi_th",  "RooGLWADSDmixAcpVar", rbk,  dbk, kbk, rf,    df,    kf, g, xD, yD, _Mxy, AcpD)));
	theory->add(*(new RooGLWADSDmixAcpVar("acp_dkpipi_kk_th",    "RooGLWADSDmixAcpVar", rbk,  dbk, kbk, rfGLW, dfGLW, kf, g, xD, yD, _Mxy, AcpDKK)));
	theory->add(*(new RooGLWADSDmixAcpVar("acp_dkpipi_pipi_th",  "RooGLWADSDmixAcpVar", rbk,  dbk, kbk, rfGLW, dfGLW, kf, g, xD, yD, _Mxy, AcpDpp)));
	theory->add(*(new RooGLWADSDmixRpmVar("rp_dkpipi_th",        "RooGLWADSDmixRpmVar", rbk,  dbk, kbk, rf,    df,    kf, g, xD, yD, _Mxy, "+")));
	theory->add(*(new RooGLWADSDmixRpmVar("rm_dkpipi_th",        "RooGLWADSDmixRpmVar", rbk,  dbk, kbk, rf,    df,    kf, g, xD, yD, _Mxy, "-")));
}
