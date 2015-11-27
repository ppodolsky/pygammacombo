/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#ifndef PDF_D_KstK_DCPV_h
#define PDF_D_KstK_DCPV_h

#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// CP violation in D0->KstK decays.
///
class PDF_D_KstK_DCPV : public PDF_Abs
{
public:
  PDF_D_KstK_DCPV(config cObs=babar2008, config cErr=babar2008, config cCor=babar2008);
  ~PDF_D_KstK_DCPV();
  void          buildPdf();
  void          initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  void          setCorrelations(config c);
  void          setObservables(config c);
  void          setUncertainties(config c);
};

#endif
