/**
 * Gamma Combination
 * Author: Matthew Kenzie (matthew.kenzie@cern.ch)
 * Date: June 2015
 *
 **/

#include "PDF_GLW_DK_2var.h"
#include "RooGLWAcpVar.h"
#include "RooGLWRcpVar.h"

	PDF_GLW_DK_2var::PDF_GLW_DK_2var(config cObs, config cErr, config cCor)
: PDF_Abs(2)
{
	name = "glw_dk_2var";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_GLW_DK_2var::~PDF_GLW_DK_2var(){}


void PDF_GLW_DK_2var::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("r_dk")));
	parameters->add(*(p.get("d_dk")));
	parameters->add(*(p.get("g")));
}


void PDF_GLW_DK_2var::initRelations()
{
  RooArgSet *p = (RooArgSet*)parameters;
  RooRealVar  &rbk = *((RooRealVar*)p->find("r_dk"));
  RooRealVar  &dbk = *((RooRealVar*)p->find("d_dk"));
  RooConstVar &kbk = RooConst(1.);
  RooRealVar  &g   = *((RooRealVar*)p->find("g"));
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  theory->add(*(new RooGLWAcpVar("acpp_dk_th", "Acp+ (DK)", rbk, dbk, kbk, g, "+")));
  theory->add(*(new RooGLWRcpVar("rcpp_dk_th", "Rcp+ (DK)", rbk, dbk, kbk, g, "+")));
}


void PDF_GLW_DK_2var::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("acpp_dk_obs", "Acp+ (DK) obs",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rcpp_dk_obs", "Rcp+ (DK) obs",  1, -1e4, 1e4)));
}


void PDF_GLW_DK_2var::setObservables(config c)
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
    case cdf:
      obsValSource = "FERMILAB-PUB-09-549-E"; // http://inspirehep.net/search?p=fin%20j%20PR,D81,031105
			setObservable("acpp_dk_obs",0.39);
			setObservable("rcpp_dk_obs",1.30);
      break;
    case lhcb:
			obsValSource = "LHCb-PAPER-2012-001"; // http://inspirehep.net/search?p=fin+j+PL,B712,203
			setObservable("acpp_dk_obs",0.145);
			setObservable("rcpp_dk_obs",1.007);
			break;
		default:
			cout << "PDF_GLW_DK_2var::setObservables : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DK_2var::setUncertainties(config c)
{
	switch(c)
	{
		case cdf:
			obsErrSource = "FERMILAB-PUB-09-549-E";
			StatErr[0] = 0.17; // acpp
			StatErr[1] = 0.24; // rcpp

			SystErr[0] = 0.04; // acpp
			SystErr[1] = 0.12; // rcpp
			break;

		case lhcb:
			obsErrSource = "1fb-1 LHCb-PAPER-2012-001";
			StatErr[0] = 0.032; // acpp
			StatErr[1] = 0.038; // rcpp

			SystErr[0] = 0.010; // acpp
			SystErr[1] = 0.012; // rcpp
			break;

		default:
			cout << "PDF_GLW_DK_2var::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DK_2var::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case cdf:
			corSource = "FERMILAB-PUB-09-549-E";
			corStatMatrix[1][0] = 0.;
			corSystMatrix[1][0] = 0.;
			break;

		case lhcb:
			corSource = "1fb-1 LHCb-PAPER-2012-001";
			corStatMatrix[1][0] = 0.;
			corSystMatrix[1][0] = 0.;
			break;

		default:
			cout << "PDF_GLW_DK_2var::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DK_2var::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
