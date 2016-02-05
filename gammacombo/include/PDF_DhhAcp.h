/*
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 */

#ifndef PDF_DhhAcp_h
#define PDF_DhhAcp_h

#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// PDF that constrains the direct CP violation in D->hh decays
/// by using the direct measurements of Acp(KK) and Acp(pipi)
/// rather than the knowledge on Acp(KK)-Acp(pipi).
///
class PDF_DhhAcp : public PDF_Abs
{
public:
  PDF_DhhAcp(config cObs=hfag, ParametersAbs* pars=0);
  ~PDF_DhhAcp();
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
