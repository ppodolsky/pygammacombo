/**
 * Gamma Combination
 * Author: Matthew Kenzie, matthew.kenzie@cern.ch
 * Date: Sep 2015
 *
 **/

#include "PDF_D_Cleo_Full.h"

	PDF_D_Cleo_Full::PDF_D_Cleo_Full(config cObs, config cErr, config cCor)
: PDF_Abs(13)
{
	name = "d-cleo-full";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_D_Cleo_Full::~PDF_D_Cleo_Full(){}


void PDF_D_Cleo_Full::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("xD")));
	parameters->add(*(p.get("yD")));
	parameters->add(*(p.get("dD_kpi")));
	parameters->add(*(p.get("rD_kpi")));
	parameters->add(*(p.get("rD_k3pi")));
	parameters->add(*(p.get("kD_k3pi")));
	parameters->add(*(p.get("dD_k3pi")));
	parameters->add(*(p.get("rD_kpipi0")));
	parameters->add(*(p.get("kD_kpipi0")));
	parameters->add(*(p.get("dD_kpipi0")));
	parameters->add(*(p.get("B_k3pi_FAV")));
	parameters->add(*(p.get("B_k3pi_SUP")));
	parameters->add(*(p.get("B_kpipi0_FAV")));
	parameters->add(*(p.get("B_kpipi0_SUP")));
	parameters->add(*(p.get("B_kpi_FAV")));
	parameters->add(*(p.get("B_kpi_SUP")));
}


void PDF_D_Cleo_Full::initRelations()
{
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	RooArgSet *p = (RooArgSet*)parameters;
  theory->add(*(new RooFormulaVar("B_k3pi_FAV_th"  , "B_k3pi_FAV_th"  , "B_k3pi_FAV"  , *p )));
  theory->add(*(new RooFormulaVar("B_k3pi_SUP_th"  , "B_k3pi_SUP_th"  , "B_k3pi_SUP"  , *p )));
  theory->add(*(new RooFormulaVar("B_kpipi0_FAV_th", "B_kpipi0_FAV_th", "B_kpipi0_FAV", *p )));
  theory->add(*(new RooFormulaVar("B_kpipi0_SUP_th", "B_kpipi0_SUP_th", "B_kpipi0_SUP", *p )));
  theory->add(*(new RooFormulaVar("B_kpi_FAV_th"   , "B_kpi_FAV_th"   , "B_kpi_FAV"   , *p )));
  theory->add(*(new RooFormulaVar("B_kpi_SUP_th"   , "B_kpi_SUP_th"   , "B_kpi_SUP"   , *p )));
  theory->add(*(new RooFormulaVar("rho_k3pi_LS_th"       , "rho_k3pi_LS_th"       , "(1-kD_k3pi^2) / (1. + (xD^2+yD^2)/(2.*rD_k3pi^2) - (kD_k3pi/rD_k3pi)*(yD*cos(dD_k3pi) - xD*sin(dD_k3pi)) )", *p)));
  theory->add(*(new RooFormulaVar("rho_k3pi_kpi_LS_th"   , "rho_k3pi_kpi_LS_th"   , "( (1 + rD_k3pi^2/rD_kpi^2 - 2.*(rD_k3pi/rD_kpi)*kD_k3pi*cos(dD_kpi-dD_k3pi))* ((B_k3pi_FAV*B_kpi_SUP)/(B_k3pi_FAV*B_kpi_SUP + B_k3pi_SUP*B_kpi_FAV) ) ) / ( 1. + (xD^2+yD^2)/(2.*rD_k3pi^2) - (1./rD_kpi)*(yD*cos(dD_kpi) - xD*sin(dD_kpi) ) )", *p)));
  theory->add(*(new RooFormulaVar("rho_kpipi0_LS_th"     , "rho_kpipi0_LS_th"     , "(1-kD_kpipi0^2) / (1. + (xD^2+yD^2)/(2.*rD_kpipi0^2) - (kD_kpipi0/rD_kpipi0)*(yD*cos(dD_kpipi0) - xD*sin(dD_kpipi0)) )", *p)));
  theory->add(*(new RooFormulaVar("rho_kpipi0_kpi_LS_th" , "rho_kpipi0_kpi_LS_th" , "( (1 + rD_kpipi0^2/rD_kpi^2 - 2.*(rD_kpipi0/rD_kpi)*kD_kpipi0*cos(dD_kpi-dD_kpipi0))* ((B_kpipi0_FAV*B_kpi_SUP)/(B_kpipi0_FAV*B_kpi_SUP + B_kpipi0_SUP*B_kpi_FAV) ) ) / ( 1. + (xD^2+yD^2)/(2.*rD_kpipi0^2) - (1./rD_kpi)*(yD*cos(dD_kpi) - xD*sin(dD_kpi) ) )", *p)));
  theory->add(*(new RooFormulaVar("rho_kpipi0_k3pi_LS_th", "rho_kpipi0_k3pi_LS_th", "( ( 1. + (rD_kpipi0^2/rD_k3pi^2) - 2.*(rD_kpipi0/rD_k3pi)*kD_kpipi0*kD_k3pi*cos(dD_kpipi0-dD_k3pi) )* ((B_kpipi0_FAV*B_k3pi_SUP)/(B_kpipi0_FAV*B_k3pi_SUP + B_kpipi0_SUP*B_k3pi_FAV)) ) / ( 1. + (xD^2 + yD^2)/(2.*rD_k3pi^2) - (kD_k3pi/rD_k3pi)*(yD*cos(dD_k3pi)-xD*sin(dD_k3pi)) )", *p)));
  theory->add(*(new RooFormulaVar("delta_k3pi_CP_th"     , "delta_k3pi_CP_th"     , "yD - 2.*rD_k3pi*kD_k3pi*cos(dD_k3pi)", *p)));
  theory->add(*(new RooFormulaVar("delta_kpipi0_CP_th"   , "delta_kpipi0_CP_th"   , "yD - 2.*rD_kpipi0*kD_kpipi0*cos(dD_kpipi0)", *p)));
  // need some BR measurements
}


