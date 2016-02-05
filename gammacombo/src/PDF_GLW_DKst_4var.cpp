/**
 * Gamma Combination
 * Author: Matthew Kenzie (matthew.kenzie@cern.ch)
 * Date: June 2015
 *
 **/

#include "PDF_GLW_DKst_4var.h"

#include "RooGLWRcpVar.h"
#include "RooGLWAcpVar.h"

	PDF_GLW_DKst_4var::PDF_GLW_DKst_4var(config cObs, config cErr, config cCor)
: PDF_Abs(4)
{
	name = "glw_dkst_4var";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_GLW_DKst_4var::~PDF_GLW_DKst_4var(){}


void PDF_GLW_DKst_4var::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("r_dkst")));
	parameters->add(*(p.get("d_dkst")));
  parameters->add(*(p.get("k_dkst")));
	parameters->add(*(p.get("g")));
}


void PDF_GLW_DKst_4var::initRelations()
{
  RooArgSet *p = (RooArgSet*)parameters;
  RooRealVar  &rbk = *((RooRealVar*)p->find("r_dkst"));
  RooRealVar  &dbk = *((RooRealVar*)p->find("d_dkst"));
  RooRealVar  &kbk = *((RooRealVar*)p->find("k_dkst"));
  RooRealVar  &g   = *((RooRealVar*)p->find("g"));
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  theory->add(*(new RooGLWAcpVar("acpp_dkst_th", "Acp+ (DK*)", rbk, dbk, kbk, g, "+")));
  theory->add(*(new RooGLWAcpVar("acpm_dkst_th", "Acp- (DK*)", rbk, dbk, kbk, g, "-")));
  theory->add(*(new RooGLWRcpVar("rcpp_dkst_th", "Rcp+ (DK*)", rbk, dbk, kbk, g, "+")));
  theory->add(*(new RooGLWRcpVar("rcpm_dkst_th", "Rcp- (DK*)", rbk, dbk, kbk, g, "-")));
}


void PDF_GLW_DKst_4var::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("acpp_dkst_obs", "Acp+ (DKst) obs",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acpm_dkst_obs", "Acp- (DKst) obs",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rcpp_dkst_obs", "Rcp+ (DKst) obs",  1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rcpm_dkst_obs", "Rcp- (DKst) obs",  1, -1e4, 1e4)));
}


void PDF_GLW_DKst_4var::setObservables(config c)
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
    case babar:
      obsValSource = "BABAR-PUB-09-019 "; // http://inspirehep.net/search?p=fin+j+PR,D80,092001
			setObservable("acpp_dkst_obs",0.09);
			setObservable("acpm_dkst_obs",-0.23);
			setObservable("rcpp_dkst_obs",2.17);
			setObservable("rcpm_dkst_obs",1.03);
      break;
		default:
			cout << "PDF_GLW_DKst_4var::setObservables : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DKst_4var::setUncertainties(config c)
{
	switch(c)
	{
		case babar:
      obsErrSource = "BABAR-PUB-09-019 "; // http://inspirehep.net/search?p=fin+j+PR,D80,092001
			StatErr[0] = 0.13; // acpp
			StatErr[1] = 0.21; // acpm
			StatErr[2] = 0.35; // rcpp
			StatErr[3] = 0.27; // rcpm

			SystErr[0] = 0.06; // acpp
			SystErr[1] = 0.07; // acpm
			SystErr[2] = 0.09; // rcpp
			SystErr[3] = 0.13; // rcpm
			break;

		default:
			cout << "PDF_GLW_DKst_4var::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DKst_4var::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case babar:
			corSource = "BABAR-PUB-09-019 "; // http://inspirehep.net/search?p=fin+j+PR,D80,092001
      // correlations are neglible apparently
      break;

		case belle:
			corSource = "correlations can't be found";
			break;

		default:
			cout << "PDF_GLW_DKst_4var::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DKst_4var::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
