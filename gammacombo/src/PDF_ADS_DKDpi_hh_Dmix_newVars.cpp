/**
 * Gamma Combination
 * Author: Matthew Kenzie matthew.kenzie@cern.ch
 * Date: August 2015
 *
 **/

#include "PDF_ADS_DKDpi_hh_Dmix_newVars.h"

PDF_ADS_DKDpi_hh_Dmix_newVars::PDF_ADS_DKDpi_hh_Dmix_newVars(config cObs, config cErr, config cCor,
		double Mxy, ParametersAbs* pars, TString d)
: PDF_Abs(6)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	name = "ads-dkdpi-hh-dmix-newvars";
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


PDF_ADS_DKDpi_hh_Dmix_newVars::~PDF_ADS_DKDpi_hh_Dmix_newVars(){}


void PDF_ADS_DKDpi_hh_Dmix_newVars::initParameters()
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
	parameters->add(*(p->get("xD")));
	parameters->add(*(p->get("yD")));
}


void PDF_ADS_DKDpi_hh_Dmix_newVars::initRelations()
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
	RooConstVar& AcpD   = RooConst(0);

	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	theory->add(*(new RooGLWADSDmixAcpADSVar   ("aads_dk_kpi_th",   "RooGLWADSDmixAcpADSVar"  , rbk, dbk, kbk, rf, df, kf, g, xD, yD, _Mxy, AcpD)));
	theory->add(*(new RooGLWADSDmixAcpADSVar   ("aads_dpi_kpi_th",  "RooGLWADSDmixAcpADSVar"  , rbp, dbp, kbp, rf, df, kf, g, xD, yD, _Mxy, AcpD)));
	theory->add(*(new RooGLWADSDmixAcpVar      ("afav_dk_kpi_th",   "RooGLWADSDmixAcpVar"     , rbk, dbk, kbk, rf, df, kf, g, xD, yD, _Mxy, AcpD)));
	theory->add(*(new RooGLWADSDmixRADSVar     ("rads_dk_kpi_th",   "RooGLWADSDmixRADSVar"    , rbk, dbk, kbk, rf, df, kf, g, xD, yD, _Mxy, "")));
	theory->add(*(new RooGLWADSDmixRADSVar     ("rads_dpi_kpi_th",  "RooGLWADSDmixRADSVar"    , rbp, dbp, kbp, rf, df, kf, g, xD, yD, _Mxy, "")));
	theory->add(*(new RooGLWADSDmixRkpVar      ("rkp_kpi_th",       "RooGLWADSDmixRkpVar"     , Rcab, rbk, dbk, kbk, rbp, dbp, kbp, rf, df, kf, g, xD, yD, _Mxy, "fav")));

}

void PDF_ADS_DKDpi_hh_Dmix_newVars::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("aads_dk_kpi_obs",  "A_{ADS} (DK K#pi)",   0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("aads_dpi_kpi_obs", "A_{ADS} (D#pi K#pi)", 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("afav_dk_kpi_obs",  "Afav (DK K#pi)",      0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rads_dk_kpi_obs",  "R_{ADS} (DK K#pi)",   0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rads_dpi_kpi_obs", "R_{ADS} (D#pi K#pi)", 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rkp_kpi_obs",      "R_{K/#pi} (K#pi)",    1, -1e4, 1e4)));

  latexObservables.clear();
  latexObservables.push_back("\\AadsDK");
  latexObservables.push_back("\\AadsDPi");
  latexObservables.push_back("\\AfavDkKpi");
  latexObservables.push_back("\\RadsDK");
  latexObservables.push_back("\\RadsDPi");
  latexObservables.push_back("\\RkpKpi");
}

void PDF_ADS_DKDpi_hh_Dmix_newVars::setObservables(config c)
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
				 		setObservable( "afav_dk_kpi_obs", -1.9441e-02 );
				 		setObservable( "rads_dk_kpi_obs",  1.8757e-02 );
				 		setObservable( "rads_dpi_kpi_obs", 3.5977e-03 );
				 		setObservable( "rkp_kpi_obs",      7.7937e-02 );
						break;
				 }
		case check:{
						obsValSource = "check";
				 		setObservable( "aads_dk_kpi_obs", -4.0267e-01 );
				 		setObservable( "aads_dpi_kpi_obs", 1.0031e-01 );
				 		setObservable( "afav_dk_kpi_obs", -1.9441e-02 );
				 		setObservable( "rads_dk_kpi_obs",  1.8757e-02 );
            setObservable( "rads_dpi_kpi_obs", 3.5977e-03 ); // THE REAL VALUE
            //setObservable( "rads_dpi_kpi_obs", 3.75e-03 ); // check
				 		setObservable( "rkp_kpi_obs",      7.7937e-02 );
						break;
				 }
		default:{
				 		cout << "PDF_ADS_DKDpi_hh_Dmix_newVars::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
						exit(1);
				 }
	}
}

