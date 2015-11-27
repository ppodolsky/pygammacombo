/**
 * Gamma Combination
 * Author: Matthew Kenzie matthew.kenzie@cern.ch
 * Date: August 2015
 *
 **/

#include "PDF_GLWADS_DK_hh_Dmix_newVars.h"

PDF_GLWADS_DK_hh_Dmix_newVars::PDF_GLWADS_DK_hh_Dmix_newVars(config cObs, config cErr, config cCor,
		double Mxy, ParametersAbs* pars, TString d)
: PDF_Abs(7)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	name = "glwads-dk-hh-dmix-newvars";
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


PDF_GLWADS_DK_hh_Dmix_newVars::~PDF_GLWADS_DK_hh_Dmix_newVars(){}


void PDF_GLWADS_DK_hh_Dmix_newVars::initParameters()
{
	parameters = new RooArgList("parameters");
	parameters->add(*(p->get("r_dk")));
	parameters->add(*(p->get("d_dk")));
	parameters->add(*(p->get("g")));
	parameters->add(*(p->get("rD_kpi")));
	parameters->add(*(p->get("dD_kpi")));
	parameters->add(*(p->get("AcpDKK")));
	parameters->add(*(p->get("AcpDpipi")));
	parameters->add(*(p->get("xD")));
	parameters->add(*(p->get("yD")));
}


void PDF_GLWADS_DK_hh_Dmix_newVars::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	RooRealVar&  rbk    = *((RooRealVar*)p->find("r_dk"));
	RooRealVar&  dbk    = *((RooRealVar*)p->find("d_dk"));
	RooConstVar& kbk = RooConst(1);
	RooConstVar& rbp = RooConst(0); // assume rb(Dpi)=0 for DK only
	RooConstVar& dbp = RooConst(1); // then the phase and the
	RooConstVar& kbp = RooConst(1); // coherence factor values don't matter
	RooConstVar& kf = RooConst(1);
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
	theory->add(*(new RooGLWADSDmixAcpADSVar("aads_dk_kpi_th",   "RooGLWADSDmixAcpADSVar", rbk, dbk, kbk, rf, df, kf, g, xD, yD, _Mxy, AcpD)));
	theory->add(*(new RooGLWADSDmixAcpVar   ("acp_dk_kk_th",     "RooGLWADSDmixAcpVar"   , rbk, dbk, kbk, rfGLW, dfGLW, kf, g, xD, yD, _Mxy, AcpDKK)));
	theory->add(*(new RooGLWADSDmixAcpVar   ("acp_dk_pipi_th",   "RooGLWADSDmixAcpVar"   , rbk, dbk, kbk, rfGLW, dfGLW, kf, g, xD, yD, _Mxy, AcpDpp)));
	theory->add(*(new RooGLWADSDmixAcpVar   ("afav_dk_kpi_th",   "RooGLWADSDmixAcpVar"   , rbk, dbk, kbk, rf, df, kf, g, xD, yD, _Mxy, AcpD)));
	theory->add(*(new RooGLWADSDmixRADSVar  ("rads_dk_kpi_th",   "RooGLWADSDmixRADSVar"  , rbk, dbk, kbk, rf, df, kf, g, xD, yD, _Mxy, "")));
	// ratio to Dpi is 1 in DK only
	theory->add(*(new RooGLWADSDmixRcpVar   ("rcp_kk_th", 			 "RooGLWADSDmixRcpVar"   , rbk, dbk, kbk, rf, df, kf, g, xD, yD, _Mxy)));
	theory->add(*(new RooGLWADSDmixRcpVar   ("rcp_pipi_th", 		 "RooGLWADSDmixRcpVar"   , rbk, dbk, kbk, rf, df, kf, g, xD, yD, _Mxy)));
}

void PDF_GLWADS_DK_hh_Dmix_newVars::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("aads_dk_kpi_obs",  "A_{ADS} (DK K#pi)",   0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dk_kk_obs",    "ACP (DK KK)",         0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dk_pipi_obs",  "ACP (DK #pi#pi)",     0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("afav_dk_kpi_obs",  "Afav (DK K#pi)",      0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rads_dk_kpi_obs",  "R_{ADS} (DK K#pi)",   0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rcp_kk_obs",       "R_{CP} (KK)",     		 1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rcp_pipi_obs",     "R_{CP} (#pi#pi)", 		 1, -1e4, 1e4)));
}

void PDF_GLWADS_DK_hh_Dmix_newVars::setObservables(config c)
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
				 		setObservable( "acp_dk_kk_obs",    8.6577e-02 );
				 		setObservable( "acp_dk_pipi_obs",  1.2760e-01 );
				 		setObservable( "afav_dk_kpi_obs", -1.9441e-02 );
				 		setObservable( "rads_dk_kpi_obs",  1.8757e-02 );
				 		setObservable( "rcp_kk_obs",       9.6834e-01 );
				 		setObservable( "rcp_pipi_obs",     1.0022e+00 );
						break;
				 }
		default:{
				 		cout << "PDF_GLWADS_DK_hh_Dmix_newVars::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
						exit(1);
				 }
	}
}

