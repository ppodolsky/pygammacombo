#include "TFile.h"
#include "TString.h"
#include "TH2D.h"
#include "TStopwatch.h"
#include "RooRealVar.h"
#include "TMatrixDSym.h"
#include "RooMultiVarGaussian.h"
#include "TCanvas.h"
#include "TMath.h"

Double_t sq(Double_t x)
{
  return x*x;
}

///
/// Expand the Cleo PDF by Gaussian rise and decay beyond the
/// physical boundaries of kD: [0,1] -> [-0.4, 0.6]. This means
/// twice as many bins.
///
void computeCleoPdfWithGaussianRise()
{
  TString fName = "CLEO_K3PiScan_2009";
  TString hName = "deltachisq";
  
  TFile *fExpNll = new TFile(fName+".root", "ro");
  TH2D *hExpNll = (TH2D*)fExpNll->Get(hName);
  assert(hExpNll);

  int nX = hExpNll->GetNbinsX()*2.0;
  int nY = hExpNll->GetNbinsY();
  
  // initialize a new 2D histotram
  TH2D *hNew = new TH2D("hPdf", "hPdf", nX, -0.4, 1.6, nY, 0, 2.*TMath::Pi());
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
  
  Double_t integral = 0;
  Double_t max = 0;
  Double_t xMax = 0;
  Double_t yMax = 0;
  int xBinOffset = 0.4 / hExpNll->GetXaxis()->GetBinWidth(1);
  for ( int i=1; i<=nX; i++ )
  for ( int j=1; j<=nY; j++ )
  {
    Double_t eVal = 0.0;
    if ( hNew->GetXaxis()->GetBinCenter(i)<0 )
    {
      // gaussian with width = half of kD 1 sigma error
      Double_t scale = hExpNll->GetBinContent(1,j);
      scale = TMath::Exp(-scale/2.);
      eVal = TMath::Gaus(hNew->GetXaxis()->GetBinCenter(i), 0.0, 0.26/2, false) * scale;
    }
    else if ( hNew->GetXaxis()->GetBinCenter(i)>1 )
    {
      Double_t scale = hExpNll->GetBinContent(hExpNll->GetNbinsX(),j);
      scale = TMath::Exp(-scale/2.);
      eVal = TMath::Gaus(hNew->GetXaxis()->GetBinCenter(i), 1.0, 0.26/2, false) * scale;      
    }
    else
    {
      eVal = hExpNll->GetBinContent(i-xBinOffset,j);
      eVal = TMath::Exp(-eVal/2.);
    }
    hNew->SetBinContent(i, j, eVal);
    if ( max < eVal)
    {
      xMax = hNew->GetXaxis()->GetBinCenter(i);
      yMax = hNew->GetYaxis()->GetBinCenter(j);
      max = eVal;
    }
    integral += eVal;
  }

  hNew->Scale(1./integral);

  t.Stop();
  t.Print();

  cout << "xMax = " << xMax << " yMax = " << yMax << endl; 
  
  c1->cd(2);
  hNew->Draw("colz");
  
  TString newFileName = fName+"_GaussianRise_pdf2.root";
  cout << "saving histogram " << newFileName << endl;
  TFile *fNew = new TFile(newFileName, "recreate");
  hNew->Write();
  fNew->Close();
}
