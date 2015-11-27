/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: September 2013
 *
 **/

#include "PDF_GLWADS_DKstz_hh.h"

	PDF_GLWADS_DKstz_hh::PDF_GLWADS_DKstz_hh(config cObs, config cErr, config cCor, ParametersAbs* pars, TString d)
: PDF_Abs(7)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	name = "glwads-dkstz-hh";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_GLWADS_DKstz_hh::~PDF_GLWADS_DKstz_hh(){}


void PDF_GLWADS_DKstz_hh::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("r_dkstz"))); 
	parameters->add(*(p.get("d_dkstz")));
	parameters->add(*(p.get("k_dkstz")));
	parameters->add(*(p.get("g")));
	parameters->add(*(p.get("rD_kpi")));
	parameters->add(*(p.get("dD_kpi")));
	parameters->add(*(p.get("AcpDKK")));
	parameters->add(*(p.get("AcpDpipi")));
}  


void PDF_GLWADS_DKstz_hh::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	theory->add(*(new RooFormulaVar("acp_dkstz_kk_th",    "acp_dkstz_kk",    "2*k_dkstz*r_dkstz *sin(d_dkstz) *sin(g) / (1 + r_dkstz^2  + 2*k_dkstz*r_dkstz *cos(d_dkstz) *cos(g)) + AcpDKK", *p)));
	theory->add(*(new RooFormulaVar("afav_dkstz_kpi_th",  "afav_dkstz_kpi",  "2*k_dkstz*r_dkstz*rD_kpi *sin(d_dkstz-dD_kpi) *sin(g) / (1 + r_dkstz^2*rD_kpi^2  + 2*k_dkstz*r_dkstz*rD_kpi *cos(d_dkstz-dD_kpi) *cos(g))", *p)));
	theory->add(*(new RooFormulaVar("rcp_dkstz_kk_th",    "rcp_dkstz_kk",    "(1 + r_dkstz^2  + 2*k_dkstz*r_dkstz *cos(d_dkstz) *cos(g))/(1 + r_dkstz^2*rD_kpi^2  + 2*k_dkstz*r_dkstz*rD_kpi *cos(d_dkstz-dD_kpi) *cos(g))", *p)));
	theory->add(*(new RooFormulaVar("acp_dkstz_pipi_th",  "acp_dkstz_pipi",  "2*k_dkstz*r_dkstz *sin(d_dkstz) *sin(g) / (1 + r_dkstz^2  + 2*k_dkstz*r_dkstz *cos(d_dkstz) *cos(g)) + AcpDpipi", *p)));
	theory->add(*(new RooFormulaVar("rcp_dkstz_pipi_th",  "rcp_dkstz_pipi",  "(1 + r_dkstz^2  + 2*k_dkstz*r_dkstz *cos(d_dkstz) *cos(g))/(1 + r_dkstz^2*rD_kpi^2  + 2*k_dkstz*r_dkstz*rD_kpi *cos(d_dkstz-dD_kpi) *cos(g))", *p)));
	theory->add(*(new RooFormulaVar("rp_dkstz_th",        "rp_dkstz_th",     "(r_dkstz^2  + rD_kpi^2 + 2*k_dkstz *r_dkstz *rD_kpi*cos( g+d_dkstz +dD_kpi)) / (1 + r_dkstz^2 *rD_kpi^2 + 2*k_dkstz *r_dkstz *rD_kpi*cos( g +d_dkstz -dD_kpi))", *p)));
	theory->add(*(new RooFormulaVar("rm_dkstz_th",        "rm_dkstz_th",     "(r_dkstz^2  + rD_kpi^2 + 2*k_dkstz *r_dkstz *rD_kpi*cos(-g+d_dkstz +dD_kpi)) / (1 + r_dkstz^2 *rD_kpi^2 + 2*k_dkstz *r_dkstz *rD_kpi*cos(-g +d_dkstz -dD_kpi))", *p)));
}


void PDF_GLWADS_DKstz_hh::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("acp_dkstz_kk_obs",    "A_{CP} (DK^{*}, KK)",     0, -1e4, 1e4))); // A_d^KK
	observables->add(*(new RooRealVar("afav_dkstz_kpi_obs",  "A_{fav} (DK^{*}, K#pi)",  0, -1e4, 1e4))); // A_d^Kpi
	observables->add(*(new RooRealVar("rcp_dkstz_kk_obs",    "R_{CP} (DK^{*}, KK)",     1, -1e4, 1e4))); // R_d^KK
	observables->add(*(new RooRealVar("acp_dkstz_pipi_obs",  "A_{CP} (DK^{*}, #pi#pi)", 0, -1e4, 1e4))); // A_d^pipi
	observables->add(*(new RooRealVar("rcp_dkstz_pipi_obs",  "R_{CP} (DK^{*}, #pi#pi)", 1, -1e4, 1e4))); // R_d^pipi
	observables->add(*(new RooRealVar("rp_dkstz_obs",        "R_{+} (DK^{*})",          1, -1e4, 1e4))); // R_d^+
	observables->add(*(new RooRealVar("rm_dkstz_obs",        "R_{-} (DK^{*})",          1, -1e4, 1e4))); // R_d^-
}


