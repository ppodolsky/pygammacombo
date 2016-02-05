/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Feb 2014
 *
 * The old version with 13 observables (Rkp's instead of Rcp+)
 * is in src/PDF_GLWADS_Dhpipi_hh_13.* .
 *
 **/

#include "PDF_GLWADS_Dhpipi_hh.h"

	PDF_GLWADS_Dhpipi_hh::PDF_GLWADS_Dhpipi_hh(config cObs, config cErr, config cCor, ParametersAbs* pars, TString d)
: PDF_Abs(11)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	name = "glwads-dhpipi-hh";
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

	PDF_GLWADS_Dhpipi_hh::PDF_GLWADS_Dhpipi_hh(ParametersAbs* pars, TString d, int nObs)
: PDF_Abs(nObs)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	this->dir = d;
}


PDF_GLWADS_Dhpipi_hh::~PDF_GLWADS_Dhpipi_hh(){}


void PDF_GLWADS_Dhpipi_hh::initParameters()
{
	parameters = new RooArgList("parameters");
	parameters->add(*(p->get("r_dkpipi")));
	parameters->add(*(p->get("d_dkpipi")));
	parameters->add(*(p->get("k_dkpipi")));
	parameters->add(*(p->get("r_dpipipi")));
	parameters->add(*(p->get("d_dpipipi")));
	parameters->add(*(p->get("k_dpipipi")));
	parameters->add(*(p->get("g")));
	parameters->add(*(p->get("rD_kpi")));
	parameters->add(*(p->get("dD_kpi")));
	parameters->add(*(p->get("AcpDKK")));
	parameters->add(*(p->get("AcpDpipi")));
}


void PDF_GLWADS_Dhpipi_hh::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	theory->add(*(new RooFormulaVar("rcp_dkpipi_th",       "rcp_dkpipi_th",       "1 + r_dkpipi^2 + 2*k_dkpipi*r_dkpipi*cos(d_dkpipi)*cos(g)", *p)));
	theory->add(*(new RooFormulaVar("afav_dkpipi_kpi_th",  "afav_dkpipi_kpi_th",  "2*k_dkpipi *r_dkpipi *rD_kpi*sin(g)*sin(d_dkpipi -dD_kpi) / (1 + r_dkpipi^2  * rD_kpi^2 + 2*k_dkpipi *r_dkpipi *rD_kpi*cos(g)*cos(d_dkpipi -dD_kpi))", *p)));
	theory->add(*(new RooFormulaVar("afav_dpipipi_kpi_th", "afav_dpipipi_kpi_th", "2*k_dpipipi*r_dpipipi*rD_kpi*sin(g)*sin(d_dpipipi-dD_kpi) / (1 + r_dpipipi^2 * rD_kpi^2 + 2*k_dpipipi*r_dpipipi*rD_kpi*cos(g)*cos(d_dpipipi-dD_kpi))", *p)));
	theory->add(*(new RooFormulaVar("acp_dkpipi_kk_th",    "acp_dkpipi_kk_th",    "2*k_dkpipi *r_dkpipi *sin(d_dkpipi) *sin(g) / (1 + r_dkpipi^2  + 2*k_dkpipi *r_dkpipi *cos(d_dkpipi) *cos(g)) + AcpDKK", *p)));
	theory->add(*(new RooFormulaVar("acp_dkpipi_pipi_th",  "acp_dkpipi_pipi_th",  "2*k_dkpipi *r_dkpipi *sin(d_dkpipi) *sin(g) / (1 + r_dkpipi^2  + 2*k_dkpipi *r_dkpipi *cos(d_dkpipi) *cos(g)) + AcpDpipi", *p)));
	theory->add(*(new RooFormulaVar("acp_dpipipi_kk_th",   "acp_dpipipi_kk_th",   "2*k_dpipipi*r_dpipipi*sin(d_dpipipi)*sin(g) / (1 + r_dpipipi^2 + 2*k_dpipipi*r_dpipipi*cos(d_dpipipi)*cos(g)) + AcpDKK", *p)));
	theory->add(*(new RooFormulaVar("acp_dpipipi_pipi_th", "acp_dpipipi_pipi_th", "2*k_dpipipi*r_dpipipi*sin(d_dpipipi)*sin(g) / (1 + r_dpipipi^2 + 2*k_dpipipi*r_dpipipi*cos(d_dpipipi)*cos(g)) + AcpDpipi", *p)));
	theory->add(*(new RooFormulaVar("rp_dkpipi_th",        "rp_dkpipi_th",        "(r_dkpipi^2  + rD_kpi^2 + 2*k_dkpipi *r_dkpipi *rD_kpi*cos( g+d_dkpipi +dD_kpi)) / (1 + r_dkpipi^2 *rD_kpi^2 + 2*k_dkpipi *r_dkpipi *rD_kpi*cos( g +d_dkpipi -dD_kpi))", *p)));
	theory->add(*(new RooFormulaVar("rm_dkpipi_th",        "rm_dkpipi_th",        "(r_dkpipi^2  + rD_kpi^2 + 2*k_dkpipi *r_dkpipi *rD_kpi*cos(-g+d_dkpipi +dD_kpi)) / (1 + r_dkpipi^2 *rD_kpi^2 + 2*k_dkpipi *r_dkpipi *rD_kpi*cos(-g +d_dkpipi -dD_kpi))", *p)));
	theory->add(*(new RooFormulaVar("rp_dpipipi_th",       "rp_dpipipi_th",       "(r_dpipipi^2 + rD_kpi^2 + 2*k_dpipipi*r_dpipipi*rD_kpi*cos( g+d_dpipipi+dD_kpi)) / (1 + r_dpipipi^2*rD_kpi^2 + 2*k_dpipipi*r_dpipipi*rD_kpi*cos( g +d_dpipipi-dD_kpi))", *p)));
	theory->add(*(new RooFormulaVar("rm_dpipipi_th",       "rm_dpipipi_th",       "(r_dpipipi^2 + rD_kpi^2 + 2*k_dpipipi*r_dpipipi*rD_kpi*cos(-g+d_dpipipi+dD_kpi)) / (1 + r_dpipipi^2*rD_kpi^2 + 2*k_dpipipi*r_dpipipi*rD_kpi*cos(-g +d_dpipipi-dD_kpi))", *p)));
}


