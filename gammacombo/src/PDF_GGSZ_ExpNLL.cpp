/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#include "PDF_GGSZ_ExpNLL.h"

PDF_GGSZ_ExpNLL::PDF_GGSZ_ExpNLL(config cObs, config cType, TString d)
{
  this->dir = d;
  this->cType = cType;
  name = "ggsz";
  initParameters();
  initRelations();
  initObservables();
  setObservables(cObs);
  
  xm_obs = (RooRealVar*)observables->find("xm_dk_obs");
  xm_th  = (RooRealVar*)theory     ->find("xm_dk_th");
  ym_obs = (RooRealVar*)observables->find("ym_dk_obs");
  ym_th  = (RooRealVar*)theory     ->find("ym_dk_th");
  xp_obs = (RooRealVar*)observables->find("xp_dk_obs");
  xp_th  = (RooRealVar*)theory     ->find("xp_dk_th");
  yp_obs = (RooRealVar*)observables->find("yp_dk_obs");
  yp_th  = (RooRealVar*)theory     ->find("yp_dk_th");
  
  buildPdf();
}


///
/// Here we use a 2d RooHistPdf.
///
void PDF_GGSZ_ExpNLL::buildPdfHistogram()
{
  //
  // for B+
  //
  // TString fNamePos = this->dir+"/NLL_GGSZ/histosplus.root";
  // TString hNamePos = "eggp";
  TString fNamePos = this->dir+"/NLL_GGSZ/histosplus_conv.root";
  TString hNamePos = "hConv";

  if ( !FileExists(fNamePos) ) { cout << "PDF_GGSZ_ExpNLL::buildPdf() : ERROR : File not found : " << fNamePos << endl; exit(1); }
  cout << "PDF_GGSZ_ExpNLL::buildPdf() : Opening " << fNamePos << endl;
  TFile *fExpNllPos = new TFile(fNamePos, "ro");
  TH2D *hExpNllPos = (TH2D*)fExpNllPos->Get(hNamePos);
  assert(hExpNllPos);
  RooRealVar *xp_hist = new RooRealVar("xp_hist", "xp_hist", 0, -1.0, 1.0);
  RooRealVar *yp_hist = new RooRealVar("yp_hist", "xp_hist", 0, -1.0, 1.0);
  RooDataHist *dhExpNllPos = new RooDataHist("dhPos", "dhPos", RooArgList(*xp_hist,*yp_hist), Import(*hExpNllPos));
  RooHistPdfVar *xp_pdf = new RooHistPdfVar("xp_pdf", "xp_pdf", *xp_obs, *xp_th, RooConst(-0.102837));  // those precise shifts I got from zooming into the exp nll histogram  
  RooHistPdfVar *yp_pdf = new RooHistPdfVar("yp_pdf", "yp_pdf", *yp_obs, *yp_th, RooConst(-0.0083607));
  RooHistPdf *pdfPos = new RooHistPdf("pdf_pos_"+name, "pdf_pos_"+name, RooArgList(*xp_pdf,*yp_pdf), RooArgList(*xp_hist,*yp_hist), *dhExpNllPos, 1);

  //
  // for B-
  //
  // TString fNameNeg = this->dir+"/NLL_GGSZ/histosBM.root";
  // TString hNameNeg = "eggp";
  TString fNameNeg = this->dir+"/NLL_GGSZ/histosBM_conv.root";
  TString hNameNeg = "hConv";
  if ( !FileExists(fNameNeg) ) { cout << "PDF_GGSZ_ExpNLL::buildPdf() : ERROR : File not found : " << fNameNeg << endl; exit(1); }
  cout << "PDF_GGSZ_ExpNLL::buildPdf() : Opening " << fNameNeg << endl;
  TFile *fExpNllNeg = new TFile(fNameNeg, "ro");
  TH2D *hExpNllNeg = (TH2D*)fExpNllNeg->Get(hNameNeg);
  assert(hExpNllNeg);
  RooRealVar *xm_hist = new RooRealVar("xm_hist", "xm_hist", 0, -1.0, 1.0);
  RooRealVar *ym_hist = new RooRealVar("ym_hist", "xm_hist", 0, -1.0, 1.0);
  RooDataHist *dhExpNllNeg = new RooDataHist("dhNeg", "dhNeg", RooArgList(*xm_hist,*ym_hist), Import(*hExpNllNeg));
  RooHistPdfVar *xm_pdf = new RooHistPdfVar("xm_pdf", "xm_pdf", *xm_obs, *xm_th, RooConst( 0.00152658));  
  RooHistPdfVar *ym_pdf = new RooHistPdfVar("ym_pdf", "ym_pdf", *ym_obs, *ym_th, RooConst( 0.0273623));
  RooHistPdf *pdfNeg = new RooHistPdf("pdf_neg_"+name, "pdf_neg_"+name, RooArgList(*xm_pdf,*ym_pdf), RooArgList(*xm_hist,*ym_hist), *dhExpNllNeg, 1);
  
  // multiply both
  pdf = new RooProdPdf("pdf_"+name, "pdf_"+name, RooArgSet(*pdfNeg, *pdfPos));
  
  // cleanup
  fExpNllPos->Close();
  fExpNllNeg->Close();
}

