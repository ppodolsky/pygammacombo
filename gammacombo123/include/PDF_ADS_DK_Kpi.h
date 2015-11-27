/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#ifndef PDF_ADS_DK_Kpi_h
#define PDF_ADS_DK_Kpi_h

#include "PDF_Abs.h"
#include "RooAdsCartCoordVar.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

class PDF_ADS_DK_Kpi : public PDF_Abs
{
public:
  PDF_ADS_DK_Kpi(config cObs=lumi1fb, config cErr=lumi1fb, config cCor=lumi1fb, config cTrad=zero);
  ~PDF_ADS_DK_Kpi();
  void          buildPdf();
  void          initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  void          setCorrelations(config c);
  void          setObservables(config c);
  void          setUncertainties(config c);

  config cTrad;
};

#endif
