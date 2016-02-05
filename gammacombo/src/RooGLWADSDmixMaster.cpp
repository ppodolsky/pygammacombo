#include "RooGLWADSDmixMaster.h"
#include <math.h>
#include "TMath.h"

///
/// Initializing corresponding to different acceptance/resolution
/// configurations.
/// \param rb Amplitude ratio between B->DK and B->DbarK
/// \param db Strong phase difference between B->DK and B->DbarK
/// \param kb Coherence factor of the B decay: unity for two-body decays
///           like B->DK, <1 for multibody decays like B->DKpipi
/// \param rf Amplitude ratio of D->f and Dbar->f
/// \param df Strong phase difference between D->f and Dbar->f
/// \param kf Coherence factor of the D decay
/// \param g  CKM gamma
/// \param xD D mixing parameter x
/// \param yD D mixing parameter y
/// \param Mxy Parameter describing the D decay time acceptance and resolution model.
///
RooGLWADSDmixMaster::RooGLWADSDmixMaster(
 double rb,double db,double kb,
 double rf,double df,double kf,
 double g,
 double xD,double yD,double Mxy)
: rb(rb),db(db),kb(kb),rf(rf),df(df),kf(kf),g(g),xD(xD),yD(yD)
{
  Mp = 1.;
  Mm = 0.;
  My = Mxy;
  Mx = Mxy;
}

///
/// Compute the gpgp integral. A common factor
/// of 2G is omitted. It is common to all integrals
/// and cancels when the observables are build, e.g. in
/// RooGLWADSDmixAcpVar.
///
double RooGLWADSDmixMaster::gpgpInt()
{
  return Mp;
}


double RooGLWADSDmixMaster::gmgmInt()
{
  return Mm;
}


double RooGLWADSDmixMaster::RegpgmInt()
{
  return -My*yD;
}


double RooGLWADSDmixMaster::ImgpgmInt()
{
  return Mx*xD;
}

///
/// The master equation for a favored decay of a B-:
/// B- -> D[fav] h-
/// LHCb-ANA-2014-069 v4 Eq (269)
///
double RooGLWADSDmixMaster::ABm2Dbfhm()
{
  return (1. + rb*rb*rf*rf + 2.*rb*kb*rf*kf*cos(db-df-g))*gpgpInt()
       + (rb*rb + rf*rf    + 2.*rb*kb*rf*kf*cos(db-df-g))*gmgmInt()
       + 2.*(kf*rf*(rb*rb+1.)*cos(df) + rb*kb*(1.+rf*rf)*cos(db-g))*RegpgmInt()
       + 2.*(kf*rf*(rb*rb-1.)*sin(df) + rb*kb*(1.-rf*rf)*sin(db-g))*ImgpgmInt();
}

///
/// The master equation for a favored decay of a B+:
/// B+ -> D[fav] h+
/// Obtained from the negative rate through the symmetry
/// transformation g -> -g.
///
double RooGLWADSDmixMaster::ABp2Dbfhp()
{
  g = -g;
  double val = ABm2Dbfhm();
  g = -g;
  return val;
}

///
/// The master equation for a suppressed decay of a B-:
/// B- -> D[fav] h-
/// Obtained from the favored rate through the symmetry
/// transformations (1) rf->1/rf, df->-df, (2) multiply by rf^2
///
double RooGLWADSDmixMaster::ABm2Dfhm()
{
  double rfsq = rf*rf;
  rf = 1./rf;
  df = -df;
  double val = rfsq*ABm2Dbfhm();
  rf = 1./rf;
  df = -df;
  return val;
}

///
/// The master equation for a suppressed decay of a B+:
/// B+ -> D[sup] h+
/// Obtained from the negative rate through the symmetry
/// transformation g -> -g.
///
double RooGLWADSDmixMaster::ABp2Dfhp()
{
  g = -g;
  double val = ABm2Dfhm();
  g = -g;
  return val;
}
