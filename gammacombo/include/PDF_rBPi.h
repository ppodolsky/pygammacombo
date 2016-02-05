/**
 * Gamma Combination
 * Author: Matt Kenzie
 * Date: September 2015
 *
 * A constraint on rB from Niels
 *
 **/

#ifndef PDF_rBPi_h
#define PDF_rBPi_h

#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

class PDF_rBPi : public PDF_Abs
{
public:
  PDF_rBPi(config cObs=manual, config cErr=manual, config cCor=manual);
  ~PDF_rBPi();
  void          buildPdf();
  void          initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  void          setCorrelations(config c);
  void          setObservables(config c);
  void          setUncertainties(config c);
};

#endif
