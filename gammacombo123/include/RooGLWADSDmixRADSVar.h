#ifndef RooGLWADSDmixRADSVar_h
#define RooGLWADSDmixRADSVar_h

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "RooGLWADSDmixMaster.h"

///
/// Ratio of suppressed over favored decays, charge averaged (R_ADS):
/// \f[ R_{\rm ADS} = \frac{N^{-}_{\rm sup}+N^{+}_{\rm sup}}{N^{-}_{\rm fav}+N^{+}_{\rm fav}} \f]
/// Here, 'sup' corresponds to decay chains containing D, and 'fav'
/// corresponds to D-bar.
/// The option string can configure the inverse ratio, by giving the string "inverse":
/// \f[ R_{\rm ADS}^{-1} = \frac{N^{-}_{\rm fav}+N^{+}_{\rm fav}}{N^{-}_{\rm sup}+N^{+}_{\rm sup}} \f]
/// Implements D mixing.
/// RooFit class implementation.
///
class RooGLWADSDmixRADSVar : public RooAbsReal {
public:
  RooGLWADSDmixRADSVar() {} ; 
  RooGLWADSDmixRADSVar(const char *name, const char *title,
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
        TString option);
  RooGLWADSDmixRADSVar(const RooGLWADSDmixRADSVar& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooGLWADSDmixRADSVar(*this,newname); }
  virtual ~RooGLWADSDmixRADSVar();

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
  bool _inverse;
  Double_t evaluate() const;

private:
  ClassDef(RooGLWADSDmixRADSVar, 1);
};
 
#endif
