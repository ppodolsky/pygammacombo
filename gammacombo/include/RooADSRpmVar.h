#ifndef RooADSRpmVar_h
#define RooADSRpmVar_h

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"

///
/// Comments needed (this is not a helpful comment)
///

class RooADSRpmVar : public RooAbsReal {
public:
  RooADSRpmVar() {} ;
  RooADSRpmVar(const char *name, const char *title,
        RooAbsReal& rb,
        RooAbsReal& db,
        RooAbsReal& kb,
        RooAbsReal& rd,
        RooAbsReal& dd,
        RooAbsReal& kd,
        RooAbsReal& g ,
        TString pm );
  RooADSRpmVar(const RooADSRpmVar& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooADSRpmVar(*this,newname); }
  virtual ~RooADSRpmVar();

protected:
  RooRealProxy _rb;
  RooRealProxy _db;
  RooRealProxy _kb;
  RooRealProxy _rd;
  RooRealProxy _dd;
  RooRealProxy _kd;
  RooRealProxy _g;
  double _pm;
  Double_t evaluate() const;

private:
  ClassDef(RooADSRpmVar, 1);
};

#endif
