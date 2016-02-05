/**
 * Gamma Combination
 * Author: Matthew Kenzie (matthew.kenzie@cern.ch)
 * Date: June 2015
 *
 **/

#include "PDF_GLW_DK_KKpi0_2var.h"

#include "RooGLWAcpVar.h"
#include "RooGLWRcpVar.h"

	PDF_GLW_DK_KKpi0_2var::PDF_GLW_DK_KKpi0_2var(config cObs, config cErr, config cCor)
: PDF_Abs(2)
{
	name = "glw_like_dk_kkpi0_2var";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_GLW_DK_KKpi0_2var::~PDF_GLW_DK_KKpi0_2var(){}


void PDF_GLW_DK_KKpi0_2var::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("r_dk")));
	parameters->add(*(p.get("d_dk")));
	parameters->add(*(p.get("g")));
  parameters->add(*(p.get("F_kkpi0")));
}


void PDF_GLW_DK_KKpi0_2var::initRelations()
{
  RooArgSet *p = (RooArgSet*)parameters;
  RooRealVar    &rbk = *((RooRealVar*)p->find("r_dk"));
  RooRealVar    &dbk = *((RooRealVar*)p->find("d_dk"));
  RooFormulaVar &kbk = *(new RooFormulaVar("dilutionkk","dilutionkk","2*F_kkpi0 - 1", *p));
  RooRealVar    &g   = *((RooRealVar*)p->find("g"));
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  theory->add(*(new RooGLWAcpVar("aglw_dk_kkpi0_th", "Aglw+ (DK_KKpi0)", rbk, dbk, kbk, g, "+")));
  theory->add(*(new RooGLWRcpVar("rglw_dk_kkpi0_th", "Rglw+ (DK_KKpi0)", rbk, dbk, kbk, g, "+")));
}


void PDF_GLW_DK_KKpi0_2var::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("aglw_dk_kkpi0_obs", "Aglw+ (DK_KKpi0) obs",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rglw_dk_kkpi0_obs", "Rglw+ (DK_KKpi0) obs",  1, -1e4, 1e4)));
}


void PDF_GLW_DK_KKpi0_2var::setObservables(config c)
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
    case lhcb:
      obsValSource = "arXiv:1504.05442"; // http://arxiv.org/pdf/1504.05442v2.pdf
			setObservable("aglw_dk_kkpi0_obs",0.30);
			setObservable("rglw_dk_kkpi0_obs",0.95);
      break;
		default:
			cout << "PDF_GLW_DK_KKpi0_2var::setObservables : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DK_KKpi0_2var::setUncertainties(config c)
{
	switch(c)
	{
		case lhcb:
      obsErrSource = "arXiv:1504.05442"; // http://arxiv.org/pdf/1504.05442v2.pdf
			StatErr[0] = 0.20; // aglw
			StatErr[1] = 0.22; // rglw

			SystErr[0] = 0.02; // aglw
			SystErr[1] = 0.04; // rglw
			break;

		default:
			cout << "PDF_GLW_DK_KKpi0_2var::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DK_KKpi0_2var::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lhcb:
			corSource = "no correlation";
			corStatMatrix[1][0] = 0.;
			corSystMatrix[1][0] = 0.;
			break;

		default:
			cout << "PDF_GLW_DK_KKpi0_2var::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DK_KKpi0_2var::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
