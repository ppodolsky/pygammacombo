/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#ifndef PDF_D_K3pi_h
#define PDF_D_K3pi_h

#include "TFile.h"
#include "RooHistPdf.h"
#include "RooHistPdfVar.h"
#include "RooHistPdfAngleVar.h"
#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// The measurement of the D->Kpipipi coherence factor, rD and dD. This
/// implementation ignores D mixing, but uses the CLEO likelihood profile
/// for kappa and dD.
///
class PDF_D_K3pi : public PDF_Abs
{
public:
  PDF_D_K3pi(config cObs=belle2005cleo2009, config cErr=belle2005cleo2009, config cCor=belle2005cleo2009, 
    config cType=useHistogram, config cUseKdDdK3pi=zero, TString d=".");
  ~PDF_D_K3pi();
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
  config        cUseKdDdK3pi;
  TString       dir;
};

#endif
