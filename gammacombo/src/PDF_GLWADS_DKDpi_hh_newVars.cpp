/**
 * Gamma Combination
 * Author: Matthew Kenzie matthew.kenzie@cern.ch
 * Date: August 2015
 *
 **/

#include "PDF_GLWADS_DKDpi_hh_newVars.h"

PDF_GLWADS_DKDpi_hh_newVars::PDF_GLWADS_DKDpi_hh_newVars(config cObs, config cErr, config cCor,
		ParametersAbs* pars, TString d)
: PDF_Abs(12)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	name = "glwads-dkdpi-hh-newvars";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_GLWADS_DKDpi_hh_newVars::~PDF_GLWADS_DKDpi_hh_newVars(){}


void PDF_GLWADS_DKDpi_hh_newVars::initParameters()
{
	parameters = new RooArgList("parameters");
	parameters->add(*(p->get("r_dk")));
	parameters->add(*(p->get("d_dk")));
	parameters->add(*(p->get("r_dpi")));
	parameters->add(*(p->get("d_dpi")));
	parameters->add(*(p->get("g")));
	parameters->add(*(p->get("rD_kpi")));
	parameters->add(*(p->get("dD_kpi")));
	parameters->add(*(p->get("RBRdkdpi")));
	parameters->add(*(p->get("AcpDKK")));
	parameters->add(*(p->get("AcpDpipi")));
}


void PDF_GLWADS_DKDpi_hh_newVars::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  theory->add(*(new RooFormulaVar("aads_dk_kpi_th",  "aads_dk_kpi_th",  " ( 2*r_dk*rD_kpi*sin(d_dk+dD_kpi)*sin(g) ) / ( r_dk^2 + rD_kpi^2 + 2*r_dk*rD_kpi*cos(d_dk + dD_kpi)*cos(g) ) ", *p)));
  theory->add(*(new RooFormulaVar("aads_dpi_kpi_th", "aads_dpi_kpi_th", " ( 2*r_dpi*rD_kpi*sin(d_dpi+dD_kpi)*sin(g) ) / ( r_dpi^2 + rD_kpi^2 + 2*r_dpi*rD_kpi*cos(d_dpi + dD_kpi)*cos(g) ) ", *p)));
	theory->add(*(new RooFormulaVar("acp_dk_kk_th",    "acp_dk_kk_th",    "2*r_dk *sin(d_dk) *sin(g) / (1 + r_dk^2  + 2*r_dk *cos(d_dk) *cos(g)) + AcpDKK", *p)));
	theory->add(*(new RooFormulaVar("acp_dk_pipi_th",  "acp_dk_pipi_th",  "2*r_dk *sin(d_dk) *sin(g) / (1 + r_dk^2  + 2*r_dk *cos(d_dk) *cos(g)) + AcpDpipi", *p)));
	theory->add(*(new RooFormulaVar("acp_dpi_kk_th",   "acp_dpi_kk_th",   "2*r_dpi *sin(d_dpi) *sin(g) / (1 + r_dpi^2  + 2*r_dpi *cos(d_dpi) *cos(g)) + AcpDKK", *p)));
	theory->add(*(new RooFormulaVar("acp_dpi_pipi_th", "acp_dpi_pipi_th", "2*r_dpi *sin(d_dpi) *sin(g) / (1 + r_dpi^2  + 2*r_dpi *cos(d_dpi) *cos(g)) + AcpDpipi", *p)));
	theory->add(*(new RooFormulaVar("afav_dk_kpi_th",  "afav_dk_kpi_th",  "2*r_dk *rD_kpi*sin(g)*sin(d_dk -dD_kpi) / (1 + r_dk^2  * rD_kpi^2 + 2*r_dk *rD_kpi*cos(g)*cos(d_dk -dD_kpi))", *p)));
  theory->add(*(new RooFormulaVar("rads_dk_kpi_th",  "rads_dk_kpi_th",  " ( r_dk^2 + rD_kpi^2 + 2*r_dk*rD_kpi*cos(d_dk + dD_kpi)*cos(g) ) / ( 1 + (r_dk*rD_kpi)^2 + 2*r_dk*rD_kpi*cos(d_dk-dD_kpi)*cos(g) )", *p)));
  theory->add(*(new RooFormulaVar("rads_dpi_kpi_th", "rads_dpi_kpi_th", " ( r_dpi^2 + rD_kpi^2 + 2*r_dpi*rD_kpi*cos(d_dpi + dD_kpi)*cos(g) ) / ( 1 + (r_dpi*rD_kpi)^2 + 2*r_dpi*rD_kpi*cos(d_dpi-dD_kpi)*cos(g) )", *p)));
	theory->add(*(new RooFormulaVar("rcp_kk_th",       "rcp_kk_th",       "(1 + r_dk^2 + 2*r_dk*cos(d_dk)*cos(g))", *p)));
	theory->add(*(new RooFormulaVar("rcp_pipi_th",     "rcp_pipi_th",     "(1 + r_dk^2 + 2*r_dk*cos(d_dk)*cos(g))", *p)));
	theory->add(*(new RooFormulaVar("rkp_kpi_th",      "rkp_kpi_th",      "RBRdkdpi*(1 + r_dk^2 * rD_kpi^2 + 2*r_dk*rD_kpi*cos(g)*cos(d_dk-dD_kpi))/(1 + r_dpi^2 * rD_kpi^2 + 2*r_dpi*rD_kpi*cos(g)*cos(d_dpi-dD_kpi))", *p)));

}

