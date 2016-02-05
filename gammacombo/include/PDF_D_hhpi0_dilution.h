/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: Jan 2015
 *
 **/

#ifndef PDF_D_hhpi0_dilution_h
#define PDF_D_hhpi0_dilution_h

#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// Plain and simple Gaussian constraint on the CP dilution
/// parameters F_pipipi0 and F_kkpi0 from CLEO legacy.
///
class PDF_D_hhpi0_dilution : public PDF_Abs
{
	public:
		PDF_D_hhpi0_dilution(config cObs=hfag, config cErr=hfag, config cCor=hfag);
		~PDF_D_hhpi0_dilution();
		void          buildPdf();
		void          initObservables();
		virtual void  initParameters();
		virtual void  initRelations();
		void          setCorrelations(config c);
		void          setObservables(config c);
		void          setUncertainties(config c);
};

#endif
