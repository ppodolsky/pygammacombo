#ifndef RooGLWAcpVar_h
#define RooGLWAcpVar_h

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"

///
/// Comments needed (this is not a helpful comment)
///

class RooGLWAcpVar : public RooAbsReal {
public:
  RooGLWAcpVar() {} ;
  RooGLWAcpVar(const char *name, const char *title,
        RooAbsReal& rb,
        RooAbsReal& db,
        RooAbsReal& kb,
        RooAbsReal& g,
        TString pm);
  RooGLWAcpVar(const RooGLWAcpVar& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooGLWAcpVar(*this,newname); }
  virtual ~RooGLWAcpVar();

protected:
  RooRealProxy _rb;
  RooRealProxy _db;
  RooRealProxy _kb;
  RooRealProxy _g;
  double _pm;
  Double_t evaluate() const;

private:
  ClassDef(RooGLWAcpVar, 1);
};

#endif
