/**
 * Gamma Combination
 * Author: Matthew Kenzie matthew.kenzie@cern.ch
 * Date: November 2015
 *
 **/

#ifndef PDF_ADS_DKstz_Kpi_Dmix_h
#define PDF_ADS_DKstz_Kpi_Dmix_h

#include "TFile.h"

#include "PDF_ADS_DKstz_Kpi.h"
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
/// The B0 -> D0 K*0 ADS measurement only, added D mixing.
///
class PDF_ADS_DKstz_Kpi_Dmix : public PDF_ADS_DKstz_Kpi
{
public:
  PDF_ADS_DKstz_Kpi_Dmix(config cObs=lumi1fb, config cErr=lumi1fb, config cCor=lumi1fb,
    double Mxy=0, ParametersAbs* pars=0, TString d=".");
  ~PDF_ADS_DKstz_Kpi_Dmix();
  void        initParameters();
  void        initRelations();

private:
  double _Mxy;
};

#endif
