/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#include "PDF_ADS_DK_K3pi.h"

	PDF_ADS_DK_K3pi::PDF_ADS_DK_K3pi(config cObs, config cErr, config cCor, config cTrad)
: PDF_Abs(3)
{
	name = "ads-dk-k3pi";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_ADS_DK_K3pi::~PDF_ADS_DK_K3pi(){}


void PDF_ADS_DK_K3pi::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("r_dk"))); 
	parameters->add(*(p.get("d_dk"))); 
	parameters->add(*(p.get("g")));
	parameters->add(*(p.get("rD_k3pi"))); 
	parameters->add(*(p.get("dD_k3pi"))); 
	parameters->add(*(p.get("kD_k3pi")));
}  


void PDF_ADS_DK_K3pi::initRelations()
{
	theory = new RooArgList("theory");
	if ( cTrad == useTradObs )
	{
		theory->add(*(new RooFormulaVar("rads_dk_k3pi_th", "Rads (DK K3#pi)", 
						"(r_dk^2 + rD_k3pi^2 + 2*r_dk*rD_k3pi*kD_k3pi*cos(d_dk+dD_k3pi)*cos(g))"
						"/ (1 + r_dk^2*rD_k3pi^2 + 2*r_dk*rD_k3pi*kD_k3pi*cos(g)*cos(d_dk-dD_k3pi))", *(RooArgSet*)parameters)));
		theory->add(*(new RooFormulaVar("aads_dk_k3pi_th", "Aads (DK K3#pi)", 
						"2*r_dk*rD_k3pi*kD_k3pi*sin(d_dk+dD_k3pi)*sin(g)"
						"/ (r_dk^2 + rD_k3pi^2 + 2*r_dk*rD_k3pi*kD_k3pi*cos(d_dk+dD_k3pi)*cos(g))", *(RooArgSet*)parameters)));
		theory->add(*(new RooFormulaVar("afav_dk_k3pi_th", "Afav (DK K3#pi ADS)", 
						"2*r_dk*rD_k3pi*kD_k3pi*sin(g)*sin(d_dk-dD_k3pi)"
						"/ (1 + r_dk^2*rD_k3pi^2 + 2*r_dk*rD_k3pi*kD_k3pi*cos(g)*cos(d_dk-dD_k3pi))", *(RooArgSet*)parameters)));
	}
	else
	{
		theory->add(*(new RooFormulaVar("rp_dk_k3pi_th", "R+ (DK K3pi)", "r_dk^2 + rD_k3pi^2 + 2.*r_dk*rD_k3pi*kD_k3pi*cos( g+d_dk+dD_k3pi)", *(RooArgSet*)parameters)));
		theory->add(*(new RooFormulaVar("rm_dk_k3pi_th", "R- (DK K3pi)", "r_dk^2 + rD_k3pi^2 + 2.*r_dk*rD_k3pi*kD_k3pi*cos(-g+d_dk+dD_k3pi)", *(RooArgSet*)parameters)));
		theory->add(*(new RooFormulaVar("afav_dk_k3pi_th", "Afav (DK K3pi)", "2*r_dk*rD_k3pi*kD_k3pi*sin(g)*sin(d_dk-dD_k3pi)"
						" / (1 + r_dk^2 * rD_k3pi^2 + 2*r_dk*rD_k3pi*kD_k3pi*cos(g)*cos(d_dk-dD_k3pi))", *(RooArgSet*)parameters)));
	}
}


void PDF_ADS_DK_K3pi::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	if ( cTrad == useTradObs )
	{
		observables->add(*(new RooRealVar("rads_dk_k3pi_obs", "Rads (DK K3#pi)",  1, -1e4, 1e4)));
		observables->add(*(new RooRealVar("aads_dk_k3pi_obs", "Aads (DK K3#pi)",  1, -1e4, 1e4)));
		observables->add(*(new RooRealVar("afav_dk_k3pi_obs", "Afav (DK K3#pi)",  0, -1e4, 1e4)));
	}
	else
	{
		observables->add(*(new RooRealVar("rp_dk_k3pi_obs",   "R+ (DK K3#pi)",   1, -1e4, 1e4)));
		observables->add(*(new RooRealVar("rm_dk_k3pi_obs",   "R- (DK K3#pi)",   1, -1e4, 1e4)));
		observables->add(*(new RooRealVar("afav_dk_k3pi_obs", "Afav (DK K3#pi)", 0, -1e4, 1e4)));
	}
}


void PDF_ADS_DK_K3pi::setObservables(config c)
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
			{
				obsValSource = "1fb-1 LHCb-ANA-2012-069-v3";
				if ( cTrad == useTradObs )
				{
					setObservable("rads_dk_k3pi_obs", 0.0124);
					setObservable("aads_dk_k3pi_obs", -0.417);
					setObservable("afav_dk_k3pi_obs", -0.029);
				}
				else
				{
					setObservable("rp_dk_k3pi_obs", 0.0175426);
					setObservable("rm_dk_k3pi_obs", 0.00718564);
					setObservable("afav_dk_k3pi_obs", -0.029);
				}
				break;
			}
		default:
			cout << "PDF_ADS_DK_K3pi::setObservables() : ERROR : config not found." << endl;
			exit(1);
	}
}


void PDF_ADS_DK_K3pi::setUncertainties(config c)
{
	switch(c)
	{
		case lumi1fb:
			{
				obsErrSource = "1fb-1 LHCb-ANA-2012-069-v3";
				if ( cTrad == useTradObs )
				{
					StatErr[0] = 0.027; // rads
					StatErr[1] = 0.222; // aads
					StatErr[2] = 0.020; // afav

					SystErr[0] = 0.0;   // rads (contained in stat)
					SystErr[1] = 0.0;   // aads (contained in stat)
					SystErr[2] = 0.018; // afav
				}
				else
				{
					StatErr[0] = 0.004114;   // rp
					StatErr[1] = 0.00339094; // rm
					StatErr[2] = 0.0200754;  // afav

					SystErr[0] = 0.0010; // rp
					SystErr[1] = 0.0008; // rm
					SystErr[2] = 0.018;  // afav
				}
				break;
			}
		default: 
			cout << "PDF_ADS_DK_K3pi::setUncertainties() : ERROR : config cErr not found." << endl;
			exit(1);
	}
}


void PDF_ADS_DK_K3pi::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi1fb:
			corSource = "1fb-1 LHCb-ANA-2012-069-v3";
			break;

		default: 
			cout << "PDF_ADS_DK_K3pi::setCorrelations() : ERROR : config cErr not found." << endl;
			exit(1);    
	}
}  


void PDF_ADS_DK_K3pi::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