///
/// Here we use Manuel's bicubic histogram.
///
void PDF_GGSZ_ExpNLL::buildPdfBicubic()
{
  //
  // for B+
  //
  TString fNamePos = this->dir+"/NLL_GGSZ/histosplus_conv.root";
  TString hNamePos = "hConv";
  if ( !FileExists(fNamePos) ) { cout << "PDF_GGSZ_ExpNLL::buildPdf() : ERROR : File not found : " << fNamePos << endl; exit(1); }
  TFile *fExpNllPos = new TFile(fNamePos, "ro");
  TH2D *hExpNllPos = (TH2D*)fExpNllPos->Get(hNamePos);
  assert(hExpNllPos);
  RooHistPdfVar *xp_pdf = new RooHistPdfVar("xp_pdf", "xp_pdf", *xp_obs, *xp_th, RooConst(-0.102837));  // those precise shifts I got from zooming into the exp nll histogram  
  RooHistPdfVar *yp_pdf = new RooHistPdfVar("yp_pdf", "yp_pdf", *yp_obs, *yp_th, RooConst(-0.0083607));
  RooBinned2DBicubicPdf *pdfPos = new RooBinned2DBicubicPdf("pdf_pos_"+name, "pdf_pos_"+name, *hExpNllPos, *xp_pdf, *yp_pdf);

  //
  // for B-
  //
  TString fNameNeg = this->dir+"/NLL_GGSZ/histosBM_conv.root";
  TString hNameNeg = "hConv";  
  if ( !FileExists(fNameNeg) ) { cout << "PDF_GGSZ_ExpNLL::buildPdf() : ERROR : File not found : " << fNameNeg << endl; exit(1); }
  TFile *fExpNllNeg = new TFile(fNameNeg, "ro");
  TH2D *hExpNllNeg = (TH2D*)fExpNllNeg->Get(hNameNeg);
  assert(hExpNllNeg);
  RooHistPdfVar *xm_pdf = new RooHistPdfVar("xm_pdf", "xm_pdf", *xm_obs, *xm_th, RooConst( 0.00152658));  
  RooHistPdfVar *ym_pdf = new RooHistPdfVar("ym_pdf", "ym_pdf", *ym_obs, *ym_th, RooConst( 0.0273623));
  RooBinned2DBicubicPdf *pdfNeg = new RooBinned2DBicubicPdf("pdf_neg_"+name, "pdf_neg_"+name, *hExpNllNeg, *xm_pdf, *ym_pdf);
  
  // multiply both
  pdf = new RooProdPdf("pdf_"+name, "pdf_"+name, RooArgSet(*pdfNeg, *pdfPos));
}


