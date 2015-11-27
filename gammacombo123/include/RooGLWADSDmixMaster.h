#ifndef RooGLWADSDmixMaster_h
#define RooGLWADSDmixMaster_h

///
/// Master decay rate equation for B->DK like decays, including
/// D mixing. This is used to build the GLW/ADS observables
/// in their dedicated classes (RooGLWADSDmixAcpVar etc).
///
class RooGLWADSDmixMaster {
public:
  RooGLWADSDmixMaster(
   double rb,double db,double kb,
   double rf,double df,double kf,
   double g,
   double xD,double yD,double Mxy);

  double  ABm2Dfhm();
  double  ABp2Dfhp();
  double  ABm2Dbfhm();
  double  ABp2Dbfhp();  
  
private:
  double  gpgpInt();
  double  gmgmInt();
  double  RegpgmInt();
  double  ImgpgmInt();
  
  double rb;
  double db;
  double kb;
  double rf;
  double df;
  double kf;
  double g ;
  double xD;
  double yD;
  double Mp;
  double Mm;
  double Mx;
  double My;
};

#endif
