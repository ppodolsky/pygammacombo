/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#include "PDF_D_HFAGfit.h"

	PDF_D_HFAGfit::PDF_D_HFAGfit(config cObs, config cErr, config cCor)
: PDF_Abs(6)
{
	name = "d-hfagfit";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_D_HFAGfit::~PDF_D_HFAGfit(){}


void PDF_D_HFAGfit::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("xD")));
	parameters->add(*(p.get("yD")));
	parameters->add(*(p.get("dD_kpi")));
	parameters->add(*(p.get("rD_kpi")));
	parameters->add(*(p.get("AcpDpipi")));
	parameters->add(*(p.get("AcpDKK")));
}


void PDF_D_HFAGfit::initRelations()
{
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	RooArgSet *p = (RooArgSet*)parameters;
	theory->add(*(new RooFormulaVar("xD_th",       "xD_th",       "xD", *p)));
	theory->add(*(new RooFormulaVar("yD_th",       "yD_th",       "yD", *p)));
	theory->add(*(new RooFormulaVar("dD_kpi_th",   "dD_kpi_th",   "dD_kpi", *p)));
	theory->add(*(new RooFormulaVar("rD_kpi_th",   "rD_kpi_th",   "rD_kpi^2", *p)));
	theory->add(*(new RooFormulaVar("AcpDpipi_th", "AcpDpipi_th", "AcpDpipi", *p)));
	theory->add(*(new RooFormulaVar("AcpDKK_th",   "AcpDKK_th",   "AcpDKK", *p)));
}


