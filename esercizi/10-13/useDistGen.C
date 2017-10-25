#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>

#include "DistGen.h"

void useDistGen(int nentries = 10000){

  //alcuni parametri iniziali
  double duepi = 2*TMath::Pi();
  int nbins = 100;
  double step = (duepi+0.5-(-0.5))/nbins;
  
  double alpha1 = 0.5;
  double alpha2 = 0.001;
  DistGen gen1 = DistGen(alpha1);
  DistGen gen2 = DistGen(alpha2);

  double norm1 = duepi/(TMath::Sqrt(alpha1)*step*nentries);
  double norm2 = duepi/TMath::Sqrt(alpha2)/step/nentries;
  
  //istanza istogrammi e funzioni
  TH1D *dist1rej = new TH1D("dist1rej", "distribuzione con #alpha = 0.5 e metodo reiezione", nbins, -0.5, duepi + 0.5);
  TH1D *dist2rej = new TH1D("dist2rej", "distribuzione con #alpha = 0.001 e metodo reiezione", nbins, -0.5, duepi + 0.5);
  TH1D *dist1inv = new TH1D("dist1inv", "distribuzione con #alpha = 0.5 e metodo inversione", nbins, -0.5, duepi + 0.5);
  TH1D *dist2inv = new TH1D("dist2inv", "distribuzione con #alpha = 0.001 e metodo inversione", nbins, -0.5, duepi +0.5);
  TH1D *dist1root = new TH1D("dist1root", "distribuzione con #alpha = 0.5 e metodo inversione numerica root", nbins, -0.5, duepi + 0.5);
  TH1D *dist2root = new TH1D("dist2root", "distribuzione con #alpha = 0.001 e metodo inversione numerica root", nbins, -0.5, duepi + 0.5);

  TH1D *distsampl = new TH1D("distsampl", "distribuzione Sin con metodo importance sampling", nbins, -10., 10.);

  
  TF1 *func1 = new TF1("func1", "[0]*1/(TMath::Sin(x)*TMath::Sin(x) + [1] * TMath::Cos(x)*TMath::Cos(x))", 0., duepi);
  TF1 *func2 = new TF1("func2", "[0]*1/(TMath::Sin(x)*TMath::Sin(x) + [1] * TMath::Cos(x)*TMath::Cos(x))", 0., duepi);

  TF1 *funcSinT = new TF1("funcSinT", "(TMath::Sin(x)*TMath::Sin(x))/(x*x)", -10., 10.);
  
  func1 -> SetParameter(0, 1.);//dist1rej->Integral(0, nbins));
  func1 -> SetParameter(1, alpha1);  
  func2 -> SetParameter(0, 1.);//dist2rej->Integral(0, nbins));
  func2 -> SetParameter(1, alpha2);  
  func1 -> SetLineColor(kBlack);
  func1 -> SetLineStyle(2);
  func2 -> SetLineColor(kBlack);
  func2 -> SetLineStyle(2);

  double normSin = funcSinT->Integral(-10., 10.)/(nentries*(10.-(-10.))/nbins);
  //riempimento istogrammi 
  for(int i=0; i<nentries; i++){
    dist1rej -> Fill(gen1.rejection(), norm1);
    dist2rej -> Fill(gen2.rejection(), norm2);
    dist1inv -> Fill(gen1.inversion(), norm1);
    dist2inv -> Fill(gen2.inversion(), norm2);
    dist1root -> Fill(gen1.rootInversion(func1), norm1);
    dist2root -> Fill(gen2.rootInversion(func2), norm2);

    double a = gen1.importanceSampling(-10., 10.);
    distsampl -> Fill(a, normSin);//funcSinT->Integral(-10., 10.))); gen1.sinBig(a)*
  }

  dist1rej->SetLineColor(kRed);
  dist1inv->SetLineColor(kBlue);
  dist1root->SetLineColor(kGreen);
  dist2rej->SetLineColor(kRed);
  dist2inv->SetLineColor(kBlue);
  dist2root->SetLineColor(kGreen);


  //grafico
  TCanvas *c1 = new TCanvas("c1", "alpha = 0.5");
  TCanvas *c2 = new TCanvas("c2", "alpha = 0.001");
  TCanvas *c3 = new TCanvas("c3", "importance sampling");
  

  c1->cd();
  dist1rej->Draw();
  dist1inv->Draw("same");
  dist1root->Draw("same");
  func1->Draw("same");
  
  c2->cd();
  dist2rej->Draw();
  dist2inv->Draw("same");
  dist2root->Draw("same");
  func2->Draw("same");

  c3->cd();
  distsampl->Draw();
  funcSinT->Draw("same");
}
