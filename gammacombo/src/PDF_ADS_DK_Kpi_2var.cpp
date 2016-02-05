/**
 * Gamma Combination
 * Author: Matthew Kenzie (matthew.kenzie@cern.ch)
 * Date: June 2015
 *
 **/

#include "PDF_ADS_DK_Kpi_2var.h"

#include "RooADSAVar.h"
#include "RooADSRVar.h"

	PDF_ADS_DK_Kpi_2var::PDF_ADS_DK_Kpi_2var(config cObs, config cErr, config cCor)
: PDF_Abs(2)
{
	name = "ads_dk_kpi";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_ADS_DK_Kpi_2var::~PDF_ADS_DK_Kpi_2var(){}


void PDF_ADS_DK_Kpi_2var::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("r_dk")));
	parameters->add(*(p.get("d_dk")));
	parameters->add(*(p.get("g")));
  parameters->add(*(p.get("rD_kpi")));
  parameters->add(*(p.get("dD_kpi")));
}


void PDF_ADS_DK_Kpi_2var::initRelations()
{
  RooArgSet *p = (RooArgSet*)parameters;
  RooRealVar  &rbk = *((RooRealVar*)p->find("r_dk"));
  RooRealVar  &dbk = *((RooRealVar*)p->find("d_dk"));
  RooConstVar &kbk = RooConst(1.);
  RooRealVar  &rd  = *((RooRealVar*)p->find("rD_kpi"));
  RooRealVar  &dd  = *((RooRealVar*)p->find("dD_kpi"));
  RooConstVar &kd  = RooConst(1.);
  RooRealVar  &g   = *((RooRealVar*)p->find("g"));
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  theory->add(*(new RooADSAVar("aads_dk_th", "Aads (DK)", rbk, dbk, kbk, rd, dd, kd, g )));
  theory->add(*(new RooADSRVar("rads_dk_th", "Rads (DK)", rbk, dbk, kbk, rd, dd, kd, g )));
}


void PDF_ADS_DK_Kpi_2var::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("aads_dk_obs", "Aads (DK) obs",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rads_dk_obs", "Rads (DK) obs",  1, -1e4, 1e4)));
}


void PDF_ADS_DK_Kpi_2var::setObservables(config c)
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
      obsValSource = "PRD 82 (2010) 072006";
      setObservable("aads_dk_obs", -0.86);
      setObservable("rads_dk_obs", 0.011);
      break;
    case belle:
      obsValSource = "PRL 106 (2011) 231803";
      setObservable("aads_dk_obs", -0.390 );
      setObservable("rads_dk_obs", 0.0163 );
      break;
    case cdf:
      obsValSource = "PRD 84 (2011) 091504";
      setObservable("aads_dk_obs", -0.82 );
      setObservable("rads_dk_obs", 0.0220 );
      break;
    case lhcb:
      obsValSource = "PLB 712 (2012) 203";
      setObservable("aads_dk_obs", -0.52 );
      setObservable("rads_dk_obs", 0.0152 );
			break;
		default:
			cout << "PDF_ADS_DK_Kpi_2var::setObservables : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_ADS_DK_Kpi_2var::setUncertainties(config c)
{
	switch(c)
	{
    case babar:
      obsErrSource = "PRD 82 (2010) 072006";
      StatErr[0] = 0.47;  //aads_dk_obs
      StatErr[1] = 0.006;  //rads_dk_obs
      SystErr[0] = 0.14; //aads_dk_obs
      SystErr[1] = 0.002; //rads_dk_obs
      break;
    case belle:
      obsErrSource = "PRL 106 (2011) 231803";
      StatErr[0] = 0.27;    //aads_dk_obs
      StatErr[1] = 0.00425;   //rads_dk_obs
      SystErr[0] = 0.035; //aads_dk_obs
      SystErr[1] = 0.0010;  //rads_dk_obs
      break;
    case cdf:
      obsErrSource = "PRD 84 (2011) 091504";
      StatErr[0] = 0.44;   //aads_dk_obs
      StatErr[1] = 0.0086;   //rads_dk_obs
      SystErr[0] = 0.09; //aads_dk_obs
      SystErr[1] = 0.0026; //rads_dk_obs
      break;
    case lhcb:
      obsErrSource = "PLB 712 (2012) 203";
      StatErr[0] = 0.15; //aads_dk_obs
      StatErr[1] = 0.0020; //rads_dk_obs
      SystErr[0] = 0.02; //aads_dk_obs
      SystErr[1] = 0.0004; //rads_dk_obs
			break;
		default:
			cout << "PDF_ADS_DK_Kpi_2var::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_ADS_DK_Kpi_2var::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case babar:
      corSource = "PRD 82 (2010) 072006";
			corStatMatrix[1][0] = 0.;
			corSystMatrix[1][0] = 0.;
			break;

		case belle:
      corSource = "PRL 106 (2011) 231803";
			corSource = "FERMILAB-PUB-09-549-E";
			corStatMatrix[1][0] = 0.;
			corSystMatrix[1][0] = 0.;
			break;

		case cdf:
      corSource = "PRD 84 (2011) 091504";
			corStatMatrix[1][0] = 0.;
			corSystMatrix[1][0] = 0.;
			break;

		case lhcb:
      corSource = "PLB 712 (2012) 203";
			corStatMatrix[1][0] = 0.;
			corSystMatrix[1][0] = 0.;
			break;

		default:
			cout << "PDF_ADS_DK_Kpi_2var::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_ADS_DK_Kpi_2var::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
