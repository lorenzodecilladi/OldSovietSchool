#include "Riostream.h"
#include "Particle.h"
#include "Vertex.h"
#include "Transport.h"
#include "MultipleScattering.h"
#include "Detector.h"
#include "Rootils.h"



void testParticle();
void testVertex();
//void testTransport();
//void testMultipleScattering();
//void testSim();

void testParticle(){

  Particle *p = new Particle();
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
