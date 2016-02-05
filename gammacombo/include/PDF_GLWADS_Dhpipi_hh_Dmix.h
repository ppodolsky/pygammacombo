/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Dec 2013
 *
 **/

#ifndef PDF_GLWADS_Dhpipi_hh_Dmix_h
#define PDF_GLWADS_Dhpipi_hh_Dmix_h

#include "PDF_GLWADS_Dhpipi_hh.h"
#include "RooGLWADSDmixAcpVar.h"
#include "RooGLWADSDmixRpmVar.h"
#include "RooGLWADSDmixRkpVar.h"
#include "RooGLWADSDmixRcpVar.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// The B->Dh, D->hh, GLW/ADS measurement: B->DKpipi and B->Dpipipi, with D->Kpi, piK, pipi, KK,
/// 11 observables, added D mixing.
///
class PDF_GLWADS_Dhpipi_hh_Dmix : public PDF_GLWADS_Dhpipi_hh
{
public:
  PDF_GLWADS_Dhpipi_hh_Dmix(config cObs=lumi1fb, config cErr=lumi1fb, config cCor=lumi1fb, 
    double Mxy=0, ParametersAbs* pars=0, TString d=".");
  ~PDF_GLWADS_Dhpipi_hh_Dmix();
  void        initParameters();
  void        initRelations();

private:
  double _Mxy;
};

#endif
