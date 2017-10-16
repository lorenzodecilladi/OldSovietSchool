void drawpoisson(TString filename="poisson.root"){
  TFile *filein = new TFile(filename);
  TH1F* ndecays = (TH1F*)filein->Get("ndecays");
  TH1F* fteo = (TH1F*)filein->Get("fteo");
  TH1F* fteo2 = (TH1F*)filein->Get("fteo2");
  ndecays->SetMarkerStyle(20);
  fteo->SetLineColor(kBlue);
  fteo2->SetLineColor(2);
  ndecays->Draw("pe");
  fteo2->Draw("histcsame");
  fteo->Draw("histcsame");
  TCanvas *c2 = new TCanvas();
  fteo2->Draw("histc");
  TCanvas *c3 = new TCanvas();
  fteo->Draw("histc");
}
