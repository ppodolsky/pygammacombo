/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#ifndef PDF_GLWADS_DKDpi_K3pi_h
#define PDF_GLWADS_DKDpi_K3pi_h

#include "TFile.h"

#include "PDF_Abs.h"
#include "RooAdsCartCoordVar.h"
#include "SystCor_K3pi.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// The B->DK/Dpi, D->Kpipipi GLW/ADS measurement, 7 observables, no D mixing.
///
class PDF_GLWADS_DKDpi_K3pi : public PDF_Abs
{
public:
  PDF_GLWADS_DKDpi_K3pi(config cObs=lumi1fb, config cErr=lumi1fb, config cCor=lumi1fb, ParametersAbs* pars=0, TString d=".");
  ~PDF_GLWADS_DKDpi_K3pi();
  void          buildPdf();
  void          initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  TString       obsTmkToMalcolm(TString tmkObs);
  void          setCorrelations(config c);
  void          setObservables(config c);
  void          setUncertainties(config c);

protected:
  PDF_GLWADS_DKDpi_K3pi(ParametersAbs* pars, TString d, int nObs);
  TString         dir;
  ParametersAbs*  p;        // keeps definions of the fit parameters of the project
};

#endif
