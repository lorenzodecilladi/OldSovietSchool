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

// ~~~~~~~~~~~~~~~~~~~ Dichiarazioni ~~~~~~~~~~~~~~~~~~~

void Chiquadro(); //Funzione da chiamare per eseguire la macro con fondo basso
void ChiquadroAlto(); //Funzione da chiamare per eseguire la macro con fondo alto

double Fondo(int x);
double CalcolaChi(int n[], double nu[], const int lunghezza);
double PearsonDist(double x, const int gradiliberta, double normalizzazione);
//double PearsonDist(double x, int gradiliberta);


// ~~~~~~~~~~~~~~~~~~ Implementazioni ~~~~~~~~~~~~~~~~~~

// ----------------- Main della macro 1 ----------------
void Chiquadro(){
  
  // Dichiarazioni e inizializzazione delle variabili
  const int nbin = 12;
  const int nesperimenti = 1e6;
  const double xmin = 0.;
  const double xmax = 90.;
  const int nbinchi = 100;
  const double larghezza = (xmax - xmin) / nbinchi;
  
  const int dati[nbin] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23};
  int pesi[nbin] = {1, 3, 1, 4, 3,  5,  2,  1,  1,  0,  1,  3};
  double attesi[nbin];
  
  TF1 *fFondo = new TF1("fFondo", "0.169 * (10 - 0.01 * x)", 0, 24);
 
  TH1I *hOriginale = new TH1I("hOriginale", "Dati originali", nbin, 0, 24);
  TH1D *hChiquadro = new TH1D("hChiquadro", "Distribuzione del #chi^{2}", nbinchi, xmin, xmax);

  // Dati originali: calcolo del chiquadro e disegno dell'istogramma
  for(int i = 0; i < nbin; i++){
    hOriginale->Fill(dati[i], pesi[i]);
    attesi[i] = Fondo(dati[i]);
  }

  double chiquadrodati = CalcolaChi(pesi, attesi, nbin);
  cout << "Si ottiene come \u03c7\u00b2 dei dati: " << setprecision(6) << chiquadrodati << endl; //\u03c7\u00b2 serve per far comparire chiquadro

  TCanvas *cOriginale = new TCanvas("cOriginale", "Canvas dei dati originali", 10, 10, 600, 400);
  cOriginale->cd();
  hOriginale->SetFillColor(kBlue);
  hOriginale->Draw("histo");
  fFondo->Draw("same");
  
  // Dati simulati: simulazione degli eventi e calcolo dei chiquadro per ogni evento
  for(int i = 0; i < nesperimenti; i++){
    int datiesperimenti[nbin] = {0};
    double chiquadroesperimenti = 0.;
    
    for(int j = 0; j < nbin; j++){
      datiesperimenti[j] = gRandom->TRandom::Poisson(attesi[j]);
    }

    chiquadroesperimenti = CalcolaChi(datiesperimenti, attesi, nbin);
    hChiquadro->Fill(chiquadroesperimenti);
  }

  double integrale = larghezza * hChiquadro->Integral(xmin, xmax);
  cout << "L'integrale dell'istogramma per la normalizzazione vale: " << integrale << endl;
  TF1 *fPearson = new TF1("fPearson", "PearsonDist(x, nbin, integrale)", 0, 90);
  //TF1 *fPearson = new TF1("fPearson", "PearsonDist(x, nbin)*integrale", 0, 90);

  // Dati simulati: grafici con la distribuzione del chiquadro
  TLine *lChiquadroDati = new TLine(chiquadrodati, 0, chiquadrodati, integrale*0.05);
  
  TCanvas *cChiquadro = new TCanvas("cChiquadro", "Canvas della distribuzione chiquadro con fondo basso", 100, 100, 1200, 400);
  cChiquadro->Divide(2,1);
  
  cChiquadro->cd(1);
  hChiquadro->GetXaxis()->SetTitle("#chi^{2}");
  hChiquadro->GetYaxis()->SetTitle("Occorrenze");
  hChiquadro->SetLineColor(kBlue);
  hChiquadro->Draw();
  lChiquadroDati->SetLineColor(kViolet);
  lChiquadroDati->SetLineWidth(2);
  lChiquadroDati->Draw("same");
  fPearson->SetLineColor(kRed);
  fPearson->Draw("same");

  cChiquadro->cd(2);
  gPad->SetLogy();
  hChiquadro->Draw("hist e0");
  lChiquadroDati->Draw("same");
  fPearson->Draw("same");

  // Dati originali: calcolo del p-value
  int nbinchiquadrodati = hChiquadro->GetXaxis()->FindBin(chiquadrodati);
  double integralepvalue = larghezza * hChiquadro->Integral(nbinchiquadrodati, nbinchi);
  double pvalue = integralepvalue / integrale;

  cout << "Il p-value dei dati vale: " << pvalue << endl;
}


// --- Funzione con la distribuzione dei dati attesa ---
double Fondo(int x){
  return 0.169 * (10 - 0.01 * x);
}


