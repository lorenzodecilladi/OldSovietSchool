#if !defined(__CINT__) || defined(__MAKECINT__)
#include<Riostream.h>
#include<TFile.h>
#include<TH1D.h>
#include<TCanvas.h>
#include<TAxis.h>
#include<TRandom.h>
#endif

using namespace std;

/*
//TRandom* r = new TRandom();

//template<typename T> double mT(const T& p1, const T& p2){

 //COMPILA MA NON INTERPRETA
template<class T>
T gener(const T xmin, const T xmax){
  
  T result = xmin+xmax;  
  return result;
  
  }/**/
float gener(float xmin=0., float xmax=1., int seed = 65539)
{
  float ampl = xmax - xmin;

  float x = gRandom -> Rndm(); //puntatore globale di ROOT
  
  //float x = r -> Rndm();

  return x * ampl + xmin;
}


void limite_centrale(const int ndata = 100000){

  
  TCanvas* c = new TCanvas("c", "c");
  TH1F* hist = new TH1F("hist", "Somma di 1 variabile", 100, 0., 1.);

  TCanvas* c2 = new TCanvas("c2", "c2");
  TH1F* hist2 = new TH1F("hist2", "Somma di 2 variabili", 100, 0., 1.);

  for(int i=0; i<ndata; i++){
    float y1 = gener(0., 0.2);
      hist -> Fill(y1);
    float y2 = gener(0.8, 1.);
      hist -> Fill(y2);
  }

  hist -> Draw();
  
}

 
//TStopWatch per misurare il tempo di CPU
//Instanziamo timer
//start all inizio
//stop e print alla fine

//*/
