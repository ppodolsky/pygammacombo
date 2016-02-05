/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#include "PDF_D_KSKpi_noDmix.h"

	PDF_D_KSKpi_noDmix::PDF_D_KSKpi_noDmix(config cObs, config cErr, config cCor, config cType, TString d)
: PDF_Abs(3)
{
	name = "dkskpi-nodmix";
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


PDF_D_KSKpi_noDmix::~PDF_D_KSKpi_noDmix(){}


void PDF_D_KSKpi_noDmix::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("rD_kskpi")));
	parameters->add(*(p.get("dD_kskpi")));
	parameters->add(*(p.get("kD_kskpi")));
}


void PDF_D_KSKpi_noDmix::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  //theory->add(*(new RooFormulaVar("RD_kskpi_th", "RD_kskpi_th", "rD_kskpi^2 - kD_kskpi*rD_kskpi*(yD*cos(dD_kskpi)-xD*sin(dD_kskpi)) + 0.5*(xD^2 + yD^2)", *p)));
	theory->add(*(new RooFormulaVar("RD_kskpi_th", "RD_kskpi_th", "rD_kskpi^2", *p)));
	theory->add(*(new RooFormulaVar("dD_kskpi_th", "dD_kskpi_th", "dD_kskpi", *p)));
	theory->add(*(new RooFormulaVar("kD_kskpi_th", "kD_kskpi_th", "kD_kskpi", *p)));
}


void PDF_D_KSKpi_noDmix::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("RD_kskpi_obs", "RD (D#rightarrowK_{S}K#pi)",       0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("dD_kskpi_obs", "#deltaD (D#rightarrowK_{S}K#pi)",  0, -1.*TMath::Pi(), TMath::Pi()))); // reduced range else toy generation ...
	observables->add(*(new RooRealVar("kD_kskpi_obs", "#kappaD (D#rightarrowK_{S}K#pi)",  1, -2.,2.)));                       // produces lots of events very far away
}


