/**
 * Gamma Combination
 * Author: Matthew Kenzie matthew.kenzie@cern.ch
 * Date: Jan 2016
 *
 * coherence factor, phase and ratio for D->K3pi and D->K2pi decays
 *
 **/

#ifndef PDF_D_K3pi_Kpipi0_6D_h
#define PDF_D_K3pi_Kpipi0_6D_h

#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

class PDF_D_K3pi_Kpipi0_6D : public PDF_Abs
{
public:
  PDF_D_K3pi_Kpipi0_6D(config cObs=lhcb, config cErr=lhcb, config cCor=lhcb);
  ~PDF_D_K3pi_Kpipi0_6D();
  void          buildPdf();
  void          initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  void          setCorrelations(config c);
  void          setObservables(config c);
  void          setUncertainties(config c);
};

#endif