// ------- Funzione per il calcolo del chiquadro -------
double CalcolaChi(int n[], double nu[], const int lunghezza){
  double chiquadro = 0.;

  for(int i = 0; i < lunghezza; i++){
    chiquadro += (n[i] - nu[i])*(n[i] - nu[i])/(nu[i]);
  }

  return chiquadro;
}


// ------ Funzione con la distribuzione di Pearson -----
// /*
double PearsonDist(double x, const int gradiliberta, double normalizzazione){
  double nmezzi = gradiliberta/2;
  
  return normalizzazione * pow(x, nmezzi -1) * Exp(-x/2) / (pow(2, nmezzi) * Gamma(nmezzi));
}
// */

/*
double PearsonDist(double x, int gradiliberta){
  double nmezzi = gradiliberta/2;
  
  return pow(x, nmezzi -1) * Exp(-x/2) / (pow(2, nmezzi) * Gamma(nmezzi));
}
*/


// ----------------- Main della macro 2 ----------------
void ChiquadroAlto(){
  
  // Dichiarazioni e inizializzazione delle variabili
  const int nbin = 12;
  const int nesperimenti = 1e6;
  const double xmin = 0.;
  const double xmax = 90.;
  const int nbinchi = 100;
  const double larghezza = (xmax - xmin)/nbinchi;
  
  const int dati[nbin] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23};
  int pesi[nbin] = {1, 3, 1, 4, 3,  5,  2,  1,  1,  0,  1,  3};
  double attesi[nbin];
  
  TF1 *fFondo = new TF1("fFondo", "1000 * 0.169 * (10 - 0.01 * x)", 0, 24);
 
  TH1I *hOriginale = new TH1I("hOriginale", "Dati originali", nbin, 0, 24);
  TH1D *hChiquadro = new TH1D("hChiquadro", "Distribuzione del #chi^{2}", nbinchi, xmin, xmax);

  // Dati originali: calcolo del chiquadro e disegno dell'istogramma
  for(int i = 0; i < nbin; i++){
    hOriginale->Fill(dati[i], pesi[i]);
    attesi[i] = Fondo(dati[i]) * 1000;
  }

  double chiquadrodati = CalcolaChi(pesi, attesi, nbin);
  cout << "Si ottiene come \u03c7\u00b2 dei dati: " << setprecision(6) << chiquadrodati << endl;

  TCanvas *cOriginale = new TCanvas("cOriginale", "Canvas dei dati originali", 10, 10, 600, 400);
  cOriginale->cd();
  hOriginale->SetFillColor(kBlue);
  hOriginale->Draw("histo");
  fFondo->Draw("same");
  
  // Dati simulati: simulazione degli eventi e calcolo dei chiquadro per ogni evento
  for(int i = 0; i < nesperimenti; i++){
    int datiesperimenti[nbin] = {0};
    double chiquadroesperimenti = 0.;
    
    for(int j = 0; j < nbin; j++){
      datiesperimenti[j] = gRandom->TRandom::Poisson(attesi[j]);
    }

    chiquadroesperimenti = CalcolaChi(datiesperimenti, attesi, nbin);
    hChiquadro->Fill(chiquadroesperimenti);
  }

  double integrale = larghezza*hChiquadro->Integral(xmin, xmax);
  cout << "L'integrale dell'istogramma per la normalizzazione vale: " << integrale << endl;
  TF1 *fPearson = new TF1("fPearson", "PearsonDist(x, nbin, integrale)", 0, 90);
  //TF1 *fPearson = new TF1("fPearson", "PearsonDist(x, nbin)*integrale", 0, 90);

  // Dati simulati: grafici con la distribuzione del chiquadro
  TLine *lChiquadroDati = new TLine(chiquadrodati, 0, chiquadrodati, integrale*0.05);
  
  TCanvas *cChiquadro = new TCanvas("cChiquadro", "Canvas della distribuzione chiquadro con fondo basso", 100, 100, 1200, 400);
  cChiquadro->Divide(2,1);
  
  cChiquadro->cd(1);
  hChiquadro->GetXaxis()->SetTitle("#chi^{2}");
  hChiquadro->GetYaxis()->SetTitle("Occorrenze\n\n");
  hChiquadro->SetLineColor(kBlue);
  hChiquadro->Draw();
  lChiquadroDati->SetLineColor(kViolet);
  lChiquadroDati->SetLineWidth(2);
  lChiquadroDati->Draw("same");
  fPearson->SetLineColor(kRed);
  fPearson->Draw("same");

  cChiquadro->cd(2);
  gPad->SetLogy();
  hChiquadro->Draw("hist e0");
  lChiquadroDati->Draw("same");
  fPearson->Draw("same");

  // Dati originali: calcolo del p-value
  int nbinchiquadrodati = hChiquadro->GetXaxis()->FindBin(chiquadrodati);
  double integralepvalue = larghezza * hChiquadro->Integral(nbinchiquadrodati, nbinchi);
  double pvalue = integralepvalue / integrale;

  cout << "Il p-value dei dati vale: " << pvalue << endl;
}
