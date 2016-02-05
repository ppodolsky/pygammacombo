/**
 * Gamma Combination
 * Author: Matthew Kenzie (matthew.kenzie@cern.ch)
 * Date: June 2015
 *
 **/

#include "PDF_GLW_DKpipi_2var.h"

#include "RooGLWAcpVar.h"
#include "RooGLWRcpVar.h"

	PDF_GLW_DKpipi_2var::PDF_GLW_DKpipi_2var(config cObs, config cErr, config cCor)
: PDF_Abs(2)
{
	name = "glw_dkpipi_2var";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_GLW_DKpipi_2var::~PDF_GLW_DKpipi_2var(){}


void PDF_GLW_DKpipi_2var::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("r_dkpipi")));
	parameters->add(*(p.get("d_dkpipi")));
  parameters->add(*(p.get("k_dkpipi")));
	parameters->add(*(p.get("g")));
}


void PDF_GLW_DKpipi_2var::initRelations()
{
  RooArgSet *p = (RooArgSet*)parameters;
  RooRealVar  &rbk = *((RooRealVar*)p->find("r_dkpipi"));
  RooRealVar  &dbk = *((RooRealVar*)p->find("d_dkpipi"));
  RooRealVar  &kbk = *((RooRealVar*)p->find("k_dkpipi"));
  RooRealVar  &g   = *((RooRealVar*)p->find("g"));
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  theory->add(*(new RooGLWAcpVar("acpp_dkpipi_th", "Acp+ (DK)", rbk, dbk, kbk, g, "+")));
  theory->add(*(new RooGLWRcpVar("rcpp_dkpipi_th", "Rcp+ (DK)", rbk, dbk, kbk, g, "+")));
}


void PDF_GLW_DKpipi_2var::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("acpp_dkpipi_obs", "Acp+ (DKpipi) obs",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rcpp_dkpipi_obs", "Rcp+ (DKpipi) obs",  1, -1e4, 1e4)));
}


void PDF_GLW_DKpipi_2var::setObservables(config c)
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
      obsValSource = "arXiv:1505.07044"; // http://arxiv.org/abs/1505.07044
			setObservable("acpp_dkpipi_obs",-0.045);
			setObservable("rcpp_dkpipi_obs",1.043);
      break;
    case lhcb_pipi:
      obsValSource = "arXiv:1505.07044"; // http://arxiv.org/abs/1505.07044
			setObservable("acpp_dkpipi_obs",-0.054);
			setObservable("rcpp_dkpipi_obs",1.035);
			break;
		default:
			cout << "PDF_GLW_DKpipi_2var::setObservables : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DKpipi_2var::setUncertainties(config c)
{
	switch(c)
	{
		case lhcb_kk:
      obsErrSource = "arXiv:1505.07044"; // http://arxiv.org/abs/1505.07044
			StatErr[0] = 0.064; // acpp
			StatErr[1] = 0.069; // rcpp

			SystErr[0] = 0.011; // acpp
			SystErr[1] = 0.034; // rcpp
			break;

		case lhcb_pipi:
      obsErrSource = "arXiv:1505.07044"; // http://arxiv.org/abs/1505.07044
			StatErr[0] = 0.101; // acpp
			StatErr[1] = 0.108; // rcpp

			SystErr[0] = 0.011; // acpp
			SystErr[1] = 0.038; // rcpp
			break;

		default:
			cout << "PDF_GLW_DKpipi_2var::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DKpipi_2var::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lhcb_kk:
      corSource = "arXiv:1505.07044"; // http://arxiv.org/abs/1505.07044
			corStatMatrix[1][0] = 0.;
			corSystMatrix[1][0] = 0.;
			break;

		case lhcb_pipi:
      corSource = "arXiv:1505.07044"; // http://arxiv.org/abs/1505.07044
			corStatMatrix[1][0] = 0.;
			corSystMatrix[1][0] = 0.;
			break;

		default:
			cout << "PDF_GLW_DKpipi_2var::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DKpipi_2var::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
