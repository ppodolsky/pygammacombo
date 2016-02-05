/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Jan 2015
 *
 * Combine all 12 observables from the 3fb-1 hhpi0 GLW/ADS measurement.
 *
 **/

#include "PDF_GLWADS_DKDpi_hhpi0.h"

	PDF_GLWADS_DKDpi_hhpi0::PDF_GLWADS_DKDpi_hhpi0(config cObs, config cErr, config cCor, ParametersAbs* pars)
: PDF_Abs(11)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	name = "GLWADS_DKDpi_hhpi0_2012";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}

	PDF_GLWADS_DKDpi_hhpi0::PDF_GLWADS_DKDpi_hhpi0(ParametersAbs* pars, int nObs)
: PDF_Abs(nObs)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
}


PDF_GLWADS_DKDpi_hhpi0::~PDF_GLWADS_DKDpi_hhpi0(){}


void PDF_GLWADS_DKDpi_hhpi0::initParameters()
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
  //parameters->add(*(p->get("Aprod")));
	parameters->add(*(p->get("F_pipipi0")));
	parameters->add(*(p->get("F_kkpi0")));
}


void PDF_GLWADS_DKDpi_hhpi0::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	theory->add(*(new RooFormulaVar("aads_dk_kpipi0_th",   "aads_dk_kpipi0_th",  "(2*r_dk *kD_kpipi0*rD_kpipi0*sin(d_dk +dD_kpipi0)*sin(g))/(r_dk^2  + rD_kpipi0^2 + 2*r_dk *kD_kpipi0*rD_kpipi0*cos(d_dk +dD_kpipi0)*cos(g))", *p)));
	theory->add(*(new RooFormulaVar("aads_dpi_kpipi0_th",  "aads_dpi_kpipi0_th", "(2*r_dpi*kD_kpipi0*rD_kpipi0*sin(d_dpi+dD_kpipi0)*sin(g))/(r_dpi^2 + rD_kpipi0^2 + 2*r_dpi*kD_kpipi0*rD_kpipi0*cos(d_dpi+dD_kpipi0)*cos(g))", *p)));
	theory->add(*(new RooFormulaVar("acp_dk_kkpi0_th",     "acp_dk_kkpi0_th",    "2*r_dk *(2*F_kkpi0-1)  *sin(d_dk) *sin(g) / (1 + r_dk^2  + 2*r_dk *(2*F_kkpi0-1)  *cos(d_dk) *cos(g))", *p)));
	theory->add(*(new RooFormulaVar("acp_dk_pipipi0_th",   "acp_dk_pipipi0_th",  "2*r_dk *(2*F_pipipi0-1)*sin(d_dk) *sin(g) / (1 + r_dk^2  + 2*r_dk *(2*F_pipipi0-1)*cos(d_dk) *cos(g))", *p)));
	theory->add(*(new RooFormulaVar("acp_dpi_kkpi0_th",    "acp_dpi_kkpi0_th",   "2*r_dpi*(2*F_kkpi0-1)  *sin(d_dpi)*sin(g) / (1 + r_dpi^2 + 2*r_dpi*(2*F_kkpi0-1)  *cos(d_dpi)*cos(g))", *p)));
	theory->add(*(new RooFormulaVar("acp_dpi_pipipi0_th",  "acp_dpi_pipipi0_th", "2*r_dpi*(2*F_pipipi0-1)*sin(d_dpi)*sin(g) / (1 + r_dpi^2 + 2*r_dpi*(2*F_pipipi0-1)*cos(d_dpi)*cos(g))", *p)));
	theory->add(*(new RooFormulaVar("afav_dk_kpipi0_th",   "afav_dk_kpipi0_th",  "2*r_dk *rD_kpipi0*kD_kpipi0*sin(g)*sin(d_dk -dD_kpipi0) / (1 + r_dk^2  * rD_kpipi0^2 + 2*r_dk *rD_kpipi0*kD_kpipi0*cos(g)*cos(d_dk -dD_kpipi0))", *p)));
  //theory->add(*(new RooFormulaVar("afav_dpi_kpipi0_th",  "afav_dpi_kpipi0_th", "Aprod", *p)));
	theory->add(*(new RooFormulaVar("rads_dk_kpipi0_th",   "rads_dk_kpipi0_th",  "(r_dk^2  + rD_kpipi0^2 + 2*r_dk *kD_kpipi0*rD_kpipi0*cos(d_dk +dD_kpipi0)*cos(g))/(1 + r_dk^2 *rD_kpipi0^2 + 2*r_dk *kD_kpipi0*rD_kpipi0*cos(d_dk -dD_kpipi0)*cos(g))", *p)));
	theory->add(*(new RooFormulaVar("rads_dpi_kpipi0_th",  "rads_dpi_kpipi0_th", "(r_dpi^2 + rD_kpipi0^2 + 2*r_dpi*kD_kpipi0*rD_kpipi0*cos(d_dpi+dD_kpipi0)*cos(g))/(1 + r_dpi^2*rD_kpipi0^2 + 2*r_dpi*kD_kpipi0*rD_kpipi0*cos(d_dpi-dD_kpipi0)*cos(g))", *p)));
	theory->add(*(new RooFormulaVar("rcp_kkpi0_th",        "rcp_kkpi0_th",       "(1 + r_dk^2 + 2*r_dk*(2*F_kkpi0-1)  *cos(g)*cos(d_dk))/(1 + r_dpi^2 + 2*r_dpi*(2*F_kkpi0-1)  *cos(g)*cos(d_dpi))", *p)));
	theory->add(*(new RooFormulaVar("rcp_pipipi0_th",      "rcp_pipipi0_th",     "(1 + r_dk^2 + 2*r_dk*(2*F_pipipi0-1)*cos(g)*cos(d_dk))/(1 + r_dpi^2 + 2*r_dpi*(2*F_pipipi0-1)*cos(g)*cos(d_dpi))", *p)));
}


