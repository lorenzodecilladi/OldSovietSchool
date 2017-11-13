#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TH1I.h>
#include <TH1D.h>
#include <TLine.h>
#include <TMath.h>
#include <TRandom.h>
#include <TRandom3.h>
#endif

using namespace std;
using namespace TMath;

// ~~~~~~~~~~~~~ Dichiarazioni ~~~~~~~~~~~~~
void Chiquadro(); //Funzione da chiamare per eseguire la macro
double Fondo2(int x);
double CalcolaChi(int n[], double nu[], const int lunghezza);
double PearsonDist(double x, int gradiliberta, double norm);
//double PearsonDist(double x, int gradiliberta);

// ~~~~~~~~~~~~ Implementazioni ~~~~~~~~~~~~
void Chiquadro(){
  // dichiarazioni e inizializzazione delle variabili
  const int nbin = 12;
  const int nesperimenti = 1e4;
  const double xmin = 0.;
  const double xmax = 90.;
  const int nbinchi = 90;
  const double larghezza = (xmax - xmin)/nbinchi;
  
  const int dati[nbin] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23};
  int pesi[nbin] = {1, 3, 1, 4, 3,  5,  2,  1,  1,  0,  1,  3};
  double attesi[nbin];
  
  TF1 *Fondo = new TF1("Fondo", "0.169 * (10 - 0.01 * x)", 0, 24);
 
  TH1I *originale = new TH1I("originale", "Dati originali", nbin, 0, 24);
  TH1D *chiquadro = new TH1D("chiquadro", "Distribuzione del #chi^{2}", nbinchi, xmin, xmax);

  // Dati originali: calcolo del Chi quadro e disegno dell'istogramma
  for(int i = 0; i < nbin; i++){
    originale->Fill(dati[i], pesi[i]);
    attesi[i] = Fondo2(dati[i]);
  }

  double chiquadrodati = CalcolaChi(pesi, attesi, nbin);
  cout << "Si ottiene come chi quadro dei dati: " << setprecision(6) << chiquadrodati << endl;

  TCanvas *coriginale = new TCanvas("coriginale", "Canvas dei dati originali", 10, 10, 600, 400);
  coriginale->cd();
  originale->SetFillColor(kBlue);
  originale->Draw("histo");
  Fondo->Draw("same");

  // Simulazione degli eventi e calcolo dei chi quadro
  for(int i = 0; i < nesperimenti; i++){
    int datiesperimenti[nbin] = {0};
    double chiquadroesperimenti = 0.;
    
    for(int j = 0; j < nbin; j++){
      datiesperimenti[j] = gRandom->TRandom::Poisson(attesi[j]);
    }

    chiquadroesperimenti = CalcolaChi(datiesperimenti, attesi, nbin);
    chiquadro->Fill(chiquadroesperimenti);
  }

  double integrale = larghezza*chiquadro->Integral(xmin, xmax);
  cout << integrale << endl;
  TF1 *Pearson = new TF1("Pearson", "PearsonDist(x, 12, integrale)", 0, 90);
  //TF1 *Pearson = new TF1("Pearson", "PearsonDist(x, 12)*integrale", 0, 90);
  
  TCanvas *cchiquadro = new TCanvas("cchiquadro", "Canvas della distribuzione #chi^{2}", 620, 10, 600, 400);
  cchiquadro->cd();
  chiquadro->Draw();
  Pearson->Draw("same");
}

double Fondo2(int x){
  return 0.169 * (10 - 0.01 * x);
}

double CalcolaChi(int n[], double nu[], const int lunghezza){
  double chiquadro = 0.;

  for(int i = 0; i < lunghezza; i++){
    chiquadro += (n[i] - nu[i])*(n[i] - nu[i])/(nu[i]);
  }

  return chiquadro;
}

///*
double PearsonDist(double x, int gradiliberta, double norm){
  double nmezzi = gradiliberta/2;
  
  return norm * pow(x, nmezzi -1) * Exp(-x/2) / (pow(2, nmezzi) * Gamma(nmezzi));
}
//*/

/*
double PearsonDist(double x, int gradiliberta){
  double nmezzi = gradiliberta/2;
  
  return pow(x, nmezzi -1) * Exp(-x/2) / (pow(2, nmezzi) * Gamma(nmezzi));
}
*/
