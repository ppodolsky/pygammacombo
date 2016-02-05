/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: September 2013
 *
 **/

#ifndef PDF_GLWADS_DKstz_hh_h
#define PDF_GLWADS_DKstz_hh_h

#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// The B0 -> D0 K*0 GLW/ADS measurement.
///
class PDF_GLWADS_DKstz_hh : public PDF_Abs
{
public:
  PDF_GLWADS_DKstz_hh(config cObs=lumi1fb, config cErr=lumi1fb, config cCor=lumi1fb, ParametersAbs* pars=0, TString d=".");
  ~PDF_GLWADS_DKstz_hh();
  void          buildPdf();
  void          initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  void          setCorrelations(config c);
  void          setObservables(config c);
  void          setUncertainties(config c);
  ParametersAbs*  p;        // keeps definions of the fit parameters of the project
};

#endif
