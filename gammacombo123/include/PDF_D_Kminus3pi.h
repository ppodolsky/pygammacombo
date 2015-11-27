//
//  PDF_D_Kminus3pi.h
//
//
//  Created by Matthew Kenzie on 11/07/14.
//
//

#ifndef PDF_D_Kminus3pi_h
#define PDF_D_Kminus3pi_h

#include "TFile.h"
#include "RooHistPdf.h"
#include "RooHistPdfVar.h"
#include "RooHistPdfAngleVar.h"
#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

/// This is simply the measurement of the D->Kminusspipipi branching fraction
/// Most recent measurement from CLEO 2014 (arXiv:1312.6775)
/// Should be used in conjunction with the CLEO 2D likelihood profile (PDF_Dmixing_CLEO2D.h) of
/// kappa and dD as well as the Belle measured D->Kpluspipipi branching fraction (PDF_D_Kplus3pi.h)

class PDF_D_Kminus3pi : public PDF_Abs
{
	public:

		PDF_D_Kminus3pi(config cObs=cleo2014, config cErr=cleo2014, config cCor=cleo2014);
		~PDF_D_Kminus3pi();
		void          initObservables();
		virtual void  initParameters();
		virtual void  initRelations();
		void          setCorrelations(config c);
		void          setObservables(config c);
		void          setUncertainties(config c);
		void          buildPdf();

};
#endif

