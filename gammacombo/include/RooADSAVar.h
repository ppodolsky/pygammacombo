#ifndef RooADSAVar_h
#define RooADSAVar_h

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"

///
/// Comments needed (this is not a helpful comment)
///

class RooADSAVar : public RooAbsReal {
public:
  RooADSAVar() {} ;
  RooADSAVar(const char *name, const char *title,
        RooAbsReal& rb,
        RooAbsReal& db,
        RooAbsReal& kb,
        RooAbsReal& rd,
        RooAbsReal& dd,
        RooAbsReal& kd,
        RooAbsReal& g  );
  RooADSAVar(const RooADSAVar& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooADSAVar(*this,newname); }
  virtual ~RooADSAVar();

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
  ClassDef(RooADSAVar, 1);
};

#endif
