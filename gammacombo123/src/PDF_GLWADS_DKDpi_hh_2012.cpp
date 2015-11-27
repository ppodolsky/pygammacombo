/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Nov 2014
 *
 * Combine all 13 observables from the 2012 GLW/ADS measurement.
 *
 **/

#include "PDF_GLWADS_DKDpi_hh_2012.h"

	PDF_GLWADS_DKDpi_hh_2012::PDF_GLWADS_DKDpi_hh_2012(config cObs, config cErr, config cCor, ParametersAbs* pars)
: PDF_Abs(13)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	name = "GlwadsDkdpiKpi2012";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}

	PDF_GLWADS_DKDpi_hh_2012::PDF_GLWADS_DKDpi_hh_2012(ParametersAbs* pars, int nObs)
: PDF_Abs(nObs)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
}


PDF_GLWADS_DKDpi_hh_2012::~PDF_GLWADS_DKDpi_hh_2012(){}


void PDF_GLWADS_DKDpi_hh_2012::initParameters()
{
	parameters = new RooArgList("parameters");
	parameters->add(*(p->get("r_dk"))); 
	parameters->add(*(p->get("d_dk"))); 
	parameters->add(*(p->get("r_dpi")));
	parameters->add(*(p->get("d_dpi"))); 
	parameters->add(*(p->get("g")));
	parameters->add(*(p->get("rD_kpi")));
	parameters->add(*(p->get("dD_kpi")));
	parameters->add(*(p->get("RBRdkdpi")));
	parameters->add(*(p->get("AcpDKK")));
	parameters->add(*(p->get("AcpDpipi")));
	parameters->add(*(p->get("Aprod")));
}  


void PDF_GLWADS_DKDpi_hh_2012::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	theory->add(*(new RooFormulaVar("rkp_kpi_th",          "rkp_kpi",      "RBRdkdpi*(1 + r_dk^2 * rD_kpi^2 + 2*r_dk*rD_kpi*cos(g)*cos(d_dk-dD_kpi))/(1 + r_dpi^2 * rD_kpi^2 + 2*r_dpi*rD_kpi*cos(g)*cos(d_dpi-dD_kpi))", *p)));
	theory->add(*(new RooFormulaVar("rcp_pipi_th",         "rcp_pipi",     "((1 + r_dk^2 + 2*r_dk*cos(d_dk)*cos(g))/(1 + r_dpi^2 + 2*r_dpi*cos(d_dpi)*cos(g)))/((1 + r_dk^2 * rD_kpi^2 + 2*r_dk*rD_kpi*cos(g)*cos(d_dk-dD_kpi))/(1 + r_dpi^2 * rD_kpi^2 + 2*r_dpi*rD_kpi*cos(g)*cos(d_dpi-dD_kpi)))", *p)));
	theory->add(*(new RooFormulaVar("rcp_kk_th",           "rcp_kk",       "((1 + r_dk^2 + 2*r_dk*cos(d_dk)*cos(g))/(1 + r_dpi^2 + 2*r_dpi*cos(d_dpi)*cos(g)))/((1 + r_dk^2 * rD_kpi^2 + 2*r_dk*rD_kpi*cos(g)*cos(d_dk-dD_kpi))/(1 + r_dpi^2 * rD_kpi^2 + 2*r_dpi*rD_kpi*cos(g)*cos(d_dpi-dD_kpi)))", *p)));
	theory->add(*(new RooFormulaVar("afav_dpi_kpi_th",     "afav_dpi_kpi", "Aprod", *p)));
	theory->add(*(new RooFormulaVar("afav_dk_kpi_th",      "afav_dk_kpi",  "2*r_dk *rD_kpi*sin(g)*sin(d_dk -dD_kpi) / (1 + r_dk^2  * rD_kpi^2 + 2*r_dk *rD_kpi*cos(g)*cos(d_dk -dD_kpi)) + Aprod", *p)));
	theory->add(*(new RooFormulaVar("acp_dpi_kk_th",       "acp_dpi_kk",   "2*r_dpi*sin(d_dpi)*sin(g) / (1 + r_dpi^2 + 2*r_dpi*cos(d_dpi)*cos(g)) + AcpDKK   + Aprod", *p)));
	theory->add(*(new RooFormulaVar("acp_dpi_pipi_th",     "acp_dpi_pipi", "2*r_dpi*sin(d_dpi)*sin(g) / (1 + r_dpi^2 + 2*r_dpi*cos(d_dpi)*cos(g)) + AcpDpipi + Aprod", *p)));
	theory->add(*(new RooFormulaVar("acp_dk_kk_th",        "acp_dk_kk",    "2*r_dk *sin(d_dk) *sin(g) / (1 + r_dk^2  + 2*r_dk *cos(d_dk) *cos(g)) + AcpDKK   + Aprod", *p)));
	theory->add(*(new RooFormulaVar("acp_dk_pipi_th",      "acp_dk_pipi",  "2*r_dk *sin(d_dk) *sin(g) / (1 + r_dk^2  + 2*r_dk *cos(d_dk) *cos(g)) + AcpDpipi + Aprod", *p)));
	theory->add(*(new RooFormulaVar("rads_dk_kpi_th",      "rads_dk_kpi_th",  "(r_dk^2  + rD_kpi^2 + 2*r_dk *rD_kpi*cos(d_dk +dD_kpi)*cos(g))/(1 + r_dk^2 *rD_kpi^2 + 2*r_dk *rD_kpi*cos(d_dk -dD_kpi)*cos(g))", *p)));
	theory->add(*(new RooFormulaVar("aads_dk_kpi_th",      "aads_dk_kpi_th",  "(2*r_dk *rD_kpi*sin(d_dk +dD_kpi)*sin(g))/(r_dk^2  + rD_kpi^2 + 2*r_dk *rD_kpi*cos(d_dk +dD_kpi)*cos(g))", *p)));
	theory->add(*(new RooFormulaVar("rads_dpi_kpi_th",     "rads_dpi_kpi_th", "(r_dpi^2  + rD_kpi^2 + 2*r_dpi *rD_kpi*cos(d_dpi +dD_kpi)*cos(g))/(1 + r_dpi^2 *rD_kpi^2 + 2*r_dpi *rD_kpi*cos(d_dpi -dD_kpi)*cos(g))", *p)));
	theory->add(*(new RooFormulaVar("aads_dpi_kpi_th",     "aads_dpi_kpi_th", "(2*r_dpi *rD_kpi*sin(d_dpi +dD_kpi)*sin(g))/(r_dpi^2  + rD_kpi^2 + 2*r_dpi *rD_kpi*cos(d_dpi +dD_kpi)*cos(g))", *p)));
}


