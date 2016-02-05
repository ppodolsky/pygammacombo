/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: July 2014
 *
 **/

#ifndef PDF_GLWADS_DK_KSKpi_h
#define PDF_GLWADS_DK_KSKpi_h

#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// The B->DK part of the B->DK, D->KSKpi GLW/ADS measurement, no D mixing.
///
class PDF_GLWADS_DK_KSKpi : public PDF_Abs
{
public:
  PDF_GLWADS_DK_KSKpi(config cObs=lumi1fb, config cErr=lumi1fb, config cCor=lumi1fb, ParametersAbs* pars=0, TString d=".");
  ~PDF_GLWADS_DK_KSKpi();
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
