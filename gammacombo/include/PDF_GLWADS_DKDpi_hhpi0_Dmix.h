/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Jan 2015
 *
 **/

#ifndef PDF_GLWADS_DKDpi_hhpi0_Dmix_h
#define PDF_GLWADS_DKDpi_hhpi0_Dmix_h

#include "PDF_GLWADS_DKDpi_hhpi0.h"
#include "ParametersGammaCombo.h"
#include "RooGLWADSDmixAcpADSVar.h"
#include "RooGLWADSDmixAcpVar.h"
#include "RooGLWADSDmixRADSVar.h"
#include "RooGLWADSDmixRkpVar.h"
#include "RooGLWADSDmixRpmVar.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// The B->DK/Dpi, D->hh GLW/ADS measurement, 13 observables, added D mixing.
///
class PDF_GLWADS_DKDpi_hhpi0_Dmix : public PDF_GLWADS_DKDpi_hhpi0
{
	public:
		PDF_GLWADS_DKDpi_hhpi0_Dmix(config cObs=lumi1fb, config cErr=lumi1fb, config cCor=lumi1fb,
				double Mxy=0, ParametersAbs* pars=0);
		~PDF_GLWADS_DKDpi_hhpi0_Dmix();
		void        initParameters();
		void        initRelations();

	private:
		double _Mxy;
};

#endif
