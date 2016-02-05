#include "GLWADSNumberCheck.h"
#include "RooGLWADSDmixAcpVar.h"
#include "RooGLWADSDmixAcpADSVar.h"
#include "RooGLWADSDmixRADSVar.h"
#include "RooGLWADSDmixRcpVar.h"
#include "RooGLWADSDmixRcpNewVar.h"
#include "RooGLWADSDmixRcpRatioVar.h"
#include "RooGLWADSDmixRkpVar.h"
#include "RooGLWADSDmixMaster.h"

#include <map>
#include <iostream>

#include "TString.h"
#include "TMath.h"
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooConstVar.h"
#include "RooMsgService.h"
#include "RooFormulaVar.h"

using namespace std;
using namespace RooFit;

GLWADSNumberCheck::GLWADSNumberCheck(){}
GLWADSNumberCheck::~GLWADSNumberCheck(){}

void GLWADSNumberCheck::eval(double fMxy=0.) {

	cout << "Mxy = " << fMxy << endl;
	RooMsgService::instance().setGlobalKillBelow(FATAL);
	RooMsgService::instance().setSilentMode(true);

	double ACPDKK     = -0.00215273;
	double ACPDPIPI   =  0.000608687;
	double RBRdkdpi   =  0.0775273;
	double dD_kpi     =  195.524 / (180./TMath::Pi());
	double d_dk       =  32.3679 / (180./TMath::Pi());
	double d_dpi      =  202.412 / (180./TMath::Pi());
	double rD_kpi     =  0.0590885;
	double r_dk       =  0.0991957;
	double r_dpi      =  0.00713259;
	double rD_k3pi    =  5.67004e-02;
	double dD_k3pi    =  1.92092e+02;
	double kD_k3pi    =  0.532453;
	double F_pipipipi =  0.738495;

  double dD_kskpi   =  28.7671;
  double kD_kskpi   =  1.0166;
  double rD_kskpi   =  0.596763;



	// for gammadini
	g          =  128.279 / (180./TMath::Pi());
	x          =  0.00342849;
	y          =  0.00683989;
	rb  = r_dk;
	rb2 = rb*rb;
	db  = d_dk;
	kb  = 1;
	rd  = rD_kskpi;
	rd2 = rd*rd;
	dd  = dD_kskpi;
	kd  = kD_kskpi;
	Mxy = fMxy;

	//Mxy = 0.;

	double G_BmDK_CPP = G_b2DX_CPP();
  double G_BpDK_CPP = G_bbar2DX_CPP();
  double G_BmDK_ADS = G_b2DX_ADS();
  double G_BpDK_ADS = G_bbar2DX_ADS();
  double G_BmDK_FAV = G_b2DX_FAV();
  double G_BpDK_FAV = G_bbar2DX_FAV();

	rb  = r_dpi;
	rb2 = rb*rb;
  db  = d_dpi;
	kb  = 1;

  double G_BmDpi_CPP = G_b2DX_CPP();
  double G_BpDpi_CPP = G_bbar2DX_CPP();
  double G_BmDpi_ADS = G_b2DX_ADS();
  double G_BpDpi_ADS = G_bbar2DX_ADS();
  double G_BmDpi_FAV = G_b2DX_FAV();
  double G_BpDpi_FAV = G_bbar2DX_FAV();

	cout << G_BmDK_ADS << " " << G_BmDpi_ADS << endl;
	cout << G_BpDK_ADS << " " << G_BpDpi_ADS << endl;

	map<TString,double> gammadini_vals;
	map<TString,double> gammacombo_vals;

	bool both=false;
	bool dkonly=true;

	if ( both ) {
		gammadini_vals["rkp_kpi_th"     ] = ( G_BmDK_FAV + G_BpDK_FAV ) / ( G_BmDpi_FAV + G_BpDpi_FAV ) * RBRdkdpi;
		gammadini_vals["rcp_kk_th"      ] = ( ( G_BmDK_CPP + G_BpDK_CPP ) / ( G_BmDK_FAV + G_BpDK_FAV ) ) / ( ( G_BmDpi_CPP + G_BpDpi_CPP ) / ( G_BmDpi_FAV + G_BpDpi_FAV ) );
		gammadini_vals["rcp_pipi_th"    ] = ( ( G_BmDK_CPP + G_BpDK_CPP ) / ( G_BmDK_FAV + G_BpDK_FAV ) ) / ( ( G_BmDpi_CPP + G_BpDpi_CPP ) / ( G_BmDpi_FAV + G_BpDpi_FAV ) );
	}
  //else if ( dkonly ) {
		//gammadini_vals["rcp_kk_th"      ] = ( G_BmDK_CPP + G_BpDK_CPP ) / ( G_BmDK_FAV + G_BpDK_FAV );
		//gammadini_vals["rcp_pipi_th"    ] = ( G_BmDK_CPP + G_BpDK_CPP ) / ( G_BmDK_FAV + G_BpDK_FAV );
    //}
	if ( dkonly or both ) {
		//gammadini_vals["afav_dk_kpi_th" ] = ( G_BmDK_FAV - G_BpDK_FAV ) / ( G_BmDK_FAV + G_BpDK_FAV );
		//gammadini_vals["rads_dk_kpi_th" ] = ( G_BmDK_ADS + G_BpDK_ADS ) / ( G_BmDK_FAV + G_BpDK_FAV );
		//gammadini_vals["acp_dk_kk_th"   ] = ( G_BmDK_CPP - G_BpDK_CPP ) / ( G_BmDK_CPP + G_BpDK_CPP) + ACPDKK;
		//gammadini_vals["acp_dk_pipi_th" ] = ( G_BmDK_CPP - G_BpDK_CPP ) / ( G_BmDK_CPP + G_BpDK_CPP) + ACPDPIPI;
		//gammadini_vals["aads_dk_kpi_th" ] = ( G_BmDK_ADS - G_BpDK_ADS ) / ( G_BmDK_ADS + G_BpDK_ADS );
	  gammadini_vals["rfavsup_dk_kskpi_th"] = (G_BmDK_FAV+G_BpDK_FAV)/(G_BmDK_ADS+G_BpDK_ADS);
    gammadini_vals["afav_dk_kskpi_th"]    = (G_BmDK_FAV-G_BpDK_FAV)/(G_BmDK_FAV+G_BpDK_FAV);
    gammadini_vals["asup_dk_kskpi_th"]    = (G_BmDK_ADS-G_BpDK_ADS)/(G_BmDK_ADS+G_BpDK_ADS);
  }
	if ( both ) {
		gammadini_vals["acp_dpi_kk_th"  ] = ( G_BmDpi_CPP - G_BpDpi_CPP ) / ( G_BmDpi_CPP + G_BpDpi_CPP ) + ACPDKK;
		gammadini_vals["acp_dpi_pipi_th"] = ( G_BmDpi_CPP - G_BpDpi_CPP ) / ( G_BmDpi_CPP + G_BpDpi_CPP ) + ACPDPIPI;
		gammadini_vals["rads_dpi_kpi_th"] = ( G_BmDpi_ADS + G_BpDpi_ADS ) / ( G_BmDpi_FAV + G_BpDpi_FAV );
		gammadini_vals["aads_dpi_kpi_th"] = ( G_BmDpi_ADS - G_BpDpi_ADS ) / ( G_BmDpi_ADS + G_BpDpi_ADS );
	}

	RooConstVar rbk    ("rbk"   ,"",r_dk);
	RooConstVar dbk    ("dbk"   ,"",d_dk);
	RooConstVar kbk    ("kbk"   ,"",kb);
	double tmp_rbp;
	double tmp_dbp;
	if ( both ){
		tmp_rbp = r_dpi;
		tmp_dbp = d_dpi;
	}
	else if (dkonly) {
		tmp_rbp = 1.;
		tmp_dbp = 0.;
	}
	RooConstVar rbp    ("rbp"   ,"",tmp_rbp);
	RooConstVar dbp    ("dbp"   ,"",tmp_dbp);
	RooConstVar kbp    ("kbp"   ,"",1.);
	RooConstVar Rcab   ("Rcab"  ,"",RBRdkdpi);
	RooConstVar rf     ("rf"    ,"",rD_kskpi);
	RooConstVar df     ("df"    ,"",dD_kskpi);
	RooConstVar kf     ("kf"    ,"",kD_kskpi);
	RooConstVar rfGLW  ("rfGLW" ,"",1.);
	RooConstVar dfGLW  ("dfGLW" ,"",0.);
	RooConstVar gam    ("gam"   ,"",g);
	RooConstVar xD     ("xD"    ,"",x);
	RooConstVar yD     ("yD"    ,"",y);
	RooConstVar AcpD   ("AcpD"  ,"",0.);
	RooConstVar AcpDKK ("AcpDKK","",ACPDKK);
	RooConstVar AcpDpp ("AcpDpp","",ACPDPIPI);
	double _Mxy = -Mxy;

	RooWorkspace *w = new RooWorkspace("w","w");
	//w->import(*(new RooGLWADSDmixAcpADSVar   ("aads_dk_kpi_th",   "RooGLWADSDmixAcpADSVar"  , rbk, dbk, kbk, rf, df, kf, gam, xD, yD, _Mxy, AcpD)));
	//w->import(*(new RooGLWADSDmixAcpADSVar   ("aads_dpi_kpi_th",  "RooGLWADSDmixAcpADSVar"  , rbp, dbp, kbp, rf, df, kf, gam, xD, yD, _Mxy, AcpD)));
	//w->import(*(new RooGLWADSDmixAcpVar      ("acp_dk_kk_th",     "RooGLWADSDmixAcpVar"     , rbk, dbk, kbk, rfGLW, dfGLW, kf, gam, xD, yD, _Mxy, AcpDKK)));
	//w->import(*(new RooGLWADSDmixAcpVar      ("acp_dk_pipi_th",   "RooGLWADSDmixAcpVar"     , rbk, dbk, kbk, rfGLW, dfGLW, kf, gam, xD, yD, _Mxy, AcpDpp)));
	//w->import(*(new RooGLWADSDmixAcpVar      ("acp_dpi_kk_th",    "RooGLWADSDmixAcpVar"     , rbp, dbp, kbp, rfGLW, dfGLW, kf, gam, xD, yD, _Mxy, AcpDKK)));
	//w->import(*(new RooGLWADSDmixAcpVar      ("acp_dpi_pipi_th",  "RooGLWADSDmixAcpVar"     , rbp, dbp, kbp, rfGLW, dfGLW, kf, gam, xD, yD, _Mxy, AcpDpp)));
	//w->import(*(new RooGLWADSDmixAcpVar      ("afav_dk_kpi_th",   "RooGLWADSDmixAcpVar"     , rbk, dbk, kbk, rf, df, kf, gam, xD, yD, _Mxy, AcpD)));
	//w->import(*(new RooGLWADSDmixRADSVar     ("rads_dk_kpi_th",   "RooGLWADSDmixRADSVar"    , rbk, dbk, kbk, rf, df, kf, gam, xD, yD, _Mxy, "")));
	//w->import(*(new RooGLWADSDmixRADSVar     ("rads_dpi_kpi_th",  "RooGLWADSDmixRADSVar"    , rbp, dbp, kbp, rf, df, kf, gam, xD, yD, _Mxy, "")));
	//if (both){
	//w->import(*(new RooGLWADSDmixRcpRatioVar ("rcp_kk_th", 			  "RooGLWADSDmixRcpRatioVar", rbk, dbk, kbk, rbp, dbp, kbp, rf, df, kf, gam, xD, yD, _Mxy)));
	//w->import(*(new RooGLWADSDmixRcpRatioVar ("rcp_pipi_th", 		  "RooGLWADSDmixRcpRatioVar", rbk, dbk, kbk, rbp, dbp, kbp, rf, df, kf, gam, xD, yD, _Mxy)));
	//}
	//else if (dkonly) {
		//w->import(*(new RooGLWADSDmixRcpVar ("rcp_kk_th", 			  "RooGLWADSDmixRcpRatioVar", rbk, dbk, kbk, rf, df, kf, gam, xD, yD, _Mxy)));
		//w->import(*(new RooGLWADSDmixRcpVar ("rcp_pipi_th", 		  "RooGLWADSDmixRcpRatioVar", rbk, dbk, kbk, rf, df, kf, gam, xD, yD, _Mxy)));
    w->import(*(new RooGLWADSDmixRADSVar(  "rfavsup_dk_kskpi_th",  "RooGLWADSDmixRADSVar (inverse)", rbk, dbk, kbk, rf, df, kf, gam, xD, yD, _Mxy, "inverse")));
    w->import(*(new RooGLWADSDmixAcpVar(   "afav_dk_kskpi_th",     "RooGLWADSDmixAcpVar",    rbk, dbk, kbk, rf, df, kf, gam, xD, yD, _Mxy, AcpD)));
    w->import(*(new RooGLWADSDmixAcpADSVar("asup_dk_kskpi_th",     "RooGLWADSDmixAcpADSVar", rbk, dbk, kbk, rf, df, kf, gam, xD, yD, _Mxy, AcpD)));
    //}
  //w->import(*(new RooGLWADSDmixRkpVar      ("rkp_kpi_th",       "RooGLWADSDmixRkpVar"     , Rcab, rbk, dbk, kbk, rbp, dbp, kbp, rf, df, kf, gam, xD, yD, _Mxy, "fav")));

	//w->Print("v");

	//gammacombo_vals["aads_dk_kpi_th" ] = w->function("aads_dk_kpi_th" )->getVal();
	//gammacombo_vals["aads_dpi_kpi_th"] = w->function("aads_dpi_kpi_th")->getVal();
	//gammacombo_vals["acp_dk_kk_th"   ] = w->function("acp_dk_kk_th"   )->getVal();
	//gammacombo_vals["acp_dk_pipi_th" ] = w->function("acp_dk_pipi_th" )->getVal();
	//gammacombo_vals["acp_dpi_kk_th"  ] = w->function("acp_dpi_kk_th"  )->getVal();
	//gammacombo_vals["acp_dpi_pipi_th"] = w->function("acp_dpi_pipi_th")->getVal();
	//gammacombo_vals["afav_dk_kpi_th" ] = w->function("afav_dk_kpi_th" )->getVal();
	//gammacombo_vals["rads_dk_kpi_th" ] = w->function("rads_dk_kpi_th" )->getVal();
	//gammacombo_vals["rads_dpi_kpi_th"] = w->function("rads_dpi_kpi_th")->getVal();
	//gammacombo_vals["rcp_kk_th"      ] = w->function("rcp_kk_th"      )->getVal();
	//gammacombo_vals["rcp_pipi_th"    ] = w->function("rcp_pipi_th"    )->getVal();
	//gammacombo_vals["rkp_kpi_th"     ] = w->function("rkp_kpi_th"     )->getVal();
  //
  gammacombo_vals["rfavsup_dk_kskpi_th"] = w->function("rfavsup_dk_kskpi_th")->getVal();
  gammacombo_vals["afav_dk_kskpi_th"]    = w->function("afav_dk_kskpi_th")->getVal();
  gammacombo_vals["asup_dk_kskpi_th"]    = w->function("asup_dk_kskpi_th")->getVal();


	//cout <<  G_BmDK_CPP  << endl;
  //cout <<  G_BpDK_CPP  << endl;
  cout <<  G_BmDK_ADS  << endl;
  cout <<  G_BpDK_ADS  << endl;
  cout <<  G_BmDpi_ADS  << endl;
  cout <<  G_BpDpi_ADS  << endl;
  //cout <<  G_BmDK_FAV  << endl;
  //cout <<  G_BpDK_FAV  << endl;

	RooGLWADSDmixMaster m_dk(r_dk, d_dk, kb, rD_kpi, dD_kpi, kd, g, x, y, -Mxy);
	RooGLWADSDmixMaster m_dpi(r_dpi, d_dpi, kb, rD_kpi, dD_kpi, kd, g, x, y, -Mxy);
	cout << m_dpi.ABm2Dfhm() << endl;
	cout << m_dpi.ABp2Dfhp() << endl;
	//RooGLWADSDmixMaster mCP(r_dk, d_dk, kb, 1., 0., 1., g, x, y, -Mxy);
	//RooGLWADSDmixMaster mFav(r_dk, d_dk, kb, rD_kpi, dD_kpi, kd, g, x, y, -Mxy);
	//cout << mCP.ABm2Dfhm() << endl;
	//cout << mCP.ABp2Dfhp() << endl;
	//cout << mFav.ABm2Dbfhm() << endl;
	//cout << mFav.ABp2Dbfhp() << endl;

	for (map<TString,double>::iterator val=gammadini_vals.begin(); val!=gammadini_vals.end(); val++) {

		TString varname = val->first;
		double gd_value = val->second;
		if ( gammacombo_vals.find( varname ) == gammacombo_vals.end() ) {
			cout << "ERROR - " << varname << " not in gammacombo vals map" << endl;
			exit(1);
		}
		double gc_value = gammacombo_vals[varname];
		double diff = gd_value - gc_value;

		cout << Form("%-20s   --  %9.6f     %9.6f    -  %9.6f",varname.Data(),gd_value,gc_value,diff)  << endl;

	}

}

