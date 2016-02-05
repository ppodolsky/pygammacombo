/**
 * Gamma Combination
 * Author: Matthew Kenzie (matthew.kenzie@cern.ch)
 * Date: June 2015
 *
 **/

#include "PDF_ADS_DstK_Kpi_2var.h"

#include "RooADSAVar.h"
#include "RooADSRVar.h"

	PDF_ADS_DstK_Kpi_2var::PDF_ADS_DstK_Kpi_2var(config cObs, config cErr, config cCor)
: PDF_Abs(2)
{
	name = "ads_dstk_kpi";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_ADS_DstK_Kpi_2var::~PDF_ADS_DstK_Kpi_2var(){}


void PDF_ADS_DstK_Kpi_2var::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("r_dstk")));
	parameters->add(*(p.get("d_dstk")));
	parameters->add(*(p.get("g")));
  parameters->add(*(p.get("rD_kpi")));
  parameters->add(*(p.get("dD_kpi")));
}


void PDF_ADS_DstK_Kpi_2var::initRelations()
{
  RooArgSet *p = (RooArgSet*)parameters;
  RooRealVar  &rbk = *((RooRealVar*)p->find("r_dstk"));
  RooRealVar  &dbk = *((RooRealVar*)p->find("d_dstk"));
  RooConstVar &kbk = RooConst(1.);
  RooRealVar  &rd  = *((RooRealVar*)p->find("rD_kpi"));
  RooRealVar  &dd  = *((RooRealVar*)p->find("dD_kpi"));
  RooConstVar &kd  = RooConst(1.);
  RooRealVar  &g   = *((RooRealVar*)p->find("g"));
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  theory->add(*(new RooADSAVar("aads_dstk_th", "Aads (D*K)", rbk, dbk, kbk, rd, dd, kd, g )));
  theory->add(*(new RooADSRVar("rads_dstk_th", "Rads (D*K)", rbk, dbk, kbk, rd, dd, kd, g )));
}


void PDF_ADS_DstK_Kpi_2var::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("aads_dstk_obs", "Aads (D*K) obs",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rads_dstk_obs", "Rads (D*K) obs",  1, -1e4, 1e4)));
}


void PDF_ADS_DstK_Kpi_2var::setObservables(config c)
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
    case babar_dpi0:
      obsValSource = "PRD 82 (2010) 072006";
      setObservable("aads_dstk_obs", 0.770);
      setObservable("rads_dstk_obs", 0.018);
      break;
    case belle_dpi0:
      obsValSource = "LP 2011 prelim";
      setObservable("aads_dstk_obs", 0.400);
      setObservable("rads_dstk_obs", 0.010);
      break;
    case babar_dg:
      obsValSource = "PRD 82 (2010) 072006";
      setObservable("aads_dstk_obs", 0.360);
      setObservable("rads_dstk_obs", 0.013);
      break;
    case belle_dg:
      obsValSource = "LP 2011 prelim";
      setObservable("aads_dstk_obs",-0.510);
      setObservable("rads_dstk_obs", 0.036);
      break;
		default:
			cout << "PDF_ADS_DstK_Kpi_2var::setObservables : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_ADS_DstK_Kpi_2var::setUncertainties(config c)
{
	switch(c)
	{
    case babar_dpi0:
      obsErrSource = "PRD 82 (2010) 072006";
      StatErr[0] = 0.35;  //aads_dstk_obs
      StatErr[1] = 0.009; //rads_dstk_obs
      SystErr[0] = 0.12;  //aads_dstk_obs
      SystErr[1] = 0.004; //rads_dstk_obs
      break;
    case belle_dpi0:
      obsErrSource = "LP 2011 prelim";
      StatErr[0] = 0.9;  //aads_dstk_obs
      StatErr[1] = 0.0075; //rads_dstk_obs
      SystErr[0] = 0.15;  //aads_dstk_obs
      SystErr[1] = 0.0015; //rads_dstk_obs
      break;
    case babar_dg:
      obsErrSource = "PRD 82 (2010) 072006";
      StatErr[0] = 0.94;  //aads_dstk_obs
      StatErr[1] = 0.014; //rads_dstk_obs
      SystErr[0] = 0.33;  //aads_dstk_obs
      SystErr[1] = 0.008; //rads_dstk_obs
      break;
    case belle_dg:
      obsErrSource = "LP 2011 prelim";
      StatErr[0] = 0.32;  //aads_dstk_obs
      StatErr[1] = 0.013; //rads_dstk_obs
      SystErr[0] = 0.08;  //aads_dstk_obs
      SystErr[1] = 0.002; //rads_dstk_obs
      break;
		default:
			cout << "PDF_ADS_DstK_Kpi_2var::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_ADS_DstK_Kpi_2var::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case babar_dpi0:
      corSource = "None";
			corStatMatrix[1][0] = 0.;
			corSystMatrix[1][0] = 0.;
			break;

		case babar_dg:
      corSource = "None";
			corStatMatrix[1][0] = 0.;
			corSystMatrix[1][0] = 0.;
			break;

		case belle_dpi0:
      corSource = "None";
			corStatMatrix[1][0] = 0.;
			corSystMatrix[1][0] = 0.;
			break;

		case belle_dg:
      corSource = "None";
			corStatMatrix[1][0] = 0.;
			corSystMatrix[1][0] = 0.;
			break;

		case babar:
      corSource = "PRD 80 (2009) 092001";
			corStatMatrix[1][0] = 0.;
			corSystMatrix[1][0] = 0.;
			break;

		default:
			cout << "PDF_ADS_DstK_Kpi_2var::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_ADS_DstK_Kpi_2var::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
