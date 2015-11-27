/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: June 2014
 *
 **/

#ifndef PDF_Dmixing_xy_h
#define PDF_Dmixing_xy_h

#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// Plain and simple Gaussian constraint on the D mixing
/// parameters xD and yD, e.g. from HFAG.
///
class PDF_Dmixing_xy : public PDF_Abs
{
public:
  PDF_Dmixing_xy(config cObs=hfag, config cErr=hfag, config cCor=hfag);
  ~PDF_Dmixing_xy();
  void          buildPdf();
  void          initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  void          setCorrelations(config c);
  void          setObservables(config c);
  void          setUncertainties(config c);
};

#endif
