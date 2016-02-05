#include "RooGLWRcpVar.h"
#include "Riostream.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include <math.h>
#include "TMath.h"

RooGLWRcpVar::RooGLWRcpVar(const char *name, const char *title,
      RooAbsReal& rb,
      RooAbsReal& db,
      RooAbsReal& kb,
      RooAbsReal& g,
      TString pm):
  RooAbsReal(name,title),
  _rb   ("rb  ","rb  ",this,rb  ),
  _db   ("db  ","db  ",this,db  ),
  _kb   ("kb  ","kb  ",this,kb  ),
  _g    ("g   ","g   ",this,g   )
{
  if      ( pm==TString("+") ) _pm= 1.;
  else if ( pm==TString("-") ) _pm=-1.;
  else assert(0);
}


RooGLWRcpVar::RooGLWRcpVar(const RooGLWRcpVar& other, const char* name) :
  RooAbsReal(other,name),
  _rb   ("rb  ",this,other._rb  ),
  _db   ("db  ",this,other._db  ),
  _kb   ("kb  ",this,other._kb  ),
  _g    ("g   ",this,other._g   ),
  _pm   (other._pm)
{
}


RooGLWRcpVar::~RooGLWRcpVar() { }


Double_t RooGLWRcpVar::evaluate() const
{
  double rb   = double(_rb  );
  double db   = double(_db  );
  double kb   = double(_kb  );
  double g    = double(_g   );
  double pm   = double(_pm  );

  return ( 1. + rb*rb + pm * 2. * rb * kb * cos(db) * cos(g) ) ;
}

ClassImp(RooGLWRcpVar)
