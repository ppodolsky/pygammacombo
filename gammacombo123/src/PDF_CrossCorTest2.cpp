/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: July 2014
 *
 **/

#include "PDF_CrossCorTest2.h"

	PDF_CrossCorTest2::PDF_CrossCorTest2(config cObs, config cErr, config cCor)
: PDF_Abs(3)
{
	name = "CrossCorTest2";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_CrossCorTest2::~PDF_CrossCorTest2(){}


void PDF_CrossCorTest2::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("l_dsk"))); 
	parameters->add(*(p.get("d_dsk"))); 
	parameters->add(*(p.get("g")));
	parameters->add(*(p.get("phis")));
}


void PDF_CrossCorTest2::initRelations()
{
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	RooArgSet *p = (RooArgSet*)parameters;
	theory->add(*(new RooFormulaVar("d_dsk_th",  "D  (DsK) th", "2*l_dsk*cos(d_dsk-(g+phis))/(1+l_dsk^2)", *p)));
	theory->add(*(new RooFormulaVar("db_dsk_th", "Db (DsK) th", "2*l_dsk*cos(d_dsk+(g+phis))/(1+l_dsk^2)", *p)));
	theory->add(*(new RooFormulaVar("phis_th",   "phis_th", "phis", *p)));
}


void PDF_CrossCorTest2::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("d_dsk_obs",     "D    (DsK)", 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("db_dsk_obs",    "Dbar (DsK)", 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("phis_obs",  "phis", 0, -1e4, 1e4)));
}


void PDF_CrossCorTest2::setObservables(config c)
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
								  setObservable("d_dsk_obs",    -0.369634 );
								  setObservable("db_dsk_obs",   -0.203693 );
								  setObservable("phis_obs",      0.01); // 1304.2600
								  break;
							  }
		default:{
					cout << "PDF_CrossCorTest2::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_CrossCorTest2::setUncertainties(config c)
{
	switch(c)
	{
		case lumi1fbPapercFit:{
								  obsErrSource = "PAPER 25.6.2014 After bug fix, mail by Manuel";
								  StatErr[0] = 0.422738; // d
								  StatErr[1] = 0.413971; // db
								  StatErr[2] = 0.07; // phis // 1304.2600
								  SystErr[0] = 0.466*StatErr[0]; // d
								  SystErr[1] = 0.470*StatErr[1]; // db
								  SystErr[2] = 0.01; // phis // 1304.2600
								  break;
							  }
		default:{
					cout << "PDF_CrossCorTest2::setUncertainties() : ERROR : config cErr not found:" << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}


void PDF_CrossCorTest2::setCorrelations(config c)
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
								  //                     d       db     phis
								  double dataStat[]  = { 1.000,  0.544, 0.000,  // d
									  0.544,  1.000, 0.000,  // db
									  0.000,  0.000, 1.000}; // phis
								  corStatMatrix = TMatrixDSym(nObs,dataStat);
								  //                      d      db   phis
								  double dataSyst[]  = { 1.  ,  0.96, 0.00,  // d
									  0.96,  1.  , 0.00,  // db
									  0.00,  0.00, 1.00}; // phis
								  corSystMatrix = TMatrixDSym(nObs,dataSyst);
								  break;
							  }
		default:{
					cout << "PDF_CrossCorTest2::setCorrelations() : ERROR : config cCor not found." << ConfigToTString(c) << endl;
					exit(1);
				}
	}
}  


void PDF_CrossCorTest2::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
