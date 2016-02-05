/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Nov 2014
 *
 * Combine all 13 observables from the GLW/ADS measurement.
 *
 **/

#ifndef PDF_GLWADS_DKDpi_hh_2012_h
#define PDF_GLWADS_DKDpi_hh_2012_h

#include "TFile.h"
#include "TMatrixD.h"
#include "PDF_Abs.h"
#include "RooAdsCartCoordVar.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// The B->Dh, D->hh, GLW/ADS measurement: B->DK and B->Dpi, with D->Kpi, piK, pipi, KK.
///
class PDF_GLWADS_DKDpi_hh_2012 : public PDF_Abs
{
	public:
		PDF_GLWADS_DKDpi_hh_2012(config cObs=lumi3fb, config cErr=lumi3fb, config cCor=lumi3fb, ParametersAbs* pars=0);
		~PDF_GLWADS_DKDpi_hh_2012();
		void          buildPdf();
		void          initObservables();
		virtual void  initParameters();
		virtual void  initRelations();
		void          setCorrelations(config c);
		void          setObservables(config c);
		void          setUncertainties(config c);

	protected:
		PDF_GLWADS_DKDpi_hh_2012(ParametersAbs* pars, int nObs);
		ParametersAbs*  p;        // keeps definions of the fit parameters of the project
};

#endif
