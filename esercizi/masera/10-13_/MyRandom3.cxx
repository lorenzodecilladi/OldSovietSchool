#include <Riostream.h>
#include "MyRandom3.h"
#include "TMath.h"

ClassImp(MyRandom3)
  ///////////////////////////////////////////////////////
  // Class used to extend the number of functions managed
  // by the class TRandom3 in order to generate random numbers
  // Origin: M. Masera 17/10/02
  // Revised: 17/10/2015
  ////////////////////////////////////////////////////////
//_________________________________________________________________
  MyRandom3::MyRandom3(): TRandom3(),
fAlpha(0.),
fPi(0.),
fBig(0.),
fSqrtAlpha(0.) {
  //Default constructor

}

//_________________________________________________________________
  MyRandom3::MyRandom3(double alpha, UInt_t seed): TRandom3(seed),
fAlpha(alpha),
fPi(0.),
fBig(0.),
fSqrtAlpha(0.){
  // Standard constructor
  SetName("MyRandom3");
  SetTitle("Random number generator: Mersenne-Twister");
  Init();
}
//_________________________________________________________________
void MyRandom3::Init(){
  fPi = TMath::Pi();
  if(fAlpha<=0. || fAlpha>1.){
    Warning("Init","Invalid parameter alpha = %f8.3 \n",fAlpha);
    Warning("Init","This object should be properly initialised\n");
    fAlpha = 0.;
    fBig = 0.;
    fSqrtAlpha = 0.;
  }
  else {
    fBig = 1/fAlpha;
    fSqrtAlpha = TMath::Sqrt(fAlpha);
  }
}
//_________________________________________________________________
MyRandom3::~MyRandom3() {
  // Default destructor
}
//_________________________________________________________________
double MyRandom3::Funct1(double theta) {
  // Function funct1:  1/(sin**2 theta + alpha*cos**2 theta)
  // with positive alpha
  double tmp1 = TMath::Sin(theta);
  tmp1*=tmp1;
  double tmp2 = TMath::Cos(theta);
  tmp2*=tmp2;
  tmp1=tmp1+fAlpha*tmp2;
  return 1./tmp1;
}
//_________________________________________________________________
double MyRandom3::Funct2(double x) {
  if (x>-1.e-9 && x<1.e-9)return 1.;
  return sin(x)*sin(x)/x/x;
}

//_________________________________________________________________
double MyRandom3::Funct1RndmByInversion() {
  // returns a r.n. distributed according to Funct1, using the 
  // inversion technique
  
  double resu = TMath::ATan(fSqrtAlpha*TMath::Tan(fPi*Rndm()-fPi/2.));
  
  if(Rndm()<0.5){
    resu+=TMath::Pi();
  }
  else {
    if(resu<0)resu+=2.*TMath::Pi();
  }
  
  return resu;
}

//_________________________________________________________________
double MyRandom3::Funct1RndmByInversion2() {
  // returns a r.n. distributed according to Funct1, using the 
  // inversion technique (different implementation)

  double u = Rndm();

  double offset = 0;
  if(u>(1./4.) && u<=(3./4.))offset=fPi;
  if(u>(3./4.))offset=2.*fPi;
//  return offset+TMath::ATan(fSqrtAlpha*TMath::Tan(2.*fPi*(u-0.5)));
  return offset+TMath::ATan(fSqrtAlpha*TMath::Tan(2.*fPi*u));
}  
  
  //_________________________________________________________________
double MyRandom3::Funct1RndmByRejection() {
  // returns a r.n. distributed according to Funct1, using the 
  // rejection technique

  double x,y;
  do{
    x=2.*Rndm()*fPi;
    y=this->Rndm()*fBig;
  } while(Funct1(x)<y);
  return x;
}

//_________________________________________________________________
double MyRandom3::Funct1RndmByRejection2() {
  // returns a r.n. distributed according to Funct1, using the 
  // rejection technique - recursive

  double x = 2.*Rndm()*fPi;
  double y = Rndm()*fBig;
  if(Funct1(x)>=y) return x;
  else return Funct1RndmByRejection2();
}

//_________________________________________________________________
double MyRandom3::RndmFunct2(double xmin, double xmax,const double v1, const double v2, const double x2, const double x3){
    // questa function estrae un numero pseudorandom con distribuzione
    // [sin(x)/x]^2
    // utilizzando la tecninca dell'importance sampling
    double gx;
    double x;
    const double alpha = v1*(x2-xmin);
    const double beta = v2*(x3-x2);
    const double gamma = v1*(xmax-x3);
    // norm è l'integrale della funzione maggiorante nel dominio xmin -> xmax
    const double norm = alpha+beta+gamma;
    
    // il loop per l'estrazione del numero è ripetuto se test è vero
    Bool_t test=kTRUE;
    do {
        double u=Rndm();
        // la funzione maggiorante (gx) è definita a tratti
        // x è campionato per inversione
        // quindi la funzione cumulativa è invertita con una condizione su "u"
        // che rispecchia le dicontinuità della funzione maggiorante
        gx=v1;
        if(u<alpha/norm){
            x=norm*u/v1+xmin;
        }
        else if((u>=alpha/norm) && (u<=(alpha+beta)/norm)){
            x=x2+norm*u/v2-alpha/v2;
            gx=v2;
        }
        else {
            x=x3+(norm*u-alpha-beta)/v1;
        }
        // test di reiezione per accettare x/Users/masera/cernbox/DIDATTICA/TANS/TANS15/esercizi/MYRANDOM
        u=Rndm()*gx;
        if(u<Funct2(x))test=kFALSE;
    } while(test);
    return x;
}

  //_________________________________________________________________
void MyRandom3::SphereIso(double & th, double &phi){
  // palla
  phi = 2.*fPi*Rndm();
  th = TMath::ACos(1.-2.*Rndm());
}

  //_________________________________________________________________
double* MyRandom3::SphereIso(){
  // palla  con allocazione della memoria
  double *dire = new double [2];   // CAVEAT:  qualcuno deve 
                                       // mettere un delete da qualche parte
  // Never do that:   double dire[2];
  dire[1] = 2.*fPi*Rndm();
  dire[0] = TMath::ACos(1.-2.*Rndm());
  return dire;
}

  //_________________________________________________________________
void MyRandom3::SphereIso(double dire[]){
  // palla  con un vettore come argomento
  dire[1] = 2.*fPi*Rndm();
  dire[0] = TMath::ACos(1.-2.*Rndm());
}