void PDF_GLWADS_DKDpi_hhpi0::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("aads_dk_kpipi0_obs",  "aads_dk_kpipi0",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("aads_dpi_kpipi0_obs", "aads_dpi_kpipi0", 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dk_kkpi0_obs",    "acp_dk_kkpi0",    0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dk_pipipi0_obs",  "acp_dk_pipipi0",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dpi_kkpi0_obs",   "acp_dpi_kkpi0",   0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dpi_pipipi0_obs", "acp_dpi_pipipi0", 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("afav_dk_kpipi0_obs",  "afav_dk_kpipi0",  0, -1e4, 1e4)));
  //observables->add(*(new RooRealVar("afav_dpi_kpipi0_obs", "afav_dpi_kpipi0", 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rads_dk_kpipi0_obs",  "rads_dk_kpipi0",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rads_dpi_kpipi0_obs", "rads_dpi_kpipi0", 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rcp_kkpi0_obs",       "rcp_kkpi0",       0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rcp_pipipi0_obs",     "rcp_pipipi0",     0, -1e4, 1e4)));

  latexObservables.clear();
  latexObservables.push_back("\\AadsDKkpp");
  latexObservables.push_back("\\AadsDPikpp");
  latexObservables.push_back("\\AcpDkKKPiz");
  latexObservables.push_back("\\AcpDkPiPiPiz");
  latexObservables.push_back("\\AcpDpiKKPiz");
  latexObservables.push_back("\\AcpDpiPiPiPiz");
  latexObservables.push_back("\\AfavDkKPiPiz");
  //latexObservables.push_back("\\AfavDPiKPiPiz");
  latexObservables.push_back("\\RadsDKkpp");
  latexObservables.push_back("\\RadsDPikpp");
  latexObservables.push_back("\\RCPKKPiz");
  latexObservables.push_back("\\RCPPiPiPiz");
}


