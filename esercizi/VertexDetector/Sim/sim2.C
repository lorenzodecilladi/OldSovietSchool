/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ~ Macro for the simulation of a VERTEX DETECTOR           ~
  ~ Authors:  Arianna Corrado                               ~
  ~           Lorenzo de Cilladi                            ~
  ~ Course:   TANS - 2017/2018                              ~
  ~                                                         ~
  ~ Last modified: 18/12/2017                               ~
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


//------------------------------------------
//---------- FUNCTION DECLARATION ----------
void sim2(UInt_t nEvents = 10000, bool aripc = kFALSE);
//void hitMaker(UInt_t i, Vertex* vert, TClonesArray* hitsBP, TClonesArray* hits1L, TClonesArray* hits2L );
void hitMaker(UInt_t i, Vertex& vert, TClonesArray* hitsBP, TClonesArray* hits1L, TClonesArray* hits2L );



//--------------------------------------------
//---------- FUNCTION IMPLMENTATION ----------


//------------------ SIM2 --------------------
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
  

  for(UInt_t event=0; event<nEvents; event++){ //loop over events

    if(event%1000 == 0){cout << "Processing EVENT " << event << endl;}
    if(aripc && event>=35000){
      cout << "\nEvent " << event << " of "<< nEvents <<": too much for ari's pc. No more events processed!!\n" << endl;
      break;
    }

    
    //vert = new Vertex("gaus", 20, 5);
    //UInt_t mult = vert->getMult();
    
    Vertex vert("gaus", 20, 5); //
    UInt_t mult = vert.getMult();
    
    for(UInt_t i=0; i<mult; i++){ //loop over particles
      //hitMaker(i, vert, hitsBP, hits1L, hits2L);
      hitMaker(i, vert, hitsBP, hits1L, hits2L); // PASSA VERTICE COME REFERENZA!!
    } // end particles loop
    
    simTree->Fill();
    hitsBP->Clear();
    hits1L->Clear();
    hits2L->Clear();
    //delete vert;
  }//end events loop
  
  //vert->Clear();
  sim_file.Write();
  sim_file.Close();

  watch.Stop();
  watch.Print();
}



//---------------- HITMAKER ------------------
//void hitMaker(UInt_t i, Vertex* vert, TClonesArray* hitsBP, TClonesArray* hits1L, TClonesArray* hits2L ){
void hitMaker(UInt_t i, Vertex &vert, TClonesArray* hitsBP, TClonesArray* hits1L, TClonesArray* hits2L ){
    
  //  Particle part(vert->getPoint(), i);
  Particle part(vert.getPoint(), i);
  
  //tansport to Beam Pipe
  new((*hitsBP)[i]) Point(transport(part, rBP));  // memory leak-> (*hitsBP)[i] = new Point(transport(part, rBP));
  part.setPoint((* (Point*)hitsBP->At(i) ));

  //multiple scattering in BP
  Direction scBP(multipleScattering(part));
  part.setDirection(scBP);
  
  //tansport BP -> 1Layer
  new((*hits1L)[i]) Point(transport(part, r1L));//  (*hits1L)[i] = new Point(transport(part, r1L));
  part.setPoint((* (Point*)hits1L->At(i) ));
  
  //multiple scattering in 1L
  Direction sc1L(multipleScattering(part));
  part.setDirection(sc1L);
  
  //tansport 1L -> 2L
  new((*hits2L)[i]) Point(transport(part, r2L));//  (*hits2L)[i] = new Point(transport(part, r2L));
  part.setPoint((* (Point*)hits2L->At(i) ));
}

















/*
  //come accedere all'i-esimo elemento di un TClonesArray
  
  Point* ptrhit = (Point*)hitsBP->At(i);   //accedo al puntatore Point* dell'elemento i del TClonsArray
  Point* ptrhit = (Point*)(*hitsBP).At(i); //altro modo
  Point hit = *( ptrhit ); //per accedere all'oggetto Point vero e proprio devo ancora dereferenziare vedere come funziona      
*/
