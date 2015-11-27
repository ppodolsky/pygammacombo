/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Sep 2014
 *
 **/

#ifndef PDF_GLWADS_DK_KSKpi_DCPV_h
#define PDF_GLWADS_DK_KSKpi_DCPV_h

#include "PDF_GLWADS_DK_KSKpi.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// The B->DK part of the B->DK, D->KSKpi GLW/ADS measurement, 
/// with D CP violation, no D mixing.
///
class PDF_GLWADS_DK_KSKpi_DCPV : public PDF_GLWADS_DK_KSKpi
{
public:
  PDF_GLWADS_DK_KSKpi_DCPV(config cObs=lumi1fb, config cErr=lumi1fb, config cCor=lumi1fb, ParametersAbs* pars=0, TString d=".");
  ~PDF_GLWADS_DK_KSKpi_DCPV();
  virtual void  initParameters();
  virtual void  initRelations();
};

#endif