void PDF_GLWADS_DKDpi_hhpi0::setObservables(config c)
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
				     obsValSource = "3fb-1, LHCb-ANA-2013-075 v7, Feb 9 2015";
				     setObservable("aads_dk_kpipi0_obs",  -0.20   );
				     setObservable("aads_dpi_kpipi0_obs",  0.438  );
				     setObservable("acp_dk_kkpi0_obs",     0.30   );
				     setObservable("acp_dk_pipipi0_obs",   0.054  );
				     setObservable("acp_dpi_kkpi0_obs",   -0.030  );
				     setObservable("acp_dpi_pipipi0_obs", -0.016  );
				     setObservable("afav_dk_kpipi0_obs",   0.010  );
             //setObservable("afav_dpi_kpipi0_obs", -0.00077);
				     setObservable("rads_dk_kpipi0_obs",   0.0140 );
				     setObservable("rads_dpi_kpipi0_obs",  0.00235);
				     setObservable("rcp_kkpi0_obs",        0.95   );
				     setObservable("rcp_pipipi0_obs",      0.98   );
				     break;
			     }
		case check:{
				     obsValSource = "check";
				     setObservable("aads_dk_kpipi0_obs",  -0.20   );
             //setObservable("aads_dpi_kpipi0_obs",  0.438  ); // THE REAL VALUE
				     setObservable("aads_dpi_kpipi0_obs",  0.156  ); // check
             setObservable("acp_dk_kkpi0_obs",     0.30   );
				     setObservable("acp_dk_pipipi0_obs",   0.054  );
				     setObservable("acp_dpi_kkpi0_obs",   -0.030  );
				     setObservable("acp_dpi_pipipi0_obs", -0.016  );
				     setObservable("afav_dk_kpipi0_obs",   0.010  );
             //setObservable("afav_dpi_kpipi0_obs", -0.00077);
				     setObservable("rads_dk_kpipi0_obs",   0.0140 );
				     setObservable("rads_dpi_kpipi0_obs",  0.00235);
				     setObservable("rcp_kkpi0_obs",        0.95   );
				     setObservable("rcp_pipipi0_obs",      0.98   );
				     break;
			     }
		default:{
				cout << "PDF_GLWADS_DKDpi_hhpi0::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}
	}
}


