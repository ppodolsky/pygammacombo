/**
 * Gamma Combination
 * Author: Matthew Kenzie (matthew.kenzie@cern.ch)
 * Date: June 2015
 *
 **/

#include "PDF_ADS_DKstz_Kpi_2var.h"

#include "RooADSRpmVar.h"

	PDF_ADS_DKstz_Kpi_2var::PDF_ADS_DKstz_Kpi_2var(config cObs, config cErr, config cCor)
: PDF_Abs(2)
{
	name = "ads_dkstz_kpi";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_ADS_DKstz_Kpi_2var::~PDF_ADS_DKstz_Kpi_2var(){}


void PDF_ADS_DKstz_Kpi_2var::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("r_dkstz")));
	parameters->add(*(p.get("d_dkstz")));
  parameters->add(*(p.get("k_dkstz")));
	parameters->add(*(p.get("g")));
  parameters->add(*(p.get("rD_kpi")));
  parameters->add(*(p.get("dD_kpi")));
}


void PDF_ADS_DKstz_Kpi_2var::initRelations()
{
  RooArgSet *p = (RooArgSet*)parameters;
  RooRealVar  &rbk = *((RooRealVar*)p->find("r_dkstz"));
  RooRealVar  &dbk = *((RooRealVar*)p->find("d_dkstz"));
  RooRealVar  &kbk = *((RooRealVar*)p->find("k_dkstz"));
  RooRealVar  &rd  = *((RooRealVar*)p->find("rD_kpi"));
  RooRealVar  &dd  = *((RooRealVar*)p->find("dD_kpi"));
  RooConstVar &kd  = RooConst(1.);
  RooRealVar  &g   = *((RooRealVar*)p->find("g"));
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  theory->add(*(new RooADSRpmVar("rp_dkstz_th", "R+ (DK*0)", rbk, dbk, kbk, rd, dd, kd, g, "+" )));
  theory->add(*(new RooADSRpmVar("rm_dkstz_th", "R- (DK*0)", rbk, dbk, kbk, rd, dd, kd, g, "-" )));
}


void PDF_ADS_DKstz_Kpi_2var::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("rp_dkstz_obs", "R+ (DK*0) obs",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rm_dkstz_obs", "R- (DK*0) obs",  1, -1e4, 1e4)));
}


void PDF_ADS_DKstz_Kpi_2var::setObservables(config c)
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
      obsValSource = "PRD 90 (2014) 112002";
      setObservable("rp_dkstz_obs", 0.06);
      setObservable("rm_dkstz_obs", 0.06);
      break;
		default:
			cout << "PDF_ADS_DKstz_Kpi_2var::setObservables : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_ADS_DKstz_Kpi_2var::setUncertainties(config c)
{
	switch(c)
	{
    case lhcb:
      obsErrSource = "PRD 90 (2014) 112002";
      StatErr[0] = 0.03;  //rp_dkstz_obs
      StatErr[1] = 0.03; //rm_dkstz_obs
      SystErr[0] = 0.01;  //rp_dkstz_obs
      SystErr[1] = 0.01; //rm_dkstz_obs
      break;
		default:
			cout << "PDF_ADS_DKstz_Kpi_2var::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_ADS_DKstz_Kpi_2var::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lhcb:
      corSource = "None";
			corStatMatrix[1][0] = 0.;
			corSystMatrix[1][0] = 0.;
			break;

		default:
			cout << "PDF_ADS_DKstz_Kpi_2var::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_ADS_DKstz_Kpi_2var::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
