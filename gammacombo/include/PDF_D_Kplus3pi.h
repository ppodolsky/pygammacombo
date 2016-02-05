//
//  PDF_D_Kplus3pi.h
//
//
//  Created by Matthew Kenzie on 11/07/14.
//
//

#ifndef PDF_D_Kplus3pi_h
#define PDF_D_Kplus3pi_h

#include "TFile.h"
#include "RooHistPdf.h"
#include "RooHistPdfVar.h"
#include "RooHistPdfAngleVar.h"
#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

/// This is simply the measurement of the D->Kpluspipipi branching fraction
/// Most recent measurement from Belle 2013 (arXiv:1307.5935)
/// Should be used in conjunction with the CLEO 2D likelihood profile (PDF_Dmixing_CLEO2D.h) of
/// kappa and dD as well as the CLEO measured D->Kminuspipipi branching fraction (PDF_D_Kminus3pi.h)

class PDF_D_Kplus3pi : public PDF_Abs
{
	public:

		PDF_D_Kplus3pi(config cObs=belle2013, config cErr=belle2013, config cCor=belle2013);
		~PDF_D_Kplus3pi();
		void          initObservables();
		virtual void  initParameters();
		virtual void  initRelations();
		void          setCorrelations(config c);
		void          setObservables(config c);
		void          setUncertainties(config c);
		void          buildPdf();

};
#endif
