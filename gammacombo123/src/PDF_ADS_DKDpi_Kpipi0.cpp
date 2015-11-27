/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2014
 *
 * The Kpipi0 part from the 2012 hhpi0 GLW/ADS measurement.
 *
 **/

#include "PDF_ADS_DKDpi_Kpipi0.h"

	PDF_ADS_DKDpi_Kpipi0::PDF_ADS_DKDpi_Kpipi0(config cObs, config cErr, config cCor, ParametersAbs* pars, TString d)
: PDF_Abs(6)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	name = "AdsDkdpiKpipi02012";
	this->dir = d;
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}

	PDF_ADS_DKDpi_Kpipi0::PDF_ADS_DKDpi_Kpipi0(ParametersAbs* pars, TString d, int nObs)
: PDF_Abs(nObs)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	this->dir = d;
}


PDF_ADS_DKDpi_Kpipi0::~PDF_ADS_DKDpi_Kpipi0(){}


void PDF_ADS_DKDpi_Kpipi0::initParameters()
{
	parameters = new RooArgList("parameters");
	parameters->add(*(p->get("r_dk")));
	parameters->add(*(p->get("d_dk")));
	parameters->add(*(p->get("r_dpi")));
	parameters->add(*(p->get("d_dpi")));
	parameters->add(*(p->get("g")));
	parameters->add(*(p->get("rD_kpipi0")));
	parameters->add(*(p->get("dD_kpipi0")));
	parameters->add(*(p->get("kD_kpipi0")));
	parameters->add(*(p->get("Aprod")));
}


void PDF_ADS_DKDpi_Kpipi0::initRelations()
{
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	RooArgSet *p = (RooArgSet*)parameters;
	theory->add(*(new RooFormulaVar("aads_dk_kpipi0_th",   "aads_dk_kpipi0_th",  "(2*r_dk *kD_kpipi0*rD_kpipi0*sin(d_dk +dD_kpipi0)*sin(g))/(r_dk^2  + rD_kpipi0^2 + 2*r_dk *kD_kpipi0*rD_kpipi0*cos(d_dk +dD_kpipi0)*cos(g))", *p)));
	theory->add(*(new RooFormulaVar("aads_dpi_kpipi0_th",  "aads_dpi_kpipi0_th", "(2*r_dpi*kD_kpipi0*rD_kpipi0*sin(d_dpi+dD_kpipi0)*sin(g))/(r_dpi^2 + rD_kpipi0^2 + 2*r_dpi*kD_kpipi0*rD_kpipi0*cos(d_dpi+dD_kpipi0)*cos(g))", *p)));
	theory->add(*(new RooFormulaVar("afav_dk_kpipi0_th",   "afav_dk_kpipi0_th",  "2*r_dk *rD_kpipi0*kD_kpipi0*sin(g)*sin(d_dk -dD_kpipi0) / (1 + r_dk^2  * rD_kpipi0^2 + 2*r_dk *rD_kpipi0*kD_kpipi0*cos(g)*cos(d_dk -dD_kpipi0))", *p)));
	theory->add(*(new RooFormulaVar("afav_dpi_kpipi0_th",  "afav_dpi_kpipi0_th", "Aprod", *p)));
	theory->add(*(new RooFormulaVar("rads_dk_kpipi0_th",   "rads_dk_kpipi0_th",  "(r_dk^2  + rD_kpipi0^2 + 2*r_dk *kD_kpipi0*rD_kpipi0*cos(d_dk +dD_kpipi0)*cos(g))/(1 + r_dk^2 *rD_kpipi0^2 + 2*r_dk *kD_kpipi0*rD_kpipi0*cos(d_dk -dD_kpipi0)*cos(g))", *p)));
	theory->add(*(new RooFormulaVar("rads_dpi_kpipi0_th",  "rads_dpi_kpipi0_th", "(r_dpi^2 + rD_kpipi0^2 + 2*r_dpi*kD_kpipi0*rD_kpipi0*cos(d_dpi+dD_kpipi0)*cos(g))/(1 + r_dpi^2*rD_kpipi0^2 + 2*r_dpi*kD_kpipi0*rD_kpipi0*cos(d_dpi-dD_kpipi0)*cos(g))", *p)));
}


