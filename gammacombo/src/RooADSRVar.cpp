#include "RooADSRVar.h"
#include "Riostream.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include <math.h>
#include "TMath.h"

RooADSRVar::RooADSRVar(const char *name, const char *title,
      RooAbsReal& rb,
      RooAbsReal& db,
      RooAbsReal& kb,
      RooAbsReal& rd,
      RooAbsReal& dd,
      RooAbsReal& kd,
      RooAbsReal& g  ):
  RooAbsReal(name,title),
  _rb   ("rb  ","rb  ",this,rb  ),
  _db   ("db  ","db  ",this,db  ),
  _kb   ("kb  ","kb  ",this,kb  ),
  _rd   ("rd  ","rd  ",this,rd  ),
  _dd   ("dd  ","dd  ",this,dd  ),
  _kd   ("kd  ","kd  ",this,kd  ),
  _g    ("g   ","g   ",this,g   )
{
}


RooADSRVar::RooADSRVar(const RooADSRVar& other, const char* name) :
  RooAbsReal(other,name),
  _rb   ("rb  ",this,other._rb  ),
  _db   ("db  ",this,other._db  ),
  _kb   ("kb  ",this,other._kb  ),
  _rd   ("rd  ",this,other._rd  ),
  _dd   ("dd  ",this,other._dd  ),
  _kd   ("kd  ",this,other._kd  ),
  _g    ("g   ",this,other._g   )
{
}


RooADSRVar::~RooADSRVar() { }


Double_t RooADSRVar::evaluate() const
{
  double rb   = double(_rb  );
  double db   = double(_db  );
  double kb   = double(_kb  );
  double rd   = double(_rd  );
  double dd   = double(_dd  );
  double kd   = double(_kd  );
  double g    = double(_g   );

  return rb*rb + rd*rd  + 2. * rb * rd * kb * kd * cos(db+dd) * cos(g) ;
}

ClassImp(RooADSRVar)
