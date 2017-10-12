#if !defined(__CINT__) || defined(__MAKECINT__)
#include<Riostream.h>
#include <TF1.h>
#include <TFile.h>
#include <TH1D.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TCanvas.h>
#endif


//dichiar funz

void Decay(int& NdecTot, int n0=1000, double alpha = 2.5*pow(10.,-5), double Delt=1., double ttot = 100., unsigned int seed = 95689, bool doHist = true);

void RepeatExp(int Nexp = 1000, int n0=1000, double alpha = 2.5*pow(10.,-5), double Delt=1., double ttot = 100., bool doHist = false);

double exponential(double *x, double *par); //da usare con TF1 //non posso mettere int: la segnatura è double, double!!

double poisson(double *x, double *par);

double binomial(double *x, double *par);



//-----------------------------------------------------
//implementaz

void Decay(int& NdecTot, int n0,double alpha, double Delt, double ttot,unsigned int seed, bool doHist){
  gRandom -> SetSeed(seed);

  double T = ttot;

  
  int Nbins = static_cast<int> (T/Delt); //# int tempo
  // il cast su intero tronca il numero; non è necessario sempre: qui se non lo faccio il compilatore da warning, così gli dico stai tranqui
  //  cout << "# celle: " << Nbins << endl;


  double timetot = Delt*Nbins; //per xcreare istogrammi
  double prob = alpha*Delt; //probabilità
  //cout << "tempo totale: " << timetot << endl;
  
  TH1D *h1 = 0;
  TF1 *fteo = 0;
  bool isNull = h1 == 0;
  //  cout << isNull << endl;
  
  if(doHist){
    h1 = new TH1D("h1", "remaining nuclei", Nbins+1, -Delt/2., timetot+Delt/2.); //così centro celle
    //h1->SetFillColor(kOrange-4);
    
    fteo = new TF1("fteo", exponential, 0., timetot, 2); //exponential: invoco la mia funzione; 2: # parametri
    double N0 = n0;
    double ALPHA = alpha;
    //fteo->SetLineColor(kRed);
    fteo->SetParameters(N0,ALPHA);
    fteo->SetParNames("normalizzazione", "coefficiente");
    
    h1->Fill(0., static_cast<double>(n0)); //cast opzionale; riempio primo elemento
  }
  
  int ndecTot = 0;
  
  for(double time=Delt; time<timetot+Delt/2.; time+=Delt){
    int ndec = 0;
    for(int nuclei =0 ; nuclei<n0; nuclei++)
      if(gRandom->Rndm() < prob) {
	ndec++;
	ndecTot++;
      }
    n0-=ndec; //n0 diminuisce; invece N0 costante!!
    if(!isNull) h1->Fill(time, static_cast<double>(n0)); //aggiungo #nuclei a quel tempo

  }

  NdecTot = ndecTot;
 

  if(!isNull){ 
    TCanvas *c = new TCanvas();
    c -> cd();
    h1->Draw("histo"); //opzione histo mi toglie errori
    fteo->Draw("same");
    
    TCanvas *cLog = new TCanvas();
    cLog -> cd();
    cLog -> SetLogy();
    
    h1 -> Draw("histo");
    fteo -> Draw("same");
    // }
  
  
    //  if(!(h1 = NULL) && !(fteo = NULL)){ 
    
    TFile *file = new TFile("decay.root", "recreate");
    h1->Write();
    fteo->Write();
    
    file->ls(); //stampa cosa c'è nel file
  }
  
}


void RepeatExp(int Nexp, int n0, double alpha, double Delt, double ttot, bool doHist){

  int NdecTot = 0;

  TH1F *hrep = new TH1F("hrep", "Num decays in fixed time T", n0+1, -0.5, n0+0.5);
  
  for(int i=0; i<Nexp; i++){
    //    cout << "\nEvento #: " << i+1 << endl;

    unsigned int seed = static_cast<unsigned int>(gRandom->Rndm() * 100000);
    
    Decay(NdecTot, n0, alpha, Delt, ttot, 0, doHist);
    hrep->Fill(NdecTot);
  }

  
  double norm = hrep->Integral(1, n0+1);
  double hMax =  hrep->GetMaximum();
  double lambda = hrep->GetBinCenter(hrep->GetMaximumBin());
  Double_t lambda_par=alpha*ttot*n0;
  double maxP = TMath::Poisson(lambda_par, lambda_par);

  TF1 *fPoisson = new TF1("fPoisson", poisson, 0., 5*lambda_par, 2);
  fPoisson->SetParameter(0, lambda_par);
  fPoisson->SetParameter(1, norm*maxP);  //dobbiamo considerare l'integrale dell'istogramma

  //cout << hrep->GetMaximum() << endl;
  //cout << norm << endl;
  cout << maxP << endl;
  cout << norm * maxP << endl;
  cout << hMax << endl;
  
  
  //  hrep->GetXaxis()->SetRange(0.,50.);
  fPoisson->Draw();
  hrep->Draw("histosame");

 
  
  //string confirm;
  //cin >> confirm;


  //oppure normalizziamo l'istogramma dividendo per l'integrale dell'istogramma

}


double exponential(double *x, double *par){
  double X = x[0];
  return par[0]*TMath::Exp(-par[1]*X);
}



  


double poisson(double *x, double *par){
  double n = x[0];
  double lambda= par[0];
  double pMax=par[1];

  //return pow(lambda,n)/TMath::Gamma(n)*TMath::Exp();
  return pMax*TMath::Exp(n*(TMath::Log(lambda/n)+1)-lambda);  
  //return TMath::Poisson(n,lambda);
}


double binomial(double *x, double *par){
  return 0.;
}


























/*

PROBLEMI

1. ogni volta che apre file, poi non lo chiude => memory leak, ad un certo punto non apre + file (troppi aperti)
2. ogni volta creare istogrammi interni a delay occupa troppa memoria (!!): per chiudere root ci mette due minuti a furia di invocare distruttori
   
Possibile soluzione: inizializzare un argomento booleano nella funzione che se, vero, fa istogrammi e file, e in RepeatDecay lo chiamiamo FALSE; lo inizializziamo a TRUE così se si esegue solo Decay li fa;

FATTO MA mi dà warning perhcè negli if successivi mi dice che h1, fteo potrebbere non essere inizializzati  -> Risolto con ptatore 0
in ogni caso non vorrei neanche dichiarare h1 e fteo, cosa che adesso devo comunque fare!! Posso farlo?

3. lui dà sempre lo stesso # di decadimenti (3), anche con 1000 eventi: forse gRandom invoca sempre lo stesso numero ??

 */