void PDF_GLWADS_DKDpi_hh_newVars::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("aads_dk_kpi_obs",  "A_{ADS} (DK K#pi)",   0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("aads_dpi_kpi_obs", "A_{ADS} (D#pi K#pi)", 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dk_kk_obs",    "ACP (DK KK)",         0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dk_pipi_obs",  "ACP (DK #pi#pi)",     0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dpi_kk_obs",   "ACP (D#pi KK)",       0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dpi_pipi_obs", "ACP (D#pi #pi#pi)",   0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("afav_dk_kpi_obs",  "Afav (DK K#pi)",      0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rads_dk_kpi_obs",  "R_{ADS} (DK K#pi)",   0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rads_dpi_kpi_obs", "R_{ADS} (D#pi K#pi)", 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rcp_kk_obs",       "R_{CP} (KK)",     		 1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rcp_pipi_obs",     "R_{CP} (#pi#pi)", 		 1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rkp_kpi_obs",      "R_{K/#pi} (K#pi)",    1, -1e4, 1e4)));

  latexObservables.clear();
  latexObservables.push_back("\\AadsDK");
  latexObservables.push_back("\\AadsDPi");
  latexObservables.push_back("\\AcpDkKK");
  latexObservables.push_back("\\AcpDkPipi");
  latexObservables.push_back("\\AcpDpiKK");
  latexObservables.push_back("\\AcpDpiPipi");
  latexObservables.push_back("\\AfavDkKpi");
  latexObservables.push_back("\\RadsDK");
  latexObservables.push_back("\\RadsDPi");
  latexObservables.push_back("\\RCPKK");
  latexObservables.push_back("\\RCPPiPi");
  latexObservables.push_back("\\RkpKpi");
}

void PDF_GLWADS_DKDpi_hh_newVars::setObservables(config c)
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
						obsValSource = "3fb-1 ANA v7 - lifted from gammadini "; // https://twiki.cern.ch/twiki/pub/LHCbPhysics/B2D0K/LHCb-ANA-2014-071-v7.pdf (see Vavas email 04/08/15)
				 		setObservable( "aads_dk_kpi_obs", -4.0267e-01 );
				 		setObservable( "aads_dpi_kpi_obs", 1.0031e-01 );
				 		setObservable( "acp_dk_kk_obs",    8.6577e-02 );
				 		setObservable( "acp_dk_pipi_obs",  1.2760e-01 );
				 		setObservable( "acp_dpi_kk_obs",  -1.4524e-02 );
				 		setObservable( "acp_dpi_pipi_obs", 4.2984e-03 );
				 		setObservable( "afav_dk_kpi_obs", -1.9441e-02 );
				 		setObservable( "rads_dk_kpi_obs",  1.8757e-02 );
				 		setObservable( "rads_dpi_kpi_obs", 3.5977e-03 );
				 		setObservable( "rcp_kk_obs",       9.6834e-01 );
				 		setObservable( "rcp_pipi_obs",     1.0022e+00 );
				 		setObservable( "rkp_kpi_obs",      7.7937e-02 );
						break;
				 }
		case check:{
						obsValSource = "check";
				 		setObservable( "aads_dk_kpi_obs", -4.0267e-01 );
				 		setObservable( "aads_dpi_kpi_obs", 1.0031e-01 );
            //setObservable( "acp_dk_kk_obs",    8.6577e-02 ); // THE REAL VALUE
				 		setObservable( "acp_dk_kk_obs",    0.12497 ); // check
				 		setObservable( "acp_dk_pipi_obs",  1.2760e-01 );
				 		setObservable( "acp_dpi_kk_obs",  -1.4524e-02 ); // THE REAL VALUE
				 		setObservable( "acp_dpi_pipi_obs", 4.2984e-03 ); // THE REAL VALUE
            //setObservable( "acp_dpi_kk_obs",  -0.0087 ); // check
            //setObservable( "acp_dpi_pipi_obs",-0.0062 ); // check
				 		setObservable( "afav_dk_kpi_obs", -1.9441e-02 );
				 		setObservable( "rads_dk_kpi_obs",  1.8757e-02 );
            setObservable( "rads_dpi_kpi_obs", 3.5977e-03 ); // THE REAL VALUE
            //setObservable( "rads_dpi_kpi_obs", 3.75e-03 ); // check
				 		setObservable( "rcp_kk_obs",       9.6834e-01 );
				 		setObservable( "rcp_pipi_obs",     1.0022e+00 );
				 		setObservable( "rkp_kpi_obs",      7.7937e-02 );
						break;
				 }
		default:{
				 		cout << "PDF_GLWADS_DKDpi_hh_newVars::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
						exit(1);
				 }
	}
}

