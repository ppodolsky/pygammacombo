//
//  PDF_D_K3pi_RWS.h
//
//
//  Created by Moritz Karbach on 28/07/14.
//
//

#ifndef PDF_D_K3pi_RWS_h
#define PDF_D_K3pi_RWS_h

#include "TFile.h"
#include "RooHistPdf.h"
#include "RooHistPdfVar.h"
#include "RooHistPdfAngleVar.h"
#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

/// This is simply the measurement of the ratio of the D->piKpipi and 
/// D->Kpipipi branching fractions.
/// Most recent measurement from Belle 2013 (arXiv:1307.5935)
/// Most recent measurement from CLEO 2014 (arXiv:1312.6775)
/// Should be used in conjunction with the CLEO 2D likelihood profile (PDF_Dmixing_CLEO2D.h) of
/// kappa and dD as well as the CLEO measured D->Kminuspipipi branching fraction (PDF_D_Kminus3pi.h)

class PDF_D_K3pi_RWS : public PDF_Abs
{
	public:

		PDF_D_K3pi_RWS(config cObs=belle2013, config cErr=belle2013, config cCor=belle2013);
		~PDF_D_K3pi_RWS();
		void          initObservables();
		virtual void  initParameters();
		virtual void  initRelations();
		void          setCorrelations(config c);
		void          setObservables(config c);
		void          setUncertainties(config c);
		void          buildPdf();

};
#endif
