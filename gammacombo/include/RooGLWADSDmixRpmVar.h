#ifndef RooGLWADSDmixRpmVar_h
#define RooGLWADSDmixRpmVar_h

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "RooGLWADSDmixMaster.h"

///
/// Ratio of suppressed over favored decays, charge specific:
/// \f[ R_{\pm} = \frac{N^{\pm}_{\rm sup}}{N^{\pm}_{\rm fav}} \f]
/// Here, 'sup' corresponds to decay chains containing D, and 'fav'
/// corresponds to D-bar.
/// The charge is selected by the "pm" string: "+" or "-".
/// Implements D mixing.
/// In the non-mixing limiting case (xD=yD=0), this implementation is equivalent to
/// \f[ R_{\pm} = \frac{r_B^2  + r_f^2 + 2\kappa_B\kappa_f r_B r_f \cos( \pm\gamma+\delta_B + \delta_f) }
/// { 1 + r_B^2 r_f^2 + 2\kappa_B\kappa_f r_B r_f\cos( \pm\gamma +\delta_B - \delta_f))} \f]
/// RooFit class implementation.
///
class RooGLWADSDmixRpmVar : public RooAbsReal {
public:
  RooGLWADSDmixRpmVar() {} ; 
  RooGLWADSDmixRpmVar(const char *name, const char *title,
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
        TString pm);
  RooGLWADSDmixRpmVar(const RooGLWADSDmixRpmVar& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooGLWADSDmixRpmVar(*this,newname); }
  virtual ~RooGLWADSDmixRpmVar();

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
  double _pm;
  Double_t evaluate() const;

private:
  ClassDef(RooGLWADSDmixRpmVar, 1);
};
 
#endif
