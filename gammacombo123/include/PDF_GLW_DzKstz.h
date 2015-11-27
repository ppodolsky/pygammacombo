/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#ifndef PDF_GLW_DZKSTZ_h
#define PDF_GLW_DZKSTZ_h

#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

class PDF_GLW_DzKstz : public PDF_Abs
{
public:
  PDF_GLW_DzKstz(config cObs=lumi1fb, config cErr=lumi1fb, config cCor=lumi1fb);
  ~PDF_GLW_DzKstz();
  void          buildPdf();
  void          initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  void          setCorrelations(config c);
  void          setObservables(config c);
  void          setUncertainties(config c);
};

#endif
