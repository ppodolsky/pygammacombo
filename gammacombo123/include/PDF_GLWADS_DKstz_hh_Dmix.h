/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Jun 2014
 *
 **/

#ifndef PDF_GLWADS_DKstz_hh_Dmix_h
#define PDF_GLWADS_DKstz_hh_Dmix_h

#include "TFile.h"

#include "PDF_GLWADS_DKstz_hh.h"
#include "RooGLWADSDmixRADSVar.h"
#include "RooGLWADSDmixAcpVar.h"
#include "RooGLWADSDmixAcpADSVar.h"
#include "RooGLWADSDmixRkpVar.h"
#include "RooGLWADSDmixRpmVar.h"
#include "RooGLWADSDmixRcpVar.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// The B0 -> D0 K*0 GLW/ADS measurement, added D mixing.
///
class PDF_GLWADS_DKstz_hh_Dmix : public PDF_GLWADS_DKstz_hh
{
public:
  PDF_GLWADS_DKstz_hh_Dmix(config cObs=lumi1fb, config cErr=lumi1fb, config cCor=lumi1fb, 
    double Mxy=0, ParametersAbs* pars=0, TString d=".");
  ~PDF_GLWADS_DKstz_hh_Dmix();
  void        initParameters();
  void        initRelations();

private:
  double _Mxy;
};

#endif
