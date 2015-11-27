//
//  PDF_D_Kpipi0.h
//
//
//  Created by Moritz Karbach on 19/08/14.
//
//

#ifndef PDF_D_Kpipi0_h
#define PDF_D_Kpipi0_h

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
/// This is the 2D likelihood profile from CLEO of D mixing through kappa
/// and dD.
///
class PDF_D_Kpipi0 : public PDF_Abs
{
	public:

		PDF_D_Kpipi0(config cObs=cleo2014, config cErr=cleo2014, config cCor=cleo2014, config cType=useHistogram, TString d=".");
		~PDF_D_Kpipi0();
		void          initObservables();
		virtual void  initParameters();
		virtual void  initRelations();
		void          setCorrelations(config c);
		void          setObservables(config c);
		void          setUncertainties(config c);
		void          buildPdf();
		void 					buildPdfGaus();

	protected:

		void buildPdfHistogram(TString fName, float scale, float kDobs, float dDobs);
		config cType;
		config cObs;
		TString dir;

};
#endif


