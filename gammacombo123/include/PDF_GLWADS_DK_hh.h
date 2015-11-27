/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 * Combine only the DK observables from 13 observables from the 
 * two body GLW/ADS measurement.
 *
 **/

#ifndef PDF_GLWADS_DK_hh_h
#define PDF_GLWADS_DK_hh_h

#include "TFile.h"
#include "PDF_GLWADS_DKDpi_hh.h"
#include "SystCor_Kpi.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

class PDF_GLWADS_DK_hh : public PDF_GLWADS_DKDpi_hh
{
	public:
		PDF_GLWADS_DK_hh(config cObs=lumi1fb, config cErr=lumi1fb, config cCor=lumi1fb, ParametersAbs* pars=0, TString d=".");
		~PDF_GLWADS_DK_hh();
		void          initObservables();
		virtual void  initParameters();
		virtual void  initRelations();
		void          setUncertainties(config c);
};

#endif
