/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#include "PDF_GLWADS_DKDpi_KSKpi.h"

	PDF_GLWADS_DKDpi_KSKpi::PDF_GLWADS_DKDpi_KSKpi(config cObs, config cErr, config cCor, ParametersAbs* pars, TString d)
: PDF_Abs(7)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	name = "glwads-dkdpi-KSKpi";
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


PDF_GLWADS_DKDpi_KSKpi::~PDF_GLWADS_DKDpi_KSKpi(){}


void PDF_GLWADS_DKDpi_KSKpi::initParameters()
{
	parameters = new RooArgList("parameters");
	parameters->add(*(p->get("r_dk"))); 
	parameters->add(*(p->get("d_dk"))); 
	parameters->add(*(p->get("r_dpi")));
	parameters->add(*(p->get("d_dpi"))); 
	parameters->add(*(p->get("g"))); 
	parameters->add(*(p->get("rD_kskpi")));
	parameters->add(*(p->get("dD_kskpi")));
	parameters->add(*(p->get("kD_kskpi")));
	parameters->add(*(p->get("RBRdkdpi")));
}  


void PDF_GLWADS_DKDpi_KSKpi::initRelations()
{
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	RooArgSet *p = (RooArgSet*)parameters;
	theory->add(*(new RooFormulaVar("rfavsup_dpi_kskpi_th", "rfavsup_dpi_kskpi_th", "(1 + r_dpi^2*rD_kskpi^2 + 2*r_dpi*rD_kskpi*kD_kskpi*cos(g)*cos(d_dpi-dD_kskpi))         /(r_dpi^2 + rD_kskpi^2   + 2*r_dpi*rD_kskpi*kD_kskpi*cos(g)*cos(d_dpi+dD_kskpi))", *p)));
	theory->add(*(new RooFormulaVar("rfav_dkdpi_kskpi_th",  "rfav_dkdpi_kskpi_th",  "RBRdkdpi*(1 + r_dk^2*rD_kskpi^2  + 2*r_dk *rD_kskpi*kD_kskpi*cos(g)*cos(d_dk -dD_kskpi))/(1 + r_dpi^2*rD_kskpi^2 + 2*r_dpi*rD_kskpi*kD_kskpi*cos(g)*cos(d_dpi-dD_kskpi))", *p)));  
	theory->add(*(new RooFormulaVar("rsup_dkdpi_kskpi_th",  "rsup_dkdpi_kskpi_th",  "RBRdkdpi*(r_dk^2 + rD_kskpi^2    + 2*r_dk *rD_kskpi*kD_kskpi*cos(g)*cos(d_dk +dD_kskpi))/(r_dpi^2 + rD_kskpi^2   + 2*r_dpi*rD_kskpi*kD_kskpi*cos(g)*cos(d_dpi+dD_kskpi))", *p)));  
	theory->add(*(new RooFormulaVar("afav_dk_kskpi_th",     "afav_dk_kskpi_th",     "2*r_dk *rD_kskpi*kD_kskpi*sin(g)*sin(d_dk -dD_kskpi) / (1 + r_dk^2  * rD_kskpi^2 + 2*r_dk *rD_kskpi*kD_kskpi*cos(g)*cos(d_dk -dD_kskpi))", *p)));
	theory->add(*(new RooFormulaVar("asup_dk_kskpi_th",     "asup_dk_kskpi_th",     "2*r_dk *rD_kskpi*kD_kskpi*sin(g)*sin(d_dk +dD_kskpi) / (r_dk^2  + rD_kskpi^2 + 2*r_dk *rD_kskpi*kD_kskpi*cos(g)*cos(d_dk +dD_kskpi))", *p)));
	theory->add(*(new RooFormulaVar("afav_dpi_kskpi_th",    "afav_dpi_kskpi_th",    "2*r_dpi*rD_kskpi*kD_kskpi*sin(g)*sin(d_dpi-dD_kskpi) / (1 + r_dpi^2 * rD_kskpi^2 + 2*r_dpi*rD_kskpi*kD_kskpi*cos(g)*cos(d_dpi-dD_kskpi))", *p)));
	theory->add(*(new RooFormulaVar("asup_dpi_kskpi_th",    "asup_dpi_kskpi_th",    "2*r_dpi*rD_kskpi*kD_kskpi*sin(g)*sin(d_dpi+dD_kskpi) / (r_dpi^2 + rD_kskpi^2 + 2*r_dpi*rD_kskpi*kD_kskpi*cos(g)*cos(d_dpi+dD_kskpi))", *p)));
}


