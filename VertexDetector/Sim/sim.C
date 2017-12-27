/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ~ Macro for the simulation of a VERTEX DETECTOR           ~
  ~ Authors:  Arianna Corrado                               ~
  ~           Lorenzo de Cilladi                            ~
  ~ Course:   TANS - 2017/2018                              ~
  ~                                                         ~
  ~ Last modified: 27/12/2017                               ~
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



#if !defined(__CINT__) || defined(__MAKECINT__)

#include "Riostream.h"
#include "Particle.h"
#include "Vertex.h"
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
void sim(UInt_t nEvents = 10000, Bool_t msON = kTRUE, Bool_t aripc = kFALSE); //if msON == kTRUE --> multiple scattering is switched on
void hitMaker(UInt_t i, Vertex* vert, TClonesArray* hitsBP, TClonesArray* hits1L, TClonesArray* hits2L, Bool_t msON);



//--------------------------------------------
//---------- FUNCTION IMPLMENTATION ----------


//------------------ SIM --------------------
void sim(UInt_t nEvents, Bool_t msON, Bool_t aripc){

  TStopwatch watch;
  watch.Start(kTRUE);
  
  TFile *sim_file = new TFile("simFile.root", "RECREATE");

  TTree *simTree = new TTree("simTree", "Sim output tree");

  TClonesArray *ptrhitsBP = new TClonesArray("Point", 100);
  TClonesArray *ptrhits1L = new TClonesArray("Point", 100);
  TClonesArray *ptrhits2L = new TClonesArray("Point", 100);
  TClonesArray& hitsBP = *ptrhitsBP;
  TClonesArray& hits1L = *ptrhits1L;
  TClonesArray& hits2L = *ptrhits2L;
  
  Vertex *ptrvert = new Vertex();
  Vertex& vert = *ptrvert;
  
  simTree->Branch("Vertex", &ptrvert);
  simTree->Branch("HitsBP", &ptrhitsBP);
  simTree->Branch("Hits1L", &ptrhits1L);
  simTree->Branch("Hits2L", &ptrhits2L);
 

  for(UInt_t event=0; event<nEvents; event++){ //loop over events

    if(event%1000 == 0){cout << "Processing EVENT " << event << endl;}
    if(aripc && event>=35000){
      cout << "\nEvent " << event << " of "<< nEvents <<": too much for ari's pc. No more events processed!!\n" << endl;
      break;
    }

    //ptrvert = new Vertex("gaus", 20, 5);
    ptrvert = new Vertex("uniform", 0, 20);
    
    UInt_t mult = ptrvert->getMult();
        
    for(UInt_t i=0; i<mult; i++){ //loop over particles
      hitMaker(i, ptrvert, ptrhitsBP, ptrhits1L, ptrhits2L, msON);
    } // end particles loop

    simTree->Fill();
    ptrhitsBP->Clear();
    ptrhits1L->Clear();
    ptrhits2L->Clear();
    delete ptrvert;
  }//end events loop
  
  sim_file->Write();
  sim_file->Close();

  watch.Stop();
  watch.Print();
}



//---------------- HITMAKER ------------------
void hitMaker(UInt_t i, Vertex* ptrvert, TClonesArray* ptrhitsBP, TClonesArray* ptrhits1L, TClonesArray* ptrhits2L, Bool_t msON){
  
  Particle *part = new Particle(ptrvert->getPoint(), i);
  
  part->transport(rBP);           //tansport to Beam Pipe
  new((*ptrhitsBP)[i]) Point(part->getPoint());
  
  if(msON) part->multipleScattering();     //MS in Beam Pipe
  
  part->transport(r1L);           //tansport BP -> Layer1
  //new((*ptrhits1L)[i]) Point(part->getPoint());
  Int_t i1L = ptrhits1L->GetEntries();
  if(TMath::Abs(part->getPoint().Z())<=detector::length/2.) new((*ptrhits1L)[i1L]) Point(part->getPoint());
  
  if(msON) part->multipleScattering();     //MS in Layer1
  
  part->transport(r2L);           //transport Layer1 -> Layer2
  //new((*ptrhits2L)[i]) Point(part->getPoint());
  Int_t i2L = ptrhits2L->GetEntries();
  if(TMath::Abs(part->getPoint().Z())<=detector::length/2.) new((*ptrhits2L)[i2L]) Point(part->getPoint());

  delete part;

}

















/*
  //come accedere all'i-esimo elemento di un TClonesArray
  
  Point* ptrhit = (Point*)ptrhitsBP->At(i);   //accedo al puntatore Point* dell'elemento i del TClonsArray
  Point* ptrhit = (Point*)(*ptrhitsBP).At(i); //altro modo
  Point hit = *( ptrhit ); //per accedere all'oggetto Point vero e proprio devo ancora dereferenziare vedere come funziona      
*/
