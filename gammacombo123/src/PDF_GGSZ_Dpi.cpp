/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: June 2014
 *
 **/

#include "PDF_GGSZ_Dpi.h"

	PDF_GGSZ_Dpi::PDF_GGSZ_Dpi(config cObs, config cErr, config cCor, ParametersAbs* pars)
: PDF_Abs(4)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	name = "ggszdpi";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}

PDF_GGSZ_Dpi::~PDF_GGSZ_Dpi(){}


void PDF_GGSZ_Dpi::initParameters()
{
	parameters = new RooArgList("parameters");
	parameters->add(*(p->get("r_dpi"))); 
	parameters->add(*(p->get("d_dpi"))); 
	parameters->add(*(p->get("g")));
}  


void PDF_GGSZ_Dpi::initRelations()
{
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	RooArgSet *p = (RooArgSet*)parameters;
	theory->add(*(new RooFormulaVar("xm_dpi_th", "x- (Dpi GGSZ)", "r_dpi*cos(d_dpi-g)", *p)));
	theory->add(*(new RooFormulaVar("ym_dpi_th", "y- (Dpi GGSZ)", "r_dpi*sin(d_dpi-g)", *p)));
	theory->add(*(new RooFormulaVar("xp_dpi_th", "x+ (Dpi GGSZ)", "r_dpi*cos(d_dpi+g)", *p)));
	theory->add(*(new RooFormulaVar("yp_dpi_th", "y+ (Dpi GGSZ)", "r_dpi*sin(d_dpi+g)", *p)));
}


void PDF_GGSZ_Dpi::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("xm_dpi_obs", "x- (DK GGSZ)", 0, -1, 1)));
	observables->add(*(new RooRealVar("ym_dpi_obs", "y- (DK GGSZ)", 0, -1, 1)));
	observables->add(*(new RooRealVar("xp_dpi_obs", "x+ (DK GGSZ)", 0, -1, 1)));
	observables->add(*(new RooRealVar("yp_dpi_obs", "y+ (DK GGSZ)", 0, -1, 1)));
}


void PDF_GGSZ_Dpi::setObservables(config c)
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
						 obsValSource = "3fb-1 LHCb-ANA-2014-040 June 11 Sect E.1";
						 setObservable("xm_dpi_obs", -0.005);
						 setObservable("ym_dpi_obs", -0.004);
						 setObservable("xp_dpi_obs", -0.004);
						 setObservable("yp_dpi_obs",  0.004);
						 break;
					 }
		default:{
					cout << "PDF_GGSZ_Dpi::setObservables() : ERROR : config not found: " << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}


void PDF_GGSZ_Dpi::setUncertainties(config c)
{
	switch(c)
	{
		case lumi3fb:{
						 obsErrSource = "3fb-1 LHCb-ANA-2014-040 June 11 Sect E.1 (assuming same systs as B->DK)";
						 StatErr[0] = 0.007; // xm
						 StatErr[1] = 0.007; // ym
						 StatErr[2] = 0.007; // xp
						 StatErr[3] = 0.007; // yp
						 SystErr[0] = sqrt(sq(0.010)+sq(0.005)); // xm
						 SystErr[1] = sqrt(sq(0.005)+sq(0.014)); // ym
						 SystErr[2] = sqrt(sq(0.010)+sq(0.004)); // xp
						 SystErr[3] = sqrt(sq(0.004)+sq(0.010)); // yp
						 break;
					 }
		default:{
					cout << "PDF_GGSZ_Dpi::setUncertainties() : ERROR : config not found: " << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}


void PDF_GGSZ_Dpi::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi3fb:{
						 corSource = "zero";
						 break;
					 }
		default:{
					cout << "PDF_GGSZ_Dpi::setCorrelations() : ERROR : config not found: " << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}  


void PDF_GGSZ_Dpi::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
