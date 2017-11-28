#include "Riostream.h"
#include "Particle.h"
#include "Vertex.h"
#include "Transport.h"
#include "MultipleScattering.h"
#include "Detector.h"
#include "Rootils.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TClonesArray.h"

using namespace detector;

void sim();
//void deleter();
//void generTree();



void sim(){
  
  TFile sim_file("sim_file.root", "RECREATE");
  
  TTree *simTree = new TTree("simTree", "Sim output tree");
  
  TClonesArray *hitsBP = new TClonesArray("Point", 100);
  //  TClonesArray& hits = *hitsBP;
  TClonesArray *hits1L = new TClonesArray("Point", 100);
  TClonesArray *hits2L = new TClonesArray("Point", 100);
  Vertex *vert = new Vertex();
  
  simTree->Branch("Vertex", &vert);
  simTree->Branch("HitsBP", &hitsBP);
  simTree->Branch("Hits1L", &hits1L);
  simTree->Branch("Hits2L", &hits2L);
  
  //Vertex generation
  //Vertex *vert = new Vertex();

  for(UInt_t event=0; event<5; event++){

    cout << "------------------------------------------------" << endl;

    vert = new Vertex();
    UInt_t mult = vert->getMult();
    cout << "\n\n Event: " << event << "\tmult : " << mult << endl;
    
    for(UInt_t i=0; i<mult; i++){
      
      //i-th particle generation
      Particle *part = new Particle(vert->getPoint(), i);
      //cout << "Generating particle..." << endl;
      //part->print();
      
      
      //tansport to Beam Pipe
      //Point prova = transport(*part, detector::rBP);
      //Point *hitBP = new Point(prova);

      new((*hitsBP)[i]) Point(transport(*part, rBP)); //also good ->   (*hitsBP)[i] = new Point(transport(*part, rBP));
      part->setPoint((* (Point*)hitsBP->At(i) )); //(* .....)    passo da Point* a Point
      /*
      //come accedere all'i-esimo elemento di un TClonesArray

      Point* ptrhit = (Point*)hitsBP->At(i);   //accedo al puntatore Point* dell'elemento i del TClonsArray
      Point* ptrhit = (Point*)(*hitsBP).At(i); //altro modo
      Point hit = *( ptrhit ); //per accedere all'oggetto Point vero e proprio devo ancora dereferenziare vedere come funziona      
      */

      //cout << "Particle at Beam Pipe..." << endl;
            
      //multiple scattering in BP
      Direction *scBP = new Direction(multipleScattering(*part));
      part->setDirection(*scBP);
      //cout << "Particle scattering in Beam Pipe..." << endl;
      
      
      //tansport BP -> 1Layer
      (*hits1L)[i] = new Point(transport(*part, r1L));
      part->setPoint((* (Point*)hits1L->At(i) ));
      //part->setPoint(*hits1L[i]);
      //cout << "Prticle at Layer 1..." << endl;
      
      
      //multiple scattering in 1L
      Direction *sc1L = new Direction(multipleScattering(*part));
      part->setDirection(*sc1L);

      
      //tansport 1L -> 2L
      (*hits2L)[i] = new Point(transport(*part, r2L));
      part->setPoint((* (Point*)hits2L->At(i) ));
      
      cout << "\n---final position in 2nd layer---";
      part->print();
      
      //delete part;
      //delete hitBP;
      //delete scBP;
      //delete hit1L;
      //delete sc1L;
      //delete hit2L;
    }
    
    simTree->Fill();
    hitsBP->Clear();
    hits1L->Clear();
    hits2L->Clear();
  }
  
  vert->Clear();
  sim_file.Write();
  sim_file.Close();
  
}



//void deleter(){
//  delete *vert;
//  delete 
//}


/*
void generTree(){
  TTree *simTree = new TTree("simTree", "Sim output tree");

  TClonesArray *hitsBP = new TClonesArray("Point", 100);
  TClonesArray *hits1L = new TClonesArray("Point", 100);
  TClonesArray *hits2L = new TClonesArray("Point", 100);

  Vertex *vertex = new Vertex();
  
  simTree->Branch("Vertex", &vertex);
  simTree->Branch("HitsBP", &hitsBP);
  simTree->Branch("Hits1L", &hits1L);
  simTree->Branch("Hits2L", &hits2L);
}
*/
