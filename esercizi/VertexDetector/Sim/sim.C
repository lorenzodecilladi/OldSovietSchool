#include "Riostream.h"
#include "Particle.h"
#include "Vertex.h"
#include "Transport.h"
#include "MultipleScattering.h"
#include "Detector.h"
#include "Rootils.h"

using namespace detector;

void sim();
void deleter();


void sim(){

  //Vertex generation
  Vertex *vert = new Vertex();

  UInt_t mult = vert->getMult();

  for(UInt_t i = 0; i<mult; i++){

    //i-th particle generation
    Particle *part = new Particle(vert->getPoint(), i);
    //cout << "Generating particle..." << endl;
    //part->print();

    
    //tansport to Beam Pipe
    //Point prova = transport(*part, detector::rBP);
    //Point *hitBP = new Point(prova);
    Point *hitBP = new Point(transport(*part, rBP));
    part->setPoint(*hitBP);
    //cout << "Particle at Beam Pipe..." << endl;
    
    
    //multiple scattering in BP
    Direction *scBP = new Direction(multipleScattering(*part));
    part->setDirection(*scBP);
    //cout << "Particle scattering in Beam Pipe..." << endl;
    

    //tansport BP -> 1Layer
    Point *hit1L = new Point(transport(*part, r1L));
    part->setPoint(*hit1L);
    //cout << "Prticle at Layer 1..." << endl;
    

    //multiple scattering in 1L
    Direction *sc1L = new Direction(multipleScattering(*part));
    part->setDirection(*sc1L);

    
    //tansport 1L -> 2L
    Point *hit2L = new Point(transport(*part, r2L));
    part->setPoint(*hit2L);    
    part->print();

    delete part;
    delete hitBP;
    delete scBP;
    delete hit1L;
    delete sc1L;
    delete hit2L;
  }

  delete vert;
}



//void deleter(){
//  delete *vert;
//  delete 
//}
