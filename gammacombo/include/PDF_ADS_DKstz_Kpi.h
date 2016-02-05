/**
 * Gamma Combination
 * Author: Matthew Kenzie matthew.kenzie@cern.ch
 * Date: November 2015
 *
 **/

#ifndef PDF_ADS_DKstz_Kpi_h
#define PDF_ADS_DKstz_Kpi_h

#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// The B0 -> D0 K*0 ADS measurement only.
///
class PDF_ADS_DKstz_Kpi : public PDF_Abs
{
public:
  PDF_ADS_DKstz_Kpi(config cObs=lumi1fb, config cErr=lumi1fb, config cCor=lumi1fb, ParametersAbs* pars=0, TString d=".");
  ~PDF_ADS_DKstz_Kpi();
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
