#include "TFile.h"
#include "TH1F.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "Riostream.h"
TH1F* maniphist();


void prova(){
  TH1F* histog = maniphist();
  new TCanvas();
  histog->SetLineColor(kBlue);
  histog->SetMinimum(0);
  histog->Draw();
}
TH1F* maniphist(){
  TFile F("kinem.root");
  TH1F *disteta = (TH1F*)F.Get("heta");
  disteta->SetDirectory(0);
  disteta->SetMinimum(0);
  F.Close();
  TAxis *xa=disteta->GetXaxis();
  Double_t step = xa->GetBinWidth(1);
  Int_t b1=xa->FindBin(-2.);
  Int_t b2=xa->FindBin(2.);
  Double_t xlow=xa->GetBinLowEdge(b1);
  Double_t xhig=xa->GetBinUpEdge(b2);
  Int_t nobins=b2-b1+1;
  Double_t step2 = (xhig-xlow)/nobins;
  cout << "Check: "<<step<<"; "<<step2<<endl;
  TH1F* heta2 = new TH1F("heta2","#eta distribution 2",nobins,xlow,xhig);
  Int_t j=1;
  for(Int_t i=b1;i<=b2;i++)heta2->SetBinContent(j++,disteta->GetBinContent(i));
  //  heta2->Draw();
  new TCanvas();
  disteta->Draw();
  heta2->SetLineColor(2);
  heta2->Draw("same");
  return heta2;
}
