#include "Riostream.h"
#include "Particle.h"
#include "Vertex.h"
#include "Transport.h"
#include "MultipleScattering.h"
#include "Detector.h"
#include "Rootils.h"


void testParticle();
void testVertex();
void testTransport();
void testTime(Particle part, Double_t R);
//void testMultipleScattering();
//void testSim();

void testParticle(){

  //  Particle *p = new Particle();
  
  Vertex *v = new Vertex();
  Particle *p = new Particle(v->getPoint(), 1);
  cout << "\n\tParticle p" << endl;
  cout << "\nx: " << p->getPoint().X() << endl;
  cout << "y: " << p->getPoint().Y() << endl;
  cout << "z: " << p->getPoint().Z() << endl;
  
  cout << "\ntheta: " << p->getDirection().theta() << endl;
  cout << "phi: " << p->getDirection().phi() << endl;
  cout << "eta: " << p->getDirection().eta() << endl;
  cout << "c1: " << p->getDirection().c1() << endl;
  cout << "c2: " << p->getDirection().c2() << endl;
  cout << "c3: " << p->getDirection().c3() << endl;
}


void testVertex(){
  Vertex *v = new Vertex();
  cout << "\n\tVertex v" << endl;
  cout << "\nx: " << v->getPoint().X() << endl;
  cout << "y: " << v->getPoint().Y() << endl;
  cout << "z: " << v->getPoint().Z() << endl;

  cout << "\nMult: " << v->getMult() << endl;

}

void testTransport(){

  Particle *p = new Particle();
  Point *hit = new Point(transport(*p, 1));
}  
void testTime(Particle part, Double_t R){
  Double_t x0 = part.getPoint().X();
  Double_t y0 = part.getPoint().Y();
  Double_t _c1 = part.getDirection().c1();
  Double_t _c2 = part.getDirection().c2();
  Double_t delta = (x0*_c1+y0*_c2)*(x0*_c1+y0*_c2) - (_c1*_c1+_c2*_c2)*(x0*x0+y0*y0-R*R);
  Double_t t1 = (-(x0*_c1+y0*_c2) - TMath::Sqrt(delta))/(_c1*_c1+_c2*_c2);
  Double_t t2 = (-(x0*_c1+y0*_c2) + TMath::Sqrt(delta))/(_c1*_c1+_c2*_c2);
  cout << "t1: " << t1 << endl;
  cout << "t2: " << t2 << endl;
}
