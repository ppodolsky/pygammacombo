/**
 * Gamma Combination
 * Author: Matthew Kenzie (matthew.kenzie@cern.ch)
 * Date: June 2015
 *
 **/

#include "PDF_GLW_DK_pipipi0_1var.h"

#include "RooGLWAcpVar.h"
#include "RooGLWRcpVar.h"

	PDF_GLW_DK_pipipi0_1var::PDF_GLW_DK_pipipi0_1var(config cObs, config cErr, config cCor)
: PDF_Abs(1)
{
	name = "glw_like_dk_pipipi0_1var";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_GLW_DK_pipipi0_1var::~PDF_GLW_DK_pipipi0_1var(){}


void PDF_GLW_DK_pipipi0_1var::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("r_dk")));
	parameters->add(*(p.get("d_dk")));
	parameters->add(*(p.get("g")));
  parameters->add(*(p.get("F_pipipi0")));
}


void PDF_GLW_DK_pipipi0_1var::initRelations()
{
  RooArgSet *p = (RooArgSet*)parameters;
  RooRealVar    &rbk = *((RooRealVar*)p->find("r_dk"));
  RooRealVar    &dbk = *((RooRealVar*)p->find("d_dk"));
  RooFormulaVar &kbk = *(new RooFormulaVar("dilutionpp_1var","dilutionpp_1var","2*F_pipipi0 - 1", *p));
  RooRealVar    &g   = *((RooRealVar*)p->find("g"));
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  theory->add(*(new RooGLWAcpVar("aglw_dk_pipipi0_th", "Aglw+ (DK_pipipi0)", rbk, dbk, kbk, g, "+")));
}


void PDF_GLW_DK_pipipi0_1var::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("aglw_dk_pipipi0_obs", "Aglw+ (DK_pipipi0) obs",  0, -1e4, 1e4)));
}


void PDF_GLW_DK_pipipi0_1var::setObservables(config c)
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
      obsValSource = "BABAR-PUB-06-073"; // http://inspirehep.net/search?p=j+PRL,99,251801
			setObservable("aglw_dk_pipipi0_obs",-0.02);
      break;
		default:
			cout << "PDF_GLW_DK_pipipi0_1var::setObservables : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DK_pipipi0_1var::setUncertainties(config c)
{
	switch(c)
	{
		case babar:
      obsErrSource = "BABAR-PUB-06-073"; // http://inspirehep.net/search?p=j+PRL,99,251801
			StatErr[0] = 0.15; // aglw
			SystErr[0] = 0.03; // aglw
			break;

		default:
			cout << "PDF_GLW_DK_pipipi0_1var::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DK_pipipi0_1var::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case babar:
			corSource = "no correlation";
			break;

		default:
			cout << "PDF_GLW_DK_pipipi0_1var::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_GLW_DK_pipipi0_1var::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
