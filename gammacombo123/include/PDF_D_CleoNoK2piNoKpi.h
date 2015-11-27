/**
 * Gamma Combination
 *
 * The Cleo measurement reduced to the K3pi part.
 *
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#ifndef PDF_D_CleoNoK2piNoKpi_h
#define PDF_D_CleoNoK2piNoKpi_h

#include "TFile.h"
#include "TMatrixDSym.h"
#include "RooHistPdf.h"

#include "RooHistPdfVar.h"
#include "RooHistPdfAngleVar.h"
#include "PDF_Abs.h"
#include "PDF_D_Cleo.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

class PDF_D_CleoNoK2piNoKpi : public PDF_D_Cleo
{
public:
  PDF_D_CleoNoK2piNoKpi(config cObs=cleo, config cType=useGaussian, config cUseKdDdK3pi=zero, TString d=".");
  ~PDF_D_CleoNoK2piNoKpi();
  virtual void  initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  virtual void  setCorrelations(config c);
  virtual void  setObservables(config c);
  virtual void  setUncertainties(config c);
};

#endif
