#if !defined(__CINT__) || defined(__MAKECINT__)
#include<Riostream.h>
#include<TFile.h>
#include<TH1D.h>
#include<TF1.h>
#include<TCanvas.h>
#include<TAxis.h>
#include<TRandom.h> //3??? 
#endif

using namespace std;



TH1F* simulation(const int N0, const float alpha, const float totalT = 300.0, const float deltaT = 1.0, int seed = 63548){

  int nbins = (int)(totalT/deltaT);
  cout << "nbins " << nbins << endl;
  TH1F *hist = new TH1F("hist", "radioactive decay", nbins, 0., totalT);
  
  int Ndec = 0; //number of decayed nuclei

  
  for(float t=0.; t<=totalT; t+=deltaT){

    cout << t << " N0 - N dec = " << N0 - Ndec << endl;

    hist -> Fill(t,N0-Ndec);
    
    for(int N=1; N<=N0-Ndec; N++) //loop over not-yet-decayed nuclei
      if(gRandom->Rndm(seed) < alpha*deltaT) Ndec++;
    
  }
  hist -> Fill(N0-Ndec);

  return hist;
}




void radioactive_decay_MC(const int N0, const float alpha, const float totalT = 300.0, const float deltaT = 1.0, int seed = 63548){

  TCanvas *c = new TCanvas();
  c -> cd();
  
  TH1F *histogram = simulation(N0, alpha, totalT, deltaT, seed);
  histogram -> Draw("hist"); //Lhist
  
  TF1 *func = new TF1("func", "[0]*TMath::Exp(-[1]*x)", 0., totalT);
  func -> SetParameter(0, N0);
  func -> SetParameter(1, alpha);
  func -> Draw("same");

  TCanvas *cLog = new TCanvas();
  cLog -> cd();
  cLog -> SetLogy();

  histogram -> Draw("hist");
  func -> Draw("same");

}








/*
TGraphError* simulation(const int N0, const float alpha, const float totalT = 300.0, const float deltaT = 1.0, int seed = 63548){

  int nbins = (int)(totalT/deltaT);
  cout << "nbins " << nbins << endl;
  TGraph *hist = new TH1F("hist", "radioactive decay", nbins, 0., totalT);
  
  int Ndec = 0; //number of decayed nuclei

  
  for(float t=0.; t<=totalT; t+=deltaT){

    cout << t << " N0 - N dec = " << N0 - Ndec << endl;

    hist -> Fill(t,N0-Ndec);
    
    for(int N=1; N<=N0-Ndec; N++) //loop over not-yet-decayed nuclei
      if(gRandom->Rndm(seed) < alpha*deltaT) Ndec++;
    
  }
  hist -> Fill(N0-Ndec);

  return hist;
}

*/
