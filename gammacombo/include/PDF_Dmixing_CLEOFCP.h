//
//  PDF_Dmixing_CLEOFCP.h
//
//
//  Created by Matthew Kenzie on 11/07/14.
//
//

#ifndef PDF_Dmixing_CLEOFCP_h
#define PDF_Dmixing_CLEOFCP_h

#include "TFile.h"
#include "RooHistPdf.h"
#include "RooHistPdfVar.h"
#include "RooHistPdfAngleVar.h"
#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

// This is the 2D likelihood profile from CLEO of D mixing through kappa
// and dD.

class PDF_Dmixing_CLEOFCP : public PDF_Abs
{
	public:

		PDF_Dmixing_CLEOFCP(config cObs=cleo2014, config cErr=cleo2014, config cCor=cleo2014, config cType=useHistogram, TString d=".");
		~PDF_Dmixing_CLEOFCP();
		void          initObservables();
		void  				initParameters();
		void  				initRelations();
		void          setCorrelations(config c);
		void          setObservables(config c);
		void          setUncertainties(config c);
		void          buildPdf();

};
#endif