void PDF_D_KSKpi_noDmix::setObservables(config c)
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
		case cleoFullDP:{
							obsValSource = "CLEO, 1203.3804, PRD 85 092016, whole Dalitz region";
							setObservable("RD_kskpi_obs",0.592);
							setObservable("dD_kskpi_obs",DegToRad(8.3));
							setObservable("kD_kskpi_obs",0.73);
							break;
						}
		case cleo:{
					  obsValSource = "CLEO, 1203.3804, PRD 85 092016, K* region of Dalitz Plot";
					  setObservable("RD_kskpi_obs",0.356);
					  setObservable("dD_kskpi_obs",DegToRad(26.5));
					  setObservable("kD_kskpi_obs",1.0);
					  break;
				  }
		default:{
					cout << "PDF_D_KSKpi_noDmix::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_D_KSKpi_noDmix::setUncertainties(config c)
{
	switch(c)
	{
		case cleoFullDP:{
							obsErrSource = "CLEO, 1203.3804, PRD 85 092016, whole Dalitz region";
							StatErr[0] = 0.044; 					// RD_kskpi_obs
							StatErr[1] = DegToRad(15.2);  // dD_kskpi_obs
							StatErr[2] = 0.08;            // kD_kskpi_obs
							SystErr[0] = 0.018; 					// RD_kskpi_obs
							SystErr[1] = 0.0;             // dD_kskpi_obs
							SystErr[2] = 0.0;             // kD_kskpi_obs
							break;
						}
		case cleo:{
					  obsErrSource = "CLEO, 1203.3804, PRD 85 092016, K* region of Dalitz Plot";
					  StatErr[0] = 0.034; 					 // RD_kskpi_obs
					  StatErr[1] = DegToRad(15.8);   // dD_kskpi_obs
					  StatErr[2] = 0.16;             // kD_kskpi_obs
					  SystErr[0] = 0.007; 					 // RD_kskpi_obs
					  SystErr[1] = 0.0;              // dD_kskpi_obs
					  SystErr[2] = 0.0;              // kD_kskpi_obs
					  break;
				  }
		default:{
					cout << "PDF_D_KSKpi_noDmix::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_D_KSKpi_noDmix::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case cleo:{
					  corSource = "chosen by eye to match the 2D histogram of CLEO, 1203.3804";
					  corStatMatrix[1][2] = 0.60;
					  break;
				  }
		case cleoFullDP:{
							corSource = "none";
							break;
						}
		default:{
					cout << "PDF_D_KSKpi_noDmix::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
					exit(1);
				}
	}
}


void PDF_D_KSKpi_noDmix::buildPdfGaus()
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
void PDF_D_KSKpi_noDmix::buildPdfHistogram(TString fName, float scale, float kDobs, float dDobs)
{
	RooMsgService::instance().setGlobalKillBelow(WARNING);
	TString hName = "hPdf";
	obsValSource += ", "+fName;
	obsErrSource += ", "+fName;
	corSource += ", "+fName;
	if ( !FileExists(fName) ){cout << "PDF_D_KSKpi_noDmix::buildPdfHistogram() : ERROR : File not found : " << fName << endl; exit(1);}
	TFile *fExpNll = new TFile(fName, "ro");
	TH2D *hExpNll = (TH2D*)fExpNll->Get(hName);
	assert(hExpNll);

	// Scale the histogram so that the best fit value gives chi2=0. The value is obtained by fitting
	// the histogram PDF to its maximum. There is some hidden scaling that I don't understand in RooHistPdf
	// or so, so one can't just use the maximum value of the histogram.
	hExpNll->Scale(1./TMath::Exp(scale/(-2.)));

	RooRealVar *x_hist = new RooRealVar("x_kskpi_hist", "x_kskpi_hist", 0, -1e4, 1e4);
	RooRealVar *y_hist = new RooRealVar("y_kskpi_hist", "y_kskpi_hist", 0, -1e4, 1e4);
	RooDataHist *dhExpNll = new RooDataHist("dh_kskpi", "dh_kskpi", RooArgList(*x_hist,*y_hist), Import(*hExpNll));
	RooRealVar *kD_kskpi_obs = (RooRealVar*)observables->find("kD_kskpi_obs");
	RooRealVar *kD_kskpi     = (RooRealVar*)theory->find("kD_kskpi_th");
	RooRealVar *dD_kskpi_obs = (RooRealVar*)observables->find("dD_kskpi_obs");
	RooRealVar *dD_kskpi     = (RooRealVar*)theory->find("dD_kskpi_th");
	RooHistPdfVar *kD_pdf = new RooHistPdfVar("kD_kskpi_pdf", "kD_kskpi_pdf", *kD_kskpi_obs, *kD_kskpi, RooConst(kDobs));
	RooHistPdfAngleVar *dD_pdf = new RooHistPdfAngleVar("dD_kskpi_pdf", "dD_kskpi_pdf", *dD_kskpi_obs, *dD_kskpi, RooConst(dDobs));
	RooHistPdf *pdf_kDdD = new RooHistPdf("pdf_kDdD_kskpi", "pdf_kDdD_kskpi", RooArgList(*kD_pdf,*dD_pdf), RooArgList(*x_hist,*y_hist), *dhExpNll, 1);

	// Use a Gaussian for RD
	RooRealVar *RD_kskpi_obs = (RooRealVar*)observables->find("RD_kskpi_obs");
	RooRealVar *RD_kskpi_th  = (RooRealVar*)theory->find("RD_kskpi_th");
	assert(RD_kskpi_obs); assert(RD_kskpi_th);
	RooGaussian *pdf_RD = new RooGaussian("pdf_RD_kskpi", "pdf_RD_kskpi", *RD_kskpi_obs, *RD_kskpi_th, RooConst(sqrt(sq(StatErr[0])+sq(SystErr[0]))));

	// multiply both
	pdf = new RooProdPdf("pdf_"+name, "pdf_"+name, RooArgSet(*pdf_kDdD, *pdf_RD));

	// cleanup
	fExpNll->Close();
	RooMsgService::instance().setGlobalKillBelow(INFO);
	addToTrash(x_hist);
	addToTrash(y_hist);
	addToTrash(dhExpNll);
	addToTrash(kD_pdf);
	addToTrash(dD_pdf);
	addToTrash(pdf_kDdD);
	addToTrash(pdf_RD);
}


void PDF_D_KSKpi_noDmix::buildPdf()
{
	buildPdfGaus();
}

