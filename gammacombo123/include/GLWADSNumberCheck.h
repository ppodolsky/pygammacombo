#ifndef GLWADSNumberCheck_h
#define GLWADSNumberCheck_h

#include <cmath>

class GLWADSNumberCheck {

	public:
		GLWADSNumberCheck();
		~GLWADSNumberCheck();

	void eval(double fMxy);
	void eval4body(double fMxy);

  double g;
  double db;
  double dd;
  double rb;
  double rd;
  double rb2;
  double rd2;
  double kd;
  double kb;
  double x;
  double y;
  double Mxy;

  double G_b2DX_CPP();
  double G_bbar2DX_CPP();
  double G_b2DX_CPM();
  double G_bbar2DX_CPM();
  double G_b2DX_ADS();
  double G_bbar2DX_ADS();
  double G_b2DX_FAV();
  double G_bbar2DX_FAV();

};

// copied over from gammadini
inline double GLWADSNumberCheck::G_b2DX_CPP()
{
  return 1+rb2+2*kb*kd*rb*cos(db-g);
}

inline double GLWADSNumberCheck::G_bbar2DX_CPP()
{
  return 1+rb2+2*kb*kd*rb*cos(db+g);
}

inline double GLWADSNumberCheck::G_b2DX_CPM()
{
  return 1+rb2-2*kb*kd*rb*cos(db-g);
}

inline double GLWADSNumberCheck::G_bbar2DX_CPM()
{
  return 1+rb2-2*kb*kd*rb*cos(db+g);
}

inline double GLWADSNumberCheck::G_b2DX_ADS()
{
  return       rd2 + rb2 + 2*rd*rb*kb*kd*cos(db+dd-g)
   + 2*((1+rb2)*rd*kd*cos(dd)+(1+rd2)*rb*kb*cos(db-g))*Mxy*y
   - 2*((1-rb2)*rd*kd*sin(dd)-(1-rd2)*rb*kb*sin(db-g))*Mxy*x;
}

inline double GLWADSNumberCheck::G_bbar2DX_ADS()
{
  return      rd2 + rb2 + 2*rd*rb*kb*kd*cos(db+dd+g)
  + 2*((1+rb2)*rd*kd*cos(dd)+(1+rd2)*rb*kb*cos(db+g))*Mxy*y
  - 2*((1-rb2)*rd*kd*sin(dd)-(1-rd2)*rb*kb*sin(db+g))*Mxy*x;
}

inline double GLWADSNumberCheck::G_b2DX_FAV()
{
  return    1 + rd2*rb2 + 2*rd*rb*kb*kd*cos(db-dd-g)
  + 2*((1+rb2)*rd*kd*cos(dd)+(1+rd2)*rb*kb*cos(db-g))*Mxy*y
  + 2*((1-rb2)*rd*kd*sin(dd)-(1-rd2)*rb*kb*sin(db-g))*Mxy*x;
}

inline double GLWADSNumberCheck::G_bbar2DX_FAV()
{
  return    1 + rd2*rb2 + 2*rd*rb*kb*kd*cos(db-dd+g)
  + 2*((1+rb2)*rd*kd*cos(dd)+(1+rd2)*rb*kb*cos(db+g))*Mxy*y
  + 2*((1-rb2)*rd*kd*sin(dd)-(1-rd2)*rb*kb*sin(db+g))*Mxy*x;
}

#endif
