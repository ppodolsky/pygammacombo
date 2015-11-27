/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Sep 2014
 *
 **/

#include "PDF_GLWADS_DKDpi_KSKpi_DCPV_Dmix.h"

PDF_GLWADS_DKDpi_KSKpi_DCPV_Dmix::PDF_GLWADS_DKDpi_KSKpi_DCPV_Dmix(config cObs, config cErr, config cCor,
		double Mxy, ParametersAbs* pars, TString d)
: PDF_GLWADS_DKDpi_KSKpi_DCPV(cObs,cErr,cCor,pars,d)
{
	name = "glwadsDkdpiKSKpiDCPVDmix";
	_Mxy = Mxy;
	initParameters();
	initRelations();
	delete pdf; // it was built already by the super class constructor
	buildPdf();
}


PDF_GLWADS_DKDpi_KSKpi_DCPV_Dmix::~PDF_GLWADS_DKDpi_KSKpi_DCPV_Dmix(){}


void PDF_GLWADS_DKDpi_KSKpi_DCPV_Dmix::initParameters()
{
	parameters->add(*(p->get("xD")));
	parameters->add(*(p->get("yD")));
}


void PDF_GLWADS_DKDpi_KSKpi_DCPV_Dmix::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	delete theory; theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	RooRealVar& rbk = *((RooRealVar*)p->find("r_dk"));
	RooRealVar& dbk = *((RooRealVar*)p->find("d_dk"));
	RooConstVar& kbk = RooConst(1);
	RooRealVar& rbp = *((RooRealVar*)p->find("r_dpi"));
	RooRealVar& dbp = *((RooRealVar*)p->find("d_dpi"));
	RooConstVar& kbp = RooConst(1);
	RooRealVar& kf  = *((RooRealVar*)p->find("kD_kskpi"));
	RooRealVar& rf  = *((RooRealVar*)p->find("rD_kskpi"));
	RooRealVar& df  = *((RooRealVar*)p->find("dD_kskpi"));
	RooRealVar& g   = *((RooRealVar*)p->find("g"));
	RooRealVar& xD  = *((RooRealVar*)p->find("xD"));
	RooRealVar& yD  = *((RooRealVar*)p->find("yD"));
	RooRealVar& Rcab = *((RooRealVar*)p->find("RBRdkdpi"));
	RooRealVar&  AcpDfav = *((RooRealVar*)p->find("AcpDzKstpKm"));
	RooRealVar&  AcpDsup = *((RooRealVar*)p->find("AcpDzKstmKp"));

	theory->add(*(new RooGLWADSDmixRADSVar(  "rfavsup_dpi_kskpi_th", "RooGLWADSDmixRADSVar (inverse)", rbp, dbp, kbp, rf, df, kf, g, xD, yD, _Mxy, "inverse")));
	theory->add(*(new RooGLWADSDmixRkpVar(   "rfav_dkdpi_kskpi_th",  "RooGLWADSDmixRkpVar (fav)", Rcab, rbk, dbk, kbk, rbp, dbp, kbp, rf, df, kf, g, xD, yD, _Mxy, "fav")));
	theory->add(*(new RooGLWADSDmixRkpVar(   "rsup_dkdpi_kskpi_th",  "RooGLWADSDmixRkpVar (sup)", Rcab, rbk, dbk, kbk, rbp, dbp, kbp, rf, df, kf, g, xD, yD, _Mxy, "sup")));
	theory->add(*(new RooGLWADSDmixAcpVar(   "afav_dk_kskpi_th",     "RooGLWADSDmixAcpVar",    rbk, dbk, kbk, rf, df, kf, g, xD, yD, _Mxy, AcpDfav)));
	theory->add(*(new RooGLWADSDmixAcpADSVar("asup_dk_kskpi_th",     "RooGLWADSDmixAcpADSVar", rbk, dbk, kbk, rf, df, kf, g, xD, yD, _Mxy, AcpDsup)));
	theory->add(*(new RooGLWADSDmixAcpVar(   "afav_dpi_kskpi_th",    "RooGLWADSDmixAcpVar",    rbp, dbp, kbp, rf, df, kf, g, xD, yD, _Mxy, AcpDfav)));
	theory->add(*(new RooGLWADSDmixAcpADSVar("asup_dpi_kskpi_th",    "RooGLWADSDmixAcpADSVar", rbp, dbp, kbp, rf, df, kf, g, xD, yD, _Mxy, AcpDsup)));
}
