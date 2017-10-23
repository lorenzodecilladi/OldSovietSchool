#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TCanvas.h>
#include <TFile.h>
#include <TH1F.h>
#include <TRandom3.h>
#include <TString.h>
#include <TStopwatch.h>
#include <TStyle.h>
#endif
// dichiarazione di funzioni
// questa macro funziona solo con Root 6
double myfunc(double theta, double* alpha);
double myfunc2(double x, double* par);
double rejection(double(*funz)(double , double* ),double big, double x1, double x2, double *par);
void mytest(TString choice);

// funzione per testare l'estrazione di numeri casuali
void mytest(TString choice){
    double par[1];
    double big;
    double xmin;
    double xmax;
    
    double (*fptr)(double, double*);
    
    if(choice.Contains("uno")){
        fptr = &myfunc;
        par[0]=0.001;
        big=1./par[0];
        xmin=0.;
        xmax=2.*acos(-1.);
    }
    else {
        fptr = &myfunc2;
        par[0]=1.;
        big=1./par[0];
        xmin=-10.;
        xmax=10.;
    }
    
    int nobins=500;
    int ntrials=1000000;
    double step=(xmax-xmin)/nobins;
    
    TH1F* hteo = new TH1F("hteo","funzione teorica",nobins,xmin,xmax);
    double x=xmin+step/2.;
    for(int i=0;i<nobins;i++){
        hteo->Fill(x,fptr(x,par));
        x+=step;
    }
    TH1F* hmc = new TH1F("hmc","estrazione MC",nobins,xmin,xmax);
    
    double norm=hteo->Integral()/ntrials;
    for(int i=0; i<ntrials; i++)hmc->Fill(rejection(fptr,big,xmin,xmax,par),norm);
    
    hmc->SetMarkerStyle(20);
    hmc->Draw("pe");
    hteo->SetLineColor(kRed);
    hteo->Draw("histcsame");
}

// estrazione random number con tecnica della reiezione
double rejection(double(*funz)(double , double* ),double big, double x1, double x2, double *par){
  double x,y;
  do {
    x=gRandom->Rndm()*(x2-x1)+x1;
    y=big*gRandom->Rndm();

  }while(y>funz(x,par));
  return x;
}

// funzione 1
double myfunc(double theta, double* alpha){
    double tmp1=sin(theta);
    tmp1*=tmp1;
    double tmp2=cos(theta);
    tmp2*=tmp2;
    tmp1=tmp1+alpha[0]*tmp2;
    return 1./tmp1;
}

// funzione 2 (N.B. ha la stessa signature di myfunc)
double myfunc2(double x, double*){
    double tmp=sin(x)/x;
    return tmp*=tmp;
}



