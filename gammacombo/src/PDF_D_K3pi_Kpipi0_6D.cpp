/**
 * Gamma Combination
 * Author: Matthew Kenzie, matthew.kenzie@cern.ch
 * Date: Jan 2016
 *
 * coherence factor, phase and ratio for D->K3pi and D->K2pi decays
 *
 **/

#include "PDF_D_K3pi_Kpipi0_6D.h"

	PDF_D_K3pi_Kpipi0_6D::PDF_D_K3pi_Kpipi0_6D(config cObs, config cErr, config cCor)
: PDF_Abs(6)
{
	name = "dk3pi_dkpipi0_constraints";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_D_K3pi_Kpipi0_6D::~PDF_D_K3pi_Kpipi0_6D(){}


void PDF_D_K3pi_Kpipi0_6D::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
  parameters->add(*(p.get("kD_k3pi")));
  parameters->add(*(p.get("dD_k3pi")));
  parameters->add(*(p.get("kD_kpipi0")));
  parameters->add(*(p.get("dD_kpipi0")));
  parameters->add(*(p.get("rD_k3pi")));
  parameters->add(*(p.get("rD_kpipi0")));
}


void PDF_D_K3pi_Kpipi0_6D::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	theory->add(*(new RooFormulaVar("kD_k3pi_th"  , "kD_k3pi_th"  , "kD_k3pi"  , *p)));
	theory->add(*(new RooFormulaVar("dD_k3pi_th"  , "dD_k3pi_th"  , "dD_k3pi"  , *p)));
	theory->add(*(new RooFormulaVar("kD_kpipi0_th", "kD_kpipi0_th", "kD_kpipi0", *p)));
	theory->add(*(new RooFormulaVar("dD_kpipi0_th", "dD_kpipi0_th", "dD_kpipi0", *p)));
	theory->add(*(new RooFormulaVar("rD_k3pi_th"  , "rD_k3pi_th"  , "rD_k3pi"  , *p)));
	theory->add(*(new RooFormulaVar("rD_kpipi0_th", "rD_kpipi0_th", "rD_kpipi0", *p)));
}


void PDF_D_K3pi_Kpipi0_6D::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("kD_k3pi_obs"  , "kD_k3pi"  ,       1, -2, 2)));
	observables->add(*(new RooRealVar("dD_k3pi_obs"  , "dD_k3pi"  ,       0, 0, 2.*TMath::Pi(), "Rad")));
	observables->add(*(new RooRealVar("kD_kpipi0_obs", "kD_kpipi0",       1, -2, 2)));
	observables->add(*(new RooRealVar("dD_kpipi0_obs", "dD_kpipi0",       0, 0, 2.*TMath::Pi(), "Rad")));
	observables->add(*(new RooRealVar("rD_k3pi_obs"  , "rD_k3pi"  ,       1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rD_kpipi0_obs", "rD_kpipi0",       1, -1e4, 1e4)));
}


void PDF_D_K3pi_Kpipi0_6D::setObservables(config c)
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
		case lhcb:
			obsValSource = "CLEO+LHCb"; // from Guy
			setObservable("kD_k3pi_obs"  , 0.32 );
			setObservable("dD_k3pi_obs"  , (170./180.)*TMath::Pi() );
			setObservable("kD_kpipi0_obs", 0.81 );
			setObservable("dD_kpipi0_obs", (180./180.)*TMath::Pi() );
			setObservable("rD_k3pi_obs"  , 5.52e-2 );
			setObservable("rD_kpipi0_obs", 4.40e-2 );
			break;

		default:
			cout << "PDF_D_K3pi_Kpipi0_6D::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_D_K3pi_Kpipi0_6D::setUncertainties(config c)
{
	switch(c)
	{
		case lhcb:
			obsErrSource = "CLEO+LHCb"; // from Guy
			StatErr[0] = 0.10;
			StatErr[1] = (38./180.)*TMath::Pi();
			StatErr[2] = 0.065;
			StatErr[3] = (17./180.)*TMath::Pi();
			StatErr[4] = 0.07e-2;
			StatErr[5] = 0.12e-2;

      SystErr[0] = 0.0;
			SystErr[1] = 0.0;
			SystErr[2] = 0.0;
      SystErr[3] = 0.0;
			SystErr[4] = 0.0;
			SystErr[5] = 0.0;
			break;

		default:
			cout << "PDF_D_K3pi_Kpipi0_6D::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_D_K3pi_Kpipi0_6D::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
    case check: {
			corSource = "CLEO+LHCb (only d,k corrs)"; // from Guy

      //                    kD_k3pi dD_k3pi kD_kpipi0 dD_kpipi0 rD_k3pi rD_kpipi0
      double corStat[] = {  1.00 ,  0.40 ,  0.00 ,  0.00 ,  0.00 ,  0.00 ,    // kD_k3pi
                            0.40 ,  1.00 ,  0.00 ,  0.00 ,  0.00 ,  0.00 ,    // dD_k3pi
                            0.00 ,  0.00 ,  1.00 , -0.29 ,  0.00 ,  0.00 ,    // kD_kpipi0
                            0.00 ,  0.00 , -0.29 ,  1.00 ,  0.00 ,  0.00 ,    // dD_kpipi0
                            0.00 ,  0.00 ,  0.00 ,  0.00 ,  1.00 ,  0.00 ,    // rD_k3pi
                            0.00 ,  0.00 ,  0.00 ,  0.00 ,  0.00 ,  1.00 } ;  // rD_kpipi0

      corStatMatrix = TMatrixDSym( nObs, corStat );

      // no systematic correlation

			break;
    }

		case lhcb: {
			corSource = "CLEO+LHCb"; // from Guy

      //                    kD_k3pi dD_k3pi kD_kpipi0 dD_kpipi0 rD_k3pi rD_kpipi0
      double corStat[] = {  1.00 ,  0.40 ,  0.00 , -0.14 , -0.33 ,  0.05 ,    // kD_k3pi
                            0.40 ,  1.00 ,  0.13 , -0.29 ,  0.43 , -0.20 ,    // dD_k3pi
                            0.00 ,  0.13 ,  1.00 , -0.29 ,  0.07 , -0.33 ,    // kD_kpipi0
                           -0.14 , -0.29 , -0.29 ,  1.00 , -0.18 ,  0.37 ,    // dD_kpipi0
                           -0.33 ,  0.43 ,  0.07 , -0.18 ,  1.00 , -0.11 ,    // rD_k3pi
                            0.05 , -0.20 , -0.33 ,  0.37 , -0.11 ,  1.00 } ;  // rD_kpipi0

      corStatMatrix = TMatrixDSym( nObs, corStat );

      // no systematic correlation

			break;
    }
		default:
			cout << "PDF_D_K3pi_Kpipi0_6D::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_D_K3pi_Kpipi0_6D::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
