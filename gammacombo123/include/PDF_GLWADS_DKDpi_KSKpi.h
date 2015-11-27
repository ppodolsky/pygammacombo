/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#ifndef PDF_GLWADS_DKDpi_KSKpi_h
#define PDF_GLWADS_DKDpi_KSKpi_h

#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// The B->DK/Dpi, D->KSKpi GLW/ADS measurement, 7 observables, no D mixing.
///
class PDF_GLWADS_DKDpi_KSKpi : public PDF_Abs
{
public:
  PDF_GLWADS_DKDpi_KSKpi(config cObs=lumi1fb, config cErr=lumi1fb, config cCor=lumi1fb, ParametersAbs* pars=0, TString d=".");
  ~PDF_GLWADS_DKDpi_KSKpi();
  void          buildPdf();
  void          initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  void          setCorrelations(config c);
  void          setObservables(config c);
  void          setUncertainties(config c);

protected:
  TString         dir;
  ParametersAbs*  p;        // keeps definions of the fit parameters of the project
};

#endif
