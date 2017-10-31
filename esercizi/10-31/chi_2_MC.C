#if !defined(__CINT__) || defined(__MAKECINT__)
#include<Riostream.h>
#include <TF1.h>
#include <TFile.h>
#include <TH1D.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TCanvas.h>
#endif



double poisson(double *x, double *par);
double chi2(double *x, double *mu, int N);
double rootInversion(TF1* funcPtr);
  




void chi_2_MC(const int nloop = 1000){

  const int nbins = 12;
  double data[nbins] = {1., 3., 1., 4., 3., 5., 2., 1., 1., 0., 1., 3.};
  double mu[nbins];
  TCanvas *c1 = new TCanvas();
  c1->cd();
  TH1D *histData = new TH1D("histData","Istogramma dati osservati",nbins,0.,24.);
  for(int i=0; i<nbins; i++){
    histData -> Fill(2*i+1,data[i]);
    mu[i] = 0.169*(10-0.01*(2*i+1));
  }
  histData-> Draw("hist");


  TF1 *expBg = new TF1("expBg", "0.169*(10-0.01*x)",0.,24.);
  expBg->Draw("same");


  cout << chi2(data,mu,nbins) <<endl;
  

  TCanvas *c2 = new TCanvas();
  c2->cd();
  TH1D *histChi2 = new TH1D("histChi2","Istogramma chi quadri MC",30,0.,60.);
  TF1 *fPoisson = new TF1("fPoisson", poisson, 0., 24, 1);
  double x[nbins];
  
  for(int j=0; j<nloop; j++){
    for(int i=0; i<nbins; i++){
      fPoisson->SetParameter(0, mu[i]);
      x[i]= rootInversion(fPoisson);
    }
    histChi2->Fill(chi2(x,mu,nbins));
  }
  histChi2->Draw();
  
}



double chi2(double *x, double *mu, int N){
  double chiSquare = 0.;
  for(int i=0; i<N; i++)
    chiSquare += (x[i] - mu[i])*(x[i] - mu[i])/(mu[i]);
  return chiSquare;
}


double poisson(double *x, double *par){
  double n = x[0];
  double lambda= par[0];
  //double pMax=par[1];

  //return pow(lambda,n)/TMath::Gamma(n)*TMath::Exp();
  return TMath::Exp(n*(TMath::Log(lambda/n)+1)-lambda);  
  //return TMath::Poisson(n,lambda);
}


//ROOT NUMERICAL INVERSION
double rootInversion(TF1* funcPtr){

  //funcPtr.SetParameter(0, fParam);  
  return funcPtr->GetRandom();
}
