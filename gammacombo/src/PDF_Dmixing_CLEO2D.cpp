///
///  PDF_Dmixing_CLEO2D.cpp
///
///
///  Created by Matthew Kenzie on 11/07/14.
///
#include "PDF_Dmixing_CLEO2D.h"

PDF_Dmixing_CLEO2D::PDF_Dmixing_CLEO2D(config cObs, config cErr, config cCor, config cType, TString d):
	PDF_Abs(2)
{
	name = "dk3pi_dmixing_cleo";
	this->cType = cType;
	this->cObs = cObs;
	this->dir = d;
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();

}

PDF_Dmixing_CLEO2D::~PDF_Dmixing_CLEO2D(){}

void PDF_Dmixing_CLEO2D::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("dD_k3pi")));
	parameters->add(*(p.get("kD_k3pi")));
}

void PDF_Dmixing_CLEO2D::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory");
	theory->add(*(new RooFormulaVar("dD_k3pi_th", "dD_k3pi_th", "dD_k3pi", *p)));
	theory->add(*(new RooFormulaVar("kD_k3pi_th", "kD_k3pi_th", "kD_k3pi", *p)));
}

void PDF_Dmixing_CLEO2D::initObservables()
{
	observables = new RooArgList("observables");
	observables->add(*(new RooRealVar("dD_k3pi_obs", "#deltaD (D#rightarrowK3#pi)",  0,  0, 2*TMath::Pi(), "Rad"))); // reduced range else toy generation ...
	observables->add(*(new RooRealVar("kD_k3pi_obs", "#kappaD (D#rightarrowK3#pi)",  0, -2., 2.)));                    // produces lots of events very far away
}

