/**
 * Gamma Combination
 * Author: Matthew Kenzie (matthew.kenzie@cern.ch)
 * Date: June 2015
 *
 **/

#include "PDF_GLW_DKstz_2var.h"
#include "RooGLWAcpVar.h"
#include "RooGLWRcpVar.h"

	PDF_GLW_DKstz_2var::PDF_GLW_DKstz_2var(config cObs, config cErr, config cCor)
: PDF_Abs(2)
{
	name = "glw_dkstz_2var";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_GLW_DKstz_2var::~PDF_GLW_DKstz_2var(){}


void PDF_GLW_DKstz_2var::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("r_dkstz")));
	parameters->add(*(p.get("d_dkstz")));
  parameters->add(*(p.get("k_dkstz")));
	parameters->add(*(p.get("g")));
}


void PDF_GLW_DKstz_2var::initRelations()
{
  RooArgSet *p = (RooArgSet*)parameters;
  RooRealVar  &rbk = *((RooRealVar*)p->find("r_dkstz"));
  RooRealVar  &dbk = *((RooRealVar*)p->find("d_dkstz"));
  RooRealVar  &kbk = *((RooRealVar*)p->find("k_dkstz"));
  RooRealVar  &g   = *((RooRealVar*)p->find("g"));
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  theory->add(*(new RooGLWAcpVar("acpp_dkstz_th", "Acp+ (DK*0)", rbk, dbk, kbk, g, "+")));
  theory->add(*(new RooGLWRcpVar("rcpp_dkstz_th", "Rcp+ (DK*0)", rbk, dbk, kbk, g, "+")));
}


void PDF_GLW_DKstz_2var::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("acpp_dkstz_obs", "Acp+ (DK*0) obs",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rcpp_dkstz_obs", "Rcp+ (DK*0) obs",  1, -1e4, 1e4)));
}


void PDF_GLW_DKstz_2var::setObservables(config c)
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
    case lhcb_kk:
      obsValSource = "PRD 90 (2014) 112002";
			setObservable("acpp_dkstz_obs",-0.20);
			setObservable("rcpp_dkstz_obs", 1.05);
      break;
    case lhcb_pipi:
      obsValSource = "PRD 90 (2014) 112002";
			setObservable("acpp_dkstz_obs",-0.09);
			setObservable("rcpp_dkstz_obs", 1.21);
			break;
		default:
			cout << "PDF_GLW_DKstz_2var::setObservables : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DKstz_2var::setUncertainties(config c)
{
	switch(c)
	{
		case lhcb_kk:
			obsErrSource = "PRD 90 (2014) 112002";
			StatErr[0] = 0.15; // acpp
			StatErr[1] = 0.16; // rcpp

			SystErr[0] = 0.02; // acpp
			SystErr[1] = 0.04; // rcpp
			break;

    case lhcb_pipi:
			obsErrSource = "PRD 90 (2014) 112002";
			StatErr[0] = 0.22; // acpp
			StatErr[1] = 0.265; // rcpp

			SystErr[0] = 0.02; // acpp
			SystErr[1] = 0.05; // rcpp
			break;

		default:
			cout << "PDF_GLW_DKstz_2var::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DKstz_2var::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lhcb_kk:
			corSource = "None";
			corStatMatrix[1][0] = 0.;
			corSystMatrix[1][0] = 0.;
			break;

		case lhcb_pipi:
			corSource = "None";
			corStatMatrix[1][0] = 0.;
			corSystMatrix[1][0] = 0.;
			break;

		default:
			cout << "PDF_GLW_DKstz_2var::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DKstz_2var::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
