/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Jul 2014
 *
 * The DKpipi part of the Dhpipi GLWADS measurement.
 *
 **/

#ifndef PDF_GLWADS_DKpipi_hh_h
#define PDF_GLWADS_DKpipi_hh_h

#include "PDF_GLWADS_Dhpipi_hh.h"
#include "PDF_Abs.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// The B->DKpipi, D->hh, GLW/ADS measurement: B->DKpipi, with D->Kpi, piK, pipi, KK,
/// 6 observables, no D mixing.
///
class PDF_GLWADS_DKpipi_hh : public PDF_Abs
{
	public:
		PDF_GLWADS_DKpipi_hh(config cObs=lumi3fb, config cErr=lumi3fb, config cCor=lumi3fb);
		~PDF_GLWADS_DKpipi_hh();
		void          buildPdf();
		void          initObservables();
		virtual void  initParameters();
		virtual void  initRelations();
		void          setCorrelations(config c);
		void          setObservables(config c);
		void          setUncertainties(config c);

	protected:
		ParametersAbs*  p;        // keeps definions of the fit parameters of the project

	private:
		vector<int> 	indicesDKDpi;
};

#endif
