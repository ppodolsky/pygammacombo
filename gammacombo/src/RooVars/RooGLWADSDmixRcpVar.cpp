#include "RooGLWADSDmixRcpVar.h"
#include "Riostream.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include <math.h>
#include "TMath.h"

RooGLWADSDmixRcpVar::RooGLWADSDmixRcpVar(const char *name, const char *title,
  RooAbsReal& rb,
  RooAbsReal& db,
  RooAbsReal& kb,
  RooAbsReal& rf,
  RooAbsReal& df,
  RooAbsReal& kf,
  RooAbsReal& g,
  RooAbsReal& xD,
  RooAbsReal& yD,
  double Mxy):
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
{}


RooGLWADSDmixRcpVar::RooGLWADSDmixRcpVar(const RooGLWADSDmixRcpVar& other, const char* name) :
  RooAbsReal(other,name),
  _rb   ("rb  ",this,other._rb),
  _db   ("db  ",this,other._db),
  _kb   ("kb  ",this,other._kb),
  _rf   ("rf  ",this,other._rf),
  _df   ("df  ",this,other._df),
  _kf   ("kf  ",this,other._kf),
  _g    ("g   ",this,other._g ),
  _xD   ("xD  ",this,other._xD),
  _yD   ("yD  ",this,other._yD),
  _Mxy    (other._Mxy)
{}


RooGLWADSDmixRcpVar::~RooGLWADSDmixRcpVar() { }


Double_t RooGLWADSDmixRcpVar::evaluate() const
{
  double rb   = double(_rb);
  double db   = double(_db);
  double kb   = double(_kb);
  double rf   = double(_rf);
  double df   = double(_df);
  double kf   = double(_kf);
  double g    = double(_g );
  double xD   = double(_xD);
  double yD   = double(_yD);
  RooGLWADSDmixMaster mCP (rb,db,kb,1.,0.,1.,g,xD,yD,0.);
  RooGLWADSDmixMaster mFav(rb,db,kb,rf,df,kf,g,xD,yD,_Mxy);
  return (mCP.ABm2Dfhm()+mCP.ABp2Dfhp())/(mFav.ABm2Dbfhm()+mFav.ABp2Dbfhp());
}

ClassImp(RooGLWADSDmixRcpVar)