void PDF_GLWADS_DK_hh_Dmix_newVars::setUncertainties(config c)
{
	switch(c){
		case lumi3fb:
			{
						obsErrSource = "3fb-1 ANA v7 - lifted from gammadini "; // https://twiki.cern.ch/twiki/pub/LHCbPhysics/B2D0K/LHCb-ANA-2014-071-v7.pdf (see Vavas email 04/08/15)
						StatErr[0]  = 5.62e-02 ; // aads_dk_kpi
						StatErr[1]  = 2.02e-02 ; // acp_dk_kk
						StatErr[2]  = 3.69e-02 ; // acp_dk_pipi
						StatErr[3]  = 7.18e-03 ; // afav_dk_kpi
						StatErr[4]  = 1.14e-03 ; // rads_dk_kpi
						StatErr[5]  = 2.17e-02 ; // rcp_kk
						StatErr[6]  = 4.00e-02 ; // rcp_pipi

						SystErr[0]  = 0.0106   ; // aads_dk_kpi
						SystErr[1]  = 0.0081   ; // acp_dk_kk
						SystErr[2]  = 0.012    ; // acp_dk_pipi
						SystErr[3]  = 0.0060   ; // afav_dk_kpi
						SystErr[4]  = 0.0010   ; // rads_dk_kpi
						SystErr[5]  = 0.021    ; // rcp_kk
						SystErr[6]  = 0.026    ; // rcp_pipi

						break;
			}
		default:
			{
				cout << "PDF_GLWADS_DK_hh_Dmix_newVars::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}
	}
}

void PDF_GLWADS_DK_hh_Dmix_newVars::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi3fb:
			{
						corSource = "3fb-1 ANA v7 - lifted from gammadini "; // https://twiki.cern.ch/twiki/pub/LHCbPhysics/B2D0K/LHCb-ANA-2014-071-v7.pdf (see Vavas email 04/08/15)

						// lifted from gammadini
						const double statCorrelations[49] = {
							1.0   , 0.0023, 0.0012, 0.0078, 0.1024, 0.0006, 0.0009,
							0.0023, 1.0,    0.0043, 0.0243,-0.0003,-0.0144,-0.0001,
							0.0012, 0.0043, 1.0   , 0.0143,-0.0010,-0.0002,-0.0382,
							0.0078, 0.0243, 0.0143, 1.0   ,-0.0001, 0.0002, 0.0000,
							0.1024,-0.0003,-0.0010,-0.0001, 1.0   , 0.0399, 0.0245,
							0.0006,-0.0144,-0.0002, 0.0002, 0.0399, 1.0   , 0.0597,
							0.0009,-0.0001,-0.0382, 0.0000, 0.0245, 0.0597, 1.0   };

						corStatMatrix = TMatrixDSym( nObs, statCorrelations );

						// lifted from gammadini
						const double systCorrelations[49] = {
							1.00, -0.06,  0.27,  0.09,  0.78,  0.23, -0.04,
						 -0.06,  1.00, -0.02,  0.09, -0.10, -0.28,  0.03,
							0.27, -0.02,  1.00, -0.01,  0.35,  0.11, -0.22,
							0.09,  0.09, -0.01,  1.00, -0.11, -0.02, -0.01,
							0.78, -0.10,  0.35, -0.11,  1.00,  0.33, -0.14,
							0.23, -0.28,  0.11, -0.02,  0.33,  1.00,  0.17,
						 -0.04,  0.03, -0.22, -0.01, -0.14,  0.17,  1.00};

						corSystMatrix = TMatrixDSym( nObs, systCorrelations );

						break;
			}
		default:
			{
				cout << "PDF_GLWADS_DK_hh_Dmix_newVars::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}
	}
}

void PDF_GLWADS_DK_hh_Dmix_newVars::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
