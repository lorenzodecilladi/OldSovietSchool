void drawdecay(TString filename="decay.root"){
  TFile *file = new TFile(filename);
  TH1 *h1 =(TH1*)file->Get("h1");
  TF1 *fteo=(TF1*)file->Get("fteo");
  h1->SetFillColor(kOrange-4);
  TCanvas *c1 = new TCanvas();
  h1->Draw("histo");
  fteo->Draw("same");
  TCanvas *c2 = new TCanvas();
  c2->SetLogy();
  h1->Draw("histo");
  fteo->Draw("same");
}
