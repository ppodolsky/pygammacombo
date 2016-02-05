/**
 * Gamma Combination
 * Author: Matthew Kenzie matthew.kenzie@cern.ch
 * Date: August 2015
 *
 **/

#include "PDF_ADS_DKDpi_K3pi_Dmix_newVars.h"

PDF_ADS_DKDpi_K3pi_Dmix_newVars::PDF_ADS_DKDpi_K3pi_Dmix_newVars(config cObs, config cErr, config cCor,
  double Mxy, ParametersAbs* pars, TString d)
: PDF_Abs(6)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
  name = "ads-dkdpi-k3pi-dmix-newvars";
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


PDF_ADS_DKDpi_K3pi_Dmix_newVars::~PDF_ADS_DKDpi_K3pi_Dmix_newVars(){}


void PDF_ADS_DKDpi_K3pi_Dmix_newVars::initParameters()
{
	parameters = new RooArgList("parameters");
	parameters->add(*(p->get("r_dk")));
	parameters->add(*(p->get("d_dk")));
	parameters->add(*(p->get("r_dpi")));
	parameters->add(*(p->get("d_dpi")));
	parameters->add(*(p->get("g")));
	parameters->add(*(p->get("rD_k3pi")));
	parameters->add(*(p->get("dD_k3pi")));
	parameters->add(*(p->get("kD_k3pi")));
	parameters->add(*(p->get("RBRdkdpi")));
  parameters->add(*(p->get("xD")));
  parameters->add(*(p->get("yD")));
}


void PDF_ADS_DKDpi_K3pi_Dmix_newVars::initRelations()
{
  RooArgSet *p = (RooArgSet*)parameters;
  delete theory; theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  RooRealVar& rbk = *((RooRealVar*)p->find("r_dk"));
  RooRealVar& dbk = *((RooRealVar*)p->find("d_dk"));
  RooConstVar& kbk = RooConst(1);
  RooRealVar& rbp = *((RooRealVar*)p->find("r_dpi"));
  RooRealVar& dbp = *((RooRealVar*)p->find("d_dpi"));
  RooConstVar& kbp = RooConst(1);
  RooRealVar& kf  = *((RooRealVar*)p->find("kD_k3pi"));
  RooRealVar& rf  = *((RooRealVar*)p->find("rD_k3pi"));
	RooConstVar& rfGLW  = RooConst(1);
  RooRealVar& df  = *((RooRealVar*)p->find("dD_k3pi"));
	RooConstVar& dfGLW  = RooConst(0);
  RooRealVar& g   = *((RooRealVar*)p->find("g"));
  RooRealVar& xD  = *((RooRealVar*)p->find("xD"));
  RooRealVar& yD  = *((RooRealVar*)p->find("yD"));
	RooRealVar& F4pi = *((RooRealVar*)p->find("F_pipipipi"));
  RooRealVar& Rcab = *((RooRealVar*)p->find("RBRdkdpi"));
  RooConstVar& AcpD = RooConst(0);
	RooConstVar& AcpDpppp = RooConst(0);

	theory->add(*(new RooGLWADSDmixAcpADSVar   ("aads_dk_k3pi_th",   "RooGLWADSDmixAcpADSVar", rbk, dbk, kbk, rf, df, kf, g, xD, yD, _Mxy, AcpD)));
	theory->add(*(new RooGLWADSDmixAcpADSVar   ("aads_dpi_k3pi_th",  "RooGLWADSDmixAcpADSVar", rbp, dbp, kbp, rf, df, kf, g, xD, yD, _Mxy, AcpD)));
	theory->add(*(new RooGLWADSDmixAcpVar      ("afav_dk_k3pi_th",   "RooGLWADSDmixAcpVar"   , rbk, dbk, kbk, rf, df, kf, g, xD, yD, _Mxy, AcpD)));
	theory->add(*(new RooGLWADSDmixRADSVar     ("rads_dk_k3pi_th",   "RooGLWADSDmixRADSVar"  , rbk, dbk, kbk, rf, df, kf, g, xD, yD, _Mxy, "")));
	theory->add(*(new RooGLWADSDmixRADSVar     ("rads_dpi_k3pi_th",  "RooGLWADSDmixRADSVar"  , rbp, dbp, kbp, rf, df, kf, g, xD, yD, _Mxy, "")));
	theory->add(*(new RooGLWADSDmixRkpVar      ("rkp_k3pi_th",       "RooGLWADSDmixRkpVar"   , Rcab, rbk, dbk, kbk, rbp, dbp, kbp, rf, df, kf, g, xD, yD, _Mxy, "fav")));

}

