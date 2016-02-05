/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 * Combine all 13 observables from the GLW/ADS measurement.
 *
 **/

#include "PDF_GLWADS_Dpi_hh_Dmix.h"

PDF_GLWADS_Dpi_hh_Dmix::PDF_GLWADS_Dpi_hh_Dmix(config cObs, config cErr, config cCor, 
		double Mxy, ParametersAbs* pars, TString d)
: PDF_GLWADS_Dpi_hh(cObs,cErr,cCor,pars,d)
{
	name = "glwads-dpi-hh-dmix";
	_Mxy = Mxy;
	initParameters();
	initRelations();
	delete pdf; // it was built already by the super class constructor
	buildPdf();
}


PDF_GLWADS_Dpi_hh_Dmix::~PDF_GLWADS_Dpi_hh_Dmix(){}


void PDF_GLWADS_Dpi_hh_Dmix::initParameters()
{
	parameters->add(*(p->get("xD")));
	parameters->add(*(p->get("yD")));
}  


void PDF_GLWADS_Dpi_hh_Dmix::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	delete theory; theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	RooRealVar& rbp    = *((RooRealVar*)p->find("r_dpi"));
	RooRealVar& dbp    = *((RooRealVar*)p->find("d_dpi"));
	RooConstVar& kbp = RooConst(1);
	RooConstVar& kf = RooConst(1);
	RooRealVar& rf     = *((RooRealVar*)p->find("rD_kpi"));
	RooConstVar& rfGLW = RooConst(1);
	RooRealVar& df     = *((RooRealVar*)p->find("dD_kpi"));
	RooConstVar& dfGLW = RooConst(0);
	RooRealVar& g      = *((RooRealVar*)p->find("g"));
	RooRealVar& xD     = *((RooRealVar*)p->find("xD"));
	RooRealVar& yD     = *((RooRealVar*)p->find("yD"));
	RooRealVar& AcpDKK = *((RooRealVar*)p->find("AcpDKK"));
	RooRealVar& AcpDpp = *((RooRealVar*)p->find("AcpDpipi"));
	RooConstVar& AcpD = RooConst(0);
	theory->add(*(new RooGLWADSDmixAcpVar("afav_dpi_kpi_th",     "RooGLWADSDmixAcpVar", rbp,  dbp, kbp, rf,    df,    kf, g, xD, yD, _Mxy, AcpD)));
	theory->add(*(new RooGLWADSDmixAcpVar("acp_dpi_kk_kpi_th",   "RooGLWADSDmixAcpVar", rbp,  dbp, kbp, rfGLW, dfGLW, kf, g, xD, yD, _Mxy, AcpDKK)));
	theory->add(*(new RooGLWADSDmixAcpVar("acp_dpi_pipi_kpi_th", "RooGLWADSDmixAcpVar", rbp,  dbp, kbp, rfGLW, dfGLW, kf, g, xD, yD, _Mxy, AcpDpp)));
	theory->add(*(new RooGLWADSDmixRpmVar("rp_dpi_kpi_th",       "RooGLWADSDmixRpmVar", rbp,  dbp, kbp, rf,    df,    kf, g, xD, yD, _Mxy, "+")));
	theory->add(*(new RooGLWADSDmixRpmVar("rm_dpi_kpi_th",       "RooGLWADSDmixRpmVar", rbp,  dbp, kbp, rf,    df,    kf, g, xD, yD, _Mxy, "-")));
}