void PDF_GLWADS_DKDpi_hh_2012::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("rkp_kpi_obs",     "rkp_kpi_obs",      1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rcp_pipi_obs",    "rcp_pipi_obs",     1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rcp_kk_obs",      "rcp_kk_obs",       1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("afav_dpi_kpi_obs","afav_dpi_kpi_obs", 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("afav_dk_kpi_obs", "afav_dk_kpi_obs",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dpi_kk_obs",  "acp_dpi_kk_obs",   0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dpi_pipi_obs","acp_dpi_pipi_obs", 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dk_kk_obs",   "acp_dk_kk_obs",    0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dk_pipi_obs", "acp_dk_pipi_obs",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rads_dk_kpi_obs", "rads_dk_kpi_obs",     1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("aads_dk_kpi_obs", "aads_dk_kpi_obs",     0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rads_dpi_kpi_obs","rads_dpi_kpi_obs",    1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("aads_dpi_kpi_obs","aads_dpi_kpi_obs",    0, -1e4, 1e4)));
}


void PDF_GLWADS_DKDpi_hh_2012::setObservables(config c)
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
				     obsValSource = "3fb-1 ANA v2, ADS values still blind (using Asimov/HFAG/1fb values)";
				     setObservable("rkp_kpi_obs",       0.0785 );
				     setObservable("rcp_pipi_obs",      1.045  );
				     setObservable("rcp_kk_obs",        0.981  );
				     setObservable("afav_dpi_kpi_obs",  -0.0033); // now Aprod
				     setObservable("afav_dk_kpi_obs",   -0.0158);
				     setObservable("acp_dpi_kk_obs",    -0.0162);
				     setObservable("acp_dpi_pipi_obs",  0.00315);
				     setObservable("acp_dk_kk_obs",     0.0844 );
				     setObservable("acp_dk_pipi_obs",   0.117  ); 
				     setObservable("rads_dk_kpi_obs",   0.015  ); // HFAG 2014
				     setObservable("aads_dk_kpi_obs",   -0.54  ); // HFAG 2014
				     setObservable("rads_dpi_kpi_obs",  0.0035 ); // Asimov r_dpi=0.005
				     setObservable("aads_dpi_kpi_obs",  0.12   ); // Asimov r_dpi=0.005
				     break;			
			     }
		default:{
				cout << "PDF_GLWADS_DKDpi_hh_2012::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}
	}
}


