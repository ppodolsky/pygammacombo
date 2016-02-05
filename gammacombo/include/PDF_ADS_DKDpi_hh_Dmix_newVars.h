/**
 * Gamma Combination
 * Author: Matthew Kenzie matthew.kenzie@cern.ch
 * Date: August 2015
 *
 **/

#ifndef PDF_ADS_DKDpi_hh_Dmix_newVars_h
#define PDF_ADS_DKDpi_hh_Dmix_newVars_h

#include "PDF_GLWADS_DKDpi_hh.h"
#include "RooGLWADSDmixRkpVar.h"
#include "RooGLWADSDmixRcpVar.h"
#include "RooGLWADSDmixRcpRatioVar.h"
#include "RooGLWADSDmixAcpVar.h"
#include "RooGLWADSDmixAcpADSVar.h"
#include "RooGLWADSDmixRADSVar.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// The B->DK/Dpi, D->hh GLW/ADS measurement, 12 observables, added D mixing.
///
class PDF_ADS_DKDpi_hh_Dmix_newVars : public PDF_Abs
{
	public:
		PDF_ADS_DKDpi_hh_Dmix_newVars(config cObs=lumi3fb, config cErr=lumi3fb, config cCor=lumi3fb,
				double Mxy=0, ParametersAbs* pars=0, TString d=".");
		~PDF_ADS_DKDpi_hh_Dmix_newVars();

		void        buildPdf();
		void 				initObservables();
		void        initParameters();
		void        initRelations();
		void        setCorrelations(config c);
		void        setObservables(config c);
		void        setUncertainties(config c);

	protected:
		ParametersAbs* p;
	private:
		double _Mxy;
};

#endif
