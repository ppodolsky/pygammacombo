/**
 * Gamma Combination
 * Author: Matthew Kenzie (matthew.kenzie@cern.ch)
 * Date: June 2015
 *
 **/

#include "PDF_GLW_DstK_4var.h"

#include "RooGLWAcpVar.h"
#include "RooGLWRcpVar.h"

	PDF_GLW_DstK_4var::PDF_GLW_DstK_4var(config cObs, config cErr, config cCor)
: PDF_Abs(4)
{
	name = "glw_dstk_4var";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_GLW_DstK_4var::~PDF_GLW_DstK_4var(){}


void PDF_GLW_DstK_4var::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("r_dstk")));
	parameters->add(*(p.get("d_dstk")));
	parameters->add(*(p.get("g")));
}


void PDF_GLW_DstK_4var::initRelations()
{
  RooArgSet *p = (RooArgSet*)parameters;
  RooRealVar  &rbk = *((RooRealVar*)p->find("r_dstk"));
  RooRealVar  &dbk = *((RooRealVar*)p->find("d_dstk"));
  RooConstVar &kbk = RooConst(1.);
  RooRealVar  &g   = *((RooRealVar*)p->find("g"));
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  theory->add(*(new RooGLWAcpVar("acpp_dstk_th", "Acp+ (D*K)", rbk, dbk, kbk, g, "+")));
  theory->add(*(new RooGLWAcpVar("acpm_dstk_th", "Acp- (D*K)", rbk, dbk, kbk, g, "-")));
  theory->add(*(new RooGLWRcpVar("rcpp_dstk_th", "Rcp+ (D*K)", rbk, dbk, kbk, g, "+")));
  theory->add(*(new RooGLWRcpVar("rcpm_dstk_th", "Rcp- (D*K)", rbk, dbk, kbk, g, "-")));
}


void PDF_GLW_DstK_4var::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("acpp_dstk_obs", "Acp+ (DstK) obs",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("acpm_dstk_obs", "Acp- (DstK) obs",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rcpp_dstk_obs", "Rcp+ (DstK) obs",  1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rcpm_dstk_obs", "Rcp- (DstK) obs",  1, -1e4, 1e4)));
}


void PDF_GLW_DstK_4var::setObservables(config c)
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
      obsValSource = "BABAR-PUB-08-017 "; // http://inspirehep.net/search?p=fin+j+PR,D78,092002
			setObservable("acpp_dstk_obs",-0.11);
			setObservable("acpm_dstk_obs",0.06);
			setObservable("rcpp_dstk_obs",1.31);
			setObservable("rcpm_dstk_obs",1.09);
      break;
    case belle:
			obsValSource = "HFAG"; // http://www.slac.stanford.edu/xorg/hfag/triangle/latest/#gamma_DCPK
			setObservable("acpp_dstk_obs",-0.14);
			setObservable("acpm_dstk_obs",0.22);
			setObservable("rcpp_dstk_obs",1.19);
			setObservable("rcpm_dstk_obs",1.03);
			break;
		default:
			cout << "PDF_GLW_DstK_4var::setObservables : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DstK_4var::setUncertainties(config c)
{
	switch(c)
	{
		case babar:
      obsErrSource = "BABAR-PUB-08-017 "; // http://inspirehep.net/search?p=fin+j+PR,D78,092002
			StatErr[0] = 0.09; // acpp
			StatErr[1] = 0.10; // acpm
			StatErr[2] = 0.13; // rcpp
			StatErr[3] = 0.12; // rcpm

			SystErr[0] = 0.01; // acpp
			SystErr[1] = 0.02; // acpm
			SystErr[2] = 0.03; // rcpp
			SystErr[3] = 0.04; // rcpm
			break;

		case belle:
			obsErrSource = "HFAG"; // http://www.slac.stanford.edu/xorg/hfag/triangle/latest/#gamma_DCPK
			StatErr[0] = 0.10; // acpp
			StatErr[1] = 0.11; // acpm
			StatErr[2] = 0.13; // rcpp
			StatErr[3] = 0.13; // rcpm

			SystErr[0] = 0.01; // acpp
			SystErr[1] = 0.01; // acpm
			SystErr[2] = 0.03; // rcpp
			SystErr[3] = 0.03; // rcpm
			break;

		default:
			cout << "PDF_GLW_DstK_4var::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DstK_4var::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case babar:
			corSource = "BABAR-PUB-08-017 ";
      // correlations are neglible apparently
      break;

		case belle:
			corSource = "correlations can't be found";
			break;

		default:
			cout << "PDF_GLW_DstK_4var::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DstK_4var::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
