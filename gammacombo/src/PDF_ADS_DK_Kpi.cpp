/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#include "PDF_ADS_DK_Kpi.h"

	PDF_ADS_DK_Kpi::PDF_ADS_DK_Kpi(config cObs, config cErr, config cCor, config cTrad)
: PDF_Abs(3)
{
	name = "ads-dk-kpi";
	this->cTrad = cTrad;
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_ADS_DK_Kpi::~PDF_ADS_DK_Kpi(){}


void PDF_ADS_DK_Kpi::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("r_dk"))); 
	parameters->add(*(p.get("d_dk"))); 
	parameters->add(*(p.get("g")));
	parameters->add(*(p.get("rD_kpi"))); 
	parameters->add(*(p.get("dD_kpi")));
}  


void PDF_ADS_DK_Kpi::initRelations()
{
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	if ( cTrad == useTradObs )
	{
		theory->add(*(new RooFormulaVar("rads_dk_kpi_th", "Rads (DK K#pi)", "(r_dk^2 + rD_kpi^2 + 2*r_dk*rD_kpi*cos(d_dk+dD_kpi)*cos(g))"
						"/ (1 + r_dk^2*rD_kpi^2 + 2*r_dk*rD_kpi*cos(g)*cos(d_dk-dD_kpi))", *(RooArgSet*)parameters)));
		theory->add(*(new RooFormulaVar("aads_dk_kpi_th", "Aads (DK K#pi)", "2*r_dk*rD_kpi*sin(d_dk+dD_kpi)*sin(g)"
						"/ (r_dk^2 + rD_kpi^2 + 2*r_dk*rD_kpi*cos(d_dk+dD_kpi)*cos(g))", *(RooArgSet*)parameters)));
		theory->add(*(new RooFormulaVar("afav_dk_kpi_th", "Afav (DK K#pi ADS)", "2*r_dk*rD_kpi*sin(g)*sin(d_dk-dD_kpi)"
						"/ (1 + r_dk^2*rD_kpi^2 + 2*r_dk*rD_kpi*cos(g)*cos(d_dk-dD_kpi))", *(RooArgSet*)parameters)));
	}
	else
	{
		theory->add(*(new RooFormulaVar("rp_dk_kpi_th", "R+ (DK K#pi ADS)", "r_dk^2 + rD_kpi^2 + 2.*r_dk*rD_kpi*cos( g+d_dk+dD_kpi)", *(RooArgSet*)parameters)));
		theory->add(*(new RooFormulaVar("rm_dk_kpi_th", "R- (DK K#pi ADS)", "r_dk^2 + rD_kpi^2 + 2.*r_dk*rD_kpi*cos(-g+d_dk+dD_kpi)", *(RooArgSet*)parameters)));
		theory->add(*(new RooFormulaVar("afav_dk_kpi_th", "Afav (DK K#pi ADS)", "2*r_dk*rD_kpi*sin(g)*sin(d_dk-dD_kpi)"
						" / (1 + r_dk^2 * rD_kpi^2 + 2*r_dk*rD_kpi*cos(g)*cos(d_dk-dD_kpi))", *(RooArgSet*)parameters)));
	}
}


void PDF_ADS_DK_Kpi::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	if ( cTrad == useTradObs )
	{
		observables->add(*(new RooRealVar("rads_dk_kpi_obs", "R_{ADS} (DK, K#pi)", 1, -1e4, 1e4)));
		observables->add(*(new RooRealVar("aads_dk_kpi_obs", "A_{ADS} (DK, K#pi)", 1, -1e4, 1e4)));
		observables->add(*(new RooRealVar("afav_dk_kpi_obs", "A_{fav} (DK, K#pi)", 0, -1e4, 1e4)));
	}
	else
	{
		observables->add(*(new RooRealVar("rp_dk_kpi_obs",   "R+ (DK, K#pi)",   1, -1e4, 1e4)));
		observables->add(*(new RooRealVar("rm_dk_kpi_obs",   "R- (DK, K#pi)",   1, -1e4, 1e4)));
		observables->add(*(new RooRealVar("afav_dk_kpi_obs", "Afav (DK, K#pi)", 0, -1e4, 1e4)));
	}
}


void PDF_ADS_DK_Kpi::setObservables(config c)
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
				obsValSource = "1fb-1 LHCb-PAPER-2012-001";
				if ( cTrad == useTradObs )
				{
					setObservable("rads_dk_kpi_obs", 0.0152);
					setObservable("aads_dk_kpi_obs", -0.52);
					setObservable("afav_dk_kpi_obs", 0.0044);
				}
				else
				{
					setObservable("rp_dk_kpi_obs",0.0232);
					setObservable("rm_dk_kpi_obs",0.0073);
					setObservable("afav_dk_kpi_obs",0.0044);
				}
				break;
			}
		default:
			cout << "PDF_ADS_DK_Kpi::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_ADS_DK_Kpi::setUncertainties(config c)
{
	switch(c)
	{
		case lumi1fb:
			{
				obsErrSource = "1fb-1 LHCb-PAPER-2012-001";
				if ( cTrad == useTradObs )
				{
					float scale = 1.; ///< set this to ~20 for a 2d scan predicting R_ADS and A_ADS
					StatErr[0] = 0.0020/scale; // rads
					StatErr[1] = 0.15/scale;   // aads
					StatErr[2] = 0.0144;  // afav

					SystErr[0] = 0.0004/scale; // rads
					SystErr[1] = 0.02/scale;   // aads
					SystErr[2] = 0.0174;  // afav
				}
				else
				{
					StatErr[0] = 0.0034; // rp
					StatErr[1] = 0.0023; // rm
					StatErr[2] = 0.0144; // afav

					SystErr[0] = 0.0007; // rp
					SystErr[1] = 0.0004; // rm
					SystErr[2] = 0.0174; // afav
				}
				break;
			}
		case lumi1fbNoAfav:
			obsErrSource = "1fb-1 LHCb-PAPER-2012-001 with inflated error on Afav";
			StatErr[0] = 0.0034; // rp
			StatErr[1] = 0.0023; // rm
			StatErr[2] = 10.0; // afav

			SystErr[0] = 0.0007; // rp
			SystErr[1] = 0.0004; // rm
			SystErr[2] = 10.0; // afav
			break;

		default:
			cout << "PDF_ADS_DK_Kpi::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_ADS_DK_Kpi::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi1fb:
			corSource = "1fb-1 LHCb-PAPER-2012-001";
			break;

		default: 
			cout << "PDF_ADS_DK_Kpi::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);    
	}
}  


void PDF_ADS_DK_Kpi::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
