/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#ifndef PDF_GGSZ_ExpNLL_h
#define PDF_GGSZ_ExpNLL_h

#include "TFile.h"
#include "RooHistPdf.h"
#include "RooPolyVar.h"
#include "RooBifurGauss.h"
#include "RooMinuit.h"
#include "RooNLLVar.h"

#include "PDF_Abs.h"
#include "PDF_GGSZ.h"
#include "RooHistPdfVar.h"
#include "RooPoly3Var.h"
#include "RooPoly4Var.h"
//#include "RooHistInterpol_Dict.h"
#include "RooBinned2DBicubicBase.h"
#include "rdtsc.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

class PDF_GGSZ_ExpNLL : public PDF_GGSZ
{
public:
  PDF_GGSZ_ExpNLL(config cObs=lumi1fb, config cType=useParametric, TString d=".");
  void buildPdf();
  void buildPdfHistogram();
  void buildPdfParametric();
  void buildPdfBicubic();

  RooRealVar *xm_obs;
  RooRealVar *xm_th ;
  RooRealVar *ym_obs;
  RooRealVar *ym_th ;
  RooRealVar *xp_obs;
  RooRealVar *xp_th ;
  RooRealVar *yp_obs;
  RooRealVar *yp_th ;

  TString dir;
  config cType;
};

#endif
