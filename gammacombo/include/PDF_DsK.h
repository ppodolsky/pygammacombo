/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#ifndef PDF_DsK_h
#define PDF_DsK_h

#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

class PDF_DsK : public PDF_Abs
{
public:
  PDF_DsK(config cObs=lumi1fbPapercFit, config cErr=lumi1fbPapercFit, config cCor=lumi1fbPapercFit);
  ~PDF_DsK();
  void          buildPdf();
  void          initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  void          setCorrelations(TMatrixDSym &c, config systCor=zero);
  void          setCorrelations(config c);
  void          setObservables(float c, float d, float db, float s, float sb, float phis_obs = -0.002);
  void          setObservables(config c);
  void          setUncertainties(config c);
  void          setErrors(float ec, float ed, float edb, float es, float esb, float ephis_obs = 0.087, config systErr=zero);
};

#endif
