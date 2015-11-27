/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Jul 2014
 *
 **/

#ifndef PDF_GLWADS_DKpipi_hh_Dmix_h
#define PDF_GLWADS_DKpipi_hh_Dmix_h

#include "PDF_GLWADS_DKpipi_hh.h"
#include "RooGLWADSDmixAcpVar.h"
#include "RooGLWADSDmixRpmVar.h"
#include "RooGLWADSDmixRkpVar.h"
#include "RooGLWADSDmixRcpVar.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// The B->DKpipi, D->hh, GLW/ADS measurement: B->DKpipi, with D->Kpi, piK, pipi, KK,
/// 6 observables, including D mixing.
///
class PDF_GLWADS_DKpipi_hh_Dmix : public PDF_GLWADS_DKpipi_hh
{
	public:
		PDF_GLWADS_DKpipi_hh_Dmix(config cObs=lumi3fb, config cErr=lumi3fb, config cCor=lumi3fb, double Mxy=0);
		~PDF_GLWADS_DKpipi_hh_Dmix();
		virtual void  initParameters();
		virtual void  initRelations();

	private:
		double _Mxy;
};

#endif