void PDF_ADS_DKDpi_hh_Dmix_newVars::setUncertainties(config c)
{
	switch(c){
		case lumi3fb:
			{
						obsErrSource = "3fb-1 ANA v7 - lifted from gammadini "; // https://twiki.cern.ch/twiki/pub/LHCbPhysics/B2D0K/LHCb-ANA-2014-071-v7.pdf (see Vavas email 04/08/15)
						StatErr[0]  = 5.62e-02 ; // aads_dk_kpi
						StatErr[1]  = 3.14e-02 ; // aads_dpi_kpi
						StatErr[2]  = 7.18e-03 ; // afav_dk_kpi
						StatErr[3]  = 1.14e-03 ; // rads_dk_kpi
						StatErr[4]  = 1.16e-04 ; // rads_dpi_kpi
						StatErr[5]  = 5.82e-04 ; // rkp_kpi

						SystErr[0]  = 0.0106   ; // aads_dk_kpi
						SystErr[1]  = 0.0094   ; // aads_dpi_kpi
						SystErr[2]  = 0.0060   ; // afav_dk_kpi
						SystErr[3]  = 0.0010   ; // rads_dk_kpi
						SystErr[4]  = 0.00009  ; // rads_dpi_kpi
						SystErr[5]  = 0.0019   ; // rkp_kpi

						break;
			}
		default:
			{
				cout << "PDF_ADS_DKDpi_hh_Dmix_newVars::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}
	}
}

void PDF_ADS_DKDpi_hh_Dmix_newVars::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi3fb:
			{
						corSource = "3fb-1 ANA v7 - lifted from gammadini "; // https://twiki.cern.ch/twiki/pub/LHCbPhysics/B2D0K/LHCb-ANA-2014-071-v7.pdf (see Vavas email 04/08/15)

						// lifted from gammadini
						const double statCorrelations[36] = {
							1.0   ,-0.0474, 0.0078, 0.1024,-0.0032, 0.0003,   // aads_dk_kpi
						 -0.0474, 1.0   , 0.0144, 0.0155,-0.0431, 0.0000,   // aads_dpi_kpi
							0.0078, 0.0144, 1.0   ,-0.0001,-0.0001,-0.0004,   // afav_dk_kpi
							0.1024, 0.0155,-0.0001, 1.0   ,-0.0219,-0.1136,   // rads_dk_kpi
						 -0.0032,-0.0431,-0.0001,-0.0219, 1.0   , 0.0114,   // rads_dpi_kpi
							0.0003, 0.0000,-0.0004,-0.1136, 0.0114, 1.0   };  // rkp_kpi

						corStatMatrix = TMatrixDSym( nObs, statCorrelations );

						// lifted from gammadini
						const double systCorrelations[36] = {
							1.00,  0.36,  0.09,  0.78, -0.43, -0.14,   // aads_dk_kpi
							0.36,  1.00, -0.55,  0.59, -0.47, -0.04,   // aads_dpi_kpi
							0.09, -0.55,  1.00, -0.11,  0.05, -0.02,   // afav_dk_kpi
							0.78,  0.59, -0.11,  1.00, -0.57, -0.22,   // rads_dk_kpi
						 -0.43, -0.47,  0.05, -0.57,  1.00,  0.02,   // rads_dpi_kpi
						 -0.14, -0.04, -0.02, -0.22,  0.02,  1.00};  // rkp_kpi

						corSystMatrix = TMatrixDSym( nObs, systCorrelations );

						break;
			}
		default:
			{
				cout << "PDF_ADS_DKDpi_hh_Dmix_newVars::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}
	}
}

void PDF_ADS_DKDpi_hh_Dmix_newVars::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
