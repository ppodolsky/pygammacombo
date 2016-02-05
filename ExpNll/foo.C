{
gStyle->SetOptStat(0);

TFile f("CoveragePlot_forMoritz.root");
TH2F *sta = (TH2F*)f.Get("loglik");
TH2F* zoom = new TH2F("","",50,0.96,1.06,50,0,36);
for(int i=1;i<51;++i){
	for(int j=1; j<51; ++j){
		double entry = sta->GetBinContent(i+200,j+250);
		if(entry>0.1)entry=0.1;
		zoom->SetBinContent(i,j,entry);
	}
}
zoom->Draw("COLZ");
}
