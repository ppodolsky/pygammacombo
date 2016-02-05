/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Jan 2015
 *
 **/

#include "PDF_GLWADS_DK_hhpi0_Dmix.h"

PDF_GLWADS_DK_hhpi0_Dmix::PDF_GLWADS_DK_hhpi0_Dmix(config cObs, config cErr, config cCor,
		double Mxy, ParametersAbs* pars)
: PDF_GLWADS_DK_hhpi0(cObs,cErr,cCor,pars)
{
	name = "GLWADS_DK_hhpi0_2012_Dmix";
	_Mxy = Mxy;
	initParameters();
	initRelations();
	delete pdf; // it was built already by the super class constructor
	buildPdf();
}


PDF_GLWADS_DK_hhpi0_Dmix::~PDF_GLWADS_DK_hhpi0_Dmix(){}


void PDF_GLWADS_DK_hhpi0_Dmix::initParameters()
{
	parameters->add(*(p->get("xD")));
	parameters->add(*(p->get("yD")));
}


void PDF_GLWADS_DK_hhpi0_Dmix::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	delete theory; theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	RooConstVar&  Rcab   = RooConst(1);
	RooRealVar&  rbk    = *((RooRealVar*)p->find("r_dk"));
	RooRealVar&  dbk    = *((RooRealVar*)p->find("d_dk"));
	RooConstVar& kbk    = RooConst(1);
	RooConstVar& rbp    = RooConst(0);
	RooConstVar& dbp    = RooConst(0);
	RooConstVar& kbp    = RooConst(1);
	RooRealVar&    kf      = *((RooRealVar*)p->find("kD_kpipi0"));
	RooFormulaVar& kfGLWkk = *(new RooFormulaVar("dilutionkk", "dilutionkk", "2*F_kkpi0 - 1",   *p));
	RooFormulaVar& kfGLWpp = *(new RooFormulaVar("dilutionpp", "dilutionpp", "2*F_pipipi0 - 1", *p));
	RooRealVar&  rf     = *((RooRealVar*)p->find("rD_kpipi0"));
	RooConstVar& rfGLW  = RooConst(1);
	RooRealVar&  df     = *((RooRealVar*)p->find("dD_kpipi0"));
	RooConstVar& dfGLW  = RooConst(0);
	RooRealVar&  g      = *((RooRealVar*)p->find("g"));
	RooRealVar&  xD     = *((RooRealVar*)p->find("xD"));
	RooRealVar&  yD     = *((RooRealVar*)p->find("yD"));
	RooConstVar& AcpD   = RooConst(0);

	//theory->add(*(new RooFormulaVar("aads_dk_kpipi0_th",   "aads_dk_kpipi0_th",  "(2*r_dk *kD_kpipi0*rD_kpipi0*sin(d_dk +dD_kpipi0)*sin(g))/(r_dk^2  + rD_kpipi0^2 + 2*r_dk *kD_kpipi0*rD_kpipi0*cos(d_dk +dD_kpipi0)*cos(g))", *p)));
	//theory->add(*(new RooFormulaVar("acp_dk_kkpi0_th",     "acp_dk_kkpi0_th",    "2*r_dk *(2*F_kkpi0-1)  *sin(d_dk) *sin(g) / (1 + r_dk^2  + 2*r_dk *(2*F_kkpi0-1)  *cos(d_dk) *cos(g))", *p)));
	//theory->add(*(new RooFormulaVar("acp_dk_pipipi0_th",   "acp_dk_pipipi0_th",  "2*r_dk *(2*F_pipipi0-1)*sin(d_dk) *sin(g) / (1 + r_dk^2  + 2*r_dk *(2*F_pipipi0-1)*cos(d_dk) *cos(g))", *p)));
	//theory->add(*(new RooFormulaVar("afav_dk_kpipi0_th",   "afav_dk_kpipi0_th",  "2*r_dk *rD_kpipi0*kD_kpipi0*sin(g)*sin(d_dk -dD_kpipi0) / (1 + r_dk^2  * rD_kpipi0^2 + 2*r_dk *rD_kpipi0*kD_kpipi0*cos(g)*cos(d_dk -dD_kpipi0))", *p)));
	//theory->add(*(new RooFormulaVar("rads_dk_kpipi0_th",   "rads_dk_kpipi0_th",  "(r_dk^2  + rD_kpipi0^2 + 2*r_dk *kD_kpipi0*rD_kpipi0*cos(d_dk +dD_kpipi0)*cos(g))/(1 + r_dk^2 *rD_kpipi0^2 + 2*r_dk *kD_kpipi0*rD_kpipi0*cos(d_dk -dD_kpipi0)*cos(g))", *p)));
	//theory->add(*(new RooFormulaVar("rcp_kkpi0_th",        "rcp_kkpi0_th",       "(1 + r_dk^2 + 2*r_dk*(2*F_kkpi0-1)  *cos(g)*cos(d_dk))", *p)));
	//theory->add(*(new RooFormulaVar("rcp_pipipi0_th",      "rcp_pipipi0_th",     "(1 + r_dk^2 + 2*r_dk*(2*F_pipipi0-1)*cos(g)*cos(d_dk))", *p)));

	theory->add(*(new RooGLWADSDmixAcpADSVar("aads_dk_kpipi0_th",  "RooGLWADSDmixAcpADSVar", rbk,  dbk, kbk, rf, df, kf, g, xD, yD, _Mxy, AcpD)));
	theory->add(*(new RooGLWADSDmixAcpVar(   "acp_dk_kkpi0_th",    "RooGLWADSDmixAcpVar",    rbk,  dbk, kbk, rfGLW, dfGLW, kfGLWkk, g, xD, yD, _Mxy, AcpD)));
	theory->add(*(new RooGLWADSDmixAcpVar(   "acp_dk_pipipi0_th",  "RooGLWADSDmixAcpVar",    rbk,  dbk, kbk, rfGLW, dfGLW, kfGLWpp, g, xD, yD, _Mxy, AcpD)));
	theory->add(*(new RooGLWADSDmixAcpVar(   "afav_dk_kpipi0_th",  "RooGLWADSDmixAcpVar",    rbk,  dbk, kbk, rf,    df,    kf, g, xD, yD, _Mxy, AcpD)));
	theory->add(*(new RooGLWADSDmixRADSVar(  "rads_dk_kpipi0_th",  "RooGLWADSDmixRADSVar",   rbk,  dbk, kbk, rf, df, kf, g, xD, yD, _Mxy, "")));
	theory->add(*(new RooGLWADSDmixRkpVar(   "rcp_kkpi0_th",       "RooGLWADSDmixRkpVar",    Rcab, rbk, dbk, kbk, rbp, dbp, kbp, rfGLW, dfGLW, kfGLWkk, g, xD, yD, _Mxy, "fav")));
	theory->add(*(new RooGLWADSDmixRkpVar(   "rcp_pipipi0_th",     "RooGLWADSDmixRkpVar",    Rcab, rbk, dbk, kbk, rbp, dbp, kbp, rfGLW, dfGLW, kfGLWpp, g, xD, yD, _Mxy, "fav")));
}

