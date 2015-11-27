/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Jan 2015
 *
 * Combine all 7 DK observables from the 3fb-1 hhpi0 GLW/ADS measurement.
 *
 **/

#include "PDF_GLWADS_DK_hhpi0.h"

	PDF_GLWADS_DK_hhpi0::PDF_GLWADS_DK_hhpi0(config cObs, config cErr, config cCor, ParametersAbs* pars)
: PDF_Abs(7), indicesDKDpi({0,2,3,6,7,9,10})
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
	name = "GLWADS_DK_hhpi0_2012";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}

	PDF_GLWADS_DK_hhpi0::PDF_GLWADS_DK_hhpi0(ParametersAbs* pars, int nObs)
: PDF_Abs(nObs)
{
	if ( pars ) p = pars;
	else p = new ParametersGammaCombo();
}


PDF_GLWADS_DK_hhpi0::~PDF_GLWADS_DK_hhpi0(){}


void PDF_GLWADS_DK_hhpi0::initParameters()
{
	parameters = new RooArgList("parameters");
	parameters->add(*(p->get("r_dk")));
	parameters->add(*(p->get("d_dk")));
	parameters->add(*(p->get("g")));
	parameters->add(*(p->get("rD_kpipi0")));
	parameters->add(*(p->get("dD_kpipi0")));
	parameters->add(*(p->get("kD_kpipi0")));
	parameters->add(*(p->get("F_pipipi0")));
	parameters->add(*(p->get("F_kkpi0")));
}


void PDF_GLWADS_DK_hhpi0::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	theory->add(*(new RooFormulaVar("aads_dk_kpipi0_th",   "aads_dk_kpipi0_th",  "(2*r_dk *kD_kpipi0*rD_kpipi0*sin(d_dk +dD_kpipi0)*sin(g))/(r_dk^2  + rD_kpipi0^2 + 2*r_dk *kD_kpipi0*rD_kpipi0*cos(d_dk +dD_kpipi0)*cos(g))", *p)));
	theory->add(*(new RooFormulaVar("acp_dk_kkpi0_th",     "acp_dk_kkpi0_th",    "2*r_dk *(2*F_kkpi0-1)  *sin(d_dk) *sin(g) / (1 + r_dk^2  + 2*r_dk *(2*F_kkpi0-1)  *cos(d_dk) *cos(g))", *p)));
	theory->add(*(new RooFormulaVar("acp_dk_pipipi0_th",   "acp_dk_pipipi0_th",  "2*r_dk *(2*F_pipipi0-1)*sin(d_dk) *sin(g) / (1 + r_dk^2  + 2*r_dk *(2*F_pipipi0-1)*cos(d_dk) *cos(g))", *p)));
	theory->add(*(new RooFormulaVar("afav_dk_kpipi0_th",   "afav_dk_kpipi0_th",  "2*r_dk *rD_kpipi0*kD_kpipi0*sin(g)*sin(d_dk -dD_kpipi0) / (1 + r_dk^2  * rD_kpipi0^2 + 2*r_dk *rD_kpipi0*kD_kpipi0*cos(g)*cos(d_dk -dD_kpipi0))", *p)));
	theory->add(*(new RooFormulaVar("rads_dk_kpipi0_th",   "rads_dk_kpipi0_th",  "(r_dk^2  + rD_kpipi0^2 + 2*r_dk *kD_kpipi0*rD_kpipi0*cos(d_dk +dD_kpipi0)*cos(g))/(1 + r_dk^2 *rD_kpipi0^2 + 2*r_dk *kD_kpipi0*rD_kpipi0*cos(d_dk -dD_kpipi0)*cos(g))", *p)));
	theory->add(*(new RooFormulaVar("rcp_kkpi0_th",        "rcp_kkpi0_th",       "(1 + r_dk^2 + 2*r_dk*(2*F_kkpi0-1)  *cos(g)*cos(d_dk))", *p)));
	theory->add(*(new RooFormulaVar("rcp_pipipi0_th",      "rcp_pipipi0_th",     "(1 + r_dk^2 + 2*r_dk*(2*F_pipipi0-1)*cos(g)*cos(d_dk))", *p)));
}


void PDF_GLWADS_DK_hhpi0::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("aads_dk_kpipi0_obs",  "aads_dk_kpipi0",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dk_kkpi0_obs",    "acp_dk_kkpi0",    0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acp_dk_pipipi0_obs",  "acp_dk_pipipi0",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("afav_dk_kpipi0_obs",  "afav_dk_kpipi0",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rads_dk_kpipi0_obs",  "rads_dk_kpipi0",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rcp_kkpi0_obs",       "rcp_kkpi0",       0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rcp_pipipi0_obs",     "rcp_pipipi0",     0, -1e4, 1e4)));
}


void PDF_GLWADS_DK_hhpi0::setObservables(config c)
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
					 // copy the central values over from the DKDpi class
					 PDF_GLWADS_DKDpi_hhpi0* dkdpi = new PDF_GLWADS_DKDpi_hhpi0(lumi3fb,lumi3fb,lumi3fb);
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
				cout << "PDF_GLWADS_DK_hhpi0::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}
	}
}


void PDF_GLWADS_DK_hhpi0::setUncertainties(config c)
{
	switch(c){
		case lumi3fb:{
					 // copy the errors over from the DKDpi class
					 PDF_GLWADS_DKDpi_hhpi0* dkdpi = new PDF_GLWADS_DKDpi_hhpi0(lumi3fb,lumi3fb,lumi3fb);
				     obsErrSource = dkdpi->getErrorSourceString();
					 for ( int i=0; i<nObs; i++ ){
						 StatErr[i] = dkdpi->StatErr[indicesDKDpi[i]];
						 SystErr[i] = dkdpi->SystErr[indicesDKDpi[i]];
					 }
					 delete dkdpi;
				     break;
			     }
		default:{
				cout << "PDF_GLWADS_DK_hhpi0::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}
	}
}


void PDF_GLWADS_DK_hhpi0::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lumi3fb:{
						 PDF_GLWADS_DKDpi_hhpi0* dkdpi = new PDF_GLWADS_DKDpi_hhpi0(lumi3fb,lumi3fb,lumi3fb);
						 corSource = dkdpi->getCorrelationSourceString();
						 dkdpi->getSubCorrelationStat(corStatMatrix, indicesDKDpi);
						 dkdpi->getSubCorrelationSyst(corSystMatrix, indicesDKDpi);
						 delete dkdpi;
						 break;
		}
		case zero:{
					  break;
				  }
		default:{
				cout << "PDF_GLWADS_DK_hhpi0::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
				exit(1);
			}
	}
}


void PDF_GLWADS_DK_hhpi0::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}

