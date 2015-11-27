/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#ifndef PDF_D_KSKpi_h
#define PDF_D_KSKpi_h

#include "PDF_Abs.h"
#include "TFile.h"
#include "RooHistPdf.h"
#include "RooHistPdfVar.h"
#include "RooHistPdfAngleVar.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// The measurement of the D->KSKpi coherence factor, rD and dD.
///
class PDF_D_KSKpi : public PDF_Abs
{
public:
  PDF_D_KSKpi(config cObs=cleo, config cErr=cleo, config cCor=cleo, 
    config cType=useGaussian, TString d=".");
  ~PDF_D_KSKpi();
  void          buildPdf();
  void          initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  void          setCorrelations(config c);
  void          setObservables(config c);
  void          setUncertainties(config c);

protected:
	void          buildPdfGaus();
  void          buildPdfHistogram(TString fName, float scale, float kDobs, float dDobs);        
  config        cType;
  config        cObs;
  TString       dir;
};

#endif
