//
//  PDF_Dmixing_K3pi.h
//
//
//  Created by Sam Harnew on 10/08/15.
//
//

#ifndef PDF_Dmixing_K3pi_h
#define PDF_Dmixing_K3pi_h

#include "TFile.h"
#include "RooHistPdf.h"
#include "RooHistPdfVar.h"
#include "RooHistPdfAngleVar.h"
#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

//This is a time-dependent measurement of the ratio of WS to RS D0->Kpipipi decays. 
//This measurement is sensitive to 
//    rDK3pi (ratio of DCS to CF amplitudes)
//    kDK3pi (coherence factor)
//    dDK3pi (average strong phase difference)
//    xD     (dimensionless D mixing parameters)
//    yD     (dimensionless D mixing parameters)

//measurement is only has 3 observables that are dependent on the above parameters - therefore 
//extrnal input for xD and yD is needed to get constraints in the kDK3pi-dDK3pi plane


class PDF_Dmixing_K3pi : public PDF_Abs
{
	public:

		PDF_Dmixing_K3pi(config cObs=lhcb2012, config cErr=lhcb2012, config cCor=lhcb2012);
		~PDF_Dmixing_K3pi();
		void          initObservables();
		virtual void  initParameters();
		virtual void  initRelations();
		void          setCorrelations(config c);
		void          setObservables(config c);
		void          setUncertainties(config c);
		void          buildPdf();

};
#endif
