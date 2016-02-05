/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: July 2014
 *
 **/

#ifndef PDF_GLWADS_DK_KSKpi_DCPV_Dmix_h
#define PDF_GLWADS_DK_KSKpi_DCPV_Dmix_h

#include "PDF_GLWADS_DK_KSKpi_DCPV.h"
#include "PDF_GLWADS_DK_KSKpi.h"
#include "RooGLWADSDmixRADSVar.h"
#include "RooGLWADSDmixAcpVar.h"
#include "RooGLWADSDmixAcpADSVar.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// The B->DK part of the B->DK, D->KSKpi GLW/ADS measurement, with D CP violation, 
/// with D mixing.
///
class PDF_GLWADS_DK_KSKpi_DCPV_Dmix : public PDF_GLWADS_DK_KSKpi_DCPV
{
public:
  PDF_GLWADS_DK_KSKpi_DCPV_Dmix(config cObs=lumi3fb, config cErr=lumi3fb, config cCor=lumi3fb, 
    double Mxy=0, ParametersAbs* pars=0, TString d=".");  
  ~PDF_GLWADS_DK_KSKpi_DCPV_Dmix();
  virtual void  initParameters();
  virtual void  initRelations();

private:
  double _Mxy;
};

#endif
