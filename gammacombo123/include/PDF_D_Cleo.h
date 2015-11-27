/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#ifndef PDF_D_Cleo_h
#define PDF_D_Cleo_h

#include "TFile.h"
#include "TMatrixDSym.h"
#include "RooHistPdf.h"
#include "RooHistPdfVar.h"
#include "RooHistPdfAngleVar.h"
#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

class PDF_D_Cleo : public PDF_Abs
{
public:
  PDF_D_Cleo(config cObs=cleo, config cType=useGaussian, config cUseKdDdK3pi=zero, TString d=".");
  ~PDF_D_Cleo();
  void          buildPdf();
  void          buildPdfHistogram();
  void          buildPdfGaus();
  virtual void  initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  virtual void  setCorrelations(config c);
  virtual void  setObservables(config c);
  virtual void  setUncertainties(config c);
  
  config cType;
  config cUseKdDdK3pi;
  TString dir;
  
protected:
  PDF_D_Cleo(config cObs, config cType, config cUseKdDdK3pi, TString d, int nObs);
  
private:
  void          constructorBody(config cObs, config cType, config cUseKdDdK3pi, TString d);
};

#endif
