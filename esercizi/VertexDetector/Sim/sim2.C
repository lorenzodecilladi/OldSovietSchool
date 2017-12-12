/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ~ Macro per l'esecuzione della simulazione d'esame        ~
  ~ Autori:  ~
  ~          ~
  ~ Ultima modifica: 15/11/2017                             ~
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



#if !defined(__CINT__) || defined(__MAKECINT__)

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
#include "TStopwatch.h"

#endif

using namespace detector;

void sim2(UInt_t nEvents = 10000, bool aripc = kFALSE);
//void deleter();
//void generTree();
void hitMaker(UInt_t i, Vertex* vert, TClonesArray* hitsBP, TClonesArray* hits1L, TClonesArray* hits2L );


//------------------------------SIM2--------------------------------

void sim2(UInt_t nEvents, bool aripc){

  TStopwatch watch;
  watch.Start(kTRUE);
  
  TFile sim_file("sim2results.root", "RECREATE");
  
  TTree *simTree = new TTree("simTree", "Sim output tree");
  
  TClonesArray *hitsBP = new TClonesArray("Point", 100);
  TClonesArray *hits1L = new TClonesArray("Point", 100);
  TClonesArray *hits2L = new TClonesArray("Point", 100);
  Vertex *vert = new Vertex();
  
  simTree->Branch("Vertex", &vert);
  simTree->Branch("HitsBP", &hitsBP);
  simTree->Branch("Hits1L", &hits1L);
  simTree->Branch("Hits2L", &hits2L);
  

  for(UInt_t event=0; event<nEvents; event++){
    
    vert = new Vertex("gaus", 20, 5);
    UInt_t mult = vert->getMult();

    //    cout << "\n---------------------------------------------" << endl;
    //    cout << " EVENT: " << event << "\tMULT: " << mult << endl;

    if(aripc && event>=35000){
      cout << "\nEvent " << event << " of "<< nEvents <<": too much for ari's pc. No more events processed!!\n" << endl;
      break;
    }
    
    if(event%1000 == 0){cout << "Processing EVENT " << event << endl;}
    
    for(UInt_t i=0; i<mult; i++){hitMaker(i, vert, hitsBP, hits1L, hits2L);}
    
    simTree->Fill();
    hitsBP->Clear();
    hits1L->Clear();
    hits2L->Clear();
  }//end events loop
  
  vert->Clear();
  sim_file.Write();
  sim_file.Close();

  watch.Stop();
  watch.Print();
}




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


void hitMaker(UInt_t i, Vertex* vert, TClonesArray* hitsBP, TClonesArray* hits1L, TClonesArray* hits2L ){
    
  //cout << "Generating particle" << i <<..." << endl;
  Particle part(vert->getPoint(), i);
  
  //tansport to Beam Pipe
  (*hitsBP)[i] = new Point(transport(part, rBP));   //also good -> new((*hitsBP)[i]) Point(transport(*part, rBP));
  part.setPoint((* (Point*)hitsBP->At(i) ));        //(* .....)    passo da Point* a Point
  
  
  //cout << "Particle at Beam Pipe..." << endl;
  //cout << "Particle scattering in Beam Pipe..." << endl;
  Direction scBP(multipleScattering(part));
  part.setDirection(scBP);
  
  
  //tansport BP -> 1Layer
  //cout << "Particle at Layer 1..." << endl;
  (*hits1L)[i] = new Point(transport(part, r1L));
  part.setPoint((* (Point*)hits1L->At(i) ));
  
  
  //multiple scattering in 1L
  Direction sc1L(multipleScattering(part));
  part.setDirection(sc1L);
  
  //tansport 1L -> 2L
  (*hits2L)[i] = new Point(transport(part, r2L));
  part.setPoint((* (Point*)hits2L->At(i) ));
  
}



/*
  //come accedere all'i-esimo elemento di un TClonesArray
  
  Point* ptrhit = (Point*)hitsBP->At(i);   //accedo al puntatore Point* dell'elemento i del TClonsArray
  Point* ptrhit = (Point*)(*hitsBP).At(i); //altro modo
  Point hit = *( ptrhit ); //per accedere all'oggetto Point vero e proprio devo ancora dereferenziare vedere come funziona      
*/
