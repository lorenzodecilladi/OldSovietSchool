#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <TMath.h>
#include <TH1F.h>
#include <TRandom3.h>
#include <TStyle.h>
#include <TLine.h>
#endif

double nomea;  // numero misure (default 5)
double tau0 = 1.;  // valore vero del parametro esponenziale

//______________________________________________________________________
double evalfun(double tau,double somma){
  //__________  Log-likelihood esponenziale
  double par=nomea*TMath::Log(1./tau);
  double llik=par-somma/tau;
  return llik;
}

//______________________________________________________________________
double trovazero(double t1, double t2,double somma){
  //_____ valutazione dei 2 valori del parametro per cui LnL è pari
  //_____ al massimo -.5 (intervallo al primo quantile)
  //_____ metodo di bisezione
  do{
    double t=(t1+t2)/2.;
    double s=evalfun(t,somma)-(evalfun(somma/nomea,somma)-0.5);
    double s1=evalfun(t1,somma)-(evalfun(somma/nomea,somma)-0.5);
    if(s*s1>0.){
      t1=t;
    }
    else {
      t2=t;
    } 
  }while((t2-t1)>1.e-9);
  return t2;
}

void llexp(UInt_t seed = 98765432, double nm=5.){
  //_____ main macro
  //_____ nm ---> Numero di misure di variabile aleatoria esponenziale con par tau
  nomea = nm;
  gRandom->SetSeed(seed);
  double somma=0.;
  for(Int_t i=0;i<nomea;i++){
    double meas = gRandom->Exp(tau0);
    printf("%d) %5.3f\n",i+1,meas);
    somma+=meas;
  }
  double stima = somma/nomea;
  double llmax= evalfun(stima,somma); 
  double lmin=llmax-1.;
  double lmax=llmax+0.1;
  double estr1=trovazero(0.01,stima,somma);
  double estr2=trovazero(stima,5.*tau0,somma);
  char tito[60];
  sprintf(tito,"%d misure esponenziali",(int)nomea);
  double xmin=estr1*0.5;
  double xmax=estr2*1.5;
  TH1F *val = new TH1F("val",tito,100,xmin,xmax);
  val->SetMinimum(lmin);
  val->SetMaximum(lmax);
  printf("\n Stima: %5.3f\n",stima);
  double step=(xmax-xmin)/100.;
  for(double tau=xmin+step/2. ; tau<xmax ; tau+=step){
    val->Fill(tau,evalfun(tau,somma));
  }
  gStyle->SetOptStat(0);
  val->GetXaxis()->SetTitle("#tau");
  val->GetYaxis()->SetTitle("ln L(#tau )");
  val->SetLineColor(2);
  val->SetLineWidth(4);
  val->Draw("lhist");
  TLine *l = new TLine(stima,lmin,stima,lmax);
  l->SetLineWidth(2);
  l->SetLineColor(kGreen+2);
  l->Draw();
  TLine *l2 = new TLine(xmin,llmax,xmax,llmax);
  l2->SetLineStyle(2);
  l2->Draw();
  TLine *l3 = new TLine(xmin,llmax-0.5,xmax,llmax-0.5);
  l3->SetLineStyle(2);
  l3->SetLineColor(kBlue);
  l3->Draw();
  printf("Estremi: %5.3f   %5.3f \n",estr1,estr2);  
  TLine *l4 = new TLine(estr1,lmin,estr1,llmax-0.5);
  l4->SetLineStyle(2);
  l4->SetLineColor(kBlue);
  l4->Draw();
  TLine *l5 = new TLine(estr2,lmin,estr2,llmax-0.5);
  l5->SetLineStyle(2);
  l5->SetLineColor(kBlue);
  l5->Draw();
  TLine *l6 = new TLine(tau0,lmin,tau0,lmax);
  l6->SetLineStyle(5);
  l6->SetLineWidth(2);
  l6->SetLineColor(kMagenta);
  l6->Draw();
  double binf = stima-estr1;
  double bsup = estr2-stima;
  printf("Valore stimato %5.3f -%5.3f +%5.3f \n",stima,binf,bsup);
}