void PDF_D_HFAGfit::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("xD_obs",       "xD (HFAG)",       0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("yD_obs",       "yD (HFAG)",       0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("dD_kpi_obs",   "dD_kpi (HFAG)",   0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rD_kpi_obs",   "rD_kpi (HFAG)",   0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("AcpDpipi_obs", "AcpDpipi (HFAG)", 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("AcpDKK_obs",   "AcpDKK (HFAG)",   0, -1e4, 1e4)));
}


void PDF_D_HFAGfit::setObservables(config c)
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
							setObservable("xD_obs",       0.41e-2);
							// setObservable("xD_obs",       0.71e-2); // hunt down 2nd minimum
							setObservable("yD_obs",       0.63e-2);
							setObservable("dD_kpi_obs",   DegToRad(7.3+180.0));
							// setObservable("dD_kpi_obs",   DegToRad(27.3+180.0));  // hunt down 2nd minimum
							setObservable("rD_kpi_obs",   0.349e-2);
							// setObservable("rD_kpi_obs",   0.372e-2);  // hunt down 2nd minimum
							setObservable("AcpDpipi_obs", 0.14e-2);
							setObservable("AcpDKK_obs",   -0.11e-2);
							break;
						}
		case hfagCHARM2015:{
							// http://www.slac.stanford.edu/xorg/hfag/charm/CHARM15/results_mix_cpv.html
							obsValSource = "HFAG CHARM2015, CPV allowed";
							setObservable("xD_obs",       0.37e-2);
							setObservable("yD_obs",       0.66e-2);
							setObservable("dD_kpi_obs",   DegToRad(11.8+180.0));
							setObservable("rD_kpi_obs",   0.349e-2);
							setObservable("AcpDpipi_obs", 0.10e-2);
							setObservable("AcpDKK_obs",   -0.15e-2);
							break;
						}
		default:{
					cout << "PDF_D_HFAGfit::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_D_HFAGfit::setUncertainties(config c)
{
	switch(c)
	{
		case hfagFP2014:{
							obsErrSource = "HFAG FP2014, CPV allowed";
							StatErr[0] = 0.15e-2;        // xD_obs
							StatErr[1] = 0.08e-2;        // yD_obs
							StatErr[2] = DegToRad(11.5); // dD_kpi_obs
							StatErr[3] = 0.004e-2;       // rD_kpi_obs
							// StatErr[2] = DegToRad(8.8); // dD_kpi_obs // hunt down 2nd minimum
							// StatErr[3] = 0.0075e-2;       // rD_kpi_obs // hunt down 2nd minimum
							StatErr[4] = 0.15e-2;        // AcpDpipi_obs
							StatErr[5] = 0.14e-2;        // AcpDKK_obs
							SystErr[0] = 0.; // xD_obs
							SystErr[1] = 0.; // yD_obs
							SystErr[2] = 0.; // dD_kpi_obs
							SystErr[3] = 0.; // rD_kpi_obs
							SystErr[4] = 0.; // AcpDpipi_obs
							SystErr[5] = 0.; // AcpDKK_obs
							break;
						}
		case hfagCHARM2015:{
							obsErrSource = "HFAG CHARM2015, CPV allowed";
							StatErr[0] = 0.16e-2;         // xD_obs
							StatErr[1] = 0.085e-2;        // yD_obs
							StatErr[2] = DegToRad(12.1); // dD_kpi_obs
							StatErr[3] = 0.004e-2;       // rD_kpi_obs
							StatErr[4] = 0.15e-2;        // AcpDpipi_obs
							StatErr[5] = 0.14e-2;        // AcpDKK_obs
							SystErr[0] = 0.; // xD_obs
							SystErr[1] = 0.; // yD_obs
							SystErr[2] = 0.; // dD_kpi_obs
							SystErr[3] = 0.; // rD_kpi_obs
							SystErr[4] = 0.; // AcpDpipi_obs
							SystErr[5] = 0.; // AcpDKK_obs
							break;
						}
		default:{
					cout << "PDF_D_HFAGfit::setUncertainties() : ERROR : config cErr not found:" << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}


void PDF_D_HFAGfit::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case hfagFP2014:{
							corSource = "HFAG FP2014, CPV allowed";
							//                      1      2       3       4       9       10
							double dataStat[]  = { 1.000, -0.270, -0.119,  0.352,  0.070,  0.079,   // xD_obs       = 1
                                    -0.270,  1.000,  0.918,  0.119, -0.124, -0.137,   // yD_obs       = 2
                                    -0.119,  0.918,  1.000,  0.404, -0.149, -0.162,   // dD_kpi_obs   = 3
                                     0.352,  0.119,  0.404,  1.000, -0.026, -0.025,   // rD_kpi_obs   = 4
                                     0.070, -0.124, -0.149, -0.026,  1.000,  0.716,   // AcpDpipi_obs = 9
                                     0.079, -0.137, -0.162, -0.025,  0.716,  1.000 }; // AcpDKK_obs   = 10
							// debug bayesians: disable x,y correlation
							// double dataStat[]  = { 1.000, -0.270,  0.0,    0.0,    0.0,    0.0,     // xD_obs       = 1
							//                       -0.270,  1.000,  0.0,    0.0,    0.0,    0.0,     // yD_obs       = 2
							//                          0.0,    0.0,  1.000,  0.404, -0.149, -0.162,   // dD_kpi_obs   = 3
							//                          0.0,    0.0,  0.404,  1.000, -0.026, -0.025,   // rD_kpi_obs   = 4
							//                          0.0,    0.0, -0.149, -0.026,  1.000,  0.716,   // AcpDpipi_obs = 9
							//                          0.0,    0.0, -0.162, -0.025,  0.716,  1.000 }; // AcpDKK_obs   = 10
							corStatMatrix = TMatrixDSym(nObs,dataStat);
							// no syst cor
							break;
						}
		case hfagCHARM2015:{
							corSource = "HFAG CHARM2015, CPV allowed";
							//                      1      2       3       4       9       10
							double dataStat[]  = { 1.000, -0.361, -0.332,  0.234,  0.117,  0.146,   // xD_obs       = 1
																		-0.361,  1.000,  0.941,  0.234, -0.180, -0.221,   // yD_obs       = 2
																		-0.332,  0.941,  1.000,  0.439, -0.200, -0.237,   // dD_kpi_obs   = 3
																		 0.234,  0.234,  0.439,  1.000, -0.078, -0.067,   // rD_kpi_obs   = 4
																		 0.117, -0.180, -0.200, -0.078,  1.000,  0.726,   // AcpDpipi_obs = 9
																		 0.146, -0.221, -0.237, -0.067,  0.726,  1.000 }; // AcpDKK_obs   = 10
							// debug bayesians: disable x,y correlation
							// double dataStat[]  = { 1.000, -0.270,  0.0,    0.0,    0.0,    0.0,     // xD_obs       = 1
							//                       -0.270,  1.000,  0.0,    0.0,    0.0,    0.0,     // yD_obs       = 2
							//                          0.0,    0.0,  1.000,  0.404, -0.149, -0.162,   // dD_kpi_obs   = 3
							//                          0.0,    0.0,  0.404,  1.000, -0.026, -0.025,   // rD_kpi_obs   = 4
							//                          0.0,    0.0, -0.149, -0.026,  1.000,  0.716,   // AcpDpipi_obs = 9
							//                          0.0,    0.0, -0.162, -0.025,  0.716,  1.000 }; // AcpDKK_obs   = 10
							corStatMatrix = TMatrixDSym(nObs,dataStat);
							// no syst cor
							break;
						}
		default:{
					cout << "PDF_D_HFAGfit::setCorrelations() : ERROR : config cCor not found." << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}


void PDF_D_HFAGfit::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
