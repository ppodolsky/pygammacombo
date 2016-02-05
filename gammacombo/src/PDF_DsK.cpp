/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#include "PDF_DsK.h"

	PDF_DsK::PDF_DsK(config cObs, config cErr, config cCor)
: PDF_Abs(6)
{
	name = "dsk";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_DsK::~PDF_DsK(){}


void PDF_DsK::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("l_dsk")));
	parameters->add(*(p.get("d_dsk")));
	parameters->add(*(p.get("g")));
	parameters->add(*(p.get("phis")));
}


void PDF_DsK::initRelations()
{
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	RooArgSet *p = (RooArgSet*)parameters;
	theory->add(*(new RooFormulaVar("c_dsk_th",  "C  (DsK) th", "(1-l_dsk^2)/(1+l_dsk^2)",                 *p)));
	theory->add(*(new RooFormulaVar("d_dsk_th",  "D  (DsK) th", "2*l_dsk*cos(d_dsk-(g+phis))/(1+l_dsk^2)", *p)));
	theory->add(*(new RooFormulaVar("db_dsk_th", "Db (DsK) th", "2*l_dsk*cos(d_dsk+(g+phis))/(1+l_dsk^2)", *p)));
	theory->add(*(new RooFormulaVar("s_dsk_th",  "S  (DsK) th", "2*l_dsk*sin(d_dsk-(g+phis))/(1+l_dsk^2)", *p)));
	theory->add(*(new RooFormulaVar("sb_dsk_th", "Sb (DsK) th", "2*l_dsk*sin(d_dsk+(g+phis))/(1+l_dsk^2)", *p)));
	theory->add(*(new RooFormulaVar("phis_th",   "phis_th", "phis", *p)));
}