void PDF_GLWADS_DKDpi_KSKpi::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("rfavsup_dpi_kskpi_obs", "R_{SS/OS,D#pi} (K_{S}K#pi)" , 1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rfav_dkdpi_kskpi_obs",  "R_{DK/D#pi, SS} (K_{S}K#pi)", 1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rsup_dkdpi_kskpi_obs",  "R_{DK/D#pi, OS} (K_{S}K#pi)", 1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("afav_dk_kskpi_obs",     "A_{SS,DK} (K_{S}K#pi)",       0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("asup_dk_kskpi_obs",     "A_{OS,DK} (K_{S}K#pi)",       0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("afav_dpi_kskpi_obs",    "A_{SS,D#pi} (K_{S}K#pi)",     0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("asup_dpi_kskpi_obs",    "A_{OS,D#pi} (K_{S}K#pi)",     0, -1e4, 1e4)));
}


void PDF_GLWADS_DKDpi_KSKpi::setObservables(config c)
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
							   obsValSource = "3fb-1, Dan's presentation at LHCb Week Dec 2013, whole Dalitz plot";
							   setObservable("rfavsup_dpi_kskpi_obs",  1.528);
							   setObservable("rfav_dkdpi_kskpi_obs",   0.092);
							   setObservable("rsup_dkdpi_kskpi_obs",   0.066);
							   setObservable("afav_dk_kskpi_obs",      0.040);
							   setObservable("asup_dk_kskpi_obs",      0.233);
							   setObservable("afav_dpi_kskpi_obs",    -0.025);
							   setObservable("asup_dpi_kskpi_obs",    -0.052);
							   break;
						   }
		case lumi3fb:{
						 obsValSource = "3fb-1, paper draft as of LHCb Week Dec 2013, K* region of Dalitz plot";
						 setObservable("rfavsup_dpi_kskpi_obs",  2.57);
						 setObservable("rfav_dkdpi_kskpi_obs",   0.084);
						 setObservable("rsup_dkdpi_kskpi_obs",   0.056);
						 setObservable("afav_dk_kskpi_obs",      0.026); // SS
						 setObservable("asup_dk_kskpi_obs",      0.336); // OS
						 setObservable("afav_dpi_kskpi_obs",    -0.012);
						 setObservable("asup_dpi_kskpi_obs",    -0.054);
						 break;
					 }
		default:
					 {
						 cout << "PDF_GLWADS_DKDpi_KSKpi::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
						 exit(1);
					 }
	}
}


