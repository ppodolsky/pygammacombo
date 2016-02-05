/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: June 2014
 *
 **/

#ifndef PDF_GGSZ_DPI_h
#define PDF_GGSZ_DPI_h

#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"
#include "TFile.h"
#include "RooMinuit.h"
#include "RooNLLVar.h"
#include "rdtsc.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

class PDF_GGSZ_Dpi : public PDF_Abs
{
public:
  PDF_GGSZ_Dpi(config cObs=lumi3fb, config cErr=lumi3fb, config cCor=lumi3fb, ParametersAbs* pars=0);
  ~PDF_GGSZ_Dpi();
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
