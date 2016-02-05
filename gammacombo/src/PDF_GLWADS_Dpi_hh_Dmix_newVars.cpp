/**
 * Gamma Combination
 * Author: Matthew Kenzie matthew.kenzie@cern.ch
 * Date: August 2015
 *
 **/

#include "PDF_GLWADS_Dpi_hh_Dmix_newVars.h"

PDF_GLWADS_Dpi_hh_Dmix_newVars::PDF_GLWADS_Dpi_hh_Dmix_newVars(config cObs, config cErr, config cCor,
		double Mxy, ParametersAbs* pars, TString d)
: PDF_Abs(4)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	name = "glwads-dkdpi-hh-dmix-newvars";
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


PDF_GLWADS_Dpi_hh_Dmix_newVars::~PDF_GLWADS_Dpi_hh_Dmix_newVars(){}


void PDF_GLWADS_Dpi_hh_Dmix_newVars::initParameters()
{
	parameters = new RooArgList("parameters");
	parameters->add(*(p->get("r_dpi")));
	parameters->add(*(p->get("d_dpi")));
	parameters->add(*(p->get("g")));
	parameters->add(*(p->get("rD_kpi")));
	parameters->add(*(p->get("dD_kpi")));
	parameters->add(*(p->get("AcpDKK")));
	parameters->add(*(p->get("AcpDpipi")));
	parameters->add(*(p->get("xD")));
	parameters->add(*(p->get("yD")));
}


void PDF_GLWADS_Dpi_hh_Dmix_newVars::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
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
	theory->add(*(new RooGLWADSDmixAcpADSVar("aads_dpi_kpi_th",  "RooGLWADSDmixAcpADSVar", rbp, dbp, kbp, rf, df, kf, g, xD, yD, _Mxy, AcpD)));
	theory->add(*(new RooGLWADSDmixAcpVar   ("acp_dpi_kk_th",    "RooGLWADSDmixAcpVar"   , rbp, dbp, kbp, rfGLW, dfGLW, kf, g, xD, yD, _Mxy, AcpDKK)));
	theory->add(*(new RooGLWADSDmixAcpVar   ("acp_dpi_pipi_th",  "RooGLWADSDmixAcpVar"   , rbp, dbp, kbp, rfGLW, dfGLW, kf, g, xD, yD, _Mxy, AcpDpp)));
	theory->add(*(new RooGLWADSDmixRADSVar  ("rads_dpi_kpi_th",  "RooGLWADSDmixRADSVar"  , rbp, dbp, kbp, rf, df, kf, g, xD, yD, _Mxy, "")));

}

void PDF_GLWADS_Dpi_hh_Dmix_newVars::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("aads_dpi_kpi_obs", "A_{ADS} (D#pi K#pi)", 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dpi_kk_obs",   "ACP (D#pi KK)",       0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dpi_pipi_obs", "ACP (D#pi #pi#pi)",   0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rads_dpi_kpi_obs", "R_{ADS} (D#pi K#pi)", 0, -1e4, 1e4)));
}

void PDF_GLWADS_Dpi_hh_Dmix_newVars::setObservables(config c)
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
				 		setObservable( "aads_dpi_kpi_obs", 1.0031e-01 );
				 		setObservable( "acp_dpi_kk_obs",  -1.4524e-02 );
				 		setObservable( "acp_dpi_pipi_obs", 4.2984e-03 );
				 		setObservable( "rads_dpi_kpi_obs", 3.5977e-03 );
						break;
				 }
		default:{
				 		cout << "PDF_GLWADS_Dpi_hh_Dmix_newVars::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
						exit(1);
				 }
	}
}

void PDF_GLWADS_Dpi_hh_Dmix_newVars::setUncertainties(config c)
{
	switch(c){
		case lumi3fb:
			{
						obsErrSource = "3fb-1 ANA v7 - lifted from gammadini "; // https://twiki.cern.ch/twiki/pub/LHCbPhysics/B2D0K/LHCb-ANA-2014-071-v7.pdf (see Vavas email 04/08/15)
						StatErr[0]  = 3.14e-02 ; // aads_dpi_kpi
						StatErr[1]  = 4.95e-03 ; // acp_dpi_kk
						StatErr[2]  = 8.60e-03 ; // acp_dpi_pipi
						StatErr[3]  = 1.16e-04 ; // rads_dpi_kpi

						SystErr[0]  = 0.0094   ; // aads_dpi_kpi
						SystErr[1]  = 0.0017   ; // acp_dpi_kk
						SystErr[2]  = 0.00309  ; // acp_dpi_pipi
						SystErr[3]  = 0.00009  ; // rads_dpi_kpi

						break;
			}
		default:
			{
				cout << "PDF_GLWADS_Dpi_hh_Dmix_newVars::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}
	}
}

void PDF_GLWADS_Dpi_hh_Dmix_newVars::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi3fb:
			{
						corSource = "3fb-1 ANA v7 - lifted from gammadini "; // https://twiki.cern.ch/twiki/pub/LHCbPhysics/B2D0K/LHCb-ANA-2014-071-v7.pdf (see Vavas email 04/08/15)

						// lifted from gammadini
						const double statCorrelations[16] = {
							 1.0,    0.0174, 0.01,   -0.0431,
							 0.0174, 1.0,    0.0639, -0.0002,
							 0.01,   0.0639, 1.0,    -0.0001,
							-0.0431,-0.0002,-0.0001,  1.0  };

						corStatMatrix = TMatrixDSym( nObs, statCorrelations );

						// lifted from gammadini
						const double systCorrelations[16] = {
							 1.00,  0.22, -0.06, -0.47,
							 0.22,  1.00,  0.11, -0.21,
							-0.06,  0.11,  1.00,  0.06,
							-0.47, -0.21,  0.06,  1.00};

						corSystMatrix = TMatrixDSym( nObs, systCorrelations );

						break;
			}
		default:
			{
				cout << "PDF_GLWADS_Dpi_hh_Dmix_newVars::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}
	}
}

void PDF_GLWADS_Dpi_hh_Dmix_newVars::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
