#ifndef RooGLWADSDmixRcpVar_h
#define RooGLWADSDmixRcpVar_h

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "RooGLWADSDmixMaster.h"

///
/// R_CP+: Ratio of CP even yields (e.g. from D->KK) over favored decays (e.g. D->Kpi), charge averaged:
/// \f[ R_{\rm CP} = \frac{N^{-}_{\rm CP}+N^{+}_{\rm CP}}{N^{-}_{\rm fav}+N^{+}_{\rm fav}} \f]
/// Implements D mixing.
/// In the non-mixing limiting case (xD=yD=0), this implementation is equivalent to
/// \f[ R_{\rm CP} = \frac{1 + r_B^2  + 2\kappa_B r_B\cos(\delta_B)\cos(\gamma)}
///                       {1 + r_B^2 r_f^2  + 2 \kappa_B \kappa_f r_B r_f \cos(\delta_B-\delta_f)\cos(\gamma))} \f]
/// RooFit class implementation.
///
class RooGLWADSDmixRcpVar : public RooAbsReal {
public:
  RooGLWADSDmixRcpVar() {} ;
  RooGLWADSDmixRcpVar(const char *name, const char *title,
        RooAbsReal& rb,
        RooAbsReal& db,
        RooAbsReal& kb,
        RooAbsReal& rf,
        RooAbsReal& df,
        RooAbsReal& kf,
        RooAbsReal& g,
        RooAbsReal& xD,
        RooAbsReal& yD,
        double Mxy);
  RooGLWADSDmixRcpVar(const RooGLWADSDmixRcpVar& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooGLWADSDmixRcpVar(*this,newname); }
  virtual ~RooGLWADSDmixRcpVar();

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
  Double_t evaluate() const;

private:
  ClassDef(RooGLWADSDmixRcpVar, 1);
};

#endif
