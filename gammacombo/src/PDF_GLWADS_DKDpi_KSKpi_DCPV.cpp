/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Sep 2014
 *
 **/

#include "PDF_GLWADS_DKDpi_KSKpi_DCPV.h"

PDF_GLWADS_DKDpi_KSKpi_DCPV::PDF_GLWADS_DKDpi_KSKpi_DCPV(config cObs, config cErr, config cCor, ParametersAbs* pars, TString d)
: PDF_GLWADS_DKDpi_KSKpi(cObs,cErr,cCor,pars,d)
{
	if ( ! ( cObs==lumi3fb && cErr==lumi3fb && cCor==lumi3fb ) ){
		cout << "PDF_GLWADS_DKDpi_KSKpi_DCPV() : WARNING : This PDF only makes sense for the full K*K dalitz plot." << endl;
	}
  name = "glwadsDkdpiKSKpiDCPV";
  initParameters();
  initRelations();
  // initObservables();
  // setObservables(cObs);
  // setUncertainties(cErr);
  // setCorrelations(cCor);
  // buildCov();
	delete pdf; // it was built already by the super class constructor
  buildPdf();
}


void PDF_GLWADS_DKDpi_KSKpi_DCPV::initParameters()
{
  parameters->add(*(p->get("AcpDzKstpKm")));
  parameters->add(*(p->get("AcpDzKstmKp")));
}


void PDF_GLWADS_DKDpi_KSKpi_DCPV::initRelations()
{
  theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  RooArgSet *p = (RooArgSet*)parameters;
  theory->add(*(new RooFormulaVar("rfavsup_dpi_kskpi_th", "rfavsup_dpi_kskpi_th", "(1 + r_dpi^2*rD_kskpi^2 + 2*r_dpi*rD_kskpi*kD_kskpi*cos(g)*cos(d_dpi-dD_kskpi))         /(r_dpi^2 + rD_kskpi^2   + 2*r_dpi*rD_kskpi*kD_kskpi*cos(g)*cos(d_dpi+dD_kskpi))", *p)));
  theory->add(*(new RooFormulaVar("rfav_dkdpi_kskpi_th",  "rfav_dkdpi_kskpi_th",  "RBRdkdpi*(1 + r_dk^2*rD_kskpi^2  + 2*r_dk *rD_kskpi*kD_kskpi*cos(g)*cos(d_dk -dD_kskpi))/(1 + r_dpi^2*rD_kskpi^2 + 2*r_dpi*rD_kskpi*kD_kskpi*cos(g)*cos(d_dpi-dD_kskpi))", *p)));  
  theory->add(*(new RooFormulaVar("rsup_dkdpi_kskpi_th",  "rsup_dkdpi_kskpi_th",  "RBRdkdpi*(r_dk^2 + rD_kskpi^2    + 2*r_dk *rD_kskpi*kD_kskpi*cos(g)*cos(d_dk +dD_kskpi))/(r_dpi^2 + rD_kskpi^2   + 2*r_dpi*rD_kskpi*kD_kskpi*cos(g)*cos(d_dpi+dD_kskpi))", *p)));  
  theory->add(*(new RooFormulaVar("afav_dk_kskpi_th",     "afav_dk_kskpi_th",     "2*r_dk *rD_kskpi*kD_kskpi*sin(g)*sin(d_dk -dD_kskpi) / (1 + r_dk^2  * rD_kskpi^2 + 2*r_dk *rD_kskpi*kD_kskpi*cos(g)*cos(d_dk -dD_kskpi)) + AcpDzKstpKm", *p))); // SS
  theory->add(*(new RooFormulaVar("asup_dk_kskpi_th",     "asup_dk_kskpi_th",     "2*r_dk *rD_kskpi*kD_kskpi*sin(g)*sin(d_dk +dD_kskpi) / (r_dk^2  + rD_kskpi^2 + 2*r_dk *rD_kskpi*kD_kskpi*cos(g)*cos(d_dk +dD_kskpi))     + AcpDzKstmKp", *p))); // OS
  theory->add(*(new RooFormulaVar("afav_dpi_kskpi_th",    "afav_dpi_kskpi_th",    "2*r_dpi*rD_kskpi*kD_kskpi*sin(g)*sin(d_dpi-dD_kskpi) / (1 + r_dpi^2 * rD_kskpi^2 + 2*r_dpi*rD_kskpi*kD_kskpi*cos(g)*cos(d_dpi-dD_kskpi)) + AcpDzKstpKm", *p)));
  theory->add(*(new RooFormulaVar("asup_dpi_kskpi_th",    "asup_dpi_kskpi_th",    "2*r_dpi*rD_kskpi*kD_kskpi*sin(g)*sin(d_dpi+dD_kskpi) / (r_dpi^2 + rD_kskpi^2 + 2*r_dpi*rD_kskpi*kD_kskpi*cos(g)*cos(d_dpi+dD_kskpi))     + AcpDzKstmKp", *p)));
}
