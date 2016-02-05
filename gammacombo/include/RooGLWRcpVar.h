#ifndef RooGLWRcpVar_h
#define RooGLWRcpVar_h

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"

///
/// Comments needed (this is not a helpful comment)
///

class RooGLWRcpVar : public RooAbsReal {
public:
  RooGLWRcpVar() {} ;
  RooGLWRcpVar(const char *name, const char *title,
        RooAbsReal& rb,
        RooAbsReal& db,
        RooAbsReal& kb,
        RooAbsReal& g,
        TString pm);
  RooGLWRcpVar(const RooGLWRcpVar& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooGLWRcpVar(*this,newname); }
  virtual ~RooGLWRcpVar();

protected:
  RooRealProxy _rb;
  RooRealProxy _db;
  RooRealProxy _kb;
  RooRealProxy _g;
  double _pm;
  Double_t evaluate() const;

private:
  ClassDef(RooGLWRcpVar, 1);
};

#endif
