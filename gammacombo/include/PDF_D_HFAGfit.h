/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: July 2014
 *
 **/

#ifndef PDF_D_HFAGfit_h
#define PDF_D_HFAGfit_h

#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// The HFAG charm fit, restricted to observables that we also
/// have in the gamma combination.
///
class PDF_D_HFAGfit : public PDF_Abs
{
public:
  PDF_D_HFAGfit(config cObs=hfagFP2014, config cErr=hfagFP2014, config cCor=hfagFP2014);
  ~PDF_D_HFAGfit();
  void          buildPdf();
  void          initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  void          setCorrelations(config c);
  void          setObservables(config c);
  void          setUncertainties(config c);
};

#endif
