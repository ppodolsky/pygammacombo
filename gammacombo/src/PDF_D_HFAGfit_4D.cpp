/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#include "PDF_D_HFAGfit_4D.h"

	PDF_D_HFAGfit_4D::PDF_D_HFAGfit_4D(config cObs, config cErr, config cCor)
: PDF_Abs(4)
{
	name = "d-hfagfit_4D";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_D_HFAGfit_4D::~PDF_D_HFAGfit_4D(){}


void PDF_D_HFAGfit_4D::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("dD_kpi")));
	parameters->add(*(p.get("rD_kpi")));
	parameters->add(*(p.get("AcpDpipi")));
	parameters->add(*(p.get("AcpDKK")));
}


void PDF_D_HFAGfit_4D::initRelations()
{
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	RooArgSet *p = (RooArgSet*)parameters;
	theory->add(*(new RooFormulaVar("dD_kpi_th",   "dD_kpi_th",   "dD_kpi", *p)));
	theory->add(*(new RooFormulaVar("rD_kpi_th",   "rD_kpi_th",   "rD_kpi^2", *p)));
	theory->add(*(new RooFormulaVar("AcpDpipi_th", "AcpDpipi_th", "AcpDpipi", *p)));
	theory->add(*(new RooFormulaVar("AcpDKK_th",   "AcpDKK_th",   "AcpDKK", *p)));
}


void PDF_D_HFAGfit_4D::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("dD_kpi_obs",   "dD_kpi (HFAG)",   0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rD_kpi_obs",   "rD_kpi (HFAG)",   0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("AcpDpipi_obs", "AcpDpipi (HFAG)", 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("AcpDKK_obs",   "AcpDKK (HFAG)",   0, -1e4, 1e4)));
}


void PDF_D_HFAGfit_4D::setObservables(config c)
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
		case hfagFP2014:{
							// http://www.slac.stanford.edu/xorg/hfag/charm/FPCP14/results_mix+cpv.html
							obsValSource = "HFAG FP2014, CPV allowed";
							setObservable("dD_kpi_obs",   DegToRad(7.3+180.0));
							setObservable("rD_kpi_obs",   0.349e-2);
							setObservable("AcpDpipi_obs", 0.14e-2);
							setObservable("AcpDKK_obs",   -0.11e-2);
							break;
						}
		case hfagCHARM2015:{
							// http://www.slac.stanford.edu/xorg/hfag/charm/CHARM15/results_mix_cpv.html
							obsValSource = "HFAG CHARM2015, CPV allowed";
							setObservable("dD_kpi_obs",   DegToRad(11.8+180.0));
							setObservable("rD_kpi_obs",   0.349e-2);
							setObservable("AcpDpipi_obs", 0.10e-2);
							setObservable("AcpDKK_obs",   -0.15e-2);
							break;
						}
		default:{
					cout << "PDF_D_HFAGfit_4D::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_D_HFAGfit_4D::setUncertainties(config c)
{
	switch(c)
	{
		case hfagFP2014:{
							obsErrSource = "HFAG FP2014, CPV allowed";
							StatErr[0] = DegToRad(11.5); // dD_kpi_obs
							StatErr[1] = 0.004e-2;       // rD_kpi_obs
							StatErr[2] = 0.15e-2;        // AcpDpipi_obs
							StatErr[3] = 0.14e-2;        // AcpDKK_obs
							SystErr[0] = 0.; // dD_kpi_obs
							SystErr[1] = 0.; // rD_kpi_obs
							SystErr[2] = 0.; // AcpDpipi_obs
							SystErr[3] = 0.; // AcpDKK_obs
							break;
						}
		case hfagCHARM2015:{
							obsErrSource = "HFAG CHARM2015, CPV allowed";
							StatErr[0] = DegToRad(12.1); // dD_kpi_obs
							StatErr[1] = 0.004e-2;       // rD_kpi_obs
							StatErr[2] = 0.15e-2;        // AcpDpipi_obs
							StatErr[3] = 0.14e-2;        // AcpDKK_obs
							SystErr[0] = 0.; // dD_kpi_obs
							SystErr[1] = 0.; // rD_kpi_obs
							SystErr[2] = 0.; // AcpDpipi_obs
							SystErr[3] = 0.; // AcpDKK_obs
							break;
						}
		default:{
					cout << "PDF_D_HFAGfit_4D::setUncertainties() : ERROR : config cErr not found:" << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}


void PDF_D_HFAGfit_4D::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case hfagFP2014:{
							corSource = "HFAG FP2014, CPV allowed";
							//                       3       4       9       10
							double dataStat[]  = { 1.000,  0.404, -0.149, -0.162,   // dD_kpi_obs   = 3
                                     0.404,  1.000, -0.026, -0.025,   // rD_kpi_obs   = 4
                                    -0.149, -0.026,  1.000,  0.716,   // AcpDpipi_obs = 9
                                    -0.162, -0.025,  0.716,  1.000 }; // AcpDKK_obs   = 10
							corStatMatrix = TMatrixDSym(nObs,dataStat);
							// no syst cor
							break;
						}
		case hfagCHARM2015:{
							corSource = "HFAG CHARM2015, CPV allowed";
							//                       3       4       9       10
							double dataStat[]  = { 1.000,  0.439, -0.200, -0.237,   // dD_kpi_obs   = 3
																		 0.439,  1.000, -0.078, -0.067,   // rD_kpi_obs   = 4
																		-0.200, -0.078,  1.000,  0.726,   // AcpDpipi_obs = 9
																		-0.237, -0.067,  0.726,  1.000 }; // AcpDKK_obs   = 10
							corStatMatrix = TMatrixDSym(nObs,dataStat);
							// no syst cor
							break;
						}
		default:{
					cout << "PDF_D_HFAGfit_4D::setCorrelations() : ERROR : config cCor not found." << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}


void PDF_D_HFAGfit_4D::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
