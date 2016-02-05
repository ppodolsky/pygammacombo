/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#include "PDF_D_CleoNoK2pi.h"

	PDF_D_CleoNoK2pi::PDF_D_CleoNoK2pi(config cObs, config cType, ParametersAbs* pars, config cUseKdDdK3pi, TString d)
: PDF_D_Cleo(cObs, cType, cUseKdDdK3pi, d, 9) 
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	name = "dcleo-nok2pi";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cleo);
	setCorrelations(cleo);
	buildCov();
	buildPdf();
}


PDF_D_CleoNoK2pi::~PDF_D_CleoNoK2pi(){}


void PDF_D_CleoNoK2pi::initParameters()
{
	parameters = new RooArgList("parameters");
	parameters->add(*(p->get("rD_k3pi")));
	parameters->add(*(p->get("kD_k3pi")));
	parameters->add(*(p->get("dD_k3pi")));
	parameters->add(*(p->get("xD")     ));
	parameters->add(*(p->get("yD")     ));
	parameters->add(*(p->get("rD_kpi") ));
	parameters->add(*(p->get("dD_kpi") ));
	parameters->add(*(p->get("B1")     ));
	parameters->add(*(p->get("B3")     ));
}  


void PDF_D_CleoNoK2pi::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	theory->add(*(new RooFormulaVar("kD_k3pi_th", "kD_k3pi_th", "kD_k3pi", *p)));
	theory->add(*(new RooFormulaVar("dD_k3pi_th", "dD_k3pi_th", "dD_k3pi", *p)));
	theory->add(*(new RooFormulaVar("xD_th", "xD_th", "xD", *p)));
	theory->add(*(new RooFormulaVar("yD_th", "yD_th", "yD", *p)));
	theory->add(*(new RooFormulaVar("dD_kpi_th", "dD_kpi_th", "dD_kpi", *p)));
	theory->add(*(new RooFormulaVar("B1_th", "B1_th", "B1", *p)));
	theory->add(*(new RooFormulaVar("B2_th", "B2_th", "B1*rD_kpi^2 *(1-(yD/rD_kpi)         *cos(dD_kpi) +(xD/rD_kpi)         *sin(dD_kpi) +(yD^2+xD^2)/(2*rD_kpi^2))",  *p)));
	theory->add(*(new RooFormulaVar("B3_th", "B3_th", "B3", *p)));
	theory->add(*(new RooFormulaVar("B4_th", "B4_th", "B3*rD_k3pi^2*(1-(yD/rD_k3pi)*kD_k3pi*cos(dD_k3pi)+(xD/rD_k3pi)*kD_k3pi*sin(dD_k3pi)+(yD^2+xD^2)/(2*rD_k3pi^2))", *p)));
}


