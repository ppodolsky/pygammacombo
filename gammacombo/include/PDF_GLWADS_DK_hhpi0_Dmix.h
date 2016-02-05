/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Jan 2015
 *
 **/

#ifndef PDF_GLWADS_DK_hhpi0_Dmix_h
#define PDF_GLWADS_DK_hhpi0_Dmix_h

#include "PDF_GLWADS_DK_hhpi0.h"
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
/// The B->DK, D->hhpi0 GLW/ADS measurement, 7 observables, added D mixing.
///
class PDF_GLWADS_DK_hhpi0_Dmix : public PDF_GLWADS_DK_hhpi0
{
	public:
		PDF_GLWADS_DK_hhpi0_Dmix(config cObs=lumi3fb, config cErr=lumi3fb, config cCor=lumi3fb,
				double Mxy=0, ParametersAbs* pars=0);
		~PDF_GLWADS_DK_hhpi0_Dmix();
		void        initParameters();
		void        initRelations();

	private:
		double _Mxy;
};

#endif
