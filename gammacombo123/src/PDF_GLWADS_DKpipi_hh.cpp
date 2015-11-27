/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Jul 2014
 *
 *
 **/

#include "PDF_GLWADS_DKpipi_hh.h"

	PDF_GLWADS_DKpipi_hh::PDF_GLWADS_DKpipi_hh(config cObs, config cErr, config cCor)
: PDF_Abs(6), indicesDKDpi({0,1,3,4,7,8})
{
	p = new ParametersGammaCombo();
	name = "GLWADS-DKpipi-hh";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_GLWADS_DKpipi_hh::~PDF_GLWADS_DKpipi_hh(){}


void PDF_GLWADS_DKpipi_hh::initParameters()
{
	parameters = new RooArgList("parameters");
	parameters->add(*(p->get("r_dkpipi")));
	parameters->add(*(p->get("d_dkpipi")));
	parameters->add(*(p->get("k_dkpipi")));
	parameters->add(*(p->get("g")));
	parameters->add(*(p->get("rD_kpi")));
	parameters->add(*(p->get("dD_kpi")));
	parameters->add(*(p->get("AcpDKK")));
	parameters->add(*(p->get("AcpDpipi")));
}


void PDF_GLWADS_DKpipi_hh::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	theory->add(*(new RooFormulaVar("rcp_dkpipi_th",       "rcp_dkpipi_th",       "1 + r_dkpipi^2 + 2*k_dkpipi*r_dkpipi*cos(d_dkpipi)*cos(g)", *p)));
	theory->add(*(new RooFormulaVar("afav_dkpipi_kpi_th",  "afav_dkpipi_kpi_th",  "2*k_dkpipi *r_dkpipi *rD_kpi*sin(g)*sin(d_dkpipi -dD_kpi) / (1 + r_dkpipi^2  * rD_kpi^2 + 2*k_dkpipi *r_dkpipi *rD_kpi*cos(g)*cos(d_dkpipi -dD_kpi))", *p)));
	theory->add(*(new RooFormulaVar("acp_dkpipi_kk_th",    "acp_dkpipi_kk_th",    "2*k_dkpipi *r_dkpipi *sin(d_dkpipi) *sin(g) / (1 + r_dkpipi^2  + 2*k_dkpipi *r_dkpipi *cos(d_dkpipi) *cos(g)) + AcpDKK", *p)));
	theory->add(*(new RooFormulaVar("acp_dkpipi_pipi_th",  "acp_dkpipi_pipi_th",  "2*k_dkpipi *r_dkpipi *sin(d_dkpipi) *sin(g) / (1 + r_dkpipi^2  + 2*k_dkpipi *r_dkpipi *cos(d_dkpipi) *cos(g)) + AcpDpipi", *p)));
	theory->add(*(new RooFormulaVar("rp_dkpipi_th",        "rp_dkpipi_th",        "(r_dkpipi^2  + rD_kpi^2 + 2*k_dkpipi *r_dkpipi *rD_kpi*cos( g+d_dkpipi +dD_kpi)) / (1 + r_dkpipi^2 *rD_kpi^2 + 2*k_dkpipi *r_dkpipi *rD_kpi*cos( g +d_dkpipi -dD_kpi))", *p)));
	theory->add(*(new RooFormulaVar("rm_dkpipi_th",        "rm_dkpipi_th",        "(r_dkpipi^2  + rD_kpi^2 + 2*k_dkpipi *r_dkpipi *rD_kpi*cos(-g+d_dkpipi +dD_kpi)) / (1 + r_dkpipi^2 *rD_kpi^2 + 2*k_dkpipi *r_dkpipi *rD_kpi*cos(-g +d_dkpipi -dD_kpi))", *p)));
}


void PDF_GLWADS_DKpipi_hh::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("rcp_dkpipi_obs",       "R_{CP+} (Dh#pi#pi)",           1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("afav_dkpipi_kpi_obs",  "Afav (DK#pi#pi, K#pi)",        0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dkpipi_kk_obs",    "ACP (DK#pi#pi, KK)",           0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dkpipi_pipi_obs",  "ACP (DK#pi#pi, #pi#pi)",       0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rp_dkpipi_obs",        "R+ (DK#pi#pi, K#pi)",          1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rm_dkpipi_obs",        "R- (DK#pi#pi, K#pi)",          1, -1e4, 1e4)));
}


void PDF_GLWADS_DKpipi_hh::setObservables(config c)
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
						 // copy the central values over from the Dhpipi class
						 PDF_GLWADS_Dhpipi_hh* dkdpi = new PDF_GLWADS_Dhpipi_hh(lumi3fb,lumi3fb,lumi3fb);
						 obsValSource = dkdpi->getObservableSourceString();
						 TIterator* it = observables->createIterator();
						 while ( RooRealVar* p = (RooRealVar*)it->Next() ){
							 TString obsName = p->GetName();
							 setObservable(obsName,  dkdpi->getObservableValue(obsName));
						 }
						 delete it;
						 delete dkdpi;
						 break;
					 }
		default:{
					cout << "PDF_GLWADS_DKpipi_hh::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_GLWADS_DKpipi_hh::setUncertainties(config c)
{
	switch(c)
	{
		case lumi3fb:{
						 // copy the errors over from the Dhpipi class
						 PDF_GLWADS_Dhpipi_hh* dkdpi = new PDF_GLWADS_Dhpipi_hh(lumi3fb,lumi3fb,lumi3fb);
						 obsErrSource = dkdpi->getErrorSourceString();
						 for ( int i=0; i<nObs; i++ ){
							 StatErr[i] = dkdpi->StatErr[indicesDKDpi[i]];
							 SystErr[i] = dkdpi->SystErr[indicesDKDpi[i]];
						 }
						 delete dkdpi;
						 break;
					 }
		default:{
					cout << "PDF_GLWADS_DKpipi_hh::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_GLWADS_DKpipi_hh::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi3fb:{
						 PDF_GLWADS_Dhpipi_hh* dkdpi = new PDF_GLWADS_Dhpipi_hh(lumi3fb,lumi3fb,lumi3fb);
						 corSource = dkdpi->getCorrelationSourceString();
						 dkdpi->getSubCorrelationStat(corStatMatrix, indicesDKDpi);
						 dkdpi->getSubCorrelationSyst(corSystMatrix, indicesDKDpi);
						 delete dkdpi;
						 break;
					 }
		default:{
					cout << "PDF_GLWADS_DKpipi_hh::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_GLWADS_DKpipi_hh::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}

