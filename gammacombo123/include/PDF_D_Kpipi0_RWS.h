//
//  PDF_D_Kpipi0_RWS.h
//
//
//  Created by Moritz Karbach on 19/08/14.
//
//

#ifndef PDF_D_Kpipi0_RWS_h
#define PDF_D_Kpipi0_RWS_h

#include "TFile.h"
#include "RooHistPdf.h"
#include "RooHistPdfVar.h"
#include "RooHistPdfAngleVar.h"
#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

///
/// This is simply the measurement of the ratio of the D->piKpi0 and 
/// D->Kpipi0 branching fractions.
///
class PDF_D_Kpipi0_RWS : public PDF_Abs
{
	public:

		PDF_D_Kpipi0_RWS(config cObs=cleo2014, config cErr=cleo2014, config cCor=cleo2014);
		~PDF_D_Kpipi0_RWS();
		void          initObservables();
		virtual void  initParameters();
		virtual void  initRelations();
		void          setCorrelations(config c);
		void          setObservables(config c);
		void          setUncertainties(config c);
		void          buildPdf();

};
#endif