void PDF_GGSZ_ExpNLL::buildPdfParametric()
{
  RooMsgService::instance().setGlobalKillBelow(ERROR);
  RooWorkspace *wExpNll = new RooWorkspace("wExpNll");

  //
  // for B-
  //
  RooHistPdfVar *xm_pdf = new RooHistPdfVar("xm_pdf", "xm_pdf", *xm_obs, *xm_th, RooConst( 0.000+2.62345e-03));
  RooHistPdfVar *ym_pdf = new RooHistPdfVar("ym_pdf", "ym_pdf", *ym_obs, *ym_th, RooConst( 0.027+1.88547e-03));

  double xmp0wl                        =    0.0541675;
  double xmp1wl                        =     0.018955;
  double xmp2wl                        =       0.3075;
  double xmp3wl                        =     -0.89035;
  double xmp4wl                        =     -3.44858;

  RooPoly4Var *ymwidthl = new RooPoly4Var("ymwidthl", "ymwidthl", *xm_pdf,
    xmp0wl, xmp1wl, xmp2wl, xmp3wl, xmp4wl);

  double xmp0wr                        =    0.0494967; 
  double xmp1wr                        =    0.0130424; 
  double xmp2wr                        =     0.110901; 
  double xmp3wr                        =   -0.0796312; 
  double xmp4wr                        =     0.204101;

  RooPoly4Var *ymwidthr = new RooPoly4Var("ymwidthr", "ymwidthr", *xm_pdf, 
    xmp0wr, xmp1wr, xmp2wr, xmp3wr, xmp4wr);
  
  double xmp0m                        =    0.0292742;
  double xmp1m                        =    -0.123769;
  double xmp2m                        =     -0.39777;
  double xmp3m                        =     0.825458;
    
  RooPoly3Var *ymmean = new RooPoly3Var("ymmean", "ymmean", *xm_pdf, 
    xmp0m, xmp1m, xmp2m, xmp3m);  
  RooBifurGauss *ympdf = new RooBifurGauss("ympdf", "ympdf", *ym_pdf, *ymmean, *ymwidthl, *ymwidthr);
  wExpNll->import(*ympdf);
  wExpNll->factory("RooBifurGauss::xmpdf(xm_pdf, xmmean[2.58584e-03], xmwidthl[4.37123e-02], xmwidthr[4.37101e-02])");
  wExpNll->factory("PROD::pdf_ggszexpnll_neg(xmpdf,ympdf)");
  
  //
  // for B+
  //
  RooHistPdfVar *xp_pdf = new RooHistPdfVar("xp_pdf", "xp_pdf", *xp_obs, *xp_th, RooConst(-0.103-5.74430e-03));    
  RooHistPdfVar *yp_pdf = new RooHistPdfVar("yp_pdf", "yp_pdf", *yp_obs, *yp_th, RooConst(-0.009-4.54284e-03));
    
  double xpp0wl                        =     0.0292561;
  double xpp1wl                        =     0.0703944;
  double xpp2wl                        =    -0.0922186;
  double xpp3wl                        =      -11.8135;
  double xpp4wl                        =      -34.8594;
  
  RooPoly4Var *ypwidthl = new RooPoly4Var("ypwidthl", "ypwidthl", *xp_pdf, 
    xpp0wl, xpp1wl, xpp2wl, xpp3wl, xpp4wl);

  double xpp0wr                        =   0.0403016; 
  double xpp1wr                        =   0.0367049; 
  double xpp2wr                        =    0.535281; 
  double xpp3wr                        =     2.29804; 
  double xpp4wr                        =     5.37199;

  RooPoly4Var *ypwidthr = new RooPoly4Var("ypwidthr", "ypwidthr", *xp_pdf, 
    xpp0wr, xpp1wr, xpp2wr, xpp3wr, xpp4wr);
  
  double xpp0m                        =    -0.0133043;
  double xpp1m                        =     -0.139777;
  double xpp2m                        =      -1.38657;
  double xpp3m                        =     -0.727225;
  
  RooPoly3Var *ypmean = new RooPoly3Var("ypmean", "ypmean", *xp_pdf, 
    xpp0m, xpp1m, xpp2m, xpp3m);  
  RooBifurGauss *yppdf = new RooBifurGauss("yppdf", "yppdf", *yp_pdf, *ypmean, *ypwidthl, *ypwidthr);
  wExpNll->import(*yppdf);
  wExpNll->factory("RooBifurGauss::xppdf(xp_pdf, xpmean[-1.08775e-01], xpwidthl[4.32573e-02], xpwidthr[4.93588e-02])");
  wExpNll->factory("PROD::pdf_ggszexpnll_pos(xppdf,yppdf)");

  // multiply both
  wExpNll->factory("PROD::pdf_"+name+"(pdf_ggszexpnll_neg,pdf_ggszexpnll_pos)");
  pdf = wExpNll->pdf("pdf_"+name);
  RooMsgService::instance().setGlobalKillBelow(INFO);
}


void PDF_GGSZ_ExpNLL::buildPdf()
{
  if ( cType==useHistogram )
    buildPdfHistogram();
  else if ( cType==useParametric )
    buildPdfParametric();
  else if ( cType==useBicubic )
    buildPdfBicubic();
  else
  {
    cout << "PDF_GGSZ_ExpNLL::buildPdf() : ERROR : config "+ConfigToTString(cType)+" not found." << endl;
    exit(1);
  }
}
