
void drawdecay(TString filename = "decay.root"){

  TFile *f = new TFile("filename");

  fteo->SetLineColor(kRed);
  h1->SetFillColor(kOrange-4);
  
  TCanvas *c = new TCanvas();
  c->cd();
  h1->Draw("histo"); //opzione histo mi toglie errori
  fteo->Draw("same");

  TCanvas *cLog = new TCanvas();
  cLog -> cd();
  cLog -> SetLogy();
  h1 -> Draw("histo");
  fteo -> Draw("same");

}