void PDF_D_CleoNoK2pi::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("kD_k3pi_obs", "kD (D#rightarrowK3#pi, Cleo)",      0, -2, 2)));                    // reduced range else toy generation ...
	observables->add(*(new RooRealVar("dD_k3pi_obs", "#deltaD (D#rightarrowK3#pi, Cleo)", 0, 0, 2*TMath::Pi(), "Rad")));  // produces lots of events very far away
	observables->add(*(new RooRealVar("xD_obs",      "xD (Cleo)",                         0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("yD_obs",      "yD (Cleo)",                         0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("dD_kpi_obs",  "#deltaD (D#rightarrowK#pi, Cleo)",  0, -1e4, 1e4, "Rad")));
	observables->add(*(new RooRealVar("B1_obs",      "B1 (Cleo)",                   0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("B2_obs",      "B2 (Cleo)",                   0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("B3_obs",      "B3 (Cleo)",                   0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("B4_obs",      "B4 (Cleo)",                   0, -1e4, 1e4)));
}


void PDF_D_CleoNoK2pi::setObservables(config c)
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
		case cleo:{
					  obsValSource = "Cleo 2009 ARXIV:0903.4853";
					  setObservable("kD_k3pi_obs",0.33);
					  setObservable("dD_k3pi_obs",DegToRad(114.0));
					  setObservable("xD_obs",     0.96 /100.);
					  setObservable("yD_obs",     0.81 /100.);
					  setObservable("dD_kpi_obs", DegToRad(-151.5+360.));
					  setObservable("B1_obs",     3.89e-2);
					  setObservable("B2_obs",     1.47e-4);
					  setObservable("B3_obs",     7.96e-2);
					  setObservable("B4_obs",     2.65e-4);
					  break;
				  }
		default:{
					cout << "PDF_D_CleoNoK2pi::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_D_CleoNoK2pi::setUncertainties(config c)
{
	switch(c)
	{
		case cleo:{
					  obsErrSource = "Cleo 2009 ARXIV:0903.4853";
					  StatErr[ 0] = 0.25;          // kD_k3pi_obs
					  StatErr[ 1] = DegToRad(25);  // dD_k3pi_obs
					  StatErr[ 2] = 0.25e-2;       // xD_obs     
					  StatErr[ 3] = 0.16e-2;       // yD_obs     
					  StatErr[ 4] = DegToRad(9.6); // dD_kpi_obs 
					  StatErr[ 5] = 0.05e-2;       // B1_obs     
					  StatErr[ 6] = 0.07e-4;       // B2_obs     
					  StatErr[ 7] = 0.19e-2;       // B3_obs     
					  StatErr[ 8] = 0.19e-4;       // B4_obs
					  // exlude kD, dD, to make the LHCb only Ghana plot
					  if ( cUseKdDdK3pi==excludeKdDdK3pi ){
						  cout << "PDF_D_CleoNoK2pi::setUncertainties() : WARNING : Excluding kD_k3pi and dD_k3pi!" << endl;
						  StatErr[ 0] *= 50; // kD_k3pi_obs
						  StatErr[ 1] *= 50; // dD_k3pi_obs
					  }
					  break;
				  }
		default:{
					cout << "PDF_D_CleoNoK2pi::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_D_CleoNoK2pi::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case cleo:
			{
				corSource = "Cleo 2009 ARXIV:0903.4853";

				corStatMatrix[0][ 1] = -0.067;
				corStatMatrix[0][ 2] = -0.082;
				corStatMatrix[0][ 3] = -0.020;
				corStatMatrix[0][ 4] = -0.014;
				corStatMatrix[0][ 5] = 0.002 ;
				corStatMatrix[0][ 6] = 0.008 ;
				corStatMatrix[0][ 7] = 0.071 ;
				corStatMatrix[0][ 8] = 0.325 ;

				corStatMatrix[1][ 2] = -0.008;
				corStatMatrix[1][ 3] = 0.140 ;
				corStatMatrix[1][ 4] = 0.188 ;
				corStatMatrix[1][ 5] = -0.023;
				corStatMatrix[1][ 6] = 0.096 ;
				corStatMatrix[1][ 7] = 0.244 ;
				corStatMatrix[1][ 8] = -0.031;

				corStatMatrix[2][ 3] = -0.189;
				corStatMatrix[2][ 4] = -0.188;
				corStatMatrix[2][ 5] = -0.001;
				corStatMatrix[2][ 6] = 0.005 ;
				corStatMatrix[2][ 7] = -0.037;
				corStatMatrix[2][ 8] = 0.001 ;

				corStatMatrix[3][ 4] = 0.945 ;
				corStatMatrix[3][ 5] = 0.004 ;
				corStatMatrix[3][ 6] = -0.015;
				corStatMatrix[3][ 7] = 0.107 ;
				corStatMatrix[3][ 8] = -0.014;

				corStatMatrix[4][ 5] = 0.005 ;
				corStatMatrix[4][ 6] = -0.004;
				corStatMatrix[4][ 7] = 0.121 ;
				corStatMatrix[4][ 8] = -0.002;

				corStatMatrix[5][ 6] = 0.006 ;
				corStatMatrix[5][ 7] = -0.005;
				corStatMatrix[5][ 8] = 0.008 ;

				corStatMatrix[6][ 7] = 0.005 ;
				corStatMatrix[6][ 8] = -0.028;

				corStatMatrix[7][ 8] = 0.104 ;

				break;
			}

		default: 
			cout << "PDF_D_CleoNoK2pi::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);    
	}
}  
