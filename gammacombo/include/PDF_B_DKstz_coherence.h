/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Sep 2013
 *
 * B Coherence factor in B0 -> D0 K*0
 *
 **/

#ifndef PDF_B_DKstz_coherence_h
#define PDF_B_DKstz_coherence_h

#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

class PDF_B_DKstz_coherence : public PDF_Abs
{
public:
  PDF_B_DKstz_coherence(config cObs=hfag);
  ~PDF_B_DKstz_coherence();
  void          buildPdf();
  void          initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  void          setCorrelations(config c);
  void          setObservables(config c);
  void          setUncertainties(config c);
};

#endif
