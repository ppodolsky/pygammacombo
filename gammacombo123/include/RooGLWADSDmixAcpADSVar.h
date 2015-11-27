#ifndef RooGLWADSDmixAcpADSVar_h
#define RooGLWADSDmixAcpADSVar_h

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "RooGLWADSDmixMaster.h"

///
/// Charge asymmetry:
/// \f[ A_{CP} = \frac{N_- - N_+}{N_- + N_+} \f]
/// The yields are for decay chains containing D decays.
/// Used for suppressed ADS asymmetries.
/// Implements D mixing.
/// AcpD accounts for direct CP violation.
/// RooFit class implementation.
///
class RooGLWADSDmixAcpADSVar : public RooAbsReal {
public:
  RooGLWADSDmixAcpADSVar() {} ; 
  RooGLWADSDmixAcpADSVar(const char *name, const char *title,
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
  RooGLWADSDmixAcpADSVar(const RooGLWADSDmixAcpADSVar& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooGLWADSDmixAcpADSVar(*this,newname); }
  virtual ~RooGLWADSDmixAcpADSVar();

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
  ClassDef(RooGLWADSDmixAcpADSVar, 1);
};
 
#endif
