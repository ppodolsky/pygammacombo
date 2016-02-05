/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#include "PDF_ADS_Dpi_Kpi.h"

	PDF_ADS_Dpi_Kpi::PDF_ADS_Dpi_Kpi(config cObs, config cErr, config cCor)
: PDF_Abs(3)
{
	name = "ads-dpi-kpi";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_ADS_Dpi_Kpi::~PDF_ADS_Dpi_Kpi(){}


void PDF_ADS_Dpi_Kpi::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("r_dpi"))); 
	parameters->add(*(p.get("d_dpi"))); 
	parameters->add(*(p.get("g")));
	parameters->add(*(p.get("rD_kpi"))); 
	parameters->add(*(p.get("dD_kpi")));
}


void PDF_ADS_Dpi_Kpi::initRelations()
{
	theory = new RooArgList("theory");
	theory->add(*(new RooFormulaVar("rp_dpi_kpi_th", "R+ Dpi", "r_dpi^2 + rD_kpi^2 + 2.*r_dpi*rD_kpi*cos( g+d_dpi+dD_kpi)", *(RooArgSet*)parameters)));
	theory->add(*(new RooFormulaVar("rm_dpi_kpi_th", "R- Dpi", "r_dpi^2 + rD_kpi^2 + 2.*r_dpi*rD_kpi*cos(-g+d_dpi+dD_kpi)", *(RooArgSet*)parameters)));
	theory->add(*(new RooFormulaVar("afav_dpi_kpi_th", "Afav Dpi", "2*r_dpi*rD_kpi*sin(g)*sin(d_dpi-dD_kpi)"
					" / (1 + r_dpi^2 * rD_kpi^2 + 2.*r_dpi*rD_kpi*cos(g)*cos(d_dpi-dD_kpi))", *(RooArgSet*)parameters)));
}


void PDF_ADS_Dpi_Kpi::initObservables()
{
	observables = new RooArgList("observables");
	observables->add(*(new RooRealVar("rp_dpi_kpi_obs", "R+ (D#pi K#pi ADS)",  1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rm_dpi_kpi_obs", "R- (D#pi K#pi ADS)",  1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("afav_dpi_kpi_obs", "Afav (D#pi K#pi ADS)", 0, -1e4, 1e4)));
}


void PDF_ADS_Dpi_Kpi::setObservables(config c)
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
			obsValSource = "1fb-1 paper LHCb-PAPER-2012-001";
			setObservable("rp_dpi_kpi_obs",0.00352);
			setObservable("rm_dpi_kpi_obs",0.00469);
			setObservable("afav_dpi_kpi_obs",-0.0001);
			break;

		default:
			cout << "PDF_ADS_Dpi_Kpi::setObservables() : ERROR : config not found." << endl;
			exit(1);
	}
}


void PDF_ADS_Dpi_Kpi::setUncertainties(config c)
{
	switch(c)
	{
		case lumi1fb:
			obsErrSource = "1fb-1 paper LHCb-PAPER-2012-001";
			StatErr[0] = 0.00033 ; // rp
			StatErr[1] = 0.00038; // rm
			StatErr[2] = 0.0036; // afav

			SystErr[0] = 0.00007; // rp
			SystErr[1] = 0.00008; // rm
			SystErr[2] = 0.0095; // afav
			break;

		default:
			cout << "PDF_ADS_Dpi_Kpi::setUncertainties() : ERROR : config cErr not found." << endl;
			exit(1);
	}
}


void PDF_ADS_Dpi_Kpi::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi1fb:
			corSource = "1fb-1 paper LHCb-PAPER-2012-001 (none)";
			break;

		default: 
			cout << "PDF_ADS_Dpi_Kpi::setCorrelations() : ERROR : config cCor not found." << endl;
			exit(1);    
	}
}  


void PDF_ADS_Dpi_Kpi::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
