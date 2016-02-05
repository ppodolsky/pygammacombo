/**
 * Gamma Combination
 * Author: Matthew Kenzie matthew.kenzie@cern.ch
 * Date: August 2015
 *
 **/

#include "PDF_GLW_DKDpi_hh_Dmix_newVars.h"

PDF_GLW_DKDpi_hh_Dmix_newVars::PDF_GLW_DKDpi_hh_Dmix_newVars(config cObs, config cErr, config cCor,
		double Mxy, ParametersAbs* pars, TString d)
: PDF_Abs(7)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	name = "glw-dkdpi-hh-dmix-newvars";
	_Mxy = Mxy;
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_GLW_DKDpi_hh_Dmix_newVars::~PDF_GLW_DKDpi_hh_Dmix_newVars(){}


void PDF_GLW_DKDpi_hh_Dmix_newVars::initParameters()
{
	parameters = new RooArgList("parameters");
	parameters->add(*(p->get("r_dk")));
	parameters->add(*(p->get("d_dk")));
	parameters->add(*(p->get("r_dpi")));
	parameters->add(*(p->get("d_dpi")));
	parameters->add(*(p->get("g")));
	parameters->add(*(p->get("rD_kpi")));
	parameters->add(*(p->get("dD_kpi")));
	parameters->add(*(p->get("AcpDKK")));
	parameters->add(*(p->get("AcpDpipi")));
	parameters->add(*(p->get("RBRdkdpi")));
	parameters->add(*(p->get("xD")));
	parameters->add(*(p->get("yD")));
}


void PDF_GLW_DKDpi_hh_Dmix_newVars::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
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

	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	theory->add(*(new RooGLWADSDmixAcpVar      ("acp_dk_kk_th",     "RooGLWADSDmixAcpVar"     , rbk, dbk, kbk, rfGLW, dfGLW, kf, g, xD, yD, _Mxy, AcpDKK)));
	theory->add(*(new RooGLWADSDmixAcpVar      ("acp_dk_pipi_th",   "RooGLWADSDmixAcpVar"     , rbk, dbk, kbk, rfGLW, dfGLW, kf, g, xD, yD, _Mxy, AcpDpp)));
	theory->add(*(new RooGLWADSDmixAcpVar      ("acp_dpi_kk_th",    "RooGLWADSDmixAcpVar"     , rbp, dbp, kbp, rfGLW, dfGLW, kf, g, xD, yD, _Mxy, AcpDKK)));
	theory->add(*(new RooGLWADSDmixAcpVar      ("acp_dpi_pipi_th",  "RooGLWADSDmixAcpVar"     , rbp, dbp, kbp, rfGLW, dfGLW, kf, g, xD, yD, _Mxy, AcpDpp)));
	theory->add(*(new RooGLWADSDmixRcpRatioVar ("rcp_kk_th", 			  "RooGLWADSDmixRcpRatioVar", rbk, dbk, kbk, rbp, dbp, kbp, rf, df, kf, g, xD, yD, _Mxy)));
	theory->add(*(new RooGLWADSDmixRcpRatioVar ("rcp_pipi_th", 		  "RooGLWADSDmixRcpRatioVar", rbk, dbk, kbk, rbp, dbp, kbp, rf, df, kf, g, xD, yD, _Mxy)));
	theory->add(*(new RooGLWADSDmixRkpVar      ("rkp_kpi_th",       "RooGLWADSDmixRkpVar"     , Rcab, rbk, dbk, kbk, rbp, dbp, kbp, rf, df, kf, g, xD, yD, _Mxy, "fav")));
}

void PDF_GLW_DKDpi_hh_Dmix_newVars::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("acp_dk_kk_obs",    "ACP (DK KK)",         0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dk_pipi_obs",  "ACP (DK #pi#pi)",     0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dpi_kk_obs",   "ACP (D#pi KK)",       0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dpi_pipi_obs", "ACP (D#pi #pi#pi)",   0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rcp_kk_obs",       "R_{CP} (KK)",     		 1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rcp_pipi_obs",     "R_{CP} (#pi#pi)", 		 1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rkp_kpi_obs",      "R_{K/#pi} (K#pi)",    1, -1e4, 1e4)));

  latexObservables.clear();
  latexObservables.push_back("\\AcpDkKK");
  latexObservables.push_back("\\AcpDkPipi");
  latexObservables.push_back("\\AcpDpiKK");
  latexObservables.push_back("\\AcpDpiPipi");
  latexObservables.push_back("\\RCPKK");
  latexObservables.push_back("\\RCPPiPi");
  latexObservables.push_back("\\RkpKpi");
}

void PDF_GLW_DKDpi_hh_Dmix_newVars::setObservables(config c)
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
				 		setObservable( "acp_dk_kk_obs",    8.6577e-02 );
				 		setObservable( "acp_dk_pipi_obs",  1.2760e-01 );
				 		setObservable( "acp_dpi_kk_obs",  -1.4524e-02 );
				 		setObservable( "acp_dpi_pipi_obs", 4.2984e-03 );
				 		setObservable( "rcp_kk_obs",       9.6834e-01 );
				 		setObservable( "rcp_pipi_obs",     1.0022e+00 );
				 		setObservable( "rkp_kpi_obs",      7.7937e-02 );
						break;
				 }
		case check:{
						obsValSource = "check";
            //setObservable( "acp_dk_kk_obs",    8.6577e-02 ); // THE REAL VALUE
				 		setObservable( "acp_dk_kk_obs",    0.12497 ); // check
				 		setObservable( "acp_dk_pipi_obs",  1.2760e-01 );
				 		setObservable( "acp_dpi_kk_obs",  -1.4524e-02 ); // THE REAL VALUE
				 		setObservable( "acp_dpi_pipi_obs", 4.2984e-03 ); // THE REAL VALUE
            //setObservable( "acp_dpi_kk_obs",  -0.0087 ); // check
            //setObservable( "acp_dpi_pipi_obs",-0.0062 ); // check
				 		setObservable( "rcp_kk_obs",       9.6834e-01 );
				 		setObservable( "rcp_pipi_obs",     1.0022e+00 );
				 		setObservable( "rkp_kpi_obs",      7.7937e-02 );
						break;
				 }
		default:{
				 		cout << "PDF_GLW_DKDpi_hh_Dmix_newVars::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
						exit(1);
				 }
	}
}

