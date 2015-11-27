/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#ifndef PDF_GLWADS_DK_hh_Dmix_h
#define PDF_GLWADS_DK_hh_Dmix_h

#include "PDF_GLWADS_DK_hh.h"
#include "RooGLWADSDmixAcpVar.h"
#include "RooGLWADSDmixRpmVar.h"
#include "RooGLWADSDmixRkpVar.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// The B->DK, D->hh, GLW/ADS measurement: B->DK, with D->Kpi, piK, pipi, KK,
/// 8 observables, including D mixing.
///
class PDF_GLWADS_DK_hh_Dmix : public PDF_GLWADS_DK_hh
{
	public:
		PDF_GLWADS_DK_hh_Dmix(config cObs=lumi1fb, config cErr=lumi1fb, config cCor=lumi1fb, 
				double Mxy=0, ParametersAbs* pars=0, TString d=".");
		~PDF_GLWADS_DK_hh_Dmix();
		void        initParameters();
		void        initRelations();

	private:
		double _Mxy;
};

#endif
