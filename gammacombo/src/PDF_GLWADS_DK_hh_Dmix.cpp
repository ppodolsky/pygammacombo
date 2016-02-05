/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 * Combine only the DK observables from 13 observables from the
 * two body GLW/ADS measurement.
 *
 **/

#include "PDF_GLWADS_DK_hh_Dmix.h"

PDF_GLWADS_DK_hh_Dmix::PDF_GLWADS_DK_hh_Dmix(config cObs, config cErr, config cCor,
		double Mxy, ParametersAbs* pars, TString d)
: PDF_GLWADS_DK_hh(cObs,cErr,cCor,pars,d)
{
	name = "glwads-dk-hh-dmix";
	_Mxy = Mxy;
	initParameters();
	initRelations();
	delete pdf; // it was built already by the super class constructor
	buildPdf();
}


PDF_GLWADS_DK_hh_Dmix::~PDF_GLWADS_DK_hh_Dmix(){}


void PDF_GLWADS_DK_hh_Dmix::initParameters()
{
	parameters->add(*(p->get("xD")));
	parameters->add(*(p->get("yD")));
}


void PDF_GLWADS_DK_hh_Dmix::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	delete theory; theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	RooRealVar& Rcab   = *((RooRealVar*)p->find("RBRdkdpi"));
	RooRealVar& rbk    = *((RooRealVar*)p->find("r_dk"));
	RooRealVar& dbk    = *((RooRealVar*)p->find("d_dk"));
	RooConstVar& kbk = RooConst(1);
	RooConstVar& rbp = RooConst(0); // assume rb(Dpi)=0 for DK only
	RooConstVar& dbp = RooConst(1); // then the phase and the
	RooConstVar& kbp = RooConst(1); // coherence factor values don't matter
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
	theory->add(*(new RooGLWADSDmixRkpVar("rkp_kpi_th",      "RooGLWADSDmixRkpVar", Rcab, rbk, dbk, kbk, rbp, dbp, kbp, rf,    df,    kf, g, xD, yD, _Mxy, "fav")));
	theory->add(*(new RooGLWADSDmixRkpVar("rkp_pipi_th",     "RooGLWADSDmixRkpVar", Rcab, rbk, dbk, kbk, rbp, dbp, kbp, rfGLW, dfGLW, kf, g, xD, yD, _Mxy, "fav")));
	theory->add(*(new RooGLWADSDmixRkpVar("rkp_kk_th",       "RooGLWADSDmixRkpVar", Rcab, rbk, dbk, kbk, rbp, dbp, kbp, rfGLW, dfGLW, kf, g, xD, yD, _Mxy, "fav")));
	theory->add(*(new RooGLWADSDmixAcpVar("afav_dk_kpi_th",  "RooGLWADSDmixAcpVar", rbk,  dbk, kbk, rf,    df,    kf, g, xD, yD, _Mxy, AcpD)));
	theory->add(*(new RooGLWADSDmixAcpVar("acp_dk_kk_th",    "RooGLWADSDmixAcpVar", rbk,  dbk, kbk, rfGLW, dfGLW, kf, g, xD, yD, _Mxy, AcpDKK)));
	theory->add(*(new RooGLWADSDmixAcpVar("acp_dk_pipi_th",  "RooGLWADSDmixAcpVar", rbk,  dbk, kbk, rfGLW, dfGLW, kf, g, xD, yD, _Mxy, AcpDpp)));
	theory->add(*(new RooGLWADSDmixRpmVar("rp_dk_kpi_th",    "RooGLWADSDmixRpmVar", rbk,  dbk, kbk, rf,    df,    kf, g, xD, yD, _Mxy, "+")));
	theory->add(*(new RooGLWADSDmixRpmVar("rm_dk_kpi_th",    "RooGLWADSDmixRpmVar", rbk,  dbk, kbk, rf,    df,    kf, g, xD, yD, _Mxy, "-")));
}
