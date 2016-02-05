#include "RooGLWADSDmixRcpRatioVar.h"
#include "Riostream.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include <math.h>
#include "TMath.h"

RooGLWADSDmixRcpRatioVar::RooGLWADSDmixRcpRatioVar(const char* name, const char* title,
	RooAbsReal& rbk,
	RooAbsReal& dbk,
	RooAbsReal& kbk,
	RooAbsReal& rbp,
	RooAbsReal& dbp,
	RooAbsReal& kbp,
	RooAbsReal& rf,
	RooAbsReal& df,
	RooAbsReal& kf,
	RooAbsReal& g,
	RooAbsReal& xD,
	RooAbsReal& yD,
	double Mxy):
	RooAbsReal(name,title),
	_rbk ("rbk", "rbk", this, rbk  ),
	_dbk ("dbk", "dbk", this, dbk  ),
	_kbk ("kbk", "kbk", this, kbk  ),
	_rbp ("rbp", "rbp", this, rbp  ),
	_dbp ("dbp", "dbp", this, dbp  ),
	_kbp ("kbp", "kbp", this, kbp  ),
	_rf  ("rf" , "rf" , this, rf   ),
	_df  ("df" , "df" , this, df   ),
	_kf  ("kf" , "kf" , this, kf   ),
	_g   ("g"  , "g"  , this, g    ),
	_xD  ("xD" , "xD" , this, xD   ),
	_yD  ("yD" , "yD" , this, yD   ),
	_Mxy (Mxy)
{}

RooGLWADSDmixRcpRatioVar::RooGLWADSDmixRcpRatioVar(const RooGLWADSDmixRcpRatioVar& other, const char* name) :
	RooAbsReal(other,name),
	_rbk ("rbk", this, other._rbk  ),
	_dbk ("dbk", this, other._dbk  ),
	_kbk ("kbk", this, other._kbk  ),
	_rbp ("rbp", this, other._rbp  ),
	_dbp ("dbp", this, other._dbp  ),
	_kbp ("kbp", this, other._kbp  ),
	_rf  ("rf" , this, other._rf   ),
	_df  ("df" , this, other._df   ),
	_kf  ("kf" , this, other._kf   ),
	_g   ("g"  , this, other._g    ),
	_xD  ("xD" , this, other._xD   ),
	_yD  ("yD" , this, other._yD   ),
	_Mxy (other._Mxy)
{}

RooGLWADSDmixRcpRatioVar::~RooGLWADSDmixRcpRatioVar() { }

Double_t RooGLWADSDmixRcpRatioVar::evaluate() const
{
	double rbk = double(_rbk);
	double dbk = double(_dbk);
	double kbk = double(_kbk);
	double rbp = double(_rbp);
	double dbp = double(_dbp);
	double kbp = double(_kbp);
	double rf  = double(_rf );
	double df  = double(_df );
	double kf  = double(_kf );
	double g   = double(_g  );
	double xD  = double(_xD );
	double yD  = double(_yD );

	RooGLWADSDmixMaster mCPk ( rbk, dbk, kbk, 1., 0., 1., g, xD, yD, 0.);
	RooGLWADSDmixMaster mFavk( rbk, dbk, kbk, rf, df, kf, g, xD, yD, _Mxy);
	RooGLWADSDmixMaster mCPp ( rbp, dbp, kbp, 1., 0., 1., g, xD, yD, 0.);
	RooGLWADSDmixMaster mFavp( rbp, dbp, kbp, rf, df, kf, g, xD, yD, _Mxy);

	double rCPk = (mCPk.ABm2Dfhm()+mCPk.ABp2Dfhp())/(mFavk.ABm2Dbfhm()+mFavk.ABp2Dbfhp());
	double rCPp = (mCPp.ABm2Dfhm()+mCPp.ABp2Dfhp())/(mFavp.ABm2Dbfhm()+mFavp.ABp2Dbfhp());
	return rCPk/rCPp;

}

ClassImp(RooGLWADSDmixRcpRatioVar)
