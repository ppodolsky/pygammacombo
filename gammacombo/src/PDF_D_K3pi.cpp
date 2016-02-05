/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#include "PDF_D_K3pi.h"

PDF_D_K3pi::PDF_D_K3pi(config cObs, config cErr, config cCor, config cType, config cUseKdDdK3pi, TString d)
: PDF_Abs(3)
{
  name = "dk3pi";
  this->cType = cType;
  this->cObs = cObs;
  this->cUseKdDdK3pi = cUseKdDdK3pi;
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


PDF_D_K3pi::~PDF_D_K3pi(){}


void PDF_D_K3pi::initParameters()
{
  ParametersGammaCombo p;
  parameters = new RooArgList("parameters");
  parameters->add(*(p.get("rD_k3pi")));
  parameters->add(*(p.get("dD_k3pi")));
  parameters->add(*(p.get("kD_k3pi")));
}


void PDF_D_K3pi::initRelations()
{
  RooArgSet *p = (RooArgSet*)parameters;
  theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
  theory->add(*(new RooFormulaVar("RD_k3pi_th", "RD_k3pi_th", "rD_k3pi^2", *p)));
  theory->add(*(new RooFormulaVar("dD_k3pi_th", "dD_k3pi_th", "dD_k3pi", *p)));
  theory->add(*(new RooFormulaVar("kD_k3pi_th", "kD_k3pi_th", "kD_k3pi", *p)));
}


void PDF_D_K3pi::initObservables()
{
  observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
  observables->add(*(new RooRealVar("RD_k3pi_obs", "RD (D#rightarrowK3#pi)",       0, -1e4, 1e4)));                    
	observables->add(*(new RooRealVar("dD_k3pi_obs", "#deltaD (D#rightarrowK3#pi)",  0,  0, 2*TMath::Pi(), "Rad"))); // reduced range else toy generation ...
	observables->add(*(new RooRealVar("kD_k3pi_obs", "#kappaD (D#rightarrowK3#pi)",  0, -2., 2.)));                  // produces lots of events very far away
}


void PDF_D_K3pi::setObservables(config c)
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
    case belle2005cleo2009:{
      obsValSource = "Belle 2005 (hep-ex/0507071), and CLEO 2009";
      setObservable("RD_k3pi_obs",0.00295);          // Belle 2005
      setObservable("dD_k3pi_obs",DegToRad(114.0));  // CLEO 2009
      setObservable("kD_k3pi_obs",0.33);             // CLEO 2009
      break;
    }
    case belle2013cleo2014:{
      obsValSource = "Belle 2013 (1307.5935) and CLEO 2014 (1401.1904)";
      setObservable("RD_k3pi_obs",0.00327);          // Belle 2013
      setObservable("dD_k3pi_obs",DegToRad(255.0));  // CLEO 2014
      setObservable("kD_k3pi_obs",0.32);             // CLEO 2014
      break;
    }
    default:{
      cout << "PDF_D_K3pi::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
    }
  }
}


void PDF_D_K3pi::setUncertainties(config c)
{
  switch(c)
  {
    case belle2005cleo2009:{
      obsErrSource = "Belle 2005 (hep-ex/0507071), and CLEO 2009";
      StatErr[0] = 0.00025;       // RD
      StatErr[1] = DegToRad(26);  // dD
      StatErr[2] = 0.23;          // kD
      SystErr[0] = 0.0;           // RD
      SystErr[1] = 0.0;           // dD
      SystErr[2] = 0.0;           // kD
      break;
    }
    case belle2013cleo2014:{
      obsErrSource = "Belle 2013 (1307.5935), and CLEO 2014 (1401.1904)";
      StatErr[0] = 0.00019;         // RD, Belle 2013
      StatErr[1] = DegToRad(28.5);  // dD, CLEO 2014, avg of asymmetric errors
      StatErr[2] = 0.24;            // kD, CLEO 2014, avg of asymmetric errors
      SystErr[0] = 0.0;             // RD
      SystErr[1] = 0.0;             // dD
      SystErr[2] = 0.0;             // kD
      break;
    }
    default:{
      cout << "PDF_D_K3pi::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
    }
  }
  // exlude kD, dD, to make the LHCb only Ghana plot
  if ( cUseKdDdK3pi==excludeKdDdK3pi ){
    StatErr[ 1] *= 50; // dD
    StatErr[ 2] *= 50; // kD
  }
}


void PDF_D_K3pi::setCorrelations(config c)
{
  resetCorrelations();
  switch(c)
  {
    case belle2005cleo2009:{
      corSource = "Belle 2005 (hep-ex/0507071), and CLEO 2009";
      // zero
      break;
    }
    case belle2013cleo2014:{
      corSource = "Belle 2013 (1307.5935) and CLEO 2014 (1401.1904)";
      corStatMatrix[2][1] = 0.2;
      break;
    }
    default:{
      cout << "PDF_D_K3pi::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
    }    
  }
}  


void PDF_D_K3pi::buildPdfGaus()
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
void PDF_D_K3pi::buildPdfHistogram(TString fName, float scale, float kDobs, float dDobs)
{
  RooMsgService::instance().setGlobalKillBelow(WARNING);
  TString hName = "hPdf";
  obsValSource += ", "+fName;
  obsErrSource += ", "+fName;
  corSource += ", "+fName;
  if ( !FileExists(fName) ){cout << "PDF_D_K3pi::buildPdfHistogram() : ERROR : File not found : " << fName << endl; exit(1);}
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
  RooHistPdf *pdf_kDdD = new RooHistPdf("pdf_kDdD_k3pi", "pdf_kDdD_k3pi", RooArgList(*kD_pdf,*dD_pdf), RooArgList(*x_hist,*y_hist), *dhExpNll, 2);

  // Use a Gaussian for rD
  RooRealVar *RD_k3pi_obs = (RooRealVar*)observables->find("RD_k3pi_obs");
  RooRealVar *RD_k3pi_th  = (RooRealVar*)theory->find("RD_k3pi_th");
	assert(RD_k3pi_obs); assert(RD_k3pi_th);
  RooGaussian *pdf_RD = new RooGaussian("pdf_RD_k3pi", "pdf_RD_k3pi", *RD_k3pi_obs, *RD_k3pi_th, RooConst(sqrt(sq(StatErr[0])+sq(SystErr[0]))));
  
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


void PDF_D_K3pi::buildPdf()
{
  if ( cType==useHistogram && cObs==belle2005cleo2009 )
    buildPdfHistogram(this->dir+"/ExpNll/CLEO_K3PiScan_2009_GaussianRise_pdf2.root", 0.304957, 0.3325, 1.9984);
  if ( cType==useHistogram && cObs==belle2013cleo2014 )
    buildPdfHistogram(this->dir+"/ExpNll/CLEO_K3PiScan_2014_pdf.root", 1.06322, 0.31, 4.45059);
  else if ( cType==useGaussian )
    buildPdfGaus();
}
