#ifndef RooGLWADSDmixRcpRatioVar_h
#define RooGLWADSDmixRcpRatioVar_h

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "RooGLWADSDmixMaster.h"

///
/// R_CP double ratio: Ratio of CP even yields (e.g from D->KK) over favoured decays (e.g D->Kpi), charge average, double ratio with that of D->Kpi
//
//

class RooGLWADSDmixRcpRatioVar : public RooAbsReal {

	public:
		RooGLWADSDmixRcpRatioVar() {} ;
		RooGLWADSDmixRcpRatioVar(const char *name, const char *title,
				RooAbsReal& rbk,
				RooAbsReal& dbk,
				RooAbsReal& kbk,
				RooAbsReal& rbp,
				RooAbsReal& dbp,
				RooAbsReal& kbp,
				RooAbsReal& rf,
				RooAbsReal& df,
				RooAbsReal& kf,
				RooAbsReal& g,
				RooAbsReal& xD,
				RooAbsReal& yD,
				double Mxy);
		RooGLWADSDmixRcpRatioVar(const RooGLWADSDmixRcpRatioVar& other, const char* name=0);
		virtual TObject* clone(const char* newname) const { return new RooGLWADSDmixRcpRatioVar(*this,newname); }
		virtual ~RooGLWADSDmixRcpRatioVar();

	protected:
		RooRealProxy _rbk;
		RooRealProxy _dbk;
		RooRealProxy _kbk;
		RooRealProxy _rbp;
		RooRealProxy _dbp;
		RooRealProxy _kbp;
		RooRealProxy _rf;
		RooRealProxy _df;
		RooRealProxy _kf;
		RooRealProxy _g;
		RooRealProxy _xD;
		RooRealProxy _yD;
		double _Mxy;
		Double_t evaluate() const;

	private:
		ClassDef(RooGLWADSDmixRcpRatioVar, 1);

};

#endif
