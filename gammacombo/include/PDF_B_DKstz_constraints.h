/**
 * Gamma Combination
 * Author: Matthew Kenzie matthew.kenzie@cern.ch
 * Date: Dec 2015
 *
 * B Coherence factor, RB and DeltadeltaB in B0 -> D0 K*0
 *
 **/

#ifndef PDF_B_DKstz_constraints_h
#define PDF_B_DKstz_constraints_h

#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

class PDF_B_DKstz_constraints : public PDF_Abs
{
public:
  PDF_B_DKstz_constraints(config cObs=lhcb, config cErr=lhcb, config cCor=lhcb);
  ~PDF_B_DKstz_constraints();
  void          buildPdf();
  void          initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  void          setCorrelations(config c);
  void          setObservables(config c);
  void          setUncertainties(config c);
};

#endif
