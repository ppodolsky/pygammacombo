#ifndef RooGLWADSDmixRcpNewVar_h
#define RooGLWADSDmixRcpNewVar_h

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
class RooGLWADSDmixRcpNewVar : public RooAbsReal {
public:
  RooGLWADSDmixRcpNewVar() {} ;
  RooGLWADSDmixRcpNewVar(const char *name, const char *title,
        RooAbsReal& rb,
        RooAbsReal& db,
        RooAbsReal& kb,
        RooAbsReal& rcp,
        RooAbsReal& dcp,
        RooAbsReal& kcp,
        RooAbsReal& rfav,
        RooAbsReal& dfav,
        RooAbsReal& kfav,
        RooAbsReal& g,
        RooAbsReal& xD,
        RooAbsReal& yD,
        double Mxy);
  RooGLWADSDmixRcpNewVar(const RooGLWADSDmixRcpNewVar& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooGLWADSDmixRcpNewVar(*this,newname); }
  virtual ~RooGLWADSDmixRcpNewVar();

protected:
  RooRealProxy _rb;
  RooRealProxy _db;
  RooRealProxy _kb;
  RooRealProxy _rcp;
  RooRealProxy _dcp;
  RooRealProxy _kcp;
  RooRealProxy _rfav;
  RooRealProxy _dfav;
  RooRealProxy _kfav;
  RooRealProxy _g;
  RooRealProxy _xD;
  RooRealProxy _yD;
  double _Mxy;
  Double_t evaluate() const;

private:
  ClassDef(RooGLWADSDmixRcpNewVar, 1);
};

#endif