void PDF_GLWADS_DKDpi_hhpi0::setUncertainties(config c)
{
	switch(c){
		case lumi3fb:{
				     obsErrSource = "3fb-1, LHCb-ANA-2013-075 v7, Feb 9 2015";
				     StatErr[ 0] = 0.27    ; // "aads_dk_kpipi0_obs",
				     StatErr[ 1] = 0.19    ; // "aads_dpi_kpipi0_obs",
				     StatErr[ 2] = 0.20    ; // "acp_dk_kkpi0_obs",
				     StatErr[ 3] = 0.091   ; // "acp_dk_pipipi0_obs",
				     StatErr[ 4] = 0.040   ; // "acp_dpi_kkpi0_obs",
				     StatErr[ 5] = 0.020   ; // "acp_dpi_pipipi0_obs",
				     StatErr[ 6] = 0.026   ; // "afav_dk_kpipi0_obs",
             //StatErr[ 7] = 0.0055  ; // "afav_dpi_kpipi0_obs",
				     StatErr[ 7] = 0.0047  ; // "rads_dk_kpipi0_obs",
				     StatErr[ 8] = 0.00049 ; // "rads_dpi_kpipi0_obs",
				     StatErr[ 9] = 0.22    ; // "rcp_kkpi0_obs",
				     StatErr[10] = 0.11    ; // "rcp_pipipi0_obs",

				     SystErr[ 0] = 0.04    ; // "aads_dk_kpipi0_obs",
				     SystErr[ 1] = 0.011   ; // "aads_dpi_kpipi0_obs",
				     SystErr[ 2] = 0.02    ; // "acp_dk_kkpi0_obs",
				     SystErr[ 3] = 0.011   ; // "acp_dk_pipipi0_obs",
				     SystErr[ 4] = 0.005   ; // "acp_dpi_kkpi0_obs",
				     SystErr[ 5] = 0.004   ; // "acp_dpi_pipipi0_obs",
				     SystErr[ 6] = 0.005   ; // "afav_dk_kpipi0_obs",
             //SystErr[ 7] = 0.0039  ; // "afav_dpi_kpipi0_obs",
				     SystErr[ 7] = 0.0021  ; // "rads_dk_kpipi0_obs",
				     SystErr[ 8] = 0.00006 ; // "rads_dpi_kpipi0_obs",
				     SystErr[ 9] = 0.05    ; // "rcp_kkpi0_obs",
				     SystErr[10] = 0.05    ; // "rcp_pipipi0_obs",
				     break;
			     }
		default:{
				cout << "PDF_GLWADS_DKDpi_hhpi0::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}
	}
}


void PDF_GLWADS_DKDpi_hhpi0::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi3fb:{
				corSource = "3fb-1, LHCb-ANA-2013-075 v7, Feb 9 2015"; // lifted from gammadini
        //
        const double statCorrelations[121] = {
                 1.00, -0.04,  0.00,  0.00,  0.00,  0.01,  0.01,  0.13,  0.00,  0.00,  0.00,
                -0.04,  1.00,  0.00,  0.00,  0.00,  0.01,  0.01, -0.01, -0.34, -0.00,  0.00,
                 0.00,  0.00,  1.00,  0.00, -0.04,  0.01,  0.01, -0.00, -0.00, -0.20, -0.01,
                 0.00,  0.00,  0.00,  1.00,  0.01, -0.03,  0.02, -0.00, -0.00, -0.00, -0.04,
                 0.00,  0.00, -0.04,  0.01,  1.00,  0.04,  0.04, -0.00, -0.00, -0.00,  0.00,
                 0.01,  0.01,  0.01, -0.03,  0.04,  1.00,  0.08, -0.00, -0.00, -0.00, -0.00,
                 0.01,  0.01,  0.01,  0.02,  0.04,  0.08,  1.00, -0.00,  0.00, -0.00, -0.00,
                 0.13, -0.01, -0.00, -0.00, -0.00, -0.00, -0.00,  1.00,  0.03,  0.00,  0.01,
                 0.00, -0.34, -0.00, -0.00, -0.00, -0.00,  0.00,  0.03,  1.00, -0.00, -0.00,
                 0.00, -0.00, -0.20, -0.00, -0.00, -0.00, -0.00,  0.00, -0.00,  1.00,  0.02,
                 0.00,  0.00, -0.01, -0.04,  0.00, -0.00, -0.00,  0.01, -0.00,  0.02,  1.00};
				corStatMatrix = TMatrixDSym(nObs,statCorrelations);

        const double systCorrelations[121] = {
                 1.00,  0.03,  0.07,  0.07,  0.18,  0.17, -0.16,  0.81,  0.32,  0.02,  0.13,
                 0.03,  1.00,  0.28,  0.31,  0.67,  0.68, -0.63, -0.18, -0.49, -0.00, -0.04,
                 0.07,  0.28,  1.00,  0.77,  0.07,  0.05,  0.05,  0.08, -0.08, -0.33, -0.18,
                 0.07,  0.31,  0.77,  1.00,  0.05,  0.02, -0.06,  0.13, -0.11, -0.14, -0.25,
                 0.18,  0.67,  0.07,  0.05,  1.00,  0.88, -0.82, -0.04,  0.02, -0.04,  0.02,
                 0.17,  0.68,  0.05,  0.02,  0.88,  1.00, -0.87, -0.03,  0.00,  0.00,  0.01,
                -0.16, -0.63,  0.05, -0.06, -0.82, -0.87,  1.00, -0.05,  0.06,  0.04,  0.00,
                 0.81, -0.18,  0.08,  0.13, -0.04, -0.03, -0.05,  1.00,  0.33, -0.03, -0.02,
                 0.32, -0.49, -0.08, -0.11,  0.02,  0.00,  0.06,  0.33,  1.00,  0.02, -0.02,
                 0.02, -0.00, -0.33, -0.14, -0.04,  0.00,  0.04, -0.03,  0.02,  1.00,  0.38,
                 0.13, -0.04, -0.18, -0.25,  0.02,  0.01,  0.00, -0.02, -0.02,  0.38,  1.00};
				corSystMatrix = TMatrixDSym(nObs,systCorrelations);
				break;
		}
		default:{
				cout << "PDF_GLWADS_DKDpi_hhpi0::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}
	}
}


void PDF_GLWADS_DKDpi_hhpi0::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
	TIterator* it = theory->createIterator();
}

