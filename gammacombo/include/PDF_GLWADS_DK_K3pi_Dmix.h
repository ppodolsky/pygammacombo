/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#ifndef PDF_GLWADS_DK_K3pi_Dmix_h
#define PDF_GLWADS_DK_K3pi_Dmix_h

#include "TFile.h"

#include "PDF_GLWADS_DK_K3pi.h"
#include "RooGLWADSDmixAcpVar.h"
#include "RooGLWADSDmixRpmVar.h"
#include "RooGLWADSDmixRkpVar.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// The DK observables from the D->K3pi ADS measurement, including
/// corrections for D-Db mixing.
///
class PDF_GLWADS_DK_K3pi_Dmix : public PDF_GLWADS_DK_K3pi
{
public:
  PDF_GLWADS_DK_K3pi_Dmix(config cObs=lumi1fb, config cErr=lumi1fb, config cCor=lumi1fb, 
    double Mxy=0, ParametersAbs* pars=0, TString d=".");
  ~PDF_GLWADS_DK_K3pi_Dmix();
  void        initParameters();
  void        initRelations();

private:
  double _Mxy;
};

#endif
