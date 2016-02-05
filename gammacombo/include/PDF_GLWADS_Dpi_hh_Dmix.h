/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 * Combine all Dpi observables from the two-body GLW/ADS measurement.
 *
 **/

#ifndef PDF_GLWADS_Dpi_hh_Dmix_h
#define PDF_GLWADS_Dpi_hh_Dmix_h

#include "TFile.h"

#include "PDF_GLWADS_Dpi_hh.h"
#include "RooGLWADSDmixAcpVar.h"
#include "RooGLWADSDmixRpmVar.h"
#include "RooGLWADSDmixRkpVar.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

class PDF_GLWADS_Dpi_hh_Dmix : public PDF_GLWADS_Dpi_hh
{
	public:
		PDF_GLWADS_Dpi_hh_Dmix(config cObs=lumi1fb, config cErr=lumi1fb, config cCor=lumi1fb, 
				double Mxy=0, ParametersAbs* pars=0, TString d=".");
		~PDF_GLWADS_Dpi_hh_Dmix();
		void        initParameters();
		void        initRelations();

	private:
		double _Mxy;
};

#endif
