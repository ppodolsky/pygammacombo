/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 * Combine the DK observables from the D->K3pi ADS measurement.
 *
 **/

#ifndef PDF_GLWADS_DK_K3pi_h
#define PDF_GLWADS_DK_K3pi_h

#include "TFile.h"

#include "PDF_GLWADS_DKDpi_K3pi.h"
#include "RooAdsCartCoordVar.h"
#include "SystCor_K3pi.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

class PDF_GLWADS_DK_K3pi : public PDF_GLWADS_DKDpi_K3pi
{
public:
  PDF_GLWADS_DK_K3pi(config cObs=lumi1fb, config cErr=lumi1fb, config cCor=lumi1fb, ParametersAbs* pars=0, TString d=".");
  ~PDF_GLWADS_DK_K3pi();
  void          initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  void          setUncertainties(config c);
};

#endif
