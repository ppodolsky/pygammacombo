/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Sep 2014
 *
 **/

#ifndef PDF_GLWADS_DKDpi_KSKpi_DCPV_h
#define PDF_GLWADS_DKDpi_KSKpi_DCPV_h

#include "PDF_GLWADS_DKDpi_KSKpi.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// The B->DK/Dpi, D->KSKpi GLS measurement, 7 observables, no D mixing,
/// added direct CP violation
///
class PDF_GLWADS_DKDpi_KSKpi_DCPV : public PDF_GLWADS_DKDpi_KSKpi
{
public:
  PDF_GLWADS_DKDpi_KSKpi_DCPV(config cObs=lumi1fb, config cErr=lumi1fb, config cCor=lumi1fb, ParametersAbs* pars=0, TString d=".");
  virtual void  initParameters();
  virtual void  initRelations();
};

#endif
