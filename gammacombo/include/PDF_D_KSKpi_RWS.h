/**
 * Gamma Combination
 * Author: Matthew Kenzie, matthew.kenzie@cern.ch
 * Date: January 2016
 *
 **/

#ifndef PDF_D_KSKpi_RWS_h
#define PDF_D_KSKpi_RWS_h

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
class PDF_D_KSKpi_RWS : public PDF_Abs
{
public:
  PDF_D_KSKpi_RWS(config cObs=lhcb, config cErr=lhcb, config cCor=lhcb);
  ~PDF_D_KSKpi_RWS();
  void          initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  void          setCorrelations(config c);
  void          setObservables(config c);
  void          setUncertainties(config c);
  void          buildPdf();

};

#endif
