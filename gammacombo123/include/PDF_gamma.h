/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Nov 2014
 *
 **/

#ifndef PDF_gamma_h
#define PDF_gamma_h

#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

class PDF_gamma : public PDF_Abs
{
public:
  PDF_gamma(config cObs=year2014, config cErr=year2014, config cCor=year2014);
  ~PDF_gamma();
  void          buildPdf();
  void          initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  void          setCorrelations(config c);
  void          setObservables(config c);
  void          setUncertainties(config c);
};

#endif
