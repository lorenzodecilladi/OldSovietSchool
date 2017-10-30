#include<Riostream.h>
#include<TH1D.h>
#include<TRandom3.h>

// dichiarazione di funzioni
double myfunc1(double, double*);
double myfunc2(double, double*);
double metralg(double & , double(*funz)(double , double* ), double* ,double, const double*);


// steering macro
void metropol(int choice=1, double deno=5.){

  // costanti
  const double range[2]={-10.,10.};
  const int nbins = 300;
  const double step = (range[1]-range[0])/nbins;
  const int kNev=9000000;
  const double knorm =step*kNev;
  double delta=(range[1]-range[0])/deno;
  double x0=0.;
  double par[2]={0.,0.};
    
  double (*fptr)(double, double*);
  if(choice==1){
    fptr = &myfunc1;
  }
  else if(choice==2){
    fptr = &myfunc2;
    par[0]=0.;
    par[1]=3.;
  }
  else {
    cout<<"Invalid choice  - abort"<<endl;
    return;
  }
  for(int i=0;i<1000;i++)cout<<metralg(x0,fptr,par,delta,range)<<endl;
  TH1D *dis=new TH1D("dis","MC distribution",nbins,range[0],range[1]);
  TH1D *fteo=new TH1D("fteo","function normalized",nbins,range[0],range[1]);
  double scalingf=0.;
  for(double x=range[0]+step/2.;x<range[1];x+=step){
    fteo->Fill(x,fptr(x,par)*knorm);
    scalingf+=step*fptr(x,par);
  }
  fteo->Scale(1./scalingf);
  fteo->SetLineColor(kRed);
  for(int i=0;i<kNev;i++){
    dis->Fill(metralg(x0,fptr,par,delta,range));
  }
  dis->Draw("histo");
  fteo->Draw("chistosame");
}

//___________________________________________________________
double myfunc1(double x,double*){
  // funzione da campionare  sin/x al quadrato
  
  if (x>-1.e-9 && x<1.e-9)return 1.;
  return sin(x)*sin(x)/x/x;
 
}

//___________________________________________________________
double myfunc2(double x,double* par){
  // funzione da campionare: gaussiana
  double arg=(x*x-par[0]*par[0])/par[1]/par[1]/2.;
  return exp(-arg);
}
//___________________________________________________________
double metralg(double & x0, double(*funz)(double , double* ), double* par, double delta, const double* range){
  Bool_t goon=kFALSE;
  do{
    //    double dx=-delta+gRandom->Rndm()*delta*2.;
    double dx=gRandom->Gaus(0.,delta);
    double rat=funz(x0+dx,par)/funz(x0,par);
    if(rat>=1.){
      x0+=dx;
    }
    else {
      if(gRandom->Rndm()<=rat){
	x0+=dx;
      }
    }
      
    if(x0<range[0] || x0>range[1]){
      goon = kTRUE;
    }
    else {
      goon = kFALSE;
    }
  }while(goon);
    
  return x0;
}
