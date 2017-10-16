#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>

#include "DistGen.h"

void useDistGen(int nentries = 1000){

  double alpha1 = 0.5;
  double alpha2 = 0.001;
  DistGen gen1 = DistGen(alpha1);
  DistGen gen2 = DistGen(alpha2);

  TH1D *dist1rej = new TH1D("dist1rej", "distribuzione con #alpha = 0.5 e metodo reiezione", 100, -0.5, 2*TMath::Pi() + 0.5);
  TH1D *dist2rej = new TH1D("dist2rej", "distribuzione con #alpha = 0.001 e metodo reiezione", 100, -0.5, 2*TMath::Pi() + 0.5);
  TH1D *dist1inv = new TH1D("dist1inv", "distribuzione con #alpha = 0.5 e metodo inversione", 100, -0.5, 2*TMath::Pi() + 0.5);
  TH1D *dist2inv = new TH1D("dist2inv", "distribuzione con #alpha = 0.001 e metodo inversione", 100, -0.5, 2*TMath::Pi() +0.5);

  for(int i=0; i<nentries; i++){
    dist1rej -> Fill(gen1.rejection());
    dist2rej -> Fill(gen2.rejection());
    dist1inv -> Fill(gen1.inversion());
    dist2inv -> Fill(gen2.inversion());    
  }

  dist1rej->SetLineColor(kRed);
  dist1inv->SetLineColor(kBlue);
  dist2rej->SetLineColor(kRed);
  dist2inv->SetLineColor(kBlue);

  TF1 *func1 = new TF1("func1", "[0]*1/(TMath::Sin(x)*TMath::Sin(x) + [1] * TMath::Cos(x)*TMath::Cos(x))", 0., 2*TMath::Pi());
  TF1 *func2 = new TF1("func2", "[0]*1/(TMath::Sin(x)*TMath::Sin(x) + [1] * TMath::Cos(x)*TMath::Cos(x))", 0., 2*TMath::Pi());
  func1 -> SetParameter(0, 1.);//dist1rej->Integral(0, 100));
  func1 -> SetParameter(1, alpha1);  
  func2 -> SetParameter(0, 1.);//dist2rej->Integral(0, 100));
  func2 -> SetParameter(1, alpha2);  
  func1 -> SetLineColor(kGreen);
  func2 -> SetLineColor(kGreen);
  
  

  TCanvas *c1 = new TCanvas("c1", "alpha = 0.5");
  TCanvas *c2 = new TCanvas("c2", "alpha = 0.001");

  c1->cd();
  dist1rej->Draw();
  dist1inv->Draw("same");
  func1->Draw("same");
  
  c2->cd();
  dist2rej->Draw();
  dist2inv->Draw("same");
  func2->Draw("same");

}