void PDF_GLWADS_DKstz_hh::setObservables(config c)
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
						 obsValSource = "3fb-1 LHCb-PAPER-2014-028-v2, June 4";
						 setObservable("acp_dkstz_kk_obs",   -0.198); //   -0.09703     -0.46554    // A_d^KK
						 setObservable("afav_dkstz_kpi_obs", -0.032); //   -0.00626      0.02810    // A_d^Kpi
						 setObservable("rcp_dkstz_kk_obs",    1.054); //    0.89809      1.08514    // R_d^KK
						 setObservable("acp_dkstz_pipi_obs", -0.092); //   -0.09703     -0.46554    // A_d^pipi
						 setObservable("rcp_dkstz_pipi_obs",  1.214); //    0.89809      1.08514    // R_d^pipi
						 setObservable("rp_dkstz_obs",        0.057); //    0.08537      0.06271    // R_d^+
						 setObservable("rm_dkstz_obs",        0.056); //    0.11856      0.11395    // R_d^-
						 // truth values corresponding to:                 ^^ rB=0.3    ^^ rB=0.3   
						 //                                                   dB=190       dB=270   
						 break;
					 }
		default:{
					cout << "PDF_GLW_DzKstz::setObservables : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}

void PDF_GLWADS_DKstz_hh::setUncertainties(config c)
{
	switch(c)
	{
		case lumi3fb:{
						 obsErrSource = "3fb-1 LHCb-PAPER-2014-028-v2, June 4";
						 StatErr[ 0] = 0.145;  // A_d^KK   
						 StatErr[ 1] = 0.041;  // A_d^Kpi  
						 StatErr[ 2] = 0.165;  // R_d^KK   
						 StatErr[ 3] = 0.217;  // A_d^pipi 
						 StatErr[ 4] = 0.283;  // R_d^pipi 
						 StatErr[ 5] = 0.029;  // R_d^+
						 StatErr[ 6] = 0.032;  // R_d^-

						 SystErr[ 0] = 0.02;   // A_d^KK   
						 SystErr[ 1] = 0.02;   // A_d^Kpi  
						 SystErr[ 2] = 0.044;  // R_d^KK   
						 SystErr[ 3] = 0.019;  // A_d^pipi 
						 SystErr[ 4] = 0.053;  // R_d^pipi 
						 SystErr[ 5] = 0.012;  // R_d^+    
						 SystErr[ 6] = 0.012;  // R_d^-   
						 break;
					 }
		case lumi9fb:{
						 setUncertainties(lumi3fb);
						 obsErrSource = "9fb-1 errors obtained from scaling down the 3fb-1 errors (lumi3fb)";
						 for ( int i=0; i<nObs; i++ ){
							 StatErr[i] /= (sqrt(2.7));
							 SystErr[i] /= (sqrt(2.7));
						 }
						 break;
					 }
		default:{
					cout << "PDF_GLWADS_DKstz_hh::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_GLWADS_DKstz_hh::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi3fb:{
						 corSource = "3fb-1 LHCb-ANA-2012-118-v3.1";
						 double myCorData[] = {   1.000,  0.000,  0.060,  0.000,  0.000,  0.001, -0.001,  // AdKK
							 0.000,  1.000, -0.008,  0.000, -0.006,  0.091,  0.083,  // AdKpi
							 0.060, -0.008,  1.000, -0.001,  0.053,  0.031, -0.029,  // RdKK
							 0.000,  0.000, -0.001,  1.000,  0.009,  0.000,  0.000,  // Adpipi
							 0.000, -0.006,  0.053,  0.009,  1.000,  0.020, -0.019,  // Rdpipi
							 0.001,  0.091,  0.031,  0.000,  0.020,  1.000, -0.081,  // Rd+
							 -0.001,  0.083, -0.029,  0.000, -0.019, -0.081,  1.000}; // Rd-
						 corStatMatrix = TMatrixDSym(nObs,myCorData);
						 double myCorData2[] = {  1.000,  0.995,  0.759,  0.997,  0.789,  0.081,  0.084,  // AdKK
							 0.995,  1.000,  0.745,  0.998,  0.779,  0.008,  0.008,  // AdKpi
							 0.759,  0.745,  1.000,  0.749,  0.994,  0.226,  0.218,  // RdKK
							 0.997,  0.998,  0.749,  1.000,  0.778,  0.045,  0.044,  // Adpipi
							 0.789,  0.779,  0.994,  0.778,  1.000,  0.175,  0.172,  // Rdpipi
							 0.081,  0.008,  0.226,  0.045,  0.175,  1.000,  0.997,  // Rd+
							 0.084,  0.008,  0.218,  0.044,  0.172,  0.997,  1.000}; // Rd-
						 corSystMatrix = TMatrixDSym(nObs,myCorData2);      
						 break;
					 }
		default:{ 
					cout << "PDF_GLW_DzKstz::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}    
	}
} 


void PDF_GLWADS_DKstz_hh::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
