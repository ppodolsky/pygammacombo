/**
 * Gamma Combination
 * Author: Matthew Kenzie (matthew.kenzie@cern.ch)
 * Date: June 2015
 *
 **/

#include "PDF_ADS_DK_K3pi_2var.h"

#include "RooADSAVar.h"
#include "RooADSRVar.h"

	PDF_ADS_DK_K3pi_2var::PDF_ADS_DK_K3pi_2var(config cObs, config cErr, config cCor)
: PDF_Abs(2)
{
	name = "ads_dk_k3pi_2var";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_ADS_DK_K3pi_2var::~PDF_ADS_DK_K3pi_2var(){}


void PDF_ADS_DK_K3pi_2var::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("r_dk")));
	parameters->add(*(p.get("d_dk")));
	parameters->add(*(p.get("g")));
  parameters->add(*(p.get("rD_k3pi")));
  parameters->add(*(p.get("dD_k3pi")));
  parameters->add(*(p.get("kD_k3pi")));
}


void PDF_ADS_DK_K3pi_2var::initRelations()
{
  RooArgSet *p = (RooArgSet*)parameters;
  RooRealVar  &rbk = *((RooRealVar*)p->find("r_dk"));
  RooRealVar  &dbk = *((RooRealVar*)p->find("d_dk"));
  RooConstVar &kbk = RooConst(1.);
  RooRealVar  &rd  = *((RooRealVar*)p->find("rD_k3pi"));
  RooRealVar  &dd  = *((RooRealVar*)p->find("dD_k3pi"));
  RooRealVar  &kd  = *((RooRealVar*)p->find("kD_k3pi"));
  RooRealVar  &g   = *((RooRealVar*)p->find("g"));
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  theory->add(*(new RooADSAVar("aads_dk_th", "Aads (DK)", rbk, dbk, kbk, rd, dd, kd, g )));
  theory->add(*(new RooADSRVar("rads_dk_th", "Rads (DK)", rbk, dbk, kbk, rd, dd, kd, g )));
}


void PDF_ADS_DK_K3pi_2var::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("aads_dk_obs", "Aads (DK) obs",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rads_dk_obs", "Rads (DK) obs",  1, -1e4, 1e4)));
}


void PDF_ADS_DK_K3pi_2var::setObservables(config c)
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
      obsValSource = "PLB 723 (2013) 44";
      setObservable("aads_dk_obs", -0.42 );
      setObservable("rads_dk_obs", 0.0124 );
			break;
		default:
			cout << "PDF_ADS_DK_K3pi_2var::setObservables : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_ADS_DK_K3pi_2var::setUncertainties(config c)
{
	switch(c)
	{
    case lhcb:
      obsErrSource = "PLB 723 (2013) 44";
      StatErr[0] = 0.22; //aads_dk_obs
      StatErr[1] = 0.0027; //rads_dk_obs
      SystErr[0] = 0.0; //aads_dk_obs
      SystErr[1] = 0.0; //rads_dk_obs
			break;
		default:
			cout << "PDF_ADS_DK_K3pi_2var::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_ADS_DK_K3pi_2var::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lhcb:
      corSource = "PLB 723 (2013) 44";
			corStatMatrix[1][0] = 0.;
			corSystMatrix[1][0] = 0.;
			break;

		default:
			cout << "PDF_ADS_DK_K3pi_2var::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_ADS_DK_K3pi_2var::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