void PDF_ADS_DKDpi_K3pi_Dmix_newVars::initObservables()
{
	observables = new RooArgList("observables");
	observables->add(*(new RooRealVar("aads_dk_k3pi_obs",  "A_{ADS} (DK K3#pi)",    0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("aads_dpi_k3pi_obs", "A_{ADS} (D#pi K3#pi)",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("afav_dk_k3pi_obs",  "Afav (DK K3#pi)"    ,   0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rads_dk_k3pi_obs",  "R_{ADS} (DK K3#pi)",    1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rads_dpi_k3pi_obs", "R_{ADS} (D#pi K3#pi)",  1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rkp_k3pi_obs",      "R_{K/#pi} (K3#pi)"   ,  1, -1e4, 1e4)));

  latexObservables.clear();
  latexObservables.push_back("\\AadsDKKppp");
  latexObservables.push_back("\\AadsDPiKppp");
  latexObservables.push_back("\\AfavDkKppp");
  latexObservables.push_back("\\RadsDKKppp");
  latexObservables.push_back("\\RadsDPiKppp");
  latexObservables.push_back("\\RkpKppp");
}

void PDF_ADS_DKDpi_K3pi_Dmix_newVars::setObservables(config c)
{
	switch(c)
	{
		case truth:
			{
				 setObservablesTruth();
				 break;
			}
		case toy:
			{
				 setObservablesToy();
				 break;
			}
		case lumi3fb:
			{
				 obsValSource = "3fb-1 ANA v7 - lifted from gammadini "; // https://twiki.cern.ch/twiki/pub/LHCbPhysics/B2D0K/LHCb-ANA-2014-071-v7.pdf (see Vavas email 04/08/15)
				 setObservable( "aads_dk_k3pi_obs",  -3.1291e-01 );
				 setObservable( "aads_dpi_k3pi_obs",  2.3228e-02 );
				 setObservable( "afav_dk_k3pi_obs",  -4.1540e-04 );
				 setObservable( "rads_dk_k3pi_obs",   1.3992e-02 );
         setObservable( "rads_dpi_k3pi_obs",  3.7718e-03 );
				 setObservable( "rkp_k3pi_obs",       7.9306e-02 );
				 break;
			}
    case check:
      {
				 obsValSource = "check";
				 setObservable( "aads_dk_k3pi_obs",  -3.1291e-01 );
				 setObservable( "aads_dpi_k3pi_obs",  2.3228e-02 );
				 setObservable( "afav_dk_k3pi_obs",  -4.1540e-04 );
				 setObservable( "rads_dk_k3pi_obs",   1.3992e-02 );
         //setObservable( "rads_dpi_k3pi_obs",  3.7718e-03 ); // THE REAL VALUE
				 setObservable( "rads_dpi_k3pi_obs",  3.39e-03 ); // check value
				 setObservable( "rkp_k3pi_obs",       7.9306e-02 );
				 break;
      }
		default:
			{
				 cout << "PDF_ADS_DKDpi_K3pi_Dmix_newVars::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				 exit(1);
			}
	}
}

void PDF_ADS_DKDpi_K3pi_Dmix_newVars::setUncertainties(config c)
{
	switch(c)
	{
		case lumi3fb:
			{
				 obsErrSource = "3fb-1 ANA v7 - lifted from gammadini "; // https://twiki.cern.ch/twiki/pub/LHCbPhysics/B2D0K/LHCb-ANA-2014-071-v7.pdf (see Vavas email 04/08/15)

						StatErr[0]  = 1.02e-01 ; // aads_dk_k3pi_obs
						StatErr[1]  = 4.80e-02 ; // aads_dpi_k3pi_obs
						StatErr[2]  = 1.19e-02 ; // afav_dk_k3pi_obs
						StatErr[3]  = 1.49e-03 ; // rads_dk_k3pi_obs
						StatErr[4]  = 1.84e-04 ; // rads_dpi_k3pi_obs
						StatErr[5]  = 9.77e-04 ; // rkp_k3pi_obs

						SystErr[0]  = 0.038  ; // aads_dk_k3pi_obs
						SystErr[1]  = 0.005  ; // aads_dpi_k3pi_obs
						SystErr[2]  = 0.0020 ; // afav_dk_k3pi_obs
						SystErr[3]  = 0.00060; // rads_dk_k3pi_obs
						SystErr[4]  = 0.00006; // rads_dpi_k3pi_obs
						SystErr[5]  = 0.0018 ; // rkp_k3pi_obs

						break;
			}
		default:
			{
				 cout << "PDF_ADS_DKDpi_K3pi_Dmix_newVars::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				 exit(1);
			}
	}
}

void PDF_ADS_DKDpi_K3pi_Dmix_newVars::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi3fb:
			{
				corSource = "3fb-1 ANA v7 - lifted from gammadini "; // https://twiki.cern.ch/twiki/pub/LHCbPhysics/B2D0K/LHCb-ANA-2014-071-v7.pdf (see Vavas email 04/08/15)

				// lifted from gammadini
				const double statCorrelations[36] = {
					1.0   ,-0.0618, 0.0064, 0.0821,-0.0040, 0.0028,  // aads_dk_k3pi_obs
				 -0.0618, 1.0   , 0.0166, 0.0135,-0.0218, 0.0005,  // aads_dpi_k3pi_obs
					0.0064, 0.0166, 1.0   ,-0.0005,-0.0001, 0.0012,  // afav_dk_k3pi_obs
					0.0821, 0.0135,-0.0005, 1.0   ,-0.0464,-0.0990,  // rads_dk_k3pi_obs
				 -0.0040,-0.0218,-0.0001,-0.0464, 1.0   , 0.0116,  // rads_dpi_k3pi_obs
					0.0028, 0.0005, 0.0012,-0.0990, 0.0116, 1.0   }; // rkp_k3pi_obs

				corStatMatrix = TMatrixDSym( nObs, statCorrelations );

				// lifted from gammadini

        const double systCorrelations[36] = {
           1.00, -0.09,  0.02,  0.87,  0.05, -0.13,   // aads_dk_k3pi_obs
          -0.09,  1.00,  0.05,  0.10,  0.46,  0.17,   // aads_dpi_k3pi_obs
           0.02,  0.05,  1.00,  0.02, -0.02,  0.00,   // afav_dk_k3pi_obs
           0.87,  0.10,  0.02,  1.00,  0.14, -0.04,   // rads_dk_k3pi_obs
           0.05,  0.46, -0.02,  0.14,  1.00,  0.13,   // rads_dpi_k3pi_obs
          -0.13,  0.17,  0.00, -0.04,  0.13,  1.00};  // rkp_k3pi_obs

				corSystMatrix = TMatrixDSym( nObs, systCorrelations );

				break;
			}
		default:
			{
				 cout << "PDF_ADS_DKDpi_K3pi_Dmix_newVars::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				 exit(1);
			}
	}
}

void PDF_ADS_DKDpi_K3pi_Dmix_newVars::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
