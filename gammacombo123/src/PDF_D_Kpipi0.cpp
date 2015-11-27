///
///  PDF_D_Kpipi0.cpp
///
///
/// Created by Moritz Karbach on 19/08/14.
///
#include "PDF_D_Kpipi0.h"

PDF_D_Kpipi0::PDF_D_Kpipi0(config cObs, config cErr, config cCor, config cType, TString d):
	PDF_Abs(2)
{
	name = "DKpipi0";
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

PDF_D_Kpipi0::~PDF_D_Kpipi0(){}

void PDF_D_Kpipi0::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("dD_kpipi0")));
	parameters->add(*(p.get("kD_kpipi0")));
}

void PDF_D_Kpipi0::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory");
	theory->add(*(new RooFormulaVar("dD_kpipi0_th", "dD_kpipi0_th", "dD_kpipi0", *p)));
	theory->add(*(new RooFormulaVar("kD_kpipi0_th", "kD_kpipi0_th", "kD_kpipi0", *p)));
}

void PDF_D_Kpipi0::initObservables()
{
	observables = new RooArgList("observables");
	observables->add(*(new RooRealVar("dD_kpipi0_obs", "#deltaD (D#rightarrowK#pi#pi^{0})",  0,  0, 2*TMath::Pi(), "Rad"))); // reduced range else toy generation ...
	observables->add(*(new RooRealVar("kD_kpipi0_obs", "#kappaD (D#rightarrowK#pi#pi^{0})",  0, -2., 2.)));                    // produces lots of events very far away
}

void PDF_D_Kpipi0::setObservables(config c)
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
		case cleo2014:{
						  obsValSource = "arXiv:1401.1904 - CLEO 2014";
						  setObservable("dD_kpipi0_obs",DegToRad(164));  // CLEO 2014
						  setObservable("kD_kpipi0_obs",0.82);           // CLEO 2014
						  break;
					  }
		default:{
					cout << "PDF_D_Kpipi0::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}

void PDF_D_Kpipi0::setUncertainties(config c)
{
	switch(c)
	{
		case cleo2014:{
						  obsErrSource = "arXiv:1401.1904 - CLEO 2014";
						  StatErr[0] = DegToRad(20);  // dD !?! very antisymmetric error from CLEO so what number should go here?
						  StatErr[1] = 0.07;          // kD
						  SystErr[0] = 0.0;           // dD
						  SystErr[1] = 0.0;           // kD
						  break;
					  }
		default:{
					cout << "PDF_D_Kpipi0::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}

void PDF_D_Kpipi0::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case cleo2014:{
						  corSource = "CLEO 2014 (1401.1904)";
						  corStatMatrix[1][0] = -0.444;
						  break;
					  }
		default:{
					cout << "PDF_D_Kpipi0::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}

void PDF_D_Kpipi0::buildPdfGaus()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}

///
/// Build the PDF using the Cleo histogram for kD, dD.
/// \param fName    file name of the histogram, needs to contain the likelihood (not chi2),
///                 computed by ExpNll/computeCleoPdf.C
/// \param scale    A scale factor that is applied to the histogram in order to get a chi2
///                 of exactly 0 when this PDF is fit to minimum. This can be obtained by, e.g.,
///                 bin/gammacombo -i --addpdf 8:8 --var kD_kpipi0. The scale factor is then the
///                 the observed FCN value at minimum.
/// \param kDobs    kD value of the maximum in the histogram
/// \param dDobs    dD value of the maximum in the histogram
///
void PDF_D_Kpipi0::buildPdfHistogram(TString fName, float scale, float kDobs, float dDobs)
{
	RooMsgService::instance().setGlobalKillBelow(WARNING);
	TString hName = "hPdf";
	obsValSource += ", "+fName;
	obsErrSource += ", "+fName;
	corSource += ", "+fName;
	if ( !FileExists(fName) ){cout << "PDF_D_Kpipi0::buildPdfHistogram() : ERROR : File not found : " << fName << endl; exit(1);}
	TFile *fExpNll = new TFile(fName, "ro");
	TH2D *hExpNll = (TH2D*)fExpNll->Get(hName);
	assert(hExpNll);

	// Scale the histogram so that the best fit value gives chi2=0. The value is obtained by fitting
	// the histogram PDF to its maximum. There is some hidden scaling that I don't understand in RooHistPdf
	// or so, so one can't just use the maximum value of the histogram.
	hExpNll->Scale(1./TMath::Exp(scale/(-2.)));

	RooRealVar *x_hist = new RooRealVar("x_kpipi0_hist", "x_kpipi0_hist", 0,  -1e4, 1e4);
	RooRealVar *y_hist = new RooRealVar("y_kpipi0_hist", "y_kpipi0_hist", 0,  -1e4, 1e4);
	RooDataHist *dhExpNll = new RooDataHist("dh_kpipi0", "dh_kpipi0", RooArgList(*x_hist,*y_hist), Import(*hExpNll));
	RooRealVar *kD_kpipi0_obs = (RooRealVar*)observables->find("kD_kpipi0_obs");
	RooRealVar *kD_kpipi0     = (RooRealVar*)theory->find("kD_kpipi0_th");
	RooRealVar *dD_kpipi0_obs = (RooRealVar*)observables->find("dD_kpipi0_obs");
	RooRealVar *dD_kpipi0     = (RooRealVar*)theory->find("dD_kpipi0_th");
	RooHistPdfVar *kD_pdf = new RooHistPdfVar("kD_kpipi0_pdf", "kD_kpipi0_pdf", *kD_kpipi0_obs, *kD_kpipi0, RooConst(kDobs));
	RooHistPdfAngleVar *dD_pdf = new RooHistPdfAngleVar("dD_kpipi0_pdf", "dD_kpipi0_pdf", *dD_kpipi0_obs, *dD_kpipi0, RooConst(dDobs));
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

void PDF_D_Kpipi0::buildPdf()
{
	// Get the magic numbers by fitting the histogram to minimum:
	// bin/gammacombo -i -c 0:135 --var dD_kpipi0 --pr
	// They are
	// (1) the FCN, obtained from the fit when the parameter is set to 0,
	//      it can be negative,
	//      the smaller it gets, the larger the refitted FCN gets. So if the
	//      refitted FCN happens to be -4.3e-5, try making the number just a
	//      little bit smaller.
	// (2) coordinate of the minimum
	// (3) coordinates of the minimum.
	// Note that the FCN does heavily depend on the histogram file.
	// If you e.g. fill previously empty areas of the histogram with 1e-X, X large,
	// it can change by a lot. The goal is to reach FCN~=0 (but positive!).

	if ( cType==useHistogram && cObs==cleo2014 ){
		buildPdfHistogram(this->dir+"/ExpNll/CLEO_KPiPi0Scan_2014_pdf.root", -4.165, 0.829, 2.88); // corresponding to interpolation order 2
	}
	else if ( cType==useGaussian )
		buildPdfGaus();
}
