/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 * Combine all 13 observables from the GLW/ADS measurement.
 *
 **/

#include "PDF_GLWADS_Dpi_hh.h"

	PDF_GLWADS_Dpi_hh::PDF_GLWADS_Dpi_hh(config cObs, config cErr, config cCor, ParametersAbs* pars, TString d)
: PDF_GLWADS_DKDpi_hh(pars,d,5)
{
	name = "glwads-dpi-hh";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_GLWADS_Dpi_hh::~PDF_GLWADS_Dpi_hh(){}


void PDF_GLWADS_Dpi_hh::initParameters()
{
	parameters = new RooArgList("parameters");
	parameters->add(*(p->get("r_dpi")));
	parameters->add(*(p->get("d_dpi")));
	parameters->add(*(p->get("g")));
	parameters->add(*(p->get("rD_kpi")));
	parameters->add(*(p->get("dD_kpi")));
	parameters->add(*(p->get("AcpDKK")));
	parameters->add(*(p->get("AcpDpipi")));
}


void PDF_GLWADS_Dpi_hh::initRelations()
{
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	RooArgSet *p = (RooArgSet*)parameters;
	theory->add(*(new RooFormulaVar("afav_dpi_kpi_th",     "afav_dpi",     "2*r_dpi*rD_kpi*sin(g)*sin(d_dpi-dD_kpi) / (1 + r_dpi^2 * rD_kpi^2 + 2*r_dpi*rD_kpi*cos(g)*cos(d_dpi-dD_kpi))", *p)));
	theory->add(*(new RooFormulaVar("acp_dpi_kk_th",       "acp_dpi_kk",   "2*r_dpi*sin(d_dpi)*sin(g) / (1 + r_dpi^2 + 2*r_dpi*cos(d_dpi)*cos(g)) + AcpDKK", *p)));
	theory->add(*(new RooFormulaVar("acp_dpi_pipi_th",     "acp_dpi_pipi", "2*r_dpi*sin(d_dpi)*sin(g) / (1 + r_dpi^2 + 2*r_dpi*cos(d_dpi)*cos(g)) + AcpDpipi", *p)));
	theory->add(*(new RooFormulaVar("rp_dpi_kpi_th",       "rp_dpi",       "(r_dpi^2 + rD_kpi^2 + 2*r_dpi*rD_kpi*cos( g+d_dpi+dD_kpi)) / (1 + r_dpi^2*rD_kpi^2 + 2*r_dpi*rD_kpi*cos( g +d_dpi-dD_kpi))", *p)));
	theory->add(*(new RooFormulaVar("rm_dpi_kpi_th",       "rm_dpi",       "(r_dpi^2 + rD_kpi^2 + 2*r_dpi*rD_kpi*cos(-g+d_dpi+dD_kpi)) / (1 + r_dpi^2*rD_kpi^2 + 2*r_dpi*rD_kpi*cos(-g +d_dpi-dD_kpi))", *p)));
}


void PDF_GLWADS_Dpi_hh::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("afav_dpi_kpi_obs",     "Afav (D#pi K#pi)",   0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dpi_kk_obs",       "ACP (D#pi KK)",      0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dpi_pipi_obs",     "ACP (D#pi #pi#pi)",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rp_dpi_kpi_obs",       "R+ (D#pi K#pi)",     1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rm_dpi_kpi_obs",       "R- (D#pi K#pi)",     1, -1e4, 1e4)));
}


void PDF_GLWADS_Dpi_hh::setUncertainties(config c)
{
	switch(c)
	{
		case lumi1fb:
			{
				obsErrSource = "1fb-1 LHCb-PAPER-2012-001, ExpNll/winter2012ADSGLWResult.root";
				TString File = this->dir+"/ExpNll/winter2012ADSGLWResult.root";
				if ( !FileExists(File) ){cout << "PDF_GLWADS_Dpi_hh::setUncertainties : ERROR : File not found : " << File << endl; exit(1);}
				TFile *fr = TFile::Open(File);
				RooFitResult *r = (RooFitResult*)fr->Get("fitresult_model_reducedData_binned"); assert(r);
				for ( int i=0; i<nObs; i++ )
				{
					RooRealVar* pObs = (RooRealVar*)((RooArgList*)observables)->at(i);
					RooRealVar* pRes = (RooRealVar*)r->floatParsFinal().find(obsTmkToMalcolm(pObs->GetName())); assert(pRes);
					StatErr[i] = pRes->getError();
				}
				SystErr[ 0] = 0.0095;  // afav_dpi_obs
				SystErr[ 1] = 0.012;   // acp_dpi_kk_obs
				SystErr[ 2] = 0.010;   // acp_dpi_pipi_obs
				SystErr[ 3] = 0.00007; // rp_dpi_obs
				SystErr[ 4] = 0.00008; // rm_dpi_obs
				fr->Close();
				delete r;
				delete fr;
				break;
			}
		default: {
					 cout << "PDF_GLWADS_Dpi_hh::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					 exit(1);
				 }
	}
}
