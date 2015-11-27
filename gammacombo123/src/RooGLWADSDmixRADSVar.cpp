#include "RooGLWADSDmixRADSVar.h" 
#include "Riostream.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

RooGLWADSDmixRADSVar::RooGLWADSDmixRADSVar(const char *name, const char *title,
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
  TString option):
  RooAbsReal(name,title),
  _rb   ("rb",  "rb"  ,this,rb  ),
  _db   ("db",  "db"  ,this,db  ),
  _kb   ("kb",  "kb"  ,this,kb  ),
  _rf   ("rf",  "rf"  ,this,rf  ),
  _df   ("df",  "df"  ,this,df  ),
  _kf   ("kf",  "kf"  ,this,kf  ),
  _g    ("g",   "g"   ,this,g   ),
  _xD   ("xD",  "xD"  ,this,xD  ),
  _yD   ("yD",  "yD"  ,this,yD  ),
  _Mxy(Mxy)
{
  if ( option==TString("inverse") ) _inverse=true;
  else _inverse=false;
}


RooGLWADSDmixRADSVar::RooGLWADSDmixRADSVar(const RooGLWADSDmixRADSVar& other, const char* name) :  
  RooAbsReal(other,name),
  _rb   ("rb  ",this,other._rb  ),
  _db   ("db  ",this,other._db  ),
  _kb   ("kb  ",this,other._kb  ),
  _rf   ("rf  ",this,other._rf  ),
  _df   ("df  ",this,other._df  ),
  _kf   ("kf  ",this,other._kf  ),
  _g    ("g   ",this,other._g   ),
  _xD   ("xD  ",this,other._xD  ),
  _yD   ("yD  ",this,other._yD  ),
  _Mxy    (other._Mxy),
  _inverse(other._inverse)
{
} 


RooGLWADSDmixRADSVar::~RooGLWADSDmixRADSVar() { }


Double_t RooGLWADSDmixRADSVar::evaluate() const 
{
  double rb   = double(_rb  );
  double db   = double(_db  );
  double kb   = double(_kb  );
  double rf   = double(_rf  );
  double df   = double(_df  );
  double kf   = double(_kf  );
  double g    = double(_g   );
  double xD   = double(_xD  );
  double yD   = double(_yD  );
  RooGLWADSDmixMaster m(rb,db,kb,rf,df,kf,g,xD,yD,_Mxy);
  if ( _inverse ) return 1./((m.ABm2Dfhm()+m.ABp2Dfhp())/(m.ABm2Dbfhm()+m.ABp2Dbfhp()));
  else            return     (m.ABm2Dfhm()+m.ABp2Dfhp())/(m.ABm2Dbfhm()+m.ABp2Dbfhp());
}

ClassImp(RooGLWADSDmixRADSVar)
