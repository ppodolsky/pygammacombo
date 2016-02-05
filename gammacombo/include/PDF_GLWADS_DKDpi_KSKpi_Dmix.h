/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Dec 2013
 *
 **/

#ifndef PDF_GLWADS_DKDpi_KSKpi_Dmix_h
#define PDF_GLWADS_DKDpi_KSKpi_Dmix_h

#include "TFile.h"

#include "PDF_GLWADS_DKDpi_KSKpi.h"
#include "RooGLWADSDmixRADSVar.h"
#include "RooGLWADSDmixAcpVar.h"
#include "RooGLWADSDmixAcpADSVar.h"
#include "RooGLWADSDmixRkpVar.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// The D->KSKpi GLW/ADS measurement, 7 observables, added D mixing.
///
class PDF_GLWADS_DKDpi_KSKpi_Dmix : public PDF_GLWADS_DKDpi_KSKpi
{
public:
  PDF_GLWADS_DKDpi_KSKpi_Dmix(config cObs=lumi3fb, config cErr=lumi3fb, config cCor=lumi3fb, 
    double Mxy=0, ParametersAbs* pars=0, TString d=".");
  ~PDF_GLWADS_DKDpi_KSKpi_Dmix();
  void        initParameters();
  void        initRelations();

private:
  double _Mxy;
};

#endif
