#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TF1.h>
#include <TFile.h>
#include <TH1D.h>
#include <TMath.h>
#include <TRandom3.h>
#include <Riostream.h>
#endif

// Dichiarazione delle funzioni
void Decay(int n0 = 50000,double alpha = 0.03, double Delt = 1.,
           double ttot = 300., unsigned int seed=95689);
double exponential(double *x, double *par);

//_____________________________________________________________
void Decay(int n0,double alpha, double Delt,double ttot, unsigned int seed){
  gRandom->SetSeed(seed);
  int Nbins = static_cast<int>(ttot/Delt); // numero di intervalli di tempo
  cout << "Numero di celle: "<<Nbins<<" di ampiezza "<<Delt<<" s";
  double timetot = Delt*Nbins;  // tempo totale = ttot a meno di arrotondamenti
  cout<<" Tempo totale "<<timetot<<endl;
  // histogram booking
  TH1D *h1 = new TH1D("h1","Remaining nuclei",Nbins+1,-Delt/2.,timetot+Delt/2.);
  h1->SetFillColor(kOrange-4);
  //funzione teorica
  TF1 *fteo = new TF1("fteo",exponential,0.,timetot,2);
  fteo->SetLineColor(kRed);
  double N0 = n0;
  double ALPHA = alpha;
  fteo->SetParameters(N0,ALPHA);
  fteo->SetParNames("normalizzazione","coefficiente");
  double prob = alpha*Delt; //probabilita
  h1->Fill(0.,static_cast<double>(n0));
  for(double time=Delt; time<timetot+Delt/2.; time+=Delt){
    int ndec = 0;
    for(int nuclei=0; nuclei<n0;nuclei++)if(gRandom->Rndm()<prob)ndec++;
    n0-=ndec;
    h1->Fill(time,static_cast<double>(n0));
  }
  TFile *file = new TFile("decay.root","recreate");
  h1->Write();
  fteo->Write();
  h1->Draw("histo");
  fteo->Draw("same");
  file->ls();
}

//_____________________________________________________________
double exponential(double *x, double *par){
  double xx = x[0];
  return par[0]*exp(-par[1]*xx);
}