void PDF_GLWADS_DKDpi_KSKpi::setUncertainties(config c)
{
	switch(c)
	{
		case lumi3fbFullDP:{
							   obsErrSource = "3fb-1, paper draft as of LHCb Week Dec 2013, whole Dalitz plot";
							   StatErr[0] = 0.058; // rfavsup_dpi_kskpi_obs       
							   StatErr[1] = 0.009; // rfav_dkdpi_kskpi_obs       
							   StatErr[2] = 0.009; // rsup_dkdpi_kskpi_obs       
							   StatErr[3] = 0.091; // afav_dk_kskpi_obs          
							   StatErr[4] = 0.129; // asup_dk_kskpi_obs          
							   StatErr[5] = 0.024; // afav_dpi_kskpi_obs         
							   StatErr[6] = 0.029; // asup_dpi_kskpi_obs
							   SystErr[0] = 0.025; // rfavsup_dpi_kskpi_obs       
							   SystErr[1] = 0.004; // rfav_dkdpi_kskpi_obs       
							   SystErr[2] = 0.002; // rsup_dkdpi_kskpi_obs       
							   SystErr[3] = 0.018; // afav_dk_kskpi_obs          
							   SystErr[4] = 0.024; // asup_dk_kskpi_obs          
							   SystErr[5] = 0.010; // afav_dpi_kskpi_obs         
							   SystErr[6] = 0.017; // asup_dpi_kskpi_obs         
							   break;
						   }
		case lumi3fb:{
						 obsErrSource = "3fb-1, paper draft as of LHCb Week Dec 2013, K* region of Dalitz plot";
						 StatErr[0] = 0.130; // rfavsup_dpi_kskpi_obs       
						 StatErr[1] = 0.011; // rfav_dkdpi_kskpi_obs       
						 StatErr[2] = 0.013; // rsup_dkdpi_kskpi_obs       
						 StatErr[3] = 0.109; // afav_dk_kskpi_obs          
						 StatErr[4] = 0.208; // asup_dk_kskpi_obs          
						 StatErr[5] = 0.028; // afav_dpi_kskpi_obs         
						 StatErr[6] = 0.043; // asup_dpi_kskpi_obs
						 SystErr[0] = 0.060; // rfavsup_dpi_kskpi_obs       
						 SystErr[1] = 0.003; // rfav_dkdpi_kskpi_obs       
						 SystErr[2] = 0.002; // rsup_dkdpi_kskpi_obs       
						 SystErr[3] = 0.029; // afav_dk_kskpi_obs          
						 SystErr[4] = 0.026; // asup_dk_kskpi_obs          
						 SystErr[5] = 0.010; // afav_dpi_kskpi_obs         
						 SystErr[6] = 0.017; // asup_dpi_kskpi_obs         
						 break;
					 }    
		default:{
					cout << "PDF_GLWADS_DKDpi_KSKpi::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}



void PDF_GLWADS_DKDpi_KSKpi::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi3fbFullDP:{
							   // corSource = "3fb-1, values are guesses based on error propagation of the yields, full Dalitz, see OtherFiles/KSKpi_ADS.py";
							   // double myCorData[] = {  1.   ,-0.22,  0.18,  0.   , 0.   ,-0.02,  0.04,  // rfavsup_dpi_kskpi_obs
							   //                        -0.22 , 1.  ,  0.  ,  0.04 , 0.   , 0.01,  0.  ,  // rfav_dkdpi_kskpi_obs 
							   //                         0.18 , 0.  ,  1.  ,  0.   , 0.22 , 0.  ,  0.01,  // rsup_dkdpi_kskpi_obs 
							   //                         0.   , 0.04,  0.  ,  1.   , 0.   , 0.  ,  0.  ,  // afav_dk_kskpi_obs    
							   //                         0.   , 0.  ,  0.22,  0.   , 1.   , 0.  ,  0.  ,  // asup_dk_kskpi_obs    
							   //                        -0.02 , 0.01,  0.  ,  0.   , 0.   , 1.  ,  0.  ,  // afav_dpi_kskpi_obs   
							   //                         0.04 , 0.  ,  0.01,  0.   , 0.   , 0.  ,  1.  }; // asup_dpi_kskpi_obs
							   // corStatMatrix = TMatrixDSym(nObs,myCorData);
							   corSource = "3fb-1, values from the paper draft";
							   double myCorData[] = {  1.   ,-0.16 , 0.16  ,0.   , 0.  ,  0.  ,  0.  ,  // rfavsup_dpi_kskpi_obs
								   -0.16 , 1.   , 0.11  ,0.   , 0.  ,  0.  ,  0.  ,  // rfav_dkdpi_kskpi_obs 
								   0.16 , 0.11 , 1.    ,0.   , 0.  ,  0.  ,  0.  ,  // rsup_dkdpi_kskpi_obs 
								   0.   , 0.   , 0.    ,1.   , 0.  ,  0.  ,  0.  ,  // afav_dk_kskpi_obs    
								   0.   , 0.   , 0.    ,0.   , 1.  ,  0.  ,  0.  ,  // asup_dk_kskpi_obs    
								   0.   , 0.   , 0.    ,0.   , 0.  ,  1.  ,  0.  ,  // afav_dpi_kskpi_obs   
								   0.   , 0.   , 0.    ,0.   , 0.  ,  0.  ,  1.  }; // asup_dpi_kskpi_obs
							   corStatMatrix = TMatrixDSym(nObs,myCorData);

							   // no systematics correlation
							   break;
						   }
		case lumi3fb:{
						 corSource = "3fb-1, values from the paper draft";
						 double myCorData[] = {  1.   ,-0.13 , 0.16  ,0.   , 0.  ,  0.  ,  0.  ,  // rfavsup_dpi_kskpi_obs
							 -0.13 , 1.   , 0.15  ,0.   , 0.  ,  0.  ,  0.  ,  // rfav_dkdpi_kskpi_obs 
							 0.16 , 0.15 , 1.    ,0.   , 0.  ,  0.  ,  0.  ,  // rsup_dkdpi_kskpi_obs 
							 0.   , 0.   , 0.    ,1.   , 0.  ,  0.  ,  0.  ,  // afav_dk_kskpi_obs    
							 0.   , 0.   , 0.    ,0.   , 1.  ,  0.  ,  0.  ,  // asup_dk_kskpi_obs    
							 0.   , 0.   , 0.    ,0.   , 0.  ,  1.  ,  0.  ,  // afav_dpi_kskpi_obs   
							 0.   , 0.   , 0.    ,0.   , 0.  ,  0.  ,  1.  }; // asup_dpi_kskpi_obs
						 corStatMatrix = TMatrixDSym(nObs,myCorData);
						 // no systematics correlation
						 break;
					 }
		case zero:{
					  corSource = "zero";
					  break;
				  }
		default:{
					cout << "PDF_GLWADS_DKDpi_KSKpi::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}    
	}
}  


void PDF_GLWADS_DKDpi_KSKpi::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