void PDF_DsK::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("c_dsk_obs",     "C    (DsK)", 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("d_dsk_obs",     "D    (DsK)", 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("db_dsk_obs",    "Dbar (DsK)", 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("s_dsk_obs",     "S    (DsK)", 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("sb_dsk_obs",    "Sbar (DsK)", 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("phis_obs",  "phis", 0, -1e4, 1e4)));
}


void PDF_DsK::setObservables(config c)
{
	switch(c)
	{
		case truth:{
					   setObservablesTruth();
					   break;
				   }
		case toy:{
					 setObservablesToy();
					 break;
				 }
		case manual:{
						obsValSource = "manual";
						break;
					}
		case highstattoy:{
							 // - /afs/cern.ch/work/g/gligorov/public/Bs2DsKToys/sWeightToys/DsK_Toys_FullLarge_TimeFitResult_104.log
							 // - phis value from https://cdsweb.cern.ch/record/1423592/files/LHCb-CONF-2012-002.pdf
							 obsValSource = "CONF high stats toy";
							 setObservable("c_dsk_obs",    8.40472e-01 );
							 setObservable("d_dsk_obs",    3.39525e-01 );
							 setObservable("db_dsk_obs",   1.82419e-02 );
							 setObservable("s_dsk_obs",    -6.61647e-01 );
							 setObservable("sb_dsk_obs",   6.70404e-01 );
							 setObservable("phis_obs", -0.002);
							 break;
						 }
		case lumi1fbConfcFit:{
								 obsValSource = "CONF unblinding session";
								 // 14.9.2012 afternoon
								 setObservable("c_dsk_obs",     0.736 );
								 setObservable("d_dsk_obs",    -1.710 );
								 setObservable("db_dsk_obs",   -1.006 );
								 setObservable("s_dsk_obs",    -1.245 );
								 setObservable("sb_dsk_obs",    0.229 );
								 setObservable("phis_obs", 0.002);
								 break;
							 }
		case lumi1fbConfsFit:{
								 obsValSource = "CONF unblinding session";
								 // 14.9.2012 afternoon
								 setObservable("c_dsk_obs",     1.01 );
								 setObservable("d_dsk_obs",    -1.33 );
								 setObservable("db_dsk_obs",   -0.81 );
								 setObservable("s_dsk_obs",    -1.25 );
								 setObservable("sb_dsk_obs",    0.083);
								 setObservable("phis_obs", 0.002);
								 break;
							 }
		case lumi1fbPapercFit:{
								  obsValSource = "PAPER 25.6.2014 After bug fix, mail by Manuel";
								  setObservable("c_dsk_obs",     0.526386 );
								  setObservable("d_dsk_obs",    -0.369634 );
								  setObservable("db_dsk_obs",   -0.203693 );
								  setObservable("s_dsk_obs",    -1.08902 );
								  setObservable("sb_dsk_obs",    0.356743 );
								  setObservable("phis_obs",     -0.01); // 3fb JpsiHH comb
								  break;
							  }
		case lumi1fbPapersFit:{
								  obsValSource = "PAPER 3.6.2014 - unblinding - 12:14";
								  setObservable("c_dsk_obs",     0.522573 );
								  setObservable("d_dsk_obs",    -0.289873 );
								  setObservable("db_dsk_obs",   -0.142569 );
								  setObservable("s_dsk_obs",    -0.897375 );
								  setObservable("sb_dsk_obs",    0.363515);
								  setObservable("phis_obs",      0.01); // 1304.2600
								  break;
							  }
		default:{
					cout << "PDF_DsK::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_DsK::setObservables(float c, float d, float db, float s, float sb, float phis_obs)
{
	obsValSource = "manual";
	setObservable("c_dsk_obs",     c  );
	setObservable("d_dsk_obs",     d  );
	setObservable("db_dsk_obs",    db );
	setObservable("s_dsk_obs",     s  );
	setObservable("sb_dsk_obs",    sb );
	setObservable("phis_obs",  phis_obs );
}

///
/// Set the errors manually after the PDF object was created already.
/// This way one can make easy toy studies.
/// The default is to not set any systematic errors (systErr=zero).
/// Alternatively one can use pre-defined systematics (e.g. systErr=lumi1fbPapercFit).
///
void PDF_DsK::setErrors(float ec, float ed, float edb, float es, float esb, float ephis_obs, config systErr)
{
	if ( systErr!=zero ){
		setUncertainties(systErr); // also sets stat, but we overwrite them below.
	}
	else{
		SystErr[0] = 0.; // c
		SystErr[1] = 0.; // d
		SystErr[2] = 0.; // db
		SystErr[3] = 0.; // s
		SystErr[4] = 0.; // sb
		SystErr[5] = 0.; // phis
	}
	StatErr[0] = ec ;
	StatErr[1] = ed ;
	StatErr[2] = edb;
	StatErr[3] = es ;
	StatErr[4] = esb;
	StatErr[5] = ephis_obs;
	obsErrSource = "stat=manual, syst="+ConfigToTString(systErr);
	buildCov();
}


void PDF_DsK::setUncertainties(config c)
{
	switch(c)
	{
		case manual:{
						obsErrSource = "manual";
						// set errors to non-zero dummy values else the cov cannot be built
						StatErr[0] = 1.; // c
						StatErr[1] = 1.; // d
						StatErr[2] = 1.; // db
						StatErr[3] = 1.; // s
						StatErr[4] = 1.; // sb
						StatErr[5] = 1.; // phis
						break;
					}
		case lumi1fbConfcFit:{
								 // 14.9.2012 afternoon
								 StatErr[0] = 0.394; // c
								 StatErr[1] = 0.636; // d
								 StatErr[2] = 0.561; // db
								 StatErr[3] = 0.520; // s
								 StatErr[4] = 0.586; // sb
								 StatErr[5] = 0.087; // phis
								 SystErr[0] = 0.; // c
								 SystErr[1] = 0.; // d
								 SystErr[2] = 0.; // db
								 SystErr[3] = 0.; // s
								 SystErr[4] = 0.; // sb
								 SystErr[5] = 0.; // phis
								 break;
							 }
		case lumi1fbConfsFit:{
								 // 14.9.2012 afternoon
								 StatErr[0] = 0.50; // c
								 StatErr[1] = 0.60; // d
								 StatErr[2] = 0.56; // db
								 StatErr[3] = 0.56; // s
								 StatErr[4] = 0.68; // sb
								 StatErr[5] = 0.087; // phis
								 SystErr[0] = 0.23; // c
								 SystErr[1] = 0.26; // d
								 SystErr[2] = 0.26; // db
								 SystErr[3] = 0.28; // s
								 SystErr[4] = 0.24; // sb
								 SystErr[5] = 0.; // phis
							 }
		case lumi1fbPapercFit:{
								  obsErrSource = "PAPER 25.6.2014 After bug fix, mail by Manuel";
								  StatErr[0] = 0.245460; // c
								  StatErr[1] = 0.422738; // d
								  StatErr[2] = 0.413971; // db
								  StatErr[3] = 0.333093; // s
								  StatErr[4] = 0.334950; // sb
								  StatErr[5] = 0.039; // phis // 1304.2600
								  SystErr[0] = 0.187*StatErr[0]; // c
								  SystErr[1] = 0.466*StatErr[1]; // d
								  SystErr[2] = 0.470*StatErr[2]; // db
								  SystErr[3] = 0.234*StatErr[3]; // s
								  SystErr[4] = 0.226*StatErr[4]; // sb
								  SystErr[5] = 0.0; // phis // 1304.2600
								  break;
							  }
		case lumi1fbPapercFitExpected:{
										  obsErrSource = "LHCb-ANA-2012-123, v2, Tab 65";
										  StatErr[0] = 0.235; // c
										  StatErr[1] = 0.422; // d
										  StatErr[2] = 0.425; // db
										  StatErr[3] = 0.326; // s
										  StatErr[4] = 0.338; // sb
										  StatErr[5] = 0.07; // phis // 1304.2600
										  SystErr[0] = 0.187*StatErr[0]; // c
										  SystErr[1] = 0.466*StatErr[1]; // d
										  SystErr[2] = 0.470*StatErr[2]; // db
										  SystErr[3] = 0.234*StatErr[3]; // s
										  SystErr[4] = 0.226*StatErr[4]; // sb
										  SystErr[5] = 0.01; // phis // 1304.2600
										  break;
									  }
		case lumi1fbPapersFit:{
								  obsErrSource = "PAPER expected errors, LHCb-ANA-2012-123 v2 Tab 42 (stat) and Tab 47 (29.04.2014)";
								  StatErr[0] = 0.253; // c
								  StatErr[1] = 0.417; // d
								  StatErr[2] = 0.407; // db
								  StatErr[3] = 0.308; // s
								  StatErr[4] = 0.344; // sb
								  StatErr[5] = 0.07; // phis // 1304.2600
								  SystErr[0] = 0.179*StatErr[0]; // c
								  SystErr[1] = 0.427*StatErr[1]; // d
								  SystErr[2] = 0.437*StatErr[2]; // db
								  SystErr[3] = 0.161*StatErr[3]; // s
								  SystErr[4] = 0.160*StatErr[4]; // sb
								  SystErr[5] = 0.01; // phis // 1304.2600
								  break;
							  }
		case lumi3fb:{
						 setUncertainties(lumi1fbPapercFit);
						 obsErrSource = "3fb-1 errors obtained from scaling down the 1fb-1 errors (lumi1fbPapercFit)";
						 for ( int i=0; i<nObs; i++ ){
							 StatErr[i] /= sqrt(3.);
							 SystErr[i] /= sqrt(3.); // in DsK the systematics scale with the statistics
						 }
						 break;
					 }
		case lumi9fb:{
						 setUncertainties(lumi1fbPapercFit);
						 obsErrSource = "9fb-1 errors obtained from scaling down the 1fb-1 errors (lumi1fbPapercFit)";
						 for ( int i=0; i<nObs; i++ ){
							 StatErr[i] /= (sqrt(3.) * sqrt(2.7));
							 SystErr[i] /= (sqrt(3.) * sqrt(2.7));
						 }
						 break;
					 }
		case lumi50fb:{
						  setUncertainties(lumi1fbPapercFitExpected);
						  obsErrSource = "50fb-1 errors obtained from scaling down the 1fb-1 errors (lumi1fbPapercFitExpected)";
						  for ( int i=0; i<nObs; i++ ){
							  StatErr[i] /= (sqrt(130.));
							  SystErr[i] /= (sqrt(130.));
						  }
						  break;
					  }
		default:{
					cout << "PDF_DsK::setUncertainties() : ERROR : config cErr not found:" << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}


void PDF_DsK::setCorrelations(TMatrixDSym &c, config systCor)
{
	setCorrelations(systCor); // also sets stat, but we overwrite them below.
	corSource = "stat=manual, syst="+ConfigToTString(systCor);
	for ( int j=0; j<6; j++ )
		for ( int k=0; k<6; k++ ){
			corStatMatrix[j][k] = c[j][k];
		}
	buildCov();
}

///
/// Set the correlations manually after the PDF object was created already.
/// This way one can make easy toy studies.
/// The default is to not set any systematic correlations (systCor=zero).
/// Alternatively one can use pre-defined systematics correlaions (e.g. systCor=lumi1fbPapercFit).
///
void PDF_DsK::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case manual:{
						corSource = "manual";
						break;
					}
		case highstattoy:{
							 // stat cor from Vava's "high statitics toy"
							 // /afs/cern.ch/work/g/gligorov/public/Bs2DsKToys/sWeightToys/DsK_Toys_FullLarge_TimeFitResult_104.log
							 //
							 // no syst cor
							 //
							 corStatMatrix[1][0] = -0.118; // d, c
							 corStatMatrix[2][0] = -0.110; // db, c
							 corStatMatrix[2][1] =  0.515; // db, d
							 corStatMatrix[3][0] =  0.032; // s, c
							 corStatMatrix[3][1] =  0.041; // s, d
							 corStatMatrix[3][2] =  0.086; // s, db
							 corStatMatrix[4][0] = -0.039; // sb, c
							 corStatMatrix[4][1] = -0.122; // sb, d
							 corStatMatrix[4][2] = -0.060; // sb, db
							 corStatMatrix[4][3] = -0.007; // sb, s
							 break;
						 }
		case lumi1fbConfcFit:{
								 // 14.9.2012 afternoon
								 corStatMatrix[1][0] = -0.110; // d, c
								 corStatMatrix[2][0] = -0.102; // db, c
								 corStatMatrix[2][1] =  0.598; // db, d
								 corStatMatrix[3][0] =  0.042; // s, c
								 corStatMatrix[3][1] =  0.112; // s, d
								 corStatMatrix[3][2] =  0.071; // s, db
								 corStatMatrix[4][0] = -0.003; // sb, c
								 corStatMatrix[4][1] = -0.006; // sb, d
								 corStatMatrix[4][2] = -0.011; // sb, db
								 corStatMatrix[4][3] =  0.006; // sb, s
								 break;
							 }
		case lumi1fbConfsFit:{
								 // 14.9.2012 afternoon
								 corStatMatrix[1][0] = -0.155; // d, c
								 corStatMatrix[2][0] = -0.137; // db, c
								 corStatMatrix[2][1] =  0.566; // db, d
								 corStatMatrix[3][0] = -0.110; // s, c
								 corStatMatrix[3][1] = -0.057; // s, d
								 corStatMatrix[3][2] = -0.025; // s, db
								 corStatMatrix[4][0] =  0.174; // sb, c
								 corStatMatrix[4][1] = -0.026; // sb, d
								 corStatMatrix[4][2] = -0.016; // sb, db
								 corStatMatrix[4][3] = -0.020; // sb, s
								 break;
							 }
		case lumi1fbPapercFit:{
								  corSource = "PAPER 25.6.2014 After bug fix, mail by Manuel, stat. manually parsed from logfile";
								  // the logfile: /afs/cern.ch/work/m/mschille/public/cFit-v3c/paper-dsk-v3c-w-constraints-w-combo-fixed-kfactordebugged-Bd2DsKFixed] $ vi nominal.log
								  //                      c      d       db      s       sb      phis
								  double dataStat[]  = { 1.000, -0.084, -0.103, -0.008,  0.045,  0.000,  // c
									  -0.084,  1.000,  0.544,  0.117, -0.022,  0.000,  // d
									  -0.103,  0.544,  1.000,  0.067, -0.032,  0.000,  // db
									  -0.008,  0.117,  0.067,  1.000, -0.002,  0.000,  // s
									  0.045, -0.022, -0.032, -0.002,  1.000,  0.000,  // sb
									  0.000,  0.000,  0.000,  0.000,  0.000,  1.000}; // phis
								  corStatMatrix = TMatrixDSym(nObs,dataStat);
								  //                      c      d      db    s      sb     phis
								  double dataSyst[]  = { 1.  , -0.22, -0.22, -0.04,  0.03,  0.00,  // c
									  -0.22,  1.  ,  0.96,  0.17, -0.14,  0.00,  // d
									  -0.22,  0.96,  1.  ,  0.17, -0.14,  0.00,  // db
									  -0.04,  0.17,  0.17,  1.  , -0.09,  0.00,  // s
									  0.03, -0.14, -0.14, -0.09,  1.  ,  0.00,  // sb
									  0.00,  0.00,  0.00,  0.00,  0.00,  1.00}; // phis
								  corSystMatrix = TMatrixDSym(nObs,dataSyst);
								  break;
							  }
		case lumi1fbPapersFit:{
								  corSource = "LHCb-ANA-2012-123 v2 (29.05.2014) stat: Tab 43; syst: Tab 49";
								  //                     c       d       db      s       sb      phis
								  double dataStat[]  = {1.000   , -0.071  ,-0.097   , 0.117   , 0.042 ,  0.000,  // c
									  -0.071  , 1.000   , 0.500   , 0.044   , -0.003,  0.000,  // d
									  -0.097  , 0.500   , 1.000   , 0.013   , -0.005,  0.000,  // db
									  0.117   , 0.044   , 0.013   , 1.000   , -0.007,  0.000,  // s
									  0.042   , -0.003  , -0.005  , -0.007  , 1.000 ,  0.000,  // sb
									  0.000,  0.000,  0.000,  0.000,  0.000,  1.000}; // phis
								  corStatMatrix = TMatrixDSym(nObs,dataStat);
								  //                      c      d      db    s      sb     phis
								  double dataSyst[]  = { 1.  , -0.18, -0.18, -0.04,  0.04,  0.00,  // c
									  -0.18,  1.  ,  0.95,  0.17, -0.16,  0.00,  // d
									  -0.18,  0.95,  1.  ,  0.17, -0.16,  0.00,  // db
									  -0.04,  0.17,  0.17,  1.  , -0.05,  0.00,  // s
									  0.04, -0.16, -0.16, -0.05,  1.  ,  0.00,  // sb
									  0.00,  0.00,  0.00,  0.00,  0.00,  1.00}; // phis
								  corSystMatrix = TMatrixDSym(nObs,dataSyst);
								  break;
							  }
		case zero:{
					  // all elements are zero by default
					  break;
				  }
		default:{
					cout << "PDF_DsK::setCorrelations() : ERROR : config cCor not found." << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}


void PDF_DsK::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
