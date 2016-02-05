/**
 * Gamma Combination
 * Author: Matthew Kenzie matthew.kenzie@cern.ch
 * Date: November 2015
 *
 **/

///
/// The B0 -> D0 K*0 ADS measurement only.
///

#include "PDF_ADS_DKstz_Kpi.h"

	PDF_ADS_DKstz_Kpi::PDF_ADS_DKstz_Kpi(config cObs, config cErr, config cCor, ParametersAbs* pars, TString d)
: PDF_Abs(3)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	name = "ads-dkstz-kpi";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_ADS_DKstz_Kpi::~PDF_ADS_DKstz_Kpi(){}


void PDF_ADS_DKstz_Kpi::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("r_dkstz")));
	parameters->add(*(p.get("d_dkstz")));
  parameters->add(*(p.get("R_dkstz")));
  parameters->add(*(p.get("delta_dkstz")));
	parameters->add(*(p.get("k_dkstz")));
	parameters->add(*(p.get("g")));
	parameters->add(*(p.get("rD_kpi")));
	parameters->add(*(p.get("dD_kpi")));
}


void PDF_ADS_DKstz_Kpi::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	theory->add(*(new RooFormulaVar("afav_dkstz_kpi_th",  "afav_dkstz_kpi",  "2*k_dkstz*(r_dkstz*R_dkstz)*rD_kpi *sin((d_dkstz+delta_dkstz)-dD_kpi) *sin(g) / (1 + (r_dkstz*R_dkstz)^2*rD_kpi^2  + 2*k_dkstz*(r_dkstz*R_dkstz)*rD_kpi *cos((d_dkstz+delta_dkstz)-dD_kpi) *cos(g))", *p)));
	theory->add(*(new RooFormulaVar("rp_dkstz_th",        "rp_dkstz_th",     "((r_dkstz*R_dkstz)^2  + rD_kpi^2 + 2*k_dkstz *(r_dkstz*R_dkstz) *rD_kpi*cos( g+(d_dkstz+delta_dkstz) +dD_kpi)) / (1 + (r_dkstz*R_dkstz)^2 *rD_kpi^2 + 2*k_dkstz *(r_dkstz*R_dkstz) *rD_kpi*cos( g +(d_dkstz+delta_dkstz) -dD_kpi))", *p)));
	theory->add(*(new RooFormulaVar("rm_dkstz_th",        "rm_dkstz_th",     "((r_dkstz*R_dkstz)^2  + rD_kpi^2 + 2*k_dkstz *(r_dkstz*R_dkstz) *rD_kpi*cos(-g+(d_dkstz+delta_dkstz) +dD_kpi)) / (1 + (r_dkstz*R_dkstz)^2 *rD_kpi^2 + 2*k_dkstz *(r_dkstz*R_dkstz) *rD_kpi*cos(-g +(d_dkstz+delta_dkstz) -dD_kpi))", *p)));
}


void PDF_ADS_DKstz_Kpi::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("afav_dkstz_kpi_obs",  "A_{fav} (DK^{*}, K#pi)",  0, -1e4, 1e4))); // A_d^Kpi
	observables->add(*(new RooRealVar("rp_dkstz_obs",        "R_{+} (DK^{*})",          1, -1e4, 1e4))); // R_d^+
	observables->add(*(new RooRealVar("rm_dkstz_obs",        "R_{-} (DK^{*})",          1, -1e4, 1e4))); // R_d^-
}


void PDF_ADS_DKstz_Kpi::setObservables(config c)
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
						 obsValSource = "3fb-1 LHCb-PAPER-2014-028-v2, June 4";
						 setObservable("afav_dkstz_kpi_obs", -0.032); //   -0.00626      0.02810    // A_d^Kpi
						 setObservable("rp_dkstz_obs",        0.057); //    0.08537      0.06271    // R_d^+
						 setObservable("rm_dkstz_obs",        0.056); //    0.11856      0.11395    // R_d^-
						 // truth values corresponding to:                 ^^ rB=0.3    ^^ rB=0.3
						 //                                                   dB=190       dB=270
						 break;
					 }
		default:{
					cout << "PDF_ADS_DKstz_Kpi::setObservables : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}

void PDF_ADS_DKstz_Kpi::setUncertainties(config c)
{
	switch(c)
	{
		case lumi3fb:{
						 obsErrSource = "3fb-1 LHCb-PAPER-2014-028-v2, June 4";
						 StatErr[ 0] = 0.041;  // A_d^Kpi
						 StatErr[ 1] = 0.029;  // R_d^+
						 StatErr[ 2] = 0.032;  // R_d^-

						 SystErr[ 0] = 0.02;   // A_d^Kpi
						 SystErr[ 1] = 0.012;  // R_d^+
						 SystErr[ 2] = 0.012;  // R_d^-
						 break;
					 }
		default:{
					cout << "PDF_ADS_DKstz_Kpi::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_ADS_DKstz_Kpi::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi3fb:{
						 corSource = "3fb-1 LHCb-ANA-2012-118-v3.1";
             double myCorData[] = { 1.000,  0.091,  0.083,  // AdKpi
                                    0.091,  1.000, -0.081,  // Rd+
                                   -0.083, -0.081,  1.000}; // Rd-

						 corStatMatrix = TMatrixDSym(nObs,myCorData);

             double myCorData2[] = { 1.000,  0.008,  0.008,  // AdKpi
                                     0.008,  1.000,  0.997,  // Rd+
                                     0.008,  0.997,  1.000}; // Rd-
						 corSystMatrix = TMatrixDSym(nObs,myCorData2);
						 break;
					 }
		default:{
					cout << "PDF_ADS_DzKstz_Kpi::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_ADS_DKstz_Kpi::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
