/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: July 2014
 *
 **/

#include "PDF_CrossCorTest1.h"

	PDF_CrossCorTest1::PDF_CrossCorTest1(config cObs, config cErr, config cCor)
: PDF_Abs(3)
{
	name = "CrossCorTest1";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_CrossCorTest1::~PDF_CrossCorTest1(){}


void PDF_CrossCorTest1::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("l_dsk"))); 
	parameters->add(*(p.get("d_dsk"))); 
	parameters->add(*(p.get("g")));
	parameters->add(*(p.get("phis")));
}


void PDF_CrossCorTest1::initRelations()
{
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	RooArgSet *p = (RooArgSet*)parameters;
	theory->add(*(new RooFormulaVar("c_dsk_th",  "C  (DsK) th", "(1-l_dsk^2)/(1+l_dsk^2)",                 *p)));
	theory->add(*(new RooFormulaVar("s_dsk_th",  "S  (DsK) th", "2*l_dsk*sin(d_dsk-(g+phis))/(1+l_dsk^2)", *p)));
	theory->add(*(new RooFormulaVar("sb_dsk_th", "Sb (DsK) th", "2*l_dsk*sin(d_dsk+(g+phis))/(1+l_dsk^2)", *p)));
}


void PDF_CrossCorTest1::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("c_dsk_obs",     "C    (DsK)", 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("s_dsk_obs",     "S    (DsK)", 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("sb_dsk_obs",    "Sbar (DsK)", 0, -1e4, 1e4)));
}


void PDF_CrossCorTest1::setObservables(config c)
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
		case lumi1fbPapercFit:{
								  obsValSource = "PAPER 25.6.2014 After bug fix, mail by Manuel";
								  setObservable("c_dsk_obs",     0.526386 );
								  setObservable("s_dsk_obs",    -1.08902 );
								  setObservable("sb_dsk_obs",    0.356743 );
								  break;
							  }
		default:{
					cout << "PDF_CrossCorTest1::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_CrossCorTest1::setUncertainties(config c)
{
	switch(c)
	{
		case lumi1fbPapercFit:{
								  obsErrSource = "PAPER 25.6.2014 After bug fix, mail by Manuel";
								  StatErr[0] = 0.245460; // c
								  StatErr[1] = 0.333093; // s
								  StatErr[2] = 0.334950; // sb
								  SystErr[0] = 0.187*StatErr[0]; // c
								  SystErr[1] = 0.234*StatErr[1]; // s
								  SystErr[2] = 0.226*StatErr[2]; // sb
								  break;
							  }
		default:{
					cout << "PDF_CrossCorTest1::setUncertainties() : ERROR : config cErr not found:" << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}

///
/// Set the correlations manually after the PDF object was created already.
/// This way one can make easy toy studies.
/// The default is to not set any systematic correlations (systCor=zero).
/// Alternatively one can use pre-defined systematics correlaions (e.g. systCor=lumi1fbPapercFit).
///
void PDF_CrossCorTest1::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case manual:{
						corSource = "manual";
						break;
					}
		case lumi1fbPapercFit:{
								  corSource = "PAPER 25.6.2014 After bug fix, mail by Manuel, stat. manually parsed from logfile";
								  // the logfile: /afs/cern.ch/work/m/mschille/public/cFit-v3c/paper-dsk-v3c-w-constraints-w-combo-fixed-kfactordebugged-Bd2DsKFixed] $ vi nominal.log
								  //                      c      s       sb    
								  double dataStat[]  = { 1.000, -0.008,  0.045,  // c
									  -0.008,  1.000, -0.002,  // s
									  0.045, -0.002,  1.000 }; // sb
								  corStatMatrix = TMatrixDSym(nObs,dataStat);
								  //                      c     s      sb  
								  double dataSyst[]  = { 1.  , -0.04,  0.03,   // c
									  -0.04,  1.  , -0.09,   // s
									  0.03, -0.09,  1.   }; // sb
								  corSystMatrix = TMatrixDSym(nObs,dataSyst);
								  break;
							  }
		default:{
					cout << "PDF_CrossCorTest1::setCorrelations() : ERROR : config cCor not found." << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}  


void PDF_CrossCorTest1::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
