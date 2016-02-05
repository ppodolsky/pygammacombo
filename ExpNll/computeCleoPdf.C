/*
 * Take the CLEO chi2 histogram for the strong phase and the coherence
 * factor in D->K3pi and convert it into a PDF.
 *
 * The resulting histogram is then used by the PDF classes
 * PDF_D_Cleo.cpp
 * PDF_D_K3pi.cpp
 * PDF_D_Kpipi0.cpp
 *
 * Also finds the maximum bin and prints its coordinates.
 *
 */
#include "TFile.h"
#include "TString.h"
#include "TH2D.h"
#include "TStopwatch.h"
#include "RooRealVar.h"
#include "TMatrixDSym.h"
#include "RooMultiVarGaussian.h"
#include "TCanvas.h"

double sq(double x)
{
  return x*x;
}

void computeCleoPdf()
{
  //TString fName = "CLEO_K3PiScan_2009";
  //TString hName = "deltachisq";

  //TString fName = "CLEO_K3PiScan_2014";
  //TString hName = "deltachisq";

  //TString fName = "CLEO_KSKpiScan_2012_FullDP";
  //TString hName = "loglik";

  //TString fName = "CLEO_KSKpiScan_2012_Kst";
  //TString hName = "loglik";

  //TString fName = "CLEO_KPiPi0Scan_2014";
  //TString hName = "deltachisq";

  TString fName = "CLEO_LHCb_K3PiScan_2015";
  TString hName = "deltachisq";

  //
  // START THE CONVERSION
  //
  TFile *fExpNll = new TFile(fName+".root", "ro");
  TH2D *hExpNll = (TH2D*)fExpNll->Get(hName);
  assert(hExpNll);

  int nX = hExpNll->GetNbinsX();
  int nY = hExpNll->GetNbinsY();

  // initialize a new histogram
  TH2D *hNew = new TH2D("hPdf", "hPdf",
	nX, hExpNll->GetXaxis()->GetXmin(), hExpNll->GetXaxis()->GetXmax(),
	nY, hExpNll->GetYaxis()->GetXmin()/180.*TMath::Pi(), hExpNll->GetYaxis()->GetXmax()/180.*TMath::Pi());
  for ( int ii=1; ii<nX; ii++ )
  for ( int jj=1; jj<nY; jj++ )
  {
    hNew->SetBinContent(ii, jj, 0);
  }

  TCanvas *c1 = new TCanvas("c1", "c1", 800, 400);
  c1->Divide(2,1);
  c1->cd(1);
  hExpNll->Draw("colz");

  // time the macro
  TStopwatch t;
  t.Start();

  float max = 0;
  float xMax = 0;
  float yMax = 0;
  float minEval = 1e6;

  for ( int i=1; i<=nX; i++ )
  for ( int j=1; j<=nY; j++ )
  {
    // exponentionate to turn chi2 into likelihood
    float eVal = hExpNll->GetBinContent(i,j);
    // hack for bad histogram
    if (eVal>9) eVal=9;
    if (eVal>0){
	    eVal = TMath::Exp(-eVal/2.);
	    hNew->SetBinContent(i, j, eVal);
    }
    // find coordinates of maximum in the physical region, R>0
    if ( max < eVal && hNew->GetXaxis()->GetBinCenter(i)>0 )
    {
	    xMax = hNew->GetXaxis()->GetBinCenter(i);
	    yMax = hNew->GetYaxis()->GetBinCenter(j);
	    max = eVal;
    }
    // find minimum likeilihood value in the tails - we'll set any zero bin to this minimum, usually around 1e-25
    if ( 0.0 < eVal && eVal < minEval ) minEval = eVal;
  }

  // set zero bins to minimum likelihood value found
  for ( int i=1; i<=nX; i++ )
  for ( int j=1; j<=nY; j++ )
  {
    if ( hNew->GetBinContent(i,j)<=0.0 ) hNew->SetBinContent(i, j, minEval);
  }

  hNew->Scale(1./hNew->Integral());

  t.Stop();
  t.Print();

  cout << "xMax = " << xMax << " yMax = " << yMax << endl;

  c1->cd(2);
  hNew->Draw("colz");

  cout << "saving histogram " << fName+"_pdf.root" << endl;
  TFile *fNew = new TFile(fName+"_pdf.root", "recreate");
  hNew->Write();
  fNew->Close();
}
