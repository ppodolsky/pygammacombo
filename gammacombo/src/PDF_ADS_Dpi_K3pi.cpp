/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 * \todo adapt to trash bin system, use RooArgList instead of RooArgSet
 *
 **/

#include "PDF_ADS_Dpi_K3pi.h"

	PDF_ADS_Dpi_K3pi::PDF_ADS_Dpi_K3pi(config cObs, config cErr, config cCor)
: PDF_Abs(3)
{
	name = "ads-dpi-k3pi";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_ADS_Dpi_K3pi::~PDF_ADS_Dpi_K3pi(){}


void PDF_ADS_Dpi_K3pi::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("r_dpi"))); 
	parameters->add(*(p.get("d_dpi"))); 
	parameters->add(*(p.get("g")));
	parameters->add(*(p.get("rD_k3pi"))); 
	parameters->add(*(p.get("dD_k3pi"))); 
	parameters->add(*(p.get("kD_k3pi")));
}  


void PDF_ADS_Dpi_K3pi::initRelations()
{
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	theory->add(*(new RooFormulaVar("rp_dpi_k3pi_th", "rp_dpi_k3pi_th", "r_dpi^2 + rD_k3pi^2 + 2*r_dpi*rD_k3pi*kD_k3pi*cos( g+d_dpi+dD_k3pi)", *(RooArgSet*)parameters)));
	theory->add(*(new RooFormulaVar("rm_dpi_k3pi_th", "rm_dpi_k3pi_th", "r_dpi^2 + rD_k3pi^2 + 2*r_dpi*rD_k3pi*kD_k3pi*cos(-g+d_dpi+dD_k3pi)", *(RooArgSet*)parameters)));
	theory->add(*(new RooFormulaVar("afav_dpi_k3pi_th", "afav_dpi_k3pi_th", "2*r_dpi*rD_k3pi*kD_k3pi*sin(g)*sin(d_dpi-dD_k3pi)"
					" / (1 + r_dpi^2 * rD_k3pi^2 + 2*r_dpi*rD_k3pi*kD_k3pi*cos(g)*cos(d_dpi-dD_k3pi))", *(RooArgSet*)parameters)));
}


void PDF_ADS_Dpi_K3pi::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("rp_dpi_k3pi_obs", "R+ (D#pi K3pi ADS)",  1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rm_dpi_k3pi_obs", "R- (D#pi K3pi ADS)",  1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("afav_dpi_k3pi_obs", "Afav (D#pi K3#pi)",  1, -1e4, 1e4)));
}


void PDF_ADS_Dpi_K3pi::setObservables(config c)
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
		case lumi1fb:
			obsValSource = "1fb-1 CONF";
			setObservable("rp_dpi_k3pi_obs",0.00320665);
			setObservable("rm_dpi_k3pi_obs",0.00417074);
			setObservable("afav_dpi_k3pi_obs",-0.00626648);
			break;

		default:
			cout << "PDF_ADS_Dpi_K3pi::setObservables() : ERROR : config not found." << endl;
			exit(1);
	}
}


void PDF_ADS_Dpi_K3pi::setUncertainties(config c)
{
	switch(c)
	{
		case lumi1fb:
			{
				obsErrSource = "1fb-1 roofitresult";
				StatErr[0] = 0.000462689; // rp
				StatErr[1] = 0.00051738;  // rm
				StatErr[2] = 0.00500122;  // afav

				SystErr[0] = 0.00011; // rp
				SystErr[1] = 0.00011; // rm
				SystErr[2] = 0.010;   // afav
				break;
			}
		default:
			cout << "PDF_ADS_Dpi_K3pi::setUncertainties() : ERROR : config cErr not found." << endl;
			exit(1);
	}
}


void PDF_ADS_Dpi_K3pi::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi1fb:
			// no correlations
			break;

		default: 
			cout << "PDF_ADS_Dpi_K3pi::setCorrelations() : ERROR : config cCor not found." << endl;
			exit(1);    
	}
}  


void PDF_ADS_Dpi_K3pi::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
