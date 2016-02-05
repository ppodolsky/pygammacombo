#include "RooGLWADSDmixRcpNewVar.h"
#include "Riostream.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include <math.h>
#include "TMath.h"

RooGLWADSDmixRcpNewVar::RooGLWADSDmixRcpNewVar(const char *name, const char *title,
  RooAbsReal& rb,
  RooAbsReal& db,
  RooAbsReal& kb,
  RooAbsReal& rcp,
  RooAbsReal& dcp,
  RooAbsReal& kcp,
  RooAbsReal& rfav,
  RooAbsReal& dfav,
  RooAbsReal& kfav,
  RooAbsReal& g,
  RooAbsReal& xD,
  RooAbsReal& yD,
  double Mxy):
  RooAbsReal(name,title),
  _rb   ("rb",  "rb"  ,this,rb  ),
  _db   ("db",  "db"  ,this,db  ),
  _kb   ("kb",  "kb"  ,this,kb  ),
  _rcp  ("rcp", "rcp" ,this,rcp ),
  _dcp  ("dcp", "dcp" ,this,dcp ),
  _kcp  ("kcp", "kcp" ,this,kcp ),
  _rfav ("rfav","rfav",this,rfav),
  _dfav ("dfav","dfav",this,dfav),
  _kfav ("kfav","kfav",this,kfav),
  _g    ("g",   "g"   ,this,g   ),
  _xD   ("xD",  "xD"  ,this,xD  ),
  _yD   ("yD",  "yD"  ,this,yD  ),
  _Mxy(Mxy)
{}


RooGLWADSDmixRcpNewVar::RooGLWADSDmixRcpNewVar(const RooGLWADSDmixRcpNewVar& other, const char* name) :
  RooAbsReal(other,name),
  _rb   ("rb  ",this,other._rb),
  _db   ("db  ",this,other._db),
  _kb   ("kb  ",this,other._kb),
  _rcp   ("rcp  ",this,other._rcp),
  _dcp   ("dcp  ",this,other._dcp),
  _kcp   ("kcp  ",this,other._kcp),
  _rfav   ("rfav  ",this,other._rfav),
  _dfav   ("dfav  ",this,other._dfav),
  _kfav   ("kfav  ",this,other._kfav),
  _g    ("g   ",this,other._g ),
  _xD   ("xD  ",this,other._xD),
  _yD   ("yD  ",this,other._yD),
  _Mxy    (other._Mxy)
{}


RooGLWADSDmixRcpNewVar::~RooGLWADSDmixRcpNewVar() { }


Double_t RooGLWADSDmixRcpNewVar::evaluate() const
{
  double rb   = double(_rb);
  double db   = double(_db);
  double kb   = double(_kb);
  double rcp   = double(_rcp);
  double dcp   = double(_dcp);
  double kcp   = double(_kcp);
  double rfav   = double(_rfav);
  double dfav   = double(_dfav);
  double kfav   = double(_kfav);
  double g    = double(_g );
  double xD   = double(_xD);
  double yD   = double(_yD);
  RooGLWADSDmixMaster mCP (rb,db,kb,rcp,dcp,kcp,g,xD,yD,0.);
  RooGLWADSDmixMaster mFav(rb,db,kb,rfav,dfav,kfav,g,xD,yD,_Mxy);
  return (mCP.ABm2Dfhm()+mCP.ABp2Dfhp())/(mFav.ABm2Dbfhm()+mFav.ABp2Dbfhp());
}

ClassImp(RooGLWADSDmixRcpNewVar)
