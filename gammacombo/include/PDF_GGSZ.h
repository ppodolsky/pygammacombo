/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#ifndef PDF_GGSZ_h
#define PDF_GGSZ_h

#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"
#include "TFile.h"
#include "RooMinuit.h"
#include "RooNLLVar.h"
#include "rdtsc.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

class PDF_GGSZ : public PDF_Abs
{
public:
  PDF_GGSZ(config cObs=lumi1fb, config cErr=lumi1fb, config cCor=lumi1fb, ParametersAbs* pars=0);
  ~PDF_GGSZ();
  void          buildPdf();
  void          initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  void          setCorrelations(config c);
  void          setObservables(config c);
  void          setUncertainties(config c);

private:
  ParametersAbs*  p;        // keeps definions of the fit parameters of the project  
};

#endif
