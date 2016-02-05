/**
 * Gamma Combination
 * Author: Matthew Kenzie matthew.kenzie@cern.ch
 * Date: August 2015
 *
 **/

#include "PDF_GLW_DKDpi_K3pi_Dmix_newVars.h"

PDF_GLW_DKDpi_K3pi_Dmix_newVars::PDF_GLW_DKDpi_K3pi_Dmix_newVars(config cObs, config cErr, config cCor,
  double Mxy, ParametersAbs* pars, TString d)
: PDF_Abs(3)
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


PDF_GLW_DKDpi_K3pi_Dmix_newVars::~PDF_GLW_DKDpi_K3pi_Dmix_newVars(){}


void PDF_GLW_DKDpi_K3pi_Dmix_newVars::initParameters()
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
	parameters->add(*(p->get("F_pipipipi")));
	parameters->add(*(p->get("RBRdkdpi")));
  parameters->add(*(p->get("xD")));
  parameters->add(*(p->get("yD")));
}


void PDF_GLW_DKDpi_K3pi_Dmix_newVars::initRelations()
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
	RooFormulaVar *k4pi = new RooFormulaVar("kD_4pi", "kD_4pi", "2.*F_pipipipi-1", *p);
	RooGLWADSDmixRcpNewVar *rcp_dk_4pi  = new RooGLWADSDmixRcpNewVar("rcp_dk_4pi" ,"rcp_dk_4pi" , rbk, dbk, kbk, rfGLW, dfGLW, *k4pi, rf, df, kf, g, xD, yD, _Mxy);
	RooGLWADSDmixRcpNewVar *rcp_dpi_4pi = new RooGLWADSDmixRcpNewVar("rcp_dpi_4pi","rcp_dpi_4pi", rbp, dbp, kbp, rfGLW, dfGLW, *k4pi, rf, df, kf, g, xD, yD, _Mxy);

	theory->add(*(new RooGLWADSDmixAcpVar      ("acp_dk_4pi_th", 		 "RooGLWADSDmixAcpVar"   , rbk, dbk, kbk, rfGLW, dfGLW, *k4pi, g, xD, yD, 0., AcpDpppp)));
	theory->add(*(new RooGLWADSDmixAcpVar      ("acp_dpi_4pi_th",    "RooGLWADSDmixAcpVar"   , rbp, dbp, kbp, rfGLW, dfGLW, *k4pi, g, xD, yD, 0., AcpDpppp)));
	theory->add(*(new RooFormulaVar 					 ("rcp_4pi_th",        "RooFormulaVar"         , "@0/@1", RooArgList(*rcp_dk_4pi, *rcp_dpi_4pi))));

}

void PDF_GLW_DKDpi_K3pi_Dmix_newVars::initObservables()
{
	observables = new RooArgList("observables");
	observables->add(*(new RooRealVar("acp_dk_4pi_obs",    "ACP (DK 4#pi)",         0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dpi_4pi_obs",   "ACP (D#pi 4#pi)",       0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rcp_4pi_obs",       "R_{CP} (4#pi)",     	  1, -1e4, 1e4)));

  latexObservables.clear();
  latexObservables.push_back("\\AcpDKpppp");
  latexObservables.push_back("\\AcpDpipppp");
  latexObservables.push_back("\\RCPpppp");
}

void PDF_GLW_DKDpi_K3pi_Dmix_newVars::setObservables(config c)
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
				 setObservable( "acp_dk_4pi_obs",     1.0035e-01 );
				 setObservable( "acp_dpi_4pi_obs",   -4.1278e-03 );
				 setObservable( "rcp_4pi_obs",        9.7540e-01 );
				 break;
			}
    case check:
      {
				 obsValSource = "check";
				 setObservable( "acp_dk_4pi_obs",     1.0035e-01 );
				 setObservable( "acp_dpi_4pi_obs",   -4.1278e-03 );
				 setObservable( "rcp_4pi_obs",        9.7540e-01 );
				 break;
      }
		default:
			{
				 cout << "PDF_GLW_DKDpi_K3pi_Dmix_newVars::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				 exit(1);
			}
	}
}

void PDF_GLW_DKDpi_K3pi_Dmix_newVars::setUncertainties(config c)
{
	switch(c)
	{
		case lumi3fb:
			{
				 obsErrSource = "3fb-1 ANA v7 - lifted from gammadini "; // https://twiki.cern.ch/twiki/pub/LHCbPhysics/B2D0K/LHCb-ANA-2014-071-v7.pdf (see Vavas email 04/08/15)

						StatErr[0]  = 3.36e-02 ; // acp_dk_4pi_obs
						StatErr[1]  = 7.91e-03 ; // acp_dpi_4pi_obs
						StatErr[2]  = 3.67e-02 ; // rcp_4pi_obs

						SystErr[0]  = 0.018  ; // acp_dk_4pi_obs
						SystErr[1]  = 0.0024 ; // acp_dpi_4pi_obs
						SystErr[2]  = 0.019  ; // rcp_4pi_obs

						break;
			}
		default:
			{
				 cout << "PDF_GLW_DKDpi_K3pi_Dmix_newVars::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				 exit(1);
			}
	}
}

void PDF_GLW_DKDpi_K3pi_Dmix_newVars::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi3fb:
			{
				corSource = "3fb-1 ANA v7 - lifted from gammadini "; // https://twiki.cern.ch/twiki/pub/LHCbPhysics/B2D0K/LHCb-ANA-2014-071-v7.pdf (see Vavas email 04/08/15)

				// lifted from gammadini
				const double statCorrelations[9] = {
				 1.0   ,-0.0197,-0.0182,   // acp_dk_4pi_obs
				-0.0197, 1.0   ,-0.0041,   // acp_dpi_4pi_obs
				-0.0182,-0.0041, 1.0   };  // rcp_4pi_obs

				corStatMatrix = TMatrixDSym( nObs, statCorrelations );

				// lifted from gammadini

        const double systCorrelations[9] = {
            1.00,  0.31,  0.07,   // acp_dk_4pi_obs
            0.31,  1.00, -0.07,   // acp_dpi_4pi_obs
            0.07, -0.07,  1.00};  // rcp_4pi_obs

				corSystMatrix = TMatrixDSym( nObs, systCorrelations );

				break;
			}
		default:
			{
				 cout << "PDF_GLW_DKDpi_K3pi_Dmix_newVars::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				 exit(1);
			}
	}
}

void PDF_GLW_DKDpi_K3pi_Dmix_newVars::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
