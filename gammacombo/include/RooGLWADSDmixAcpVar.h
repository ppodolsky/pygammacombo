#ifndef RooGLWADSDmixAcpVar_h
#define RooGLWADSDmixAcpVar_h

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "RooGLWADSDmixMaster.h"

///
/// Charge asymmetry:
/// \f[ A_{CP} = \frac{N_- - N_+}{N_- + N_+} \f]
/// The yields are for decay chains containing D-bar decays.
/// Used for GLW asymmetries (with rf=1, df=0), and favored ADS asymmetries.
/// Implements D mixing.
/// AcpD accounts for direct CP violation.
/// RooFit class implementation.
///
class RooGLWADSDmixAcpVar : public RooAbsReal {
public:
  RooGLWADSDmixAcpVar() {} ; 
  RooGLWADSDmixAcpVar(const char *name, const char *title,
        RooAbsReal& rb, 
        RooAbsReal& db, 
        RooAbsReal& kb, 
        RooAbsReal& rf,
        RooAbsReal& df, 
        RooAbsReal& kf,
        RooAbsReal& g,
        RooAbsReal& xD,
        RooAbsReal& yD,
        double Mxy,
        RooAbsReal& AcpD);
  RooGLWADSDmixAcpVar(const RooGLWADSDmixAcpVar& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooGLWADSDmixAcpVar(*this,newname); }
  virtual ~RooGLWADSDmixAcpVar();

protected:
  RooRealProxy _rb; 
  RooRealProxy _db; 
  RooRealProxy _kb; 
  RooRealProxy _rf;
  RooRealProxy _df; 
  RooRealProxy _kf;
  RooRealProxy _g;
  RooRealProxy _xD;
  RooRealProxy _yD;
  double _Mxy;
  RooRealProxy _AcpD;
  Double_t evaluate() const;

private:
  ClassDef(RooGLWADSDmixAcpVar, 1);
};
 
#endif
