/**
 * Gamma Combination
 * Author: Matthew Kenzie (matthew.kenzie@cern.ch)
 * Date: June 2015
 *
 **/

#include "PDF_ADS_DKpipi_Kpi_2var.h"

#include "RooADSAVar.h"
#include "RooADSRVar.h"

	PDF_ADS_DKpipi_Kpi_2var::PDF_ADS_DKpipi_Kpi_2var(config cObs, config cErr, config cCor)
: PDF_Abs(2)
{
	name = "ads_dkpipi_kpi_2var";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_ADS_DKpipi_Kpi_2var::~PDF_ADS_DKpipi_Kpi_2var(){}


void PDF_ADS_DKpipi_Kpi_2var::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("r_dkpipi")));
	parameters->add(*(p.get("d_dkpipi")));
	parameters->add(*(p.get("k_dkpipi")));
	parameters->add(*(p.get("g")));
  parameters->add(*(p.get("rD_kpi")));
  parameters->add(*(p.get("dD_kpi")));
}


void PDF_ADS_DKpipi_Kpi_2var::initRelations()
{
  RooArgSet *p = (RooArgSet*)parameters;
  RooRealVar  &rbk = *((RooRealVar*)p->find("r_dkpipi"));
  RooRealVar  &dbk = *((RooRealVar*)p->find("d_dkpipi"));
  RooRealVar  &kbk = *((RooRealVar*)p->find("k_dkpipi"));
  RooRealVar  &rd  = *((RooRealVar*)p->find("rD_kpi"));
  RooRealVar  &dd  = *((RooRealVar*)p->find("dD_kpi"));
  RooConstVar &kd  = RooConst(1.);
  RooRealVar  &g   = *((RooRealVar*)p->find("g"));
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  theory->add(*(new RooADSAVar("aads_dkpipi_th", "Aads (DK)", rbk, dbk, kbk, rd, dd, kd, g )));
  theory->add(*(new RooADSRVar("rads_dkpipi_th", "Rads (DK)", rbk, dbk, kbk, rd, dd, kd, g )));
}


void PDF_ADS_DKpipi_Kpi_2var::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("aads_dkpipi_obs", "Aads (DK) obs",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rads_dkpipi_obs", "Rads (DK) obs",  1, -1e4, 1e4)));
}


void PDF_ADS_DKpipi_Kpi_2var::setObservables(config c)
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
      obsValSource = "arXiv:1505.07044";
      setObservable("aads_dkpipi_obs", -0.32 );
      setObservable("rads_dkpipi_obs", 0.0082 );
			break;
		default:
			cout << "PDF_ADS_DKpipi_Kpi_2var::setObservables : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_ADS_DKpipi_Kpi_2var::setUncertainties(config c)
{
	switch(c)
	{
    case lhcb:
      obsErrSource = "arXiv:1505.07044";
      StatErr[0] = 0.30; //aads_dkpipi_obs
      StatErr[1] = 0.0034; //rads_dkpipi_obs
      SystErr[0] = 0.0; //aads_dkpipi_obs
      SystErr[1] = 0.0; //rads_dkpipi_obs
			break;
		default:
			cout << "PDF_ADS_DKpipi_Kpi_2var::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_ADS_DKpipi_Kpi_2var::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lhcb:
      corSource = "arXiv:1505.07044";
			corStatMatrix[1][0] = 0.;
			corSystMatrix[1][0] = 0.;
			break;

		default:
			cout << "PDF_ADS_DKpipi_Kpi_2var::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_ADS_DKpipi_Kpi_2var::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
