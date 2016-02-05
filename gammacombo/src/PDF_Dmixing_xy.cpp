/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: June 2014
 *
 **/

#include "PDF_Dmixing_xy.h"

	PDF_Dmixing_xy::PDF_Dmixing_xy(config cObs, config cErr, config cCor)
: PDF_Abs(2)
{
	name = "DmixingXY";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_Dmixing_xy::~PDF_Dmixing_xy(){}


void PDF_Dmixing_xy::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("xD")));
	parameters->add(*(p.get("yD")));
}


void PDF_Dmixing_xy::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	theory->add(*(new RooFormulaVar("xD_th", "xD_th", "xD", *p)));
	theory->add(*(new RooFormulaVar("yD_th", "yD_th", "yD", *p)));
}


void PDF_Dmixing_xy::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("xD_obs", "xD",  0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("yD_obs", "yD",  0, -1e4, 1e4)));
}


void PDF_Dmixing_xy::setObservables(config c)
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
		case hfagLP2011:{
							obsValSource = "HFAG LP2011 CPV allowed http://www.slac.stanford.edu/xorg/hfag/charm/LP11/results_mix+cpv.html";
							setObservable("xD_obs", 0.0063);
							setObservable("yD_obs", 0.0075);
							break;
						}
		case hfag:{
					  obsValSource = "HFAG 2014 CPV allowed http://www.slac.stanford.edu/xorg/hfag/charm/CHARM13/results_mix+cpv.html";
					  setObservable("xD_obs", 0.0039);
					  setObservable("yD_obs", 0.0067);
					  break;
				  }
		case lhcb2012:{
			          //added by sam harnew - the above numbers seem to be the Nov2013 results at http://www.slac.stanford.edu/xorg/hfag/charm/CHARM13/results_mix_cpv.html
					  obsValSource = "HFAG 2014 CPV allowed"; // (From website, above looks to be 2013???!) http://www.slac.stanford.edu/xorg/hfag/charm/FPCP14/results_mix_cpv.html";
					  setObservable("xD_obs", 0.00414);
					  setObservable("yD_obs", 0.00627);
					  break;
				  }
		default:{
					cout << "PDF_Dmixing_xy::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_Dmixing_xy::setUncertainties(config c)
{
	switch(c)
	{
		case hfagLP2011:{
							obsErrSource = "HFAG LP2011 CPV allowed http://www.slac.stanford.edu/xorg/hfag/charm/LP11/results_mix+cpv.html";
							StatErr[0] = 0.0020; // xD
							StatErr[1] = 0.0012; // yD
							SystErr[0] = 0; // xD
							SystErr[1] = 0; // yD
							break;
						}
		case hfag:{
					  obsErrSource = "HFAG 2014 CPV allowed http://www.slac.stanford.edu/xorg/hfag/charm/CHARM13/results_mix+cpv.html";
					  StatErr[0] = 0.0017; // xD
					  StatErr[1] = 0.0008; // yD
					  SystErr[0] = 0; // xD
					  SystErr[1] = 0; // yD
					  break;
				  }
	    case lhcb2012:{
			          //added by sam harnew - the above numbers seem to be the Nov2013 results at http://www.slac.stanford.edu/xorg/hfag/charm/CHARM13/results_mix_cpv.html
					  obsErrSource = "HFAG 2014 CPV allowed"; // (From website, above looks to be 2013???!) http://www.slac.stanford.edu/xorg/hfag/charm/FPCP14/results_mix_cpv.html";
					  StatErr[0] = 0.00144; // xD
					  StatErr[1] = 0.00074; // yD
					  SystErr[0] = 0; // xD
					  SystErr[1] = 0; // yD
					  break;
				  }
		default:{
					cout << "PDF_Dmixing_xy::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_Dmixing_xy::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case hfagLP2011:{
							corSource = "HFAG LP2011 CPV allowed http://www.slac.stanford.edu/xorg/hfag/charm/LP11/results_mix+cpv.html";
							corStatMatrix[1][0] =  0.037; // xD, yD
							corSystMatrix[1][0] =  0.0;   // xD, yD
							break;
						}
		case hfag:{
					  corSource = "HFAG 2014 CPV allowed http://www.slac.stanford.edu/xorg/hfag/charm/CHARM13/results_mix+cpv.html";
					  corStatMatrix[1][0] = -0.218; // xD, yD
					  corSystMatrix[1][0] =  0.0;   // xD, yD
					  break;
				  }
		case lhcb2012:{
			          //added by sam harnew - the above numbers seem to be the Nov2013 results at http://www.slac.stanford.edu/xorg/hfag/charm/CHARM13/results_mix_cpv.html
					  corSource = "HFAG 2014 CPV allowed"; // (From website, above looks to be 2013???!) http://www.slac.stanford.edu/xorg/hfag/charm/FPCP14/results_mix_cpv.html";
					  corStatMatrix[1][0] = -0.27; // xD, yD
					  corSystMatrix[1][0] =  0.0;   // xD, yD
					  break;
				  }
		default:{
					cout << "PDF_Dmixing_xy::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_Dmixing_xy::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
