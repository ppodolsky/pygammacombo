/**
 * Gamma Combination
 * Author: Matthew Kenzie (matthew.kenzie@cern.ch)
 * Date: June 2015
 *
 **/

#include "PDF_ADS_DK_Kpipi0_2var.h"

#include "RooADSAVar.h"
#include "RooADSRVar.h"

	PDF_ADS_DK_Kpipi0_2var::PDF_ADS_DK_Kpipi0_2var(config cObs, config cErr, config cCor)
: PDF_Abs(2)
{
	name = "ads_dk_kpipi0";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_ADS_DK_Kpipi0_2var::~PDF_ADS_DK_Kpipi0_2var(){}


void PDF_ADS_DK_Kpipi0_2var::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("r_dk")));
	parameters->add(*(p.get("d_dk")));
	parameters->add(*(p.get("g")));
  parameters->add(*(p.get("rD_kpipi0")));
  parameters->add(*(p.get("dD_kpipi0")));
  parameters->add(*(p.get("kD_kpipi0")));
}


void PDF_ADS_DK_Kpipi0_2var::initRelations()
{
  RooArgSet *p = (RooArgSet*)parameters;
  RooRealVar  &rbk = *((RooRealVar*)p->find("r_dk"));
  RooRealVar  &dbk = *((RooRealVar*)p->find("d_dk"));
  RooConstVar &kbk = RooConst(1.);
  RooRealVar  &rd  = *((RooRealVar*)p->find("rD_kpipi0"));
  RooRealVar  &dd  = *((RooRealVar*)p->find("dD_kpipi0"));
  RooRealVar  &kd  = *((RooRealVar*)p->find("kD_kpipi0"));
  RooRealVar  &g   = *((RooRealVar*)p->find("g"));
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  theory->add(*(new RooADSAVar("aads_dk_th", "Aads (DK_kpipi0)", rbk, dbk, kbk, rd, dd, kd, g )));
  theory->add(*(new RooADSRVar("rads_dk_th", "Rads (DK_kpipi0)", rbk, dbk, kbk, rd, dd, kd, g )));
}


void PDF_ADS_DK_Kpipi0_2var::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("aads_dk_obs", "Aads (DK) obs",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rads_dk_obs", "Rads (DK) obs",  1, -1e4, 1e4)));
}


void PDF_ADS_DK_Kpipi0_2var::setObservables(config c)
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
      obsValSource = "PRD 84 (2011) 012002";
      setObservable("aads_dk_obs", 0.0 ); // not measured so set massive error
      setObservable("rads_dk_obs", 0.0091 );
      break;
    case belle:
      obsValSource = "PRD 88 (2013) 091104(R)";
      setObservable("aads_dk_obs", 0.41 );
      setObservable("rads_dk_obs", 0.0198 );
      break;
    case lhcb:
      obsValSource = "arXiv:1504.05442";
      setObservable("aads_dk_obs", -0.20 );
      setObservable("rads_dk_obs", 0.0140 );
			break;
		default:
			cout << "PDF_ADS_DK_Kpipi0_2var::setObservables : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_ADS_DK_Kpipi0_2var::setUncertainties(config c)
{
	switch(c)
	{
    case babar:
      obsErrSource = "PRD 84 (2011) 012002";
      StatErr[0] = 1.;    //aads_dk_obs // not measured
      StatErr[1] = 0.0079;   //rads_dk_obs
      SystErr[0] = 0.; //aads_dk_obs
      SystErr[1] = 0.00305;  //rads_dk_obs
      break;
    case belle:
      obsErrSource = "PRD 88 (2013) 091104(R)";
      StatErr[0] = 0.30;    //aads_dk_obs
      StatErr[1] = 0.0062;   //rads_dk_obs
      SystErr[0] = 0.05; //aads_dk_obs
      SystErr[1] = 0.0024;  //rads_dk_obs
      break;
    case lhcb:
      obsErrSource = "arXiv:1504.05442";
      StatErr[0] = 0.27; //aads_dk_obs
      StatErr[1] = 0.0047; //rads_dk_obs
      SystErr[0] = 0.03; //aads_dk_obs
      SystErr[1] = 0.0019; //rads_dk_obs
			break;
		default:
			cout << "PDF_ADS_DK_Kpipi0_2var::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_ADS_DK_Kpipi0_2var::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case babar:
      corSource = "PRD 84 (2011) 012002";
			corSource = "FERMILAB-PUB-09-549-E";
			corStatMatrix[1][0] = 0.;
			corSystMatrix[1][0] = 0.;
			break;

		case belle:
      corSource = "PRD 88 (2013) 091104(R)";
			corSource = "FERMILAB-PUB-09-549-E";
			corStatMatrix[1][0] = 0.;
			corSystMatrix[1][0] = 0.;
			break;

		case lhcb:
      corSource = "arXiv:1504.05442";
			corStatMatrix[1][0] = 0.;
			corSystMatrix[1][0] = 0.;
			break;

		default:
			cout << "PDF_ADS_DK_Kpipi0_2var::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_ADS_DK_Kpipi0_2var::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
