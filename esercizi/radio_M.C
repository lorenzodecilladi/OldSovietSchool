#include <TF1.h>
#include <TFile.h>
#include <TH1D.h>
#include <TMath.h>
#include <TRandom3.h>


//dichiar funz

void Decay(int n0=5000, double alpha = 0.03, double Delt=1., double ttot = 300., unsigned int seed = 95689);
double exponential(double *x, double *par); //da usare con TF1 //non posso mettere int: la segnatura è double, double!!

//implementaz

double exponential(double *x, double *par){
  double X=x[0];
  return par[0]*TMath::Exp(-par[1]*X);

}


void Decay(int n0,double alpha, double Delt, double ttot,unsigned int seed){
  gRandom -> SetSeed(seed);
  
  int Nbins = static_cast<int> (ttot/Delt); //# int tempo
  // il cast su intero tronca il numero; non è necessario sempre: qui se non lo faccio il compilatore da warning, così gli dico stai tranqui
  //  cout << "# celle: " << Nbins ....;

  double timetot = Delt*Nbins; //per xcreare istogrammi
  //cout << ...;

  TH1D *h1 = new TH1D("h1", "remaining nuclei", Nbins+1, -Delt/2., timetot+Delt/2.); //così centro celle
  h1->SetFillColor(kOrange-4);

  TF1 *fteo = new TF1("fteo", exponential, 0., timetot, 2); //exponential: invoco la mia funzione; 2: # parametri 
  double N0 = n0;
  double ALPHA = alpha;
  fteo->SetLineColor(kRed);
  fteo->SetParameters(N0,ALPHA);
  fteo->SetParNames("normalizzazione", "coefficiente");

  double prob = alpha*Delt; //probabilità
  h1->Fill(0., static_cast<double>(n0)); //cast opzionale; riempio primo elemento

  for(double time=Delt; time<timetot+Delt/2.; time+=Delt){
    int ndec = 0;
    for(int nuclei = 0 ; nuclei<n0; nuclei++)
      if(gRandom->Rndm() < prob) ndec++;
    n0-=ndec; //n0 diminuisce; invece N0 costante!!
    h1->Fill(time, static_cast<double>(n0)); //aggiungo #nuclei a quel tempo

  }


  TFile *file = new TFile("decay.root", "recreate");
  h1->Write();
  fteo->Write();
  h1->Draw("histo"); //opzione histo mi toglie errori
  fteo->Draw("same");
  file->ls(); //stampa cosa c'è nel file

  
  

}