void GLWADSNumberCheck::eval4body(double fMxy=0.) {

	cout << "Mxy = " << fMxy << endl;
	RooMsgService::instance().setGlobalKillBelow(FATAL);
	RooMsgService::instance().setSilentMode(true);

	double ACPDKK     = -0.00215273;
	double ACPDPIPI   =  0.000608687;
	double RBRdkdpi   =  0.0775273;
	double dD_kpi     =  195.524 / (180./TMath::Pi());
	double d_dk       =  32.3679 / (180./TMath::Pi());
	double d_dpi      =  202.412 / (180./TMath::Pi());
	double rD_kpi     =  0.0590885;
	double r_dk       =  0.0991957;
	double r_dpi      =  0.00713259;
	double rD_k3pi    =  5.67004e-02;
	double dD_k3pi    =  1.92092e+02;
	double kD_k3pi    =  0.532453;
	double F_pipipipi =  0.738495;

	// for gammadini
	g          =  128.279 / (180./TMath::Pi());
	x          =  0.00342849;
	y          =  0.00683989;
	rb  = r_dk;
	rb2 = rb*rb;
	db  = d_dk;
	kb  = 1;
	rd  = rD_k3pi;
	rd2 = rd*rd;
	dd  = dD_k3pi;
	kd  = (2*F_pipipipi-1);
	Mxy = fMxy;

	double G_BmDK_CPP = G_b2DX_CPP();
	double G_BpDK_CPP = G_bbar2DX_CPP();

	kd = kD_k3pi;

  double G_BmDK_ADS = G_b2DX_ADS();
  double G_BpDK_ADS = G_bbar2DX_ADS();
  double G_BmDK_FAV = G_b2DX_FAV();
  double G_BpDK_FAV = G_bbar2DX_FAV();

	db = d_dpi;
	rb = r_dpi;
	rb2 = rb*rb;

  double G_BmDpi_ADS = G_b2DX_ADS();
  double G_BpDpi_ADS = G_bbar2DX_ADS();
  double G_BmDpi_FAV = G_b2DX_FAV();
  double G_BpDpi_FAV = G_bbar2DX_FAV();

	kd = (2*F_pipipipi-1);

  double G_BmDpi_CPP = G_b2DX_CPP();
  double G_BpDpi_CPP = G_bbar2DX_CPP();

	map<TString,double> gammadini_vals;
	map<TString,double> gammacombo_vals;

	bool both=false;
	bool dkonly=true;

	if ( both ) {
		gammadini_vals["rkp_k3pi_th"     ] = ( G_BmDK_FAV + G_BpDK_FAV ) / ( G_BmDpi_FAV + G_BpDpi_FAV ) * RBRdkdpi;
		gammadini_vals["rcp_pipipipi_th" ] = ( ( G_BmDK_CPP + G_BpDK_CPP ) / ( G_BmDK_FAV + G_BpDK_FAV ) ) / ( ( G_BmDpi_CPP + G_BpDpi_CPP ) / ( G_BmDpi_FAV + G_BpDpi_FAV ) );
	}
	else if ( dkonly ) {
		gammadini_vals["rcp_pipipipi_th"      ] = ( G_BmDK_CPP + G_BpDK_CPP ) / ( G_BmDK_FAV + G_BpDK_FAV );
	}
	if ( dkonly or both ) {
		gammadini_vals["afav_dk_k3pi_th" ]     = ( G_BmDK_FAV - G_BpDK_FAV ) / ( G_BmDK_FAV + G_BpDK_FAV );
		gammadini_vals["acp_dk_pipipipi_th" ] = ( G_BmDK_CPP - G_BpDK_CPP ) / ( G_BmDK_CPP + G_BpDK_CPP);
		gammadini_vals["rads_dk_k3pi_th" ] = ( G_BmDK_ADS + G_BpDK_ADS ) / ( G_BmDK_FAV + G_BpDK_FAV );
		gammadini_vals["aads_dk_k3pi_th" ] = ( G_BmDK_ADS - G_BpDK_ADS ) / ( G_BmDK_ADS + G_BpDK_ADS );
	}
	if ( both ) {
		gammadini_vals["acp_dpi_pipipipi_th"  ] = ( G_BmDpi_CPP - G_BpDpi_CPP ) / ( G_BmDpi_CPP + G_BpDpi_CPP );
		gammadini_vals["rads_dpi_k3pi_th"] = ( G_BmDpi_ADS + G_BpDpi_ADS ) / ( G_BmDpi_FAV + G_BpDpi_FAV );
		gammadini_vals["aads_dpi_k3pi_th"] = ( G_BmDpi_ADS - G_BpDpi_ADS ) / ( G_BmDpi_ADS + G_BpDpi_ADS );
	}

	RooConstVar rbk    ("rbk"   ,"",r_dk);
	RooConstVar dbk    ("dbk"   ,"",d_dk);
	RooConstVar kbk    ("kbk"   ,"",kb);
	double tmp_rbp;
	double tmp_dbp;
	if ( both ){
		tmp_rbp = r_dpi;
		tmp_dbp = d_dpi;
	}
	else if (dkonly) {
		tmp_rbp = 1.;
		tmp_dbp = 0.;
	}
	RooConstVar rbp    ("rbp"   ,"",tmp_rbp);
	RooConstVar dbp    ("dbp"   ,"",tmp_dbp);
	RooConstVar kbp    ("kbp"   ,"",1.);
	RooConstVar Rcab   ("Rcab"  ,"",RBRdkdpi);
	RooConstVar rf     ("rf"    ,"",rD_k3pi);
	RooConstVar df     ("df"    ,"",dD_k3pi);
	RooConstVar kf     ("kf"    ,"",kD_k3pi);
	RooConstVar F_4pi  ("F4pi"  ,"",F_pipipipi);
	RooFormulaVar k4pi ("k4pi"  ,"","2.*@0-1",F_4pi);
	RooConstVar rfGLW  ("rfGLW" ,"",1.);
	RooConstVar dfGLW  ("dfGLW" ,"",0.);
	RooConstVar gam    ("gam"   ,"",g);
	RooConstVar xD     ("xD"    ,"",x);
	RooConstVar yD     ("yD"    ,"",y);
	RooConstVar AcpD   ("AcpD"  ,"",0.);
	RooConstVar AcpDpppp ("AcpDpppp","",0.);
	double _Mxy = -Mxy;
	RooGLWADSDmixRcpNewVar rcp_dk_4pi("rcp_dk_4pi","rcp_dk_4pi", rbk, dbk, kbk, rfGLW, dfGLW, k4pi,rf,df,kf, gam, xD, yD, _Mxy);
	RooGLWADSDmixRcpNewVar rcp_dpi_4pi("rcp_dpi_4pi","rcp_dpi_4pi", rbp, dbp, kbp, rfGLW, dfGLW, k4pi, rf, df, kf, gam, xD, yD, _Mxy);
	//RooFormulaVar rcp_4pi("rcp_pipipipi_th", "rcp_4pi", "@0/@1", RooArgList(rcp_dk_4pi,rcp_dpi_4pi));

	RooWorkspace *w = new RooWorkspace("w","w");
	w->import(*(new RooGLWADSDmixAcpADSVar   ("aads_dk_k3pi_th",      "RooGLWADSDmixAcpADSVar"  , rbk, dbk, kbk, rf, df, kf, gam, xD, yD, _Mxy, AcpD)));
	w->import(*(new RooGLWADSDmixAcpADSVar   ("aads_dpi_k3pi_th",     "RooGLWADSDmixAcpADSVar"  , rbp, dbp, kbp, rf, df, kf, gam, xD, yD, _Mxy, AcpD)));
	w->import(*(new RooGLWADSDmixAcpVar      ("acp_dk_pipipipi_th",   "RooGLWADSDmixAcpVar"     , rbk, dbk, kbk, rfGLW, dfGLW, k4pi, gam, xD, yD, 0., AcpDpppp)));
	w->import(*(new RooGLWADSDmixAcpVar      ("acp_dpi_pipipipi_th",  "RooGLWADSDmixAcpVar"     , rbp, dbp, kbp, rfGLW, dfGLW, k4pi, gam, xD, yD, 0., AcpDpppp)),RooFit::RecycleConflictNodes());
	w->import(*(new RooGLWADSDmixAcpVar      ("afav_dk_k3pi_th",      "RooGLWADSDmixAcpVar"     , rbk, dbk, kbk, rf, df, kf, gam, xD, yD, _Mxy, AcpD)));
	w->import(*(new RooGLWADSDmixRADSVar     ("rads_dk_k3pi_th",      "RooGLWADSDmixRADSVar"    , rbk, dbk, kbk, rf, df, kf, gam, xD, yD, _Mxy, "")));
	w->import(*(new RooGLWADSDmixRADSVar     ("rads_dpi_k3pi_th",     "RooGLWADSDmixRADSVar"    , rbp, dbp, kbp, rf, df, kf, gam, xD, yD, _Mxy, "")));
	if (both){
		//w->import(*(new RooGLWADSDmixRcpRatioVar ("rcp_pipipipi_th", 		"RooGLWADSDmixRcpRatioVar", rbk, dbk, kbk, rbp, dbp, kbp, rf, df, k4pi, gam, xD, yD, _Mxy)),RooFit::RecycleConflictNodes());
		w->import(*(new RooFormulaVar          ("rcp_pipipipi_th",     "RooFormulaVar"             , "@0/@1", RooArgList(rcp_dk_4pi,rcp_dpi_4pi))), RooFit::RecycleConflictNodes());
		w->import(*(new RooGLWADSDmixRkpVar    ("rkp_k3pi_th",       "RooGLWADSDmixRkpVar"       , Rcab, rbk, dbk, kbk, rbp, dbp, kbp, rf, df, kf, gam, xD, yD, _Mxy, "fav")));
	}
	else if (dkonly) {
		w->import(*(new RooGLWADSDmixRcpNewVar   ("rcp_pipipipi_th", 		  "RooGLWADSDmixRcpNewVar"  , rbk, dbk, kbk, rfGLW, dfGLW, k4pi,rf,df,kf, gam, xD, yD, _Mxy)), RooFit::RecycleConflictNodes());
	}

	//w->Print("v");

	// for 4-body DK only
	//RooGLWADSDmixMaster m_dk_k3pi_CP(r_dk, d_dk, kb, 1., 0., 2.*F_pipipipi-1., g, x, y, 0.);
	//RooGLWADSDmixMaster m_dk_k3pi_Fav(r_dk, d_dk, kb, rD_k3pi, dD_k3pi, kD_k3pi, g, x, y, -Mxy);
	//cout << m_dk_k3pi_CP.ABm2Dfhm() << endl;
	//cout << m_dk_k3pi_CP.ABp2Dfhp() << endl;
	//cout << m_dk_k3pi_Fav.ABm2Dbfhm() << endl;
	//cout << m_dk_k3pi_Fav.ABp2Dbfhp() << endl;
	RooGLWADSDmixMaster m(r_dk, d_dk, kb, rD_k3pi, dD_k3pi,2*F_pipipipi-1.,g,x,y,-Mxy);
	cout << m.ABm2Dbfhm() << endl;
	cout << m.ABp2Dbfhp() << endl;
	cout << G_BmDK_CPP << endl;
	cout << G_BpDK_CPP << endl;
	//cout << G_BmDK_FAV << endl;
	//cout << G_BpDK_FAV << endl;
	// for ADS stuff
	//RooGLWADSDmixMaster mp (r_dpi, d_dpi, kb, rD_k3pi, dD_k3pi, kD_k3pi, g, x, y, -Mxy);
	//RooGLWADSDmixMaster mk (r_dk , d_dk , kb, rD_k3pi, dD_k3pi, kD_k3pi, g, x, y, -Mxy);
	//cout << mp.ABm2Dfhm() << endl;
	//cout << mp.ABp2Dfhp() << endl;
	//cout << mk.ABm2Dfhm() << endl;
	//cout << mk.ABp2Dfhp() << endl;
	//cout << G_BmDpi_ADS << endl;
	//cout << G_BpDpi_ADS << endl;
	//cout << G_BmDK_ADS << endl;
	//cout << G_BpDK_ADS << endl;

	gammacombo_vals["aads_dk_k3pi_th" ] = w->function("aads_dk_k3pi_th" )->getVal();
	gammacombo_vals["aads_dpi_k3pi_th"] = w->function("aads_dpi_k3pi_th")->getVal();
	gammacombo_vals["acp_dk_pipipipi_th" ] = w->function("acp_dk_pipipipi_th" )->getVal();
	gammacombo_vals["acp_dpi_pipipipi_th" ] = w->function("acp_dpi_pipipipi_th" )->getVal();
	gammacombo_vals["afav_dk_k3pi_th" ] = w->function("afav_dk_k3pi_th" )->getVal();
	gammacombo_vals["rads_dk_k3pi_th" ] = w->function("rads_dk_k3pi_th" )->getVal();
	gammacombo_vals["rads_dpi_k3pi_th"] = w->function("rads_dpi_k3pi_th")->getVal();
	gammacombo_vals["rcp_pipipipi_th" ] = w->function("rcp_pipipipi_th"    )->getVal();
	if (both) gammacombo_vals["rkp_k3pi_th"      ] = w->function("rkp_k3pi_th"     )->getVal();

	for (map<TString,double>::iterator val=gammadini_vals.begin(); val!=gammadini_vals.end(); val++) {

		TString varname = val->first;
		double gd_value = val->second;
		if ( gammacombo_vals.find( varname ) == gammacombo_vals.end() ) {
			cout << "ERROR - " << varname << " not in gammacombo vals map" << endl;
			exit(1);
		}
		double gc_value = gammacombo_vals[varname];
		double diff = gd_value - gc_value;

		cout << Form("%-20s   --  %9.6f     %9.6f    -  %9.6f",varname.Data(),gd_value,gc_value,diff)  << endl;

	}

}
