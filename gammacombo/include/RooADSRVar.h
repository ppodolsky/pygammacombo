#ifndef RooADSRVar_h
#define RooADSRVar_h

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"

///
/// Comments needed (this is not a helpful comment)
///

class RooADSRVar : public RooAbsReal {
public:
  RooADSRVar() {} ;
  RooADSRVar(const char *name, const char *title,
        RooAbsReal& rb,
        RooAbsReal& db,
        RooAbsReal& kb,
        RooAbsReal& rd,
        RooAbsReal& dd,
        RooAbsReal& kd,
        RooAbsReal& g  );
  RooADSRVar(const RooADSRVar& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooADSRVar(*this,newname); }
  virtual ~RooADSRVar();

protected:
  RooRealProxy _rb;
  RooRealProxy _db;
  RooRealProxy _kb;
  RooRealProxy _rd;
  RooRealProxy _dd;
  RooRealProxy _kd;
  RooRealProxy _g;
  Double_t evaluate() const;

private:
  ClassDef(RooADSRVar, 1);
};

#endif
