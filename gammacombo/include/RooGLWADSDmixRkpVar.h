#ifndef RooGLWADSDmixRkpVar_h
#define RooGLWADSDmixRkpVar_h

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "RooGLWADSDmixMaster.h"

///
/// Ratio of DK over Dpi decays:
/// \f[ R_{K/\pi} = \frac{N_K^- + N_K^+}{N_{\pi}^- + N_{\pi}^+} \f]
/// The yields are for favored decay chains containing D-bar decays.
/// The suppressed decay chain can be selected throug the options
/// argument: option = 'sup', default is 'fav'.
/// Implements D mixing.
/// In the non-mixing limiting case (xD=yD=0), this implementation is equivalent to
/// \f[ R_{K/\pi}^{\rm fav} = R_{\rm cab}\frac{1 + (r_B^K)^2   r_f^2 + 2 \kappa_B^K   r_B^K   r_f \kappa_f^K   \cos(\gamma) \cos(\delta_B^K   - \delta_f)}
///                                           {1 + (r_B^\pi)^2 r_f^2 + 2 \kappa_B^\pi r_B^\pi r_f \kappa_f^\pi \cos(\gamma) \cos(\delta_B^\pi - \delta_f)} \f]
/// when option 'fav' is given, and
/// \f[ R_{K/\pi}^{\rm sup} = R_{\rm cab}\frac{(r_B^K)^2   + r_f^2 + 2 \kappa_B^K   r_B^K   r_f \kappa_f^K   \cos(\gamma) \cos(\delta_B^K   + \delta_f)}
///                                           {(r_B^\pi)^2 + r_f^2 + 2 \kappa_B^\pi r_B^\pi r_f \kappa_f^\pi \cos(\gamma) \cos(\delta_B^\pi + \delta_f)} \f]
/// RooFit class implementation.
///
class RooGLWADSDmixRkpVar : public RooAbsReal {
public:
  RooGLWADSDmixRkpVar() {} ;
  RooGLWADSDmixRkpVar(const char *name, const char *title,
        RooAbsReal& Rcab,
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
        double Mxy,
        TString option);
  RooGLWADSDmixRkpVar(const RooGLWADSDmixRkpVar& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooGLWADSDmixRkpVar(*this,newname); }
  virtual ~RooGLWADSDmixRkpVar();

protected:
  RooRealProxy _Rcab;
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
  bool _fav;
  Double_t evaluate() const;

private:
  ClassDef(RooGLWADSDmixRkpVar, 1);
};

#endif
