/**
 * Gamma Combination
 * Author: Matthew Kenzie, matthew.kenzie@cern.ch
 * Date: Sep 2015
 *
 **/

#ifndef PDF_D_Cleo_Full_h
#define PDF_D_Cleo_Full_h

#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// The HFAG charm fit, restricted to observables that we also
/// have in the gamma combination.
///
class PDF_D_Cleo_Full : public PDF_Abs
{
public:
  PDF_D_Cleo_Full(config cObs=cleo2014, config cErr=cleo2014, config cCor=cleo2014);
  ~PDF_D_Cleo_Full();
  void          buildPdf();
  void          initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  void          setCorrelations(config c);
  void          setObservables(config c);
  void          setUncertainties(config c);
};

#endif
