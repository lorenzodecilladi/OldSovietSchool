#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <TF1.h>
#include <TFile.h>
#include <TH1F.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TCanvas.h>
#endif

  const double knorm = 1000.;  // numero di esperimenti (--> normal. curva teorica)

// DICHIARAZIONE DELLE FUNZIONI
double Gamma(double xx);   // FUNZIONE GAMMA (FATTORIALE)
double Decay(int n0,double alpha, double Delt,double timetot);  // SIM. DECADIMENTI
double poissonian(double xx, double norm, double param); // DENSITA POISSONIANA
double binomial(double xx, double norm, double prob, double ntrials); //DENSITA BINOMIALE
void poisson(int n0 = 1000,double alpha = 2.5e-5, double Delt = 1.,double time=100.);

///////////////////////////////////////////////////////////////////////////
void poisson(int n0,double alpha, double Delt,double time){
  // gRandom punta ad un oggetto della classe TRandom, instanziato per
  // default all'avvio di root.
  unsigned int seed;
  cout<<"Inserire il seed per i numeri casuali\n";
  cin>>seed;
  gRandom->SetSeed(seed);
    
  // booking degli istogrammi
  char title[50];
  sprintf(title,"Numero di decadimenti in %4.1f s",time);
  int nbins = static_cast<int>(n0*alpha*time*4);
  cout<<"numero di celle "<<nbins<<endl;
  double high = nbins-0.5;
  TH1F *ndecays = new TH1F("ndecays",title,nbins,-0.5,high);
    
  //funzione teorica (poissoniana)
  double nu = alpha*n0*time;
  sprintf(title,"Poissoniana con parametro %10.4g ",nu);
  TH1F *fteo = new TH1F("fteo",title,nbins,-0.5,high);
    
  //funzione teorica2 (binomiale)
  double ntrials = time/Delt;
  double prob = alpha*n0*Delt;
  sprintf(title,"Binomiale con parametri p= %10.4g e m = %8.2g",prob,ntrials);
  cout<<title<<endl;
  TH1F *fteo2 = new TH1F("fteo2",title,nbins,-0.5,high);

  cout<<"Numero nuclei: "<<n0<<endl;
  cout<<"Parametro della poissoniana "<<nu<<endl;
  cout<<"Limite superiore per gli istogrammi "<<high<<endl;

// riempimento istogrammi funzioni teoriche
  for (double x=0.;x<high;x+=1.)fteo->Fill(x,poissonian(x,knorm,nu));
  for (double x=0.;x<high;x+=1.)fteo2->Fill(x,binomial(x,knorm,prob,ntrials));

// simulazione
  for(int exper = 0; exper<knorm; exper++){
    if((exper%100)==0)cout<<"Sto processando l'evento n. "<<exper<<endl;
    double nodecay=Decay(n0,alpha,Delt,time);
    ndecays->Fill(nodecay);
  }

  // SALVATAGGIO DEGLI ISTOGRAMMI
  
  TFile *file = new TFile("poisson.root","recreate");
  ndecays->Write();
  fteo->Write();
  fteo2->Write();
  file->Close(); 
  cout<<endl<<endl;

  fteo->Draw("histc");
  new TCanvas();
  fteo2->Draw("histc");
  new TCanvas();
  ndecays->Draw("hist");
  cout<<"Esecuzione terminata - gli istogrammi sono accessibili"<<endl;
  cout<<"Nel file poisson.root"<<endl;
}
///////////////////////////////////////////////////////////////////////////
double Decay(int n0,double alpha, double Delt,double timetot){
  double prob = alpha*Delt; //probabilita
  int n0init = n0; 
  for(double time=0.; time<timetot; time+=Delt){
    int ndec = 0;
    for(int nuclei=0; nuclei<n0;nuclei++)if(gRandom->Rndm()<prob)ndec++;
    n0-=ndec;
  }
  return static_cast<double>(n0init-n0);
}
///////////////////////////////////////////////////////////////////////////
double poissonian(double xx, double norm, double param){
  return norm*(TMath::Power(param,xx)*TMath::Exp(-param-Gamma(xx+1)));
}
///////////////////////////////////////////////////////////////////////////
double binomial(double xx, double norm, double prob, double ntrials){
  //  cout<<"binomial con xx= "<<xx<<" ntrials "<<ntrials<<endl;   
  double log1=Gamma(ntrials+1);
  double log2=Gamma(xx+1);
  double log3=Gamma(ntrials-xx+1);
  double bcoeff=TMath::Exp(log1-log2-log3);
  return norm*TMath::Power(prob,xx)*TMath::Power(1-prob,ntrials-xx)*bcoeff;
}
///////////////////////////////////////////////////////////////////////////
double Gamma(double xx){
  // returns log(gamma(xx)) - tratta da  "Numerical Recipes"
  if(xx<1){
    cout<<"function gamma: argomento non valido "<<xx<<endl;
    return -1.;
  }
  double x,y,tmp,ser;
  static double cof[6]={76.18009172947146,-86.50532032941677,
			24.01409824083091,-1.231739572450155,
			0.1208650973866179e-2,-0.5395239384953e-5};
  int j;

  y=x=xx;
  tmp=x+5.5;
  tmp -= (x+0.5)*TMath::Log(tmp);
  ser=1.000000000190015;
  for (j=0;j<=5;j++) ser += cof[j]/++y;
  return -tmp+log(2.5066282746310005*ser/x);
 }
