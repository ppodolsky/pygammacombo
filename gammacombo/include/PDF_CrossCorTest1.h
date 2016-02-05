/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: July 2014
 *
 **/

#ifndef PDF_CrossCorTest1_h
#define PDF_CrossCorTest1_h

#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// A PDF to test the new cross correlation mechanism.
/// It is based on the DsK PDF, but only encodes C and S
/// parameters.
///
class PDF_CrossCorTest1 : public PDF_Abs
{
public:
  PDF_CrossCorTest1(config cObs=lumi1fbPapercFit, config cErr=lumi1fbPapercFit, config cCor=lumi1fbPapercFit);
  ~PDF_CrossCorTest1();
  void          buildPdf();
  void          initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  void          setCorrelations(config c);
  void          setObservables(config c);
  void          setUncertainties(config c);
};

#endif
