/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#ifndef PDF_ADS_Dpi_K3pi_h
#define PDF_ADS_Dpi_K3pi_h

#include "PDF_Abs.h"
#include "RooAdsCartCoordVar.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

class PDF_ADS_Dpi_K3pi : public PDF_Abs
{
public:
  PDF_ADS_Dpi_K3pi(config cObs=lumi1fb, config cErr=lumi1fb, config cCor=lumi1fb);
  ~PDF_ADS_Dpi_K3pi();
  void          buildPdf();
  void          initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  void          setCorrelations(config c);
  void          setObservables(config c);
  void          setUncertainties(config c);
};

#endif
