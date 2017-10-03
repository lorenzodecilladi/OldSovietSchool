#if !defined(__CINT__) || defined(__MAKECINT__)
#include<Riostream.h>
#include<TFile.h>
#include<TH1D.h>
#include<TCanvas.h>
#include<TAxis.h>
#include<TRandom.h>
#endif

using namespace std;


//TRandom* r = new TRandom();


/*
float gener(float xmin=0., float xmax=1., int seed = 65539)
{
  float ampl = xmax - xmin;

  float x = gRandom -> Rndm(); //puntatore globale di ROOT


   //float x = r -> Rndm();

  return x * ampl + xmin;
}
*/

float gener(int seed = 65539){
  
  float x = gRandom -> Rndm(); //puntatore globale di ROOT

  if(x>=0.&&x<0.5) return (x/0.5*0.2);
  else if(x>0.5&&x<=1.0) return ((x*0.4)+0.6); //(x-0.5)/0.5 * 0.2 + 0.8
  else gener(); //eliminiamo il valore 0.5 per evitare di avere una disproporzione a destra o a sinistra
}






void limite_centrale_multipli(const int ndata = 200000, const int nbins = 100){
  
  TCanvas* c = new TCanvas("c", "c");
  TH1F* hist = new TH1F("hist", "Somma di 1 variabile", nbins, 0., 1.);

  TCanvas* c2 = new TCanvas("c2", "c2");
  TH1F* hist2 = new TH1F("hist2", "Somma di 2 variabili", nbins, 0., 2.);
  
  TCanvas* c10 = new TCanvas("c10", "c10");
  TH1F* hist10 = new TH1F("hist10", "Somma di 10 variabili", nbins, 0., 10.);

  TCanvas* c50 = new TCanvas("c50", "c50");
  TH1F* hist50 = new TH1F("hist50", "Somma di 50 variabili", nbins, 0., 50.);

  TCanvas* c300 = new TCanvas("c300", "c300");
  TH1F* hist300 = new TH1F("hist300", "Somma di 300 variabili", nbins, 0., 300.);
  
  
  
  for(int i=0; i<ndata; i++){
    
    float y = 0.;
    
    
    for(int count = 1; count <= 300; count ++){
      y+=gener();
      if(count==1) hist->Fill(y);
      if(count==2) hist2->Fill(y);
      if(count==10) hist10-> Fill(y);
      if(count==50) hist50-> Fill(y);
      if(count==300) hist300-> Fill(y);
    }
  }    

  c->cd();
  hist->Draw();
  c2->cd();
  hist2->Draw();
  c10->cd();
  hist10->Draw();
  c50->cd();
  hist50->Draw();
  c300->cd();
  hist300->Draw();
  
}







TH1F* histo_sum(const char* name, const char* title, float xmax, int nbins = 100, float xmin = 0., int ndata =200000){
  TH1F* hist = new TH1F(name, title, nbins, xmin, xmax);
  
  for(int i=0; i<ndata; i++){
    float y = 0.;
    for(int count = 1; count <= (int)xmax; count ++){
      y+=gener();
    }
    hist->Fill(y);
  }  

  return hist;
}






//TStopWatch per misurare il tempo di CPU
//Instanziamo timer
//start all inizio
//stop e print alla fine