void PDF_GLWADS_DKDpi_hh_newVars::setUncertainties(config c)
{
	switch(c){
		case lumi3fb:
			{
						obsErrSource = "3fb-1 ANA v7 - lifted from gammadini "; // https://twiki.cern.ch/twiki/pub/LHCbPhysics/B2D0K/LHCb-ANA-2014-071-v7.pdf (see Vavas email 04/08/15)
						StatErr[0]  = 5.62e-02 ; // aads_dk_kpi
						StatErr[1]  = 3.14e-02 ; // aads_dpi_kpi
						StatErr[2]  = 2.02e-02 ; // acp_dk_kk
						StatErr[3]  = 3.69e-02 ; // acp_dk_pipi
						StatErr[4]  = 4.95e-03 ; // acp_dpi_kk
						StatErr[5]  = 8.60e-03 ; // acp_dpi_pipi
						StatErr[6]  = 7.18e-03 ; // afav_dk_kpi
						StatErr[7]  = 1.14e-03 ; // rads_dk_kpi
						StatErr[8]  = 1.16e-04 ; // rads_dpi_kpi
						StatErr[9]  = 2.17e-02 ; // rcp_kk
						StatErr[10] = 4.00e-02 ; // rcp_pipi
						StatErr[11] = 5.82e-04 ; // rkp_kpi

						SystErr[0]  = 0.0106   ; // aads_dk_kpi
						SystErr[1]  = 0.0094   ; // aads_dpi_kpi
						SystErr[2]  = 0.0081   ; // acp_dk_kk
						SystErr[3]  = 0.012    ; // acp_dk_pipi
						SystErr[4]  = 0.0017   ; // acp_dpi_kk
						SystErr[5]  = 0.00309  ; // acp_dpi_pipi
						SystErr[6]  = 0.0060   ; // afav_dk_kpi
						SystErr[7]  = 0.0010   ; // rads_dk_kpi
						SystErr[8]  = 0.00009  ; // rads_dpi_kpi
						SystErr[9]  = 0.021    ; // rcp_kk
						SystErr[10] = 0.026    ; // rcp_pipi
						SystErr[11] = 0.0019   ; // rkp_kpi

						break;
			}
		default:
			{
				cout << "PDF_GLWADS_DKDpi_hh_newVars::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}
	}
}

void PDF_GLWADS_DKDpi_hh_newVars::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi3fb:
			{
						corSource = "3fb-1 ANA v7 - lifted from gammadini "; // https://twiki.cern.ch/twiki/pub/LHCbPhysics/B2D0K/LHCb-ANA-2014-071-v7.pdf (see Vavas email 04/08/15)

						// lifted from gammadini
						const double statCorrelations[144] = {
							1.0   ,-0.0474, 0.0023, 0.0012, 0.0093, 0.0053, 0.0078, 0.1024,-0.0032, 0.0006, 0.0009, 0.0003,
						 -0.0474, 1.0   , 0.0043, 0.0025, 0.0174, 0.0100, 0.0144, 0.0155,-0.0431, 0.0002, 0.0001, 0.0000,
							0.0023, 0.0043, 1.0   , 0.0043,-0.0069, 0.0158, 0.0243,-0.0003, 0.0001,-0.0144,-0.0001,-0.001,
							0.0012, 0.0025, 0.0043, 1.0   , 0.0160,-0.0359, 0.0143,-0.0010,-0.0000,-0.0002,-0.0382,-0.0021,
							0.0093, 0.0174,-0.0069, 0.0160, 1.0   , 0.0639, 0.0917,-0.0002,-0.0002,-0.0013, 0.0000,-0.0011,
							0.0053, 0.0100, 0.0158,-0.0359, 0.0639, 1.0   , 0.0530,-0.0001,-0.0001, 0.0001,-0.0029,-0.0005,
							0.0078, 0.0144, 0.0243, 0.0143, 0.0917, 0.053, 1.0    ,-0.0001,-0.0001, 0.0002, 0.0000,-0.0004,
							0.1024, 0.0155,-0.0003,-0.0010,-0.0002,-0.0001,-0.0001, 1.0   ,-0.0219, 0.0399, 0.0245,-0.1136,
						 -0.0032,-0.0431, 0.0001,-0.0000,-0.0002,-0.0001,-0.0001,-0.0219, 1.0   ,-0.0055,-0.0025, 0.0114,
							0.0006, 0.0002,-0.0144,-0.0002,-0.0013, 0.0001, 0.0002, 0.0399,-0.0055, 1.0   , 0.0597,-0.3165,
							0.0009, 0.0001,-0.0001,-0.0382, 0.0000,-0.0029, 0.0000, 0.0245,-0.0025, 0.0597, 1.0   ,-0.1756,
							0.0003, 0.0000,-0.001, -0.0021,-0.0011,-0.0005,-0.0004,-0.1136, 0.0114,-0.3165,-0.1756, 1.0   };

						corStatMatrix = TMatrixDSym( nObs, statCorrelations );

						// lifted from gammadini
						const double systCorrelations[144] = {
							1.00,  0.36, -0.06,  0.27,  0.30,  0.04,  0.09,  0.78, -0.43, -0.04,  0.23, -0.14,
							0.36,  1.00, -0.03,  0.31,  0.22, -0.06, -0.55,  0.59, -0.47, -0.01,  0.12, -0.04,
						 -0.06, -0.03,  1.00, -0.02, -0.80,  0.09,  0.09, -0.10, -0.06,  0.03, -0.28,  0.07,
							0.27,  0.31, -0.02,  1.00,  0.19, -0.42, -0.01,  0.35, -0.28, -0.22,  0.11, -0.07,
							0.30,  0.22, -0.80,  0.19,  1.00,  0.11,  0.09,  0.37, -0.21, -0.16,  0.20, -0.13,
							0.04, -0.06,  0.09, -0.42,  0.11,  1.00,  0.30, -0.03,  0.06, -0.08, -0.03, -0.09,
							0.09, -0.55,  0.09, -0.01,  0.09,  0.30,  1.00, -0.11,  0.05, -0.01, -0.02, -0.02,
							0.78,  0.59, -0.10,  0.35,  0.37, -0.03, -0.11,  1.00, -0.57, -0.14,  0.33, -0.22,
						 -0.43, -0.47, -0.06, -0.28, -0.21,  0.06,  0.05, -0.57,  1.00,  0.19,  0.10,  0.02,
						 -0.04, -0.01,  0.03, -0.22, -0.16, -0.08, -0.01, -0.14,  0.19,  1.00,  0.17,  0.21,
							0.23,  0.12, -0.28,  0.11,  0.20, -0.03, -0.02,  0.33,  0.10,  0.17,  1.00, -0.11,
						 -0.14, -0.04,  0.07, -0.07, -0.13, -0.09, -0.02, -0.22,  0.02,  0.21, -0.11,  1.00};

						corSystMatrix = TMatrixDSym( nObs, systCorrelations );

						break;
			}
		default:
			{
				cout << "PDF_GLWADS_DKDpi_hh_newVars::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}
	}
}

void PDF_GLWADS_DKDpi_hh_newVars::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
