/**
 * Gamma Combination
 * Author: Matthew Kenzie (matthew.kenzie@cern.ch)
 * Date: June 2015
 *
 **/

#include "PDF_GLW_DK_4var.h"
#include "RooGLWAcpVar.h"
#include "RooGLWRcpVar.h"

	PDF_GLW_DK_4var::PDF_GLW_DK_4var(config cObs, config cErr, config cCor)
: PDF_Abs(4)
{
	name = "glw_dk_4var";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_GLW_DK_4var::~PDF_GLW_DK_4var(){}


void PDF_GLW_DK_4var::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("r_dk")));
	parameters->add(*(p.get("d_dk")));
	parameters->add(*(p.get("g")));
}


void PDF_GLW_DK_4var::initRelations()
{
  RooArgSet *p = (RooArgSet*)parameters;
  RooRealVar  &rbk = *((RooRealVar*)p->find("r_dk"));
  RooRealVar  &dbk = *((RooRealVar*)p->find("d_dk"));
  RooConstVar &kbk = RooConst(1.);
  RooRealVar  &g   = *((RooRealVar*)p->find("g"));
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  theory->add(*(new RooGLWAcpVar("acpp_dk_th", "Acp+ (DK)", rbk, dbk, kbk, g, "+")));
  theory->add(*(new RooGLWAcpVar("acpm_dk_th", "Acp- (DK)", rbk, dbk, kbk, g, "-")));
  theory->add(*(new RooGLWRcpVar("rcpp_dk_th", "Rcp+ (DK)", rbk, dbk, kbk, g, "+")));
  theory->add(*(new RooGLWRcpVar("rcpm_dk_th", "Rcp- (DK)", rbk, dbk, kbk, g, "-")));
}


void PDF_GLW_DK_4var::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("acpp_dk_obs", "Acp+ (DK) obs",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acpm_dk_obs", "Acp- (DK) obs",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rcpp_dk_obs", "Rcp+ (DK) obs",  1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rcpm_dk_obs", "Rcp- (DK) obs",  1, -1e4, 1e4)));
}


void PDF_GLW_DK_4var::setObservables(config c)
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
      obsValSource = "BABAR-PUB-10-008 "; // http://inspirehep.net/search?p=fin+j+PR,D82,072004
			setObservable("acpp_dk_obs",0.25);
			setObservable("acpm_dk_obs",-0.09);
			setObservable("rcpp_dk_obs",1.18);
			setObservable("rcpm_dk_obs",1.07);
      break;
    case belle:
			obsValSource = "HFAG"; // http://www.slac.stanford.edu/xorg/hfag/triangle/latest/#gamma_DCPK
			setObservable("acpp_dk_obs",0.29);
			setObservable("acpm_dk_obs",-0.12);
			setObservable("rcpp_dk_obs",1.03);
			setObservable("rcpm_dk_obs",1.13);
			break;
		default:
			cout << "PDF_GLW_DK_4var::setObservables : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DK_4var::setUncertainties(config c)
{
	switch(c)
	{
		case babar:
			obsErrSource = "BABAR-PUB-10-008 "; // http://inspirehep.net/search?p=fin+j+PR,D82,072004
			StatErr[0] = 0.06; // acpp
			StatErr[1] = 0.07; // acpm
			StatErr[2] = 0.09; // rcpp
			StatErr[3] = 0.08; // rcpm

			SystErr[0] = 0.02; // acpp
			SystErr[1] = 0.02; // acpm
			SystErr[2] = 0.05; // rcpp
			SystErr[3] = 0.04; // rcpm
			break;

		case belle:
			obsErrSource = "HFAG"; // http://www.slac.stanford.edu/xorg/hfag/triangle/latest/#gamma_DCPK
			StatErr[0] = 0.06; // acpp
			StatErr[1] = 0.06; // acpm
			StatErr[2] = 0.07; // rcpp
			StatErr[3] = 0.09; // rcpm

			SystErr[0] = 0.02; // acpp
			SystErr[1] = 0.01; // acpm
			SystErr[2] = 0.03; // rcpp
			SystErr[3] = 0.05; // rcpm
			break;

		default:
			cout << "PDF_GLW_DK_4var::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DK_4var::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case babar:
			corSource = "BABAR-PUB-10-008 "; // http://inspirehep.net/search?p=fin+j+PR,D82,072004

      // just doing off diagonal terms
      corStatMatrix[1][0] = 0.56;
      corStatMatrix[2][0] = -0.06;
      corStatMatrix[3][0] = 0.;
      corStatMatrix[2][1] = 0.;
      corStatMatrix[3][1] = 0.;
      corStatMatrix[3][2] = 0.13;

      corSystMatrix[1][0] = 0.0;
      corSystMatrix[2][0] = -0.08;
      corSystMatrix[3][0] = 0.;
      corSystMatrix[2][1] = 0.;
      corSystMatrix[3][1] = 0.03;
      corSystMatrix[3][2] = 0.10;

      break;

		case belle:
			corSource = "correlations can't be found";
			break;

    case none:
      corSource = "correlations off";
      break;

		default:
			cout << "PDF_GLW_DK_4var::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DK_4var::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