void PDF_GLW_DKDpi_hh_Dmix_newVars::setUncertainties(config c)
{
	switch(c){
		case lumi3fb:
			{
						obsErrSource = "3fb-1 ANA v7 - lifted from gammadini "; // https://twiki.cern.ch/twiki/pub/LHCbPhysics/B2D0K/LHCb-ANA-2014-071-v7.pdf (see Vavas email 04/08/15)
						StatErr[0]  = 2.02e-02 ; // acp_dk_kk
						StatErr[1]  = 3.69e-02 ; // acp_dk_pipi
						StatErr[2]  = 4.95e-03 ; // acp_dpi_kk
						StatErr[3]  = 8.60e-03 ; // acp_dpi_pipi
						StatErr[4]  = 2.17e-02 ; // rcp_kk
						StatErr[5]  = 4.00e-02 ; // rcp_pipi
						StatErr[6]  = 5.82e-04 ; // rkp_kpi

						SystErr[0]  = 0.0081   ; // acp_dk_kk
						SystErr[1]  = 0.012    ; // acp_dk_pipi
						SystErr[2]  = 0.0017   ; // acp_dpi_kk
						SystErr[3]  = 0.00309  ; // acp_dpi_pipi
						SystErr[4]  = 0.021    ; // rcp_kk
						SystErr[5]  = 0.026    ; // rcp_pipi
						SystErr[6]  = 0.0019   ; // rkp_kpi

						break;
			}
		default:
			{
				cout << "PDF_GLW_DKDpi_hh_Dmix_newVars::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}
	}
}

void PDF_GLW_DKDpi_hh_Dmix_newVars::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi3fb:
			{
						corSource = "3fb-1 ANA v7 - lifted from gammadini "; // https://twiki.cern.ch/twiki/pub/LHCbPhysics/B2D0K/LHCb-ANA-2014-071-v7.pdf (see Vavas email 04/08/15)

						// lifted from gammadini
						const double statCorrelations[49] = {
						 1.0   , 0.0043,-0.0069, 0.0158,-0.0144,-0.0001,-0.001,    // acp_dk_kk
						 0.0043, 1.0   , 0.0160,-0.0359,-0.0002,-0.0382,-0.0021,   // acp_dk_pipi
						-0.0069, 0.0160, 1.0   , 0.0639,-0.0013, 0.0000,-0.0011,   // acp_dpi_kk
						 0.0158,-0.0359, 0.0639, 1.0   , 0.0001,-0.0029,-0.0005,   // acp_dpi_pipi
						-0.0144,-0.0002,-0.0013, 0.0001, 1.0   , 0.0597,-0.3165,   // rcp_kk
						-0.0001,-0.0382, 0.0000,-0.0029, 0.0597, 1.0   ,-0.1756,   // rcp_pipi
						-0.001, -0.0021,-0.0011,-0.0005,-0.3165,-0.1756, 1.0   };  // rkp_kpi

						corStatMatrix = TMatrixDSym( nObs, statCorrelations );

						// lifted from gammadini
						const double systCorrelations[49] = {
						  1.00, -0.02, -0.80,  0.09,  0.03, -0.28,  0.07,   // acp_dk_kk
						 -0.02,  1.00,  0.19, -0.42, -0.22,  0.11, -0.07,   // acp_dk_pipi
						 -0.80,  0.19,  1.00,  0.11, -0.16,  0.20, -0.13,   // acp_dpi_kk
						  0.09, -0.42,  0.11,  1.00, -0.08, -0.03, -0.09,   // acp_dpi_pipi
						  0.03, -0.22, -0.16, -0.08,  1.00,  0.17,  0.21,   // rcp_kk
						 -0.28,  0.11,  0.20, -0.03,  0.17,  1.00, -0.11,   // rcp_pipi
						  0.07, -0.07, -0.13, -0.09,  0.21, -0.11,  1.00};  // rkp_kpi

						corSystMatrix = TMatrixDSym( nObs, systCorrelations );

						break;
			}
		default:
			{
				cout << "PDF_GLW_DKDpi_hh_Dmix_newVars::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}
	}
}

void PDF_GLW_DKDpi_hh_Dmix_newVars::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
