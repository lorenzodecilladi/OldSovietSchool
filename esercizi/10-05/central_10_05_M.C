#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TCanvas.h>
#include <TFile.h>
#include <TH1D.h>
#include <TRandom3.h>
#include <TRandom2.h>
#include <TStopwatch.h>
#include <TStyle.h>
#endif
const int kNoOfIter = 200000;   //Numero di estrazioni

double numrnd();

void central(unsigned int seed=98765){
  /*********************************************************************
   * Questa macro calcola la somma di n numeri estratti secondo una    *
   * distribuzione uniforme non connessa (tra 0 e 0.2 e tra 0.8 e 1).  *
   * Si vede che la distribuzione della somma tende alla forma         *
   * gaussiana al crescere di n                                        *
   *********************************************************************/

  // TStopwatch: classe utilizzata per monitorare il tempo di CPU
  TStopwatch timer;
  timer.Start();   // il timer e` avviato
 
  // Cancellazione dell'oggetto TRandom creato in root per default
  // questa operazione e' inutile se si vuole usare TRandom3, visto che gRandom punta 
  // gia' a un oggetto TRandom3. E' necessaria qualora si voglia usare TRandom2
    delete gRandom;
  // reinizializza gRandom come oggetto della classe TRandom2  
    gRandom = new TRandom2(seed);
    
  // gRandom->SetSeed(seed);

  // istogrammi
  TH1D *vt[8];
  // file su cui veranno salvati gli istogrammi
  TFile *file = new TFile("somma.root","recreate");
  // Booking degli istogrammi
  char nome[30];
  char titolo[50];
  int smm[8]={1,2,3,5,10,50,100,300};
  double sdev=0.4;
  double aver=0.5;
  for(int i=0;i<8;i++){
    sprintf(nome,"h%d",smm[i]);
    sprintf(titolo,"Somma di %d termini",smm[i]);
    double sdevt=sqrt(smm[i]*sdev*sdev);
    double x1=aver*smm[i]-5.*sdevt;
    double x2=aver*smm[i]+5.*sdevt;
    if(x1<0.)x1=0.;
    if(x2>smm[i])x2=smm[i];
    vt[i]=new TH1D(nome,titolo,100,x1,x2);
  }
  // Estrazione
  for (int i=0; i<kNoOfIter; i++){
    double somma=0.;
    for(int j=1;j<=300;j++){
      /*                    Si usano 2 estrazioni di numeri casuali
			    double acaso=0.2*gRandom->Rndm();
			    double partial=gRandom->Rndm();
			    if(partial<0.5)acaso+=0.8;
      */
      // cosi' se ne usa una sola: confrontare le performance!
      double acaso = numrnd();
      somma+=acaso;
      for(int k=0;k<8;k++)if(j==smm[k])vt[k]->Fill(somma);
    }
  }
  TCanvas *cv[8];
  gStyle->SetOptFit();  // visualizza i parametri di fit
  for(int i=0;i<8;i++){
    cv[i] = new TCanvas();
    vt[i]->SetFillColor(43);
    if(i>4)vt[i]->Fit("gaus");   // fit gaussiano
    cv[i]->cd();
    vt[i]->Draw();
  }
  file->Write();   //scrittura degli istogrammi su file
  timer.Stop();
  timer.Print();  // stampa il tempo di esecuzione della macro
}

//______________________________________________________

double numrnd(){
  double acaso=gRandom->Rndm();
  if(acaso<0.5){
    acaso*=2*0.2;
  }
  else {
    acaso=(acaso-0.5)*2*0.2+0.8;
  }
  return acaso;
}
/*
double numrnd(){
    double acaso;
    do{
        acaso=gRandom->Rndm();
    }while(acaso>0.2 && acaso<0.8);
    return acaso;
}
*/


