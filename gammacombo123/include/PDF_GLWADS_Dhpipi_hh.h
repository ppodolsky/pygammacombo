/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Feb 2014
 *
 * The old version with 13 observables (Rkp's instead of Rcp+)
 * is in src/PDF_GLWADS_Dhpipi_hh_13.* .
 *
 **/

#ifndef PDF_GLWADS_Dhpipi_hh_h
#define PDF_GLWADS_Dhpipi_hh_h

#include "TFile.h"
#include "TMatrixD.h"
#include "PDF_Abs.h"
#include "RooAdsCartCoordVar.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// The B->Dhpipi, D->hh, GLW/ADS measurement: B->DKpipi and B->Dpipipi, with D->Kpi, piK, pipi, KK,
/// 11 observables, no D mixing.
///
class PDF_GLWADS_Dhpipi_hh : public PDF_Abs
{
public:
  PDF_GLWADS_Dhpipi_hh(config cObs=lumi3fb, config cErr=lumi3fb, config cCor=lumi3fb, ParametersAbs* pars=0, TString d=".");
  ~PDF_GLWADS_Dhpipi_hh();
  void          buildPdf();
  void          initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  void          setCorrelations(config c);
  void          setObservables(config c);
  void          setUncertainties(config c);

protected:
  PDF_GLWADS_Dhpipi_hh(ParametersAbs* pars, TString d, int nObs);
  TString         dir;
  ParametersAbs*  p;        // keeps definions of the fit parameters of the project
};

#endif
