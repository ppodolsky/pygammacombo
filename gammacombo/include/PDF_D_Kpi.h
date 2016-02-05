/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#ifndef PDF_D_Kpi_h
#define PDF_D_Kpi_h

#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

class PDF_D_Kpi : public PDF_Abs
{
public:
  PDF_D_Kpi(config cObs=hfagLP2011, config cErr=hfagLP2011, config cCor=hfagLP2011);
  ~PDF_D_Kpi();
  void          buildPdf();
  void          initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  void          setCorrelations(config c);
  void          setObservables(config c);
  void          setUncertainties(config c);
};

#endif