void PDF_D_Cleo_Full::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!

  observables->add(*(new RooRealVar( "B_k3pi_FAV_obs"        , "B_k3pi_FAV (CLEO)"  ,  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar( "B_k3pi_SUP_obs"        , "B_k3pi_SUP (CLEO)"  ,  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar( "B_kpipi0_FAV_obs"      , "B_kpipi0_FAV (CLEO)",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar( "B_kpipi0_SUP_obs"      , "B_kpipi0_SUP (CLEO)",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar( "B_kpi_FAV_obs"         , "B_kpi_FAV (CLEO)"   ,  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar( "B_kpi_SUP_obs"         , "B_kpi_SUP (CLEO)"   ,  0, -1e4, 1e4)));
  observables->add(*(new RooRealVar( "rho_k3pi_LS_obs"       , "rho_k3pi_LS (CLEO)"       ,  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar( "rho_k3pi_kpi_LS_obs"   , "rho_k3pi_kpi_LS (CLEO)"   ,  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar( "rho_kpipi0_LS_obs"     , "rho_kpipi0_LS (CLEO)"     ,  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar( "rho_kpipi0_kpi_LS_obs" , "rho_kpipi0_kpi_LS (CLEO)" ,  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar( "rho_kpipi0_k3pi_LS_obs", "rho_kpipi0_k3pi_LS (CLEO)",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar( "delta_k3pi_CP_obs"     , "delta_k3pi_CP (CLEO)"     ,  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar( "delta_kpipi0_CP_obs"   , "delta_kpipi0_CP (CLEO)"   ,  0, -1e4, 1e4)));
}


void PDF_D_Cleo_Full::setObservables(config c)
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
		case cleo2014:{
							// http://www.slac.stanford.edu/xorg/hfag/charm/FPCP14/results_mix+cpv.html
							obsValSource = "arxiv:1401.1904";
							setObservable("B_k3pi_FAV_obs"        , 8.29e-02);
							setObservable("B_k3pi_SUP_obs"        , 2.68e-04);
							setObservable("B_kpipi0_FAV_obs"      , 14.96e-02);
							setObservable("B_kpipi0_SUP_obs"      , 3.28e-04);
							setObservable("B_kpi_FAV_obs"         , 3.88e-02);
							setObservable("B_kpi_SUP_obs"         , 1.47e-04);
							setObservable("rho_k3pi_LS_obs"       , 1.116 );
							setObservable("rho_k3pi_kpi_LS_obs"   , 1.018 );
							setObservable("rho_kpipi0_LS_obs"     , 0.388 );
							setObservable("rho_kpipi0_kpi_LS_obs" , 0.180 );
							setObservable("rho_kpipi0_k3pi_LS_obs", 1.218 );
							setObservable("delta_k3pi_CP_obs"     , 0.084 );
							setObservable("delta_kpipi0_CP_obs"   , 0.119 );
							break;
						}
		default:{
					cout << "PDF_D_Cleo_Full::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_D_Cleo_Full::setUncertainties(config c)
{
	switch(c)
	{
		case cleo2014:{
							obsErrSource = "arxiv:1401.1904";
							StatErr[0]  = 0.20e-02; // B_k3pi_FAV
							StatErr[1]  = 0.11e-04; // B_k3pi_SUP
							StatErr[2]  = 0.34e-02; // B_kpipi0_FAV
							StatErr[3]  = 0.20e-04; // B_kpipi0_SUP
							StatErr[4]  = 0.05e-02; // B_kpi_FAV
							StatErr[5]  = 0.07e-04; // B_kpi_SUP
							StatErr[6]  = 0.227; // rho_k3pi_LS
							StatErr[7]  = 0.177; // rho_k3pi_kpi_LS
							StatErr[8]  = 0.127; // rho_kpipi0_LS
							StatErr[9]  = 0.076; // rho_kpipi0_kpi_LS
							StatErr[10] = 0.169; // rho_kpipi0_k3pi_LS
							StatErr[11] = 0.018; // delta_k3pi_CP
							StatErr[12] = 0.015; // delta_kpipi0_CP

							SystErr[0]  = 0.; // B_k3pi_FAV
							SystErr[1]  = 0.; // B_k3pi_SUP
							SystErr[2]  = 0.; // B_kpipi0_FAV
							SystErr[3]  = 0.; // B_kpipi0_SUP
							SystErr[4]  = 0.; // B_kpi_FAV
							SystErr[5]  = 0.; // B_kpi_SUP
							SystErr[6]  = 0.073; // rho_k3pi_LS
							SystErr[7]  = 0.054; // rho_k3pi_kpi_LS
							SystErr[8]  = 0.026; // rho_kpipi0_LS
							SystErr[9]  = 0.028; // rho_kpipi0_kpi_LS
							SystErr[10] = 0.062; // rho_kpipi0_k3pi_LS
							SystErr[11] = 0.022; // delta_k3pi_CP
							SystErr[12] = 0.022; // delta_kpipi0_CP
							break;
						}
		default:{
					cout << "PDF_D_Cleo_Full::setUncertainties() : ERROR : config cErr not found:" << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}


void PDF_D_Cleo_Full::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case cleo2014:{
          corSource = "no correlation";
          break;
         }
		default:{
					cout << "PDF_D_Cleo_Full::setCorrelations() : ERROR : config cCor not found." << ConfigToTString(c) << endl;
					exit(1);
		}
	}
}


void PDF_D_Cleo_Full::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
