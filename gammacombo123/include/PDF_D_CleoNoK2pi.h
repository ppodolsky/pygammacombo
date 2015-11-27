/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#ifndef PDF_D_CleoNoK2pi_h
#define PDF_D_CleoNoK2pi_h

#include "TFile.h"
#include "TMatrixDSym.h"
#include "RooHistPdf.h"

#include "RooHistPdfVar.h"
#include "PDF_Abs.h"
#include "PDF_D_Cleo.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

class PDF_D_CleoNoK2pi : public PDF_D_Cleo
{
public:
  PDF_D_CleoNoK2pi(config cObs=cleo, config cType=useGaussian, ParametersAbs* pars=0, config cUseKdDdK3pi=zero, TString d=".");
  ~PDF_D_CleoNoK2pi();
  virtual void  initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  virtual void  setCorrelations(config c);
  virtual void  setObservables(config c);
  virtual void  setUncertainties(config c);

private:
  ParametersAbs*  p;        // keeps definions of the fit parameters of the project
};

#endif
