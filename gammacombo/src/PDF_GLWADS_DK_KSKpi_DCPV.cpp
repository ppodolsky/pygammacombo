/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: July 2014
 *
 **/

#include "PDF_GLWADS_DK_KSKpi_DCPV.h"

PDF_GLWADS_DK_KSKpi_DCPV::PDF_GLWADS_DK_KSKpi_DCPV(config cObs, config cErr, config cCor, ParametersAbs* pars, TString d)
: PDF_GLWADS_DK_KSKpi(cObs,cErr,cCor,pars,d)
{
	if ( ! ( cObs==lumi3fb && cErr==lumi3fb && cCor==lumi3fb ) ){
		cout << "PDF_GLWADS_DK_KSKpi() : WARNING : This PDF only makes sense for the full K*K dalitz plot." << endl;
	}
  name = "glwadsDkKSKpiDCPV";
  initParameters();
  initRelations();
	delete pdf; // it was built already by the super class constructor
  buildPdf();
}


PDF_GLWADS_DK_KSKpi_DCPV::~PDF_GLWADS_DK_KSKpi_DCPV(){}


void PDF_GLWADS_DK_KSKpi_DCPV::initParameters()
{
  parameters->add(*(p->get("AcpDzKstpKm")));
  parameters->add(*(p->get("AcpDzKstmKp")));
}  


void PDF_GLWADS_DK_KSKpi_DCPV::initRelations()
{
  theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  RooArgSet *p = (RooArgSet*)parameters;
  theory->add(*(new RooFormulaVar("rfavsup_dk_kskpi_th",  "rfavsup_dk_kskpi_th",  "(1 + r_dk^2*rD_kskpi^2  + 2*r_dk *rD_kskpi*kD_kskpi*cos(g)*cos(d_dk -dD_kskpi))/(r_dk^2 + rD_kskpi^2    + 2*r_dk *rD_kskpi*kD_kskpi*cos(g)*cos(d_dk +dD_kskpi))", *p)));  
  theory->add(*(new RooFormulaVar("afav_dk_kskpi_th",     "afav_dk_kskpi_th",     "2*r_dk *rD_kskpi*kD_kskpi*sin(g)*sin(d_dk -dD_kskpi) / (1 + r_dk^2  * rD_kskpi^2 + 2*r_dk *rD_kskpi*kD_kskpi*cos(g)*cos(d_dk -dD_kskpi)) + AcpDzKstpKm", *p)));
  theory->add(*(new RooFormulaVar("asup_dk_kskpi_th",     "asup_dk_kskpi_th",     "2*r_dk *rD_kskpi*kD_kskpi*sin(g)*sin(d_dk +dD_kskpi) / (r_dk^2  + rD_kskpi^2 + 2*r_dk *rD_kskpi*kD_kskpi*cos(g)*cos(d_dk +dD_kskpi))     + AcpDzKstmKp", *p)));
}
