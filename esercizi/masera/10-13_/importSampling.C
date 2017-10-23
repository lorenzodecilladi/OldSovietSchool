#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH1D.h>
#include <TRandom3.h>
#include <TStopwatch.h>
#include "MyRandom3.h"
#endif


void impsamp(){
  // macro principale
  // Origin: M.Masera 19/10/2014
  // Modificata il 14/10/2015 (metodi spostanti in MyRandom3)
  // la simulazione è fatta
  // con la tecnica dell'importance sampling;


  // costanti
  const int kNev=1000000;
  const double xmin =-10.;
  const double xmax = 10.;
  const int nbins = 300;
  const double step = (xmax-xmin)/nbins;
  const double knorm =step*kNev;
  const double x2=-2.6;
  const double x3=2.6;
  const double v1=0.05;
  const double v2=1.;
  //

  delete gRandom;
  MyRandom3 *mior = new MyRandom3(0.5,432987);
  gRandom=mior;

  cout<<"Simulazione con la tecnica dell'importance sampling \n";

  TH1D *hr = new TH1D("hr","simulazione [sin(x)/x]^2",nbins,xmin,xmax);
  TH1D *tfn = new TH1D("tfn","funzione teorica normalizzata",nbins,xmin,xmax);
  TH1D *tf = new TH1D("tf","funzione teorica [sin(x)/x]^2",nbins,xmin,xmax);
  TH1D *mj =new TH1D("mj","maggiorante",nbins,xmin,xmax);

  //  notare le normalizzazione per il confronto funzione <--> simulazione
  double scalingf=0.;
  for(double x=xmin+step/2.;x<xmax;x+=step){
    double magg=v1;
    if(x>=x2 && x<=x3)magg=v2;
    mj->Fill(x,magg);
    tfn->Fill(x,knorm*MyRandom3::Funct2(x));
    tf->Fill(x,MyRandom3::Funct2(x));
    scalingf+=step*MyRandom3::Funct2(x);
  }
  cout<<"Fattore di normalizzazione "<<scalingf<<endl;
  tfn->Scale(1./scalingf);
  TStopwatch timer;
  timer.Start();
  for(int i=0;i<kNev;i++)hr->Fill(mior->RndmFunct2(xmin,xmax,v1,v2,x2,x3));
  timer.Stop();
  timer.Print();
  tfn->SetLineColor(kRed);
  hr->SetMarkerStyle(20);
  hr->SetMarkerSize(0.5);
  hr->Draw("pe");
  tfn->Draw("lhistsame");
  new TCanvas();
  tf->SetLineColor(kRed);
  mj->SetLineColor(kBlue);
  tf->Draw("lhist");
  mj->Draw("lhistsame");
}

