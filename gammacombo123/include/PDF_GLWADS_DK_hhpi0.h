/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Jan 2015
 *
 **/

#ifndef PDF_GLWADS_DK_hhpi0_h
#define PDF_GLWADS_DK_hhpi0_h

#include "TFile.h"
#include "TMatrixD.h"
#include "PDF_Abs.h"
#include "RooAdsCartCoordVar.h"
#include "ParametersGammaCombo.h"
#include "PDF_GLWADS_DKDpi_hhpi0.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// The B->DK, D->hhpi0, GLW/ADS measurement: B->DK and B->Dpi, with D->KKpi0, pipipi0, Kpipi0, piKpi0
///
class PDF_GLWADS_DK_hhpi0 : public PDF_Abs
{
	public:
		PDF_GLWADS_DK_hhpi0(config cObs=lumi3fb, config cErr=lumi3fb, config cCor=lumi3fb, ParametersAbs* pars=0);
		~PDF_GLWADS_DK_hhpi0();
		void          buildPdf();
		void          initObservables();
		virtual void  initParameters();
		virtual void  initRelations();
		void          setCorrelations(config c);
		void          setObservables(config c);
		void          setUncertainties(config c);

	protected:
		PDF_GLWADS_DK_hhpi0(ParametersAbs* pars, int nObs);
		ParametersAbs*  p;        // keeps definions of the fit parameters of the project

	private:
		vector<int> 	indicesDKDpi;
};

#endif
