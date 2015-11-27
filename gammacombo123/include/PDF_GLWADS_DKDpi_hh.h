/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 * Combine all 13 observables from the GLW/ADS measurement.
 *
 **/

#ifndef PDF_GLWADS_DKDpi_hh_h
#define PDF_GLWADS_DKDpi_hh_h

#include "TFile.h"
#include "TMatrixD.h"
#include "PDF_Abs.h"
#include "RooAdsCartCoordVar.h"
#include "SystCor_Kpi.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// The B->Dh, D->hh, GLW/ADS measurement: B->DK and B->Dpi, with D->Kpi, piK, pipi, KK.
///
class PDF_GLWADS_DKDpi_hh : public PDF_Abs
{
	public:
		PDF_GLWADS_DKDpi_hh(config cObs=lumi1fb, config cErr=lumi1fb, config cCor=lumi1fb, ParametersAbs* pars=0, TString d=".");
		~PDF_GLWADS_DKDpi_hh();
		void          buildPdf();
		void          initObservables();
		virtual void  initParameters();
		virtual void  initRelations();
		void          setCorrelations(config c);
		void          setObservables(config c);
		void          setUncertainties(config c);

	protected:
		PDF_GLWADS_DKDpi_hh(ParametersAbs* pars, TString d, int nObs);
		TString         obsTmkToMalcolm(TString tmkObs);
		TString         dir;
		ParametersAbs*  p;        // keeps definions of the fit parameters of the project
};

#endif