void PDF_ADS_DKDpi_Kpipi0::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("aads_dk_kpipi0_obs",  "aads_dk_kpipi0",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("aads_dpi_kpipi0_obs", "aads_dpi_kpipi0", 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("afav_dk_kpipi0_obs",  "afav_dk_kpipi0",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("afav_dpi_kpipi0_obs", "afav_dpi_kpipi0", 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rads_dk_kpipi0_obs",  "rads_dk_kpipi0",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rads_dpi_kpipi0_obs", "rads_dpi_kpipi0", 0, -1e4, 1e4)));
}


void PDF_ADS_DKDpi_Kpipi0::setObservables(config c)
{
	switch(c)
	{
		case truth:{
					   setObservablesTruth();
					   break;
				   }
		case toy:{
					 setObservablesToy();
					 break;
				 }
		case lumi3fb:{
						 obsValSource = "3fb-1 ANA v6, values still blind (using Asimov for 8 observables)";
						 setObservable("aads_dk_kpipi0_obs",  -0.56317); // Asimov
						 setObservable("aads_dpi_kpipi0_obs",  0.22524); // Asimov
						 setObservable("afav_dk_kpipi0_obs",   0.012  );
						 setObservable("afav_dpi_kpipi0_obs", -0.00077);
						 setObservable("rads_dk_kpipi0_obs",  0.01106); // Asimov
						 setObservable("rads_dpi_kpipi0_obs", 0.00300); // Asimov
						 break;
					 }
		default:{
					cout << "PDF_ADS_DKDpi_Kpipi0::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_ADS_DKDpi_Kpipi0::setUncertainties(config c)
{
	switch(c)
	{
		case lumi3fb:{
						 obsErrSource = "3fb-1 ANA v6";
						 StatErr[ 0] = 0.27    ; // "aads_dk_kpipi0_obs",
						 StatErr[ 1] = 0.19    ; // "aads_dpi_kpipi0_obs",
						 StatErr[ 2] = 0.026   ; // "afav_dk_kpipi0_obs",
						 StatErr[ 3] = 0.0055  ; // "afav_dpi_kpipi0_obs",
						 StatErr[ 4] = 0.0050  ; // "rads_dk_kpipi0_obs",
						 StatErr[ 5] = 0.00049 ; // "rads_dpi_kpipi0_obs",

						 SystErr[ 0] = 0.03    ; // "aads_dk_kpipi0_obs",
						 SystErr[ 1] = 0.04    ; // "aads_dpi_kpipi0_obs",
						 SystErr[ 2] = 0.003   ; // "afav_dk_kpipi0_obs",
						 SystErr[ 3] = 0.0044  ; // "afav_dpi_kpipi0_obs",
						 SystErr[ 4] = 0.0020  ; // "rads_dk_kpipi0_obs",
						 SystErr[ 5] = 0.00006 ; // "rads_dpi_kpipi0_obs",
						 break;
					 }
		default:{
					cout << "PDF_ADS_DKDpi_Kpipi0::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_ADS_DKDpi_Kpipi0::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi3fb:{
						 corSource = "3fb-1 ANA v6";
						 double dataStat[]  = {
							 1.0     , 0.0393  , -0.0056 , 0.0261  , -0.1743 , 0.0027  ,
							 0.0393  , 1.0     , 0.0073  , -0.0272 , -0.0121 , 0.3135  ,
							 -0.0056 , 0.0073  , 1.0     , -0.2742 , -0.0011 , -0.0002 ,
							 0.0261  , -0.0272 , -0.2742 , 1.0     , 0.0026  , -0.0003 ,
							 -0.1743 , -0.0121 , -0.0011 , 0.0026  , 1.0     , -0.042  ,
							 0.0027  , 0.3135  , -0.0002 , -0.0003 , -0.042  , 1.0     ,
						 };
						 corStatMatrix = TMatrixDSym(nObs,dataStat);
						 double dataSyst[]  = {
							 1.00    , 0.06    , -0.07   , -0.10   , 0.34    , 0.10    ,
							 0.06    , 1.00    , -0.14   , -0.12   , -0.09   , -0.85   ,
							 -0.07   , -0.14   , 1.00    , 0.53    , 0.03    , 0.03    ,
							 -0.10   , -0.12   , 0.53    , 1.00    , -0.03   , 0.01    ,
							 0.34    , -0.09   , 0.03    , -0.03   , 1.00    , 0.23    ,
							 0.10    , -0.85   , 0.03    , 0.01    , 0.23    , 1.00    ,
						 };
						 corSystMatrix = TMatrixDSym(nObs,dataSyst);
						 break;
					 }
		default:{
					cout << "PDF_ADS_DKDpi_Kpipi0::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_ADS_DKDpi_Kpipi0::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}