void PDF_GLWADS_DKDpi_hh_2012::setUncertainties(config c)
{
	switch(c){
		case lumi3fb:{
				     obsErrSource = "3fb-1 ANA v2 3fbGLWADSresultConvertToCode.py";
				     StatErr[ 0] = 0.0006 ; // rkp_kpi_obs      
				     StatErr[ 1] = 0.040  ; // rcp_pipi_obs     
				     StatErr[ 2] = 0.022  ; // rcp_kk_obs       
				     StatErr[ 3] = 0.0016 ; // afav_dpi_kpi_obs // now Aprod
				     StatErr[ 4] = 0.0072 ; // afav_dk_kpi_obs   
				     StatErr[ 5] = 0.0050 ; // acp_dpi_kk_obs   
				     StatErr[ 6] = 0.00861; // acp_dpi_pipi_obs 
				     StatErr[ 7] = 0.0200 ; // acp_dk_kk_obs    
				     StatErr[ 8] = 0.036  ; // acp_dk_pipi_obs  
				     StatErr[ 9] = 0.0011 ; // rads_dk_kpi_obs  
				     StatErr[10] = 0.0559 ; // aads_dk_kpi_obs  
				     StatErr[11] = 0.00012; // rads_dpi_kpi_obs 
				     StatErr[12] = 0.0310 ; // aads_dpi_kpi_obs 

				     SystErr[ 0] = 0.0014 ; // rkp_kpi_obs      
				     SystErr[ 1] = 0.018  ; // rcp_pipi_obs     
				     SystErr[ 2] = 0.017  ; // rcp_kk_obs       
				     SystErr[ 3] = 0.0044 ; // afav_dpi_kpi_obs // now Aprod
				     SystErr[ 4] = 0.0030 ; // afav_dk_kpi_obs  
				     SystErr[ 5] = 0.0028 ; // acp_dpi_kk_obs   
				     SystErr[ 6] = 0.00284; // acp_dpi_pipi_obs 
				     SystErr[ 7] = 0.0010 ; // acp_dk_kk_obs    
				     SystErr[ 8] = 0.002  ; // acp_dk_pipi_obs  
				     SystErr[ 9] = 0.0002 ; // rads_dk_kpi_obs  
				     SystErr[10] = 0.0046 ; // aads_dk_kpi_obs  
				     SystErr[11] = 0.00001; // rads_dpi_kpi_obs 
				     SystErr[12] = 0.0056 ; // aads_dpi_kpi_obs 
				     break;
			     }
		default:{
				cout << "PDF_GLWADS_DKDpi_hh_2012::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}
	}
}


void PDF_GLWADS_DKDpi_hh_2012::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi3fb:{
				corSource = "ANA v2 20.11.2014 ExpNll/3fbGLWADScorCorrectOrder.py";
				double dataStat[]  = { 
					 1.00 , -0.17 , -0.31 ,  0.00 ,  0.00 , -0.00 ,  0.00 , -0.00 , -0.01 , -0.11 ,  0.00 ,  0.01 ,  0.00 ,
					-0.17 ,  1.00 ,  0.06 ,  0.00 , -0.00 ,  0.00 , -0.00 , -0.00 , -0.03 ,  0.03 ,  0.00 , -0.00 ,  0.00 ,
					-0.31 ,  0.06 ,  1.00 , -0.00 , -0.00 , -0.00 ,  0.00 , -0.01 , -0.00 ,  0.04 ,  0.00 , -0.01 ,  0.00 ,
					 0.00 ,  0.00 , -0.00 ,  1.00 , -0.28 , -0.33 , -0.19 , -0.08 , -0.05 ,  0.00 , -0.03 ,  0.00 , -0.05 ,
					 0.00 , -0.00 , -0.00 , -0.28 ,  1.00 ,  0.09 ,  0.05 ,  0.02 ,  0.01 , -0.00 ,  0.01 , -0.00 ,  0.01 ,
					-0.00 ,  0.00 , -0.00 , -0.33 ,  0.09 ,  1.00 ,  0.06 , -0.01 ,  0.02 , -0.00 ,  0.01 , -0.00 ,  0.02 ,
					 0.00 , -0.00 ,  0.00 , -0.19 ,  0.05 ,  0.06 ,  1.00 ,  0.02 , -0.04 , -0.00 ,  0.01 , -0.00 ,  0.01 ,
					-0.00 , -0.00 , -0.01 , -0.08 ,  0.02 , -0.01 ,  0.02 ,  1.00 ,  0.00 , -0.00 ,  0.00 ,  0.00 ,  0.00 ,
					-0.01 , -0.03 , -0.00 , -0.05 ,  0.01 ,  0.02 , -0.04 ,  0.00 ,  1.00 , -0.00 ,  0.00 , -0.00 ,  0.00 ,
					-0.11 ,  0.03 ,  0.04 ,  0.00 , -0.00 , -0.00 , -0.00 , -0.00 , -0.00 ,  1.00 ,  0.10 , -0.02 ,  0.02 ,
					 0.00 ,  0.00 ,  0.00 , -0.03 ,  0.01 ,  0.01 ,  0.01 ,  0.00 ,  0.00 ,  0.10 ,  1.00 , -0.00 , -0.05 ,
					 0.01 , -0.00 , -0.01 ,  0.00 , -0.00 , -0.00 , -0.00 ,  0.00 , -0.00 , -0.02 , -0.00 ,  1.00 , -0.04 ,
					 0.00 ,  0.00 ,  0.00 , -0.05 ,  0.01 ,  0.02 ,  0.01 ,  0.00 ,  0.00 ,  0.02 , -0.05 , -0.04 ,  1.00 
				};
				corStatMatrix = TMatrixDSym(nObs,dataStat);
				double dataSyst[]  = { 
					 1.00 ,  0.26 ,  0.03 ,  0.00 ,  0.00 , -0.18 , -0.15 , -0.07 , -0.09 , -0.13 , -0.05 , -0.09 ,  0.07 ,
					 0.26 ,  1.00 ,  0.48 ,  0.00 , -0.02 , -0.12 , -0.24 , -0.04 , -0.16 ,  0.13 , -0.07 ,  0.06 ,  0.01 ,
					 0.03 ,  0.48 ,  1.00 ,  0.00 , -0.00 ,  0.34 , -0.05 ,  0.06 ,  0.20 ,  0.50 , -0.02 ,  0.37 , -0.22 ,
					 0.00 ,  0.00 ,  0.00 ,  1.00 ,  0.65 , -0.03 , -0.38 , -0.07 , -0.14 ,  0.01 , -0.14 , -0.03 , -0.33 ,
					 0.00 , -0.02 , -0.00 ,  0.65 ,  1.00 , -0.20 , -0.11 ,  0.02 , -0.06 , -0.03 , -0.11 , -0.08 , -0.53 ,
					-0.18 , -0.12 ,  0.34 , -0.03 , -0.20 ,  1.00 ,  0.22 , -0.40 , -0.01 ,  0.17 ,  0.01 ,  0.46 ,  0.20 ,
					-0.15 , -0.24 , -0.05 , -0.38 , -0.11 ,  0.22 ,  1.00 ,  0.14 ,  0.16 ,  0.10 ,  0.08 ,  0.06 , -0.11 ,
					-0.07 , -0.04 ,  0.06 , -0.07 ,  0.02 , -0.40 ,  0.14 ,  1.00 ,  0.66 ,  0.15 ,  0.67 , -0.31 , -0.72 ,
					-0.09 , -0.16 ,  0.20 , -0.14 , -0.06 , -0.01 ,  0.16 ,  0.66 ,  1.00 ,  0.21 ,  0.54 , -0.22 , -0.59 ,
					-0.13 ,  0.13 ,  0.50 ,  0.01 , -0.03 ,  0.17 ,  0.10 ,  0.15 ,  0.21 ,  1.00 , -0.09 ,  0.33 , -0.22 ,
					-0.05 , -0.07 , -0.02 , -0.14 , -0.11 ,  0.01 ,  0.08 ,  0.67 ,  0.54 , -0.09 ,  1.00 , -0.48 , -0.51 ,
					-0.09 ,  0.06 ,  0.37 , -0.03 , -0.08 ,  0.46 ,  0.06 , -0.31 , -0.22 ,  0.33 , -0.48 ,  1.00 ,  0.26 ,
					 0.07 ,  0.01 , -0.22 , -0.33 , -0.53 ,  0.20 , -0.11 , -0.72 , -0.59 , -0.22 , -0.51 ,  0.26 ,  1.00
				};
				corSystMatrix = TMatrixDSym(nObs,dataSyst);
				break;
		}
		default:{
				cout << "PDF_GLWADS_DKDpi_hh_2012::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);    
			}
	}
}  


void PDF_GLWADS_DKDpi_hh_2012::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
	TIterator* it = theory->createIterator();
}