void PDF_GLWADS_Dhpipi_hh::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("rcp_dkpipi_obs",       "R_{CP+} (Dh#pi#pi)",           1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("afav_dkpipi_kpi_obs",  "Afav (DK#pi#pi, K#pi)",        0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("afav_dpipipi_kpi_obs", "Afav (D#pi#pi#pi, K#pi)",      0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dkpipi_kk_obs",    "ACP (DK#pi#pi, KK)",           0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dkpipi_pipi_obs",  "ACP (DK#pi#pi, #pi#pi)",       0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dpipipi_kk_obs",   "ACP (D#pi#pi#pi, KK)",         0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dpipipi_pipi_obs", "ACP (D#pi#pi#pi, #pi#pi)",     0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rp_dkpipi_obs",        "R+ (DK#pi#pi, K#pi)",          1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rm_dkpipi_obs",        "R- (DK#pi#pi, K#pi)",          1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rp_dpipipi_obs",       "R+ (D#pi#pi#pi, K#pi)",        1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rm_dpipipi_obs",       "R- (D#pi#pi#pi, K#pi)",        1, -1e4, 1e4)));
}


void PDF_GLWADS_Dhpipi_hh::setObservables(config c)
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
						 obsValSource = "3fb-1, paper update, Steve's email from 30.7.2015";
						 setObservable("rcp_dkpipi_obs",        1.040);   // 0
             setObservable("afav_dkpipi_kpi_obs",   0.013);   // 1
						 setObservable("afav_dpipipi_kpi_obs", -0.002);   // 2
             setObservable("acp_dkpipi_kk_obs",    -0.045);   // 3
						 setObservable("acp_dkpipi_pipi_obs",  -0.054);   // 4
						 setObservable("acp_dpipipi_kk_obs",   -0.019);   // 5
						 setObservable("acp_dpipipi_pipi_obs", -0.013);   // 6
             setObservable("rp_dkpipi_obs",         0.0107);  // 7
						 setObservable("rm_dkpipi_obs",         0.0053);  // 8
						 setObservable("rp_dpipipi_obs",        0.00432); // 9
						 setObservable("rm_dpipipi_obs",        0.00421); // 10
						 break;
					 }
		default:{
					cout << "PDF_GLWADS_Dhpipi_hh::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_GLWADS_Dhpipi_hh::setUncertainties(config c)
{
	switch(c)
	{
		case lumi3fb:{
						 obsErrSource = "3fb-1, paper draft, Steve's email from 30.7.2015";
						 setUncertainty("rcp_dkpipi_obs",        0.064  , 0.0    );
						 setUncertainty("afav_dkpipi_kpi_obs",   0.019  , 0.013  );
						 setUncertainty("afav_dpipipi_kpi_obs",  0.003  , 0.011  );
						 setUncertainty("acp_dkpipi_kk_obs",     0.064  , 0.011  );
						 setUncertainty("acp_dkpipi_pipi_obs",   0.101  , 0.011  );
						 setUncertainty("acp_dpipipi_kk_obs",    0.011  , 0.010  );
						 setUncertainty("acp_dpipipi_pipi_obs",  0.016  , 0.010  );
						 setUncertainty("rp_dkpipi_obs",         0.0060 , 0.0011 );
						 setUncertainty("rm_dkpipi_obs",         0.0045 , 0.0006 );
						 setUncertainty("rp_dpipipi_obs",        0.00053, 0.00021);
						 setUncertainty("rm_dpipipi_obs",        0.00053, 0.00021);
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
					cout << "PDF_GLWADS_Dhpipi_hh::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_GLWADS_Dhpipi_hh::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi3fb:{
						 corSource = "3fb-1, LHCb-ANA-2014-011v4p1, only significant correlations are in Acp, no information on syst.cor.";
						 corStatMatrix[3][4] = 0.20; // acp_dkpipi_kk_obs : acp_dkpipi_pipi_obs
						 corStatMatrix[5][6] = 0.08; // acp_dpipipi_kk_obs : acp_dpipipi_pipi_obs
						 break;
					 }
		default:{
					cout << "PDF_GLWADS_Dhpipi_hh::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_GLWADS_Dhpipi_hh::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
