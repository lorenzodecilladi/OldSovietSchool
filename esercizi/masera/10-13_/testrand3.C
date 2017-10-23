#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <stdio.h>
#include "MyRandom3.h"
#include "TF1.h"
#include "TFile.h"
#include "TH1F.h"
#include "TMath.h"
#include "TStopwatch.h"
#endif
void testrand3(Float_t alpha = 0.001,Int_t nbins = 500, Float_t notrials=1000000, UInt_t seed=987654321){
  Bool_t debug = kFALSE;

  delete gRandom;
  MyRandom3 *mior = new MyRandom3(alpha,seed);
  gRandom = mior;

  Float_t high = 2.*TMath::Pi();
  TH1F *funz = new TH1F("funz","(sin(theta)**2+alpha*cos(theta)**2)**(-1)",nbins,0.,high);
  TH1F *inv = new TH1F("inv","Inversion technique",nbins,0.,high);
  TH1F *inv2 = new TH1F("inv2","Inversion technique (second implementation)",nbins,0.,high);
  TH1F *rej = new TH1F("rej","Rejection technique",nbins,0.,high);
  TH1F *rej2 = new TH1F("rej2","Rejection technique - recursive",nbins,0.,high);

  char testo[50];
  sprintf(testo,"1./(sin(x)*sin(x)+%9.5f *cos(x)*cos(x))",alpha);
  cout<<testo<<endl;
  TF1 *fun = new TF1("fun",testo,0.,high);
  fun->SetNpx(nbins);

  TH1F *standroot = new TH1F("standroot","native root method",nbins,0.,high);
  inv->SetLineColor(kRed);
  inv2->SetLineColor(kMagenta);
  rej->SetLineColor(kBlue);
  rej2->SetLineColor(kOrange-3);
  standroot->SetLineColor(kGreen+2);
  Float_t step = high/nbins;
  cout<<"Pararameter alpha = "<<alpha<<endl;
  cout<<"Number of bins= "<<nbins<<", Bin size = "<<step<<endl;
  cout<<"Number of extracted numbers: "<<notrials<<endl;

  Float_t xx=step/2.;
  Float_t inte=0.;
  for(Int_t i=0;i<nbins;i++){
    Double_t fu = mior->Funct1(xx);
    funz->Fill(xx,fu);
    xx+=step;
    inte+=fu;
  }
  inte=inte*step;
  if(debug)cout<<"Integral = "<<inte<<endl;
  Float_t norm = 2.*TMath::Pi()/TMath::Sqrt(alpha)/step/notrials;
  TStopwatch timer;
  timer.Start(kTRUE);
  for(Int_t i=0;i<notrials;i++){
    inv->Fill(mior->Funct1RndmByInversion(),norm);
  }
  timer.Stop();
  Double_t time1 = timer.CpuTime();

  timer.Start(kTRUE);
  for(Int_t i=0;i<notrials;i++){
    inv2->Fill(mior->Funct1RndmByInversion2(),norm);
  }
  timer.Stop();
  Double_t time1p = timer.CpuTime();

  timer.Start(kTRUE);
  for(Int_t i=0;i<notrials;i++){
    rej->Fill(mior->Funct1RndmByRejection(),norm);
  }
  timer.Stop();
  Double_t time2 = timer.CpuTime();

  timer.Start(kTRUE);
  for(Int_t i=0;i<notrials;i++){
    standroot->Fill(fun->GetRandom(),norm);
  }
  timer.Stop();
  Double_t time3 = timer.CpuTime();

  timer.Start(kTRUE);
  for(Int_t i=0;i<notrials;i++){
    rej2->Fill(mior->Funct1RndmByRejection2(),norm);
  }
  timer.Stop();
  Double_t time4 = timer.CpuTime();

  Double_t relative1,relative1p,relative2,relative3,relative4;
  relative2 = 1.;
  relative1 = time1/time2;
  relative1p = time1p/time2;
  relative3 = time3/time2;
  relative4 = time4/time2;
  cout<<"Tempo di CPU per il metodo dell'inversione (assoluto e relativo) "<<time1<<" "<<relative1<<endl;
 cout<<"Tempo di CPU per il metodo dell'inversione BIS  "<<time1p<<" "<<relative1p<<endl;
  cout<<"Tempo di CPU per il metodo della reiezione "<<time2<<" "<<relative2<<endl;
  cout<<"Tempo di CPU per il metodo della reiezione ricorsivo "<<time4<<" "<<relative4<<endl;
  cout<<"Tempo di CPU per il metodo standard di root via TF1 "<<time3<<" "<<relative3<<endl;
  TFile *fout = new TFile("testrand.root","recreate");
  funz->Write();
  inv->Write();
  inv2->Write();
  rej->Write();
  fun->Write();
  standroot->Write();
  rej2->Write();
  fout->Close();
}