void PDF_Dmixing_CLEO2D::setObservables(config c)
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
		case cleo2009:{
						  obsValSource = "arXiv:0903.4853 - CLEO 2009";
						  setObservable("dD_k3pi_obs",DegToRad(114.0));
						  setObservable("kD_k3pi_obs",0.33);
						  break;
					  }
		case cleo2014:{
						  obsValSource = "arXiv:1401.1904 - CLEO 2013";
						  setObservable("dD_k3pi_obs",DegToRad(255.0));  // CLEO 2014
						  setObservable("kD_k3pi_obs",0.32);             // CLEO 2014
						  break;
					  }
		default:{
					cout << "PDF_Dmixing_CLEO2D::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}

void PDF_Dmixing_CLEO2D::setUncertainties(config c)
{
	switch(c)
	{
		case cleo2009:{
						  obsErrSource = "arXiv:0903.4853 - CLEO 2009";
						  StatErr[0] = DegToRad(25);  // dD !?! very antisymmetric error from CLEO so what number should go here?
						  StatErr[1] = 0.25;          // kD
						  SystErr[0] = 0.0;           // dD
						  SystErr[1] = 0.0;           // kD
						  break;
					  }
		case cleo2014:{
						  obsErrSource = "arXiv:1401.1904 - CLEO 2013 ";
						  StatErr[0] = DegToRad(50);  // dD !?! very antisymmetric error from CLEO so what number should go here?
						  StatErr[1] = 0.24;          // kD
						  SystErr[0] = 0.0;           // dD
						  SystErr[1] = 0.0;           // kD
						  break;
					  }
		default:{
					cout << "PDF_Dmixing_CLEO2D::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}

void PDF_Dmixing_CLEO2D::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case cleo2009:{
						  corSource = "arXiv:0903.4853 - CLEO 2009";
						  corStatMatrix[1][0] = -0.067;
						  break;
					  }
		case cleo2014:{
						  corSource = "CLEO 2014 (1401.1904)";
						  corStatMatrix[1][0] = 0.201;
						  break;
					  }
		default:{
					cout << "PDF_Dmixing_CLEO2D::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}

void PDF_Dmixing_CLEO2D::buildPdfGaus()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}

///
/// Build the PDF using the Cleo histogram for kD, dD.
/// \param fName    file name of the histogram, needs to contain the likelihood (not chi2),
///                 computed by ExpNll/computeCleoPdf.C
/// \param scale    A scale factor that is applied to the histogram in order to get a chi2
///                 of exactly 0 when this PDF is fit to minimum. This can be obtained by, e.g.,
///                 bin/gammacombo -i --addpdf 8:8 --var kD_k3pi. The scale factor is then the
///                 the observed FCN value at minimum.
/// \param kDobs    kD value of the maximum in the histogram
/// \param dDobs    dD value of the maximum in the histogram
///
void PDF_Dmixing_CLEO2D::buildPdfHistogram(TString fName, float scale, float kDobs, float dDobs)
{
	RooMsgService::instance().setGlobalKillBelow(WARNING);
	TString hName = "hPdf";
	obsValSource += ", "+fName;
	obsErrSource += ", "+fName;
	corSource += ", "+fName;
	if ( !FileExists(fName) ){cout << "PDF_Dmixing_CLEO2D::buildPdfHistogram() : ERROR : File not found : " << fName << endl; exit(1);}
	TFile *fExpNll = new TFile(fName, "ro");
	TH2D *hExpNll = (TH2D*)fExpNll->Get(hName);
	assert(hExpNll);

	// Scale the histogram so that the best fit value gives chi2=0. The value is obtained by fitting
	// the histogram PDF to its maximum. There is some hidden scaling that I don't understand in RooHistPdf
	// or so, so one can't just use the maximum value of the histogram.
	hExpNll->Scale(1./TMath::Exp(scale/(-2.)));

	RooRealVar *x_hist = new RooRealVar("x_k3pi_hist", "x_k3pi_hist", 0,  -1e4, 1e4);
	RooRealVar *y_hist = new RooRealVar("y_k3pi_hist", "y_k3pi_hist", 0,  -1e4, 1e4);
	RooDataHist *dhExpNll = new RooDataHist("dh_k3pi", "dh_k3pi", RooArgList(*x_hist,*y_hist), Import(*hExpNll));
	RooRealVar *kD_k3pi_obs = (RooRealVar*)observables->find("kD_k3pi_obs");
	RooRealVar *kD_k3pi     = (RooRealVar*)theory->find("kD_k3pi_th");
	RooRealVar *dD_k3pi_obs = (RooRealVar*)observables->find("dD_k3pi_obs");
	RooRealVar *dD_k3pi     = (RooRealVar*)theory->find("dD_k3pi_th");
	RooHistPdfVar *kD_pdf = new RooHistPdfVar("kD_k3pi_pdf", "kD_k3pi_pdf", *kD_k3pi_obs, *kD_k3pi, RooConst(kDobs));
	RooHistPdfAngleVar *dD_pdf = new RooHistPdfAngleVar("dD_k3pi_pdf", "dD_k3pi_pdf", *dD_k3pi_obs, *dD_k3pi, RooConst(dDobs));
	pdf = new RooHistPdf("pdf_"+name, "pdf_"+name, RooArgList(*kD_pdf,*dD_pdf), RooArgList(*x_hist,*y_hist), *dhExpNll, 2);

	// cleanup
	fExpNll->Close();
	RooMsgService::instance().setGlobalKillBelow(INFO);
	addToTrash(x_hist);
	addToTrash(y_hist);
	addToTrash(dhExpNll);
	addToTrash(kD_pdf);
	addToTrash(dD_pdf);
}

void PDF_Dmixing_CLEO2D::buildPdf()
{
	// Get the magic numbers by fitting the histogram to minimum:
	// bin/gammacombo -i --addpdf 8:74 --var dD_k3pi --pr
	// They are (1) the FCN, obtained from the fit when the parameter is set to 0;
	// (2) and (3) the coordinates of the minimum.
	// Note that the FCN does heavily depend on the histogram file.
	// If you e.g. fill previously empty areas of the histogram with 1e-X, X large,
	// it can change by a lot. The goal is to reach FCN~=0 (but positive!).

	if ( cType==useHistogram && cObs==cleo2009 )
		buildPdfHistogram(this->dir+"/ExpNll/CLEO_K3PiScan_2009_GaussianRise_pdf2.root", 0.304957, 0.3325, 1.9984);
	else if ( cType==useHistogram && cObs==cleo2014 ){
		buildPdfHistogram(this->dir+"/ExpNll/CLEO_K3PiScan_2014_pdf.root", 1.06322, 0.31, 4.45059); // corresponding to interpolation order 2
		// buildPdfHistogram(this->dir+"/ExpNll/CLEO_K3PiScan_2014_Gaussian_pdf.root", 0.470901, 0.31, 4.45059);
	}
	else if ( cType==useGaussian )
		buildPdfGaus();
}
