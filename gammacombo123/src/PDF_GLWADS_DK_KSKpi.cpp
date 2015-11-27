/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: July 2014
 *
 **/

#include "PDF_GLWADS_DK_KSKpi.h"

	PDF_GLWADS_DK_KSKpi::PDF_GLWADS_DK_KSKpi(config cObs, config cErr, config cCor, ParametersAbs* pars, TString d)
: PDF_Abs(3)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	name = "glwads-dk-KSKpi";
	this->dir = d;
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_GLWADS_DK_KSKpi::~PDF_GLWADS_DK_KSKpi(){}


void PDF_GLWADS_DK_KSKpi::initParameters()
{
	parameters = new RooArgList("parameters");
	parameters->add(*(p->get("r_dk"))); 
	parameters->add(*(p->get("d_dk"))); 
	parameters->add(*(p->get("g"))); 
	parameters->add(*(p->get("rD_kskpi")));
	parameters->add(*(p->get("dD_kskpi")));
	parameters->add(*(p->get("kD_kskpi")));
}  


void PDF_GLWADS_DK_KSKpi::initRelations()
{
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	RooArgSet *p = (RooArgSet*)parameters;
	theory->add(*(new RooFormulaVar("rfavsup_dk_kskpi_th",  "rfavsup_dk_kskpi_th",  "(1 + r_dk^2*rD_kskpi^2  + 2*r_dk *rD_kskpi*kD_kskpi*cos(g)*cos(d_dk -dD_kskpi))/(r_dk^2 + rD_kskpi^2    + 2*r_dk *rD_kskpi*kD_kskpi*cos(g)*cos(d_dk +dD_kskpi))", *p)));  
	theory->add(*(new RooFormulaVar("afav_dk_kskpi_th",     "afav_dk_kskpi_th",     "2*r_dk *rD_kskpi*kD_kskpi*sin(g)*sin(d_dk -dD_kskpi) / (1 + r_dk^2  * rD_kskpi^2 + 2*r_dk *rD_kskpi*kD_kskpi*cos(g)*cos(d_dk -dD_kskpi))", *p)));
	theory->add(*(new RooFormulaVar("asup_dk_kskpi_th",     "asup_dk_kskpi_th",     "2*r_dk *rD_kskpi*kD_kskpi*sin(g)*sin(d_dk +dD_kskpi) / (r_dk^2  + rD_kskpi^2 + 2*r_dk *rD_kskpi*kD_kskpi*cos(g)*cos(d_dk +dD_kskpi))", *p)));
}


void PDF_GLWADS_DK_KSKpi::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("rfavsup_dk_kskpi_obs",  "R_{SS/OS,DK} (K_{S}K#pi)" ,   1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("afav_dk_kskpi_obs",     "A_{SS,DK} (K_{S}K#pi)",       0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("asup_dk_kskpi_obs",     "A_{OS,DK} (K_{S}K#pi)",       0, -1e4, 1e4)));
}


void PDF_GLWADS_DK_KSKpi::setObservables(config c)
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
		case lumi3fbFullDP:{
							   obsValSource = "3fb-1, 1402.2982, rfavsup_dk_kskpi_obs computed by OtherFiles/KSKpi_ExtractDK.py, full Dalitz region";
							   setObservable("rfavsup_dk_kskpi_obs",   3.545);
							   setObservable("afav_dk_kskpi_obs",      0.040);
							   setObservable("asup_dk_kskpi_obs",      0.233);
							   break;
						   }
		case lumi3fb:{
						 obsValSource = "3fb-1, 1402.2982, rfavsup_dk_kskpi_obs computed by OtherFiles/KSKpi_ExtractDK.py, K* region of Dalitz plot";
						 setObservable("rfavsup_dk_kskpi_obs",   3.855);
						 setObservable("afav_dk_kskpi_obs",      0.026);
						 setObservable("asup_dk_kskpi_obs",      0.336);
						 break;
					 }
		default:{
					cout << "PDF_GLWADS_DK_KSKpi::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_GLWADS_DK_KSKpi::setUncertainties(config c)
{
	switch(c)
	{
		case lumi3fbFullDP:{
							   obsErrSource = "3fb-1, 1402.2982, rfavsup_dk_kskpi_obs computed by OtherFiles/KSKpi_ExtractDK.py, full Dalitz region";
							   StatErr[0] = 0.965; // rfavsup_dk_kskpi_obs       
							   StatErr[1] = 0.091; // afav_dk_kskpi_obs          
							   StatErr[2] = 0.129; // asup_dk_kskpi_obs          
							   SystErr[0] = 0.025; // rfavsup_dpi_kskpi_obs       
							   SystErr[1] = 0.018; // afav_dk_kskpi_obs          
							   SystErr[2] = 0.024; // asup_dk_kskpi_obs          
							   break;
						   }
		case lumi3fb:{
						 obsErrSource = "3fb-1, 1402.2982, rfavsup_dk_kskpi_obs computed by OtherFiles/KSKpi_ExtractDK.py, K* region of Dalitz plot";
						 StatErr[0] = 0.961; // rfavsup_dk_kskpi_obs       
						 StatErr[1] = 0.109; // afav_dk_kskpi_obs          
						 StatErr[2] = 0.208; // asup_dk_kskpi_obs          
						 SystErr[0] = 0.060; // rfavsup_dpi_kskpi_obs       
						 SystErr[1] = 0.029; // afav_dk_kskpi_obs          
						 SystErr[2] = 0.026; // asup_dk_kskpi_obs          
						 break;
					 }
		case lumi9fb:{
						 setUncertainties(lumi3fb);
						 obsErrSource = "9fb-1 errors obtained from scaling down the 3fb-1 errors (lumi3fb)";
						 for ( int i=0; i<nObs; i++ ){
							 StatErr[i] /= (sqrt(2.7));
							 SystErr[i] /= (sqrt(2.7));
						 }
						 break;
					 }
		default:{
					cout << "PDF_GLWADS_DK_KSKpi::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_GLWADS_DK_KSKpi::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi3fbFullDP:{
							   corSource = "3fb-1, 1402.2982, no cor left for DK part, full Dalitz region";
							   break;
						   }
		case lumi3fb:{
						 corSource = "3fb-1, 1402.2982, no cor left for DK part, K* region of Dalitz plot";
						 break;
					 }
		case zero:{
					  corSource = "zero";
					  break;
				  }
		default:{
					cout << "PDF_GLWADS_DK_KSKpi::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}    
	}
}


void PDF_GLWADS_DK_KSKpi::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
