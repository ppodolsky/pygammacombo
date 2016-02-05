/**
 * Author: Matthew Kenzie (matthew.kenzie@cern.ch)
 * Date: June 2015
 *
 * Class to describe observed measurements in
 * GLW decays which measure only 4 variables
 * e.g. ala BaBar GLW analyses which measure A_{CP+/-}, R_{CP+/-}
 *
 **/

#ifndef PDF_GLW_DKst_4var_h
#define PDF_GLW_DKst_4var_h

#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

class PDF_GLW_DKst_4var : public PDF_Abs
{
public:
  PDF_GLW_DKst_4var(config cObs=lumi1fb, config cErr=lumi1fb, config cCor=lumi1fb);
  ~PDF_GLW_DKst_4var();
  void          buildPdf();
  void          initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  void          setCorrelations(config c);
  void          setObservables(config c);
  void          setUncertainties(config c);
};

#endif
