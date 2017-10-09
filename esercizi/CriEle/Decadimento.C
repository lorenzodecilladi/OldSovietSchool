#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TH1F.h>
#include <TF1.h>
#include <TFile.h>
#include <TRandom.h>
#include <TVirtualFitter.h>

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH
#endif

void Decadimento(int ntot, const float deltat, const float ttot, const float alfa){

  const int dimensione = (int)ttot/deltat;
  const float Ntot = ntot;
  float tempo = 0.;
  
  TH1F *istogramma = new TH1F("istogramma", "Simulazione di un decadimento", dimensione, 0., ttot);
  
  for(int i = 0; i < dimensione; i++){
    int Ndec = 0;
    
    for(int j = 0; j < ntot; j++){
      if(gRandom->Rndm() <= alfa*tempo)
	Ndec++;
    }
    
    tempo = tempo + deltat;
    ntot = ntot - Ndec;
    istogramma->TH1F::AddBinContent(i+1, (double)ntot);
  }

  TCanvas *chisto = new TCanvas("chisto", "Simulazione di un decadimento", 10, 10, 1280, 1024);
  chisto->cd();
  istogramma->Draw("HISTO");

  TF1 *fhisto = new TF1("fhisto", "[1]*TMath::Exp(-[0]*x)");
  TVirtualFitter::SetMaxIterations(100000);
  fhisto->SetParameter(0, alfa);
  fhisto->SetParameter(1, Ntot);
  fhisto->SetLineColor(2);

  istogramma->Fit(fhisto, "M");
  cout << "Chi^2:" << fhisto->GetChisquare() << ", number of DoF: " << fhisto->GetNDF() << " (Probability: " << fhisto->GetProb() << ")." << endl;
  cout << "--------------------------------------------------------------------------------------------------------" << endl;
}
