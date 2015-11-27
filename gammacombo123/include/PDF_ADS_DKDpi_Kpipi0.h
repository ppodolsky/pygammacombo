/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2014
 *
 **/

#ifndef PDF_ADS_DKDpi_Kpipi0_h
#define PDF_ADS_DKDpi_Kpipi0_h

#include "TFile.h"
#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// The Kpipi0 part from the 2012 hhpi0 GLW/ADS measurement.
///
class PDF_ADS_DKDpi_Kpipi0 : public PDF_Abs
{
public:
  PDF_ADS_DKDpi_Kpipi0(config cObs=lumi3fb, config cErr=lumi3fb, config cCor=lumi3fb, ParametersAbs* pars=0, TString d=".");
  ~PDF_ADS_DKDpi_Kpipi0();
  void          buildPdf();
  void          initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  void          setCorrelations(config c);
  void          setObservables(config c);
  void          setUncertainties(config c);

protected:
  PDF_ADS_DKDpi_Kpipi0(ParametersAbs* pars, TString d, int nObs);
  TString         dir;
  ParametersAbs*  p;        // keeps definions of the fit parameters of the project
};

#endif
