#if !defined(__CINT__) || defined(__MAKECINT__)

#include <Riostream.h>
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "Detector.h"
#include "Point.h"
#include "Vertex.h"
#include "Smearing.h"
#include "Tracklet.h"
#include "TMath.h"
#include "TClonesArray.h"
#include "TH1D.h"
#include "TStopwatch.h"

#endif

void   reco2();
TTree* readTree(TClonesArray *hitsBP, TClonesArray *hits1L, TClonesArray *hits2L, Vertex *vert);
void   eventAnalysis(Int_t event, TClonesArray *hits1L, TClonesArray *hits2L, Vertex *vert, TH1D *histRecoVertices, TH1D *histSimVertices, TH1D *histCandidates, TH1D *histSimMult);


//--------------RECO2--------------

void reco2(){

  TStopwatch watch;
  watch.Start(kTRUE);
  
  TClonesArray *hitsBP = new TClonesArray("Point", 100);
  TClonesArray *hits1L = new TClonesArray("Point", 100);
  TClonesArray *hits2L = new TClonesArray("Point", 100);
  Vertex       *vert   = new Vertex();
    
  //open and read tree
  TFile sim_file("../Sim/sim2results.root");
  TTree   *tree  = (TTree*)sim_file.Get("simTree");
  TBranch *bVert = tree -> GetBranch("Vertex");
  TBranch *bBP   = tree -> GetBranch("HitsBP");
  TBranch *b1L   = tree -> GetBranch("Hits1L");
  TBranch *b2L   = tree -> GetBranch("Hits2L");
  bVert -> SetAddress(&vert);
  bBP   -> SetAddress(&hitsBP);
  b1L   -> SetAddress(&hits1L);
  b2L   -> SetAddress(&hits2L);

  Int_t nEvents = tree -> GetEntries();
  //cout << "\nnEvents in the tree = " << nEvents << endl;

  //histograms to be filled with analysis results
  TH1D *histCandidates   = new TH1D("histCandidates"  , "z Reco Candidates"   , 10000      , -13.5, 13.5);
  TH1D *histRecoVertices = new TH1D("histRecoVertices", "z Reco Vertices"     , nEvents/50., -13.5, 13.5);
  TH1D *histSimVertices  = new TH1D("histSimVertices" , "z Sim Vertices"      , nEvents/50., -13.5, 13.5);
  TH1D *histSimMult      = new TH1D("histSimMults"    , "z Sim Multiplicities", 50         ,  0   , 50  );
  
  for(Int_t event=0; event<nEvents; event++){//loop over events

    tree -> GetEntry(event);
    eventAnalysis(event, hits1L, hits2L, vert, histRecoVertices, histSimVertices, histCandidates, histSimMult);
    
  }//end event loop
  
  //write results on a file
  TFile *reco_file = new TFile("reco2results.root", "RECREATE"); 
  histCandidates   -> Write(); //only the last one, as an example
  histRecoVertices -> Write();
  histSimVertices  -> Write();
  histSimMult      -> Write();
  reco_file -> ls();
  reco_file -> Close();
  sim_file.Close();

  watch.Stop();
  watch.Print();

}

//--------EVENT ANALYSIS------------

void eventAnalysis(Int_t event, TClonesArray *hits1L, TClonesArray *hits2L, Vertex *vert, TH1D *histRecoVertices, TH1D *histSimVertices, TH1D *histCandidates, TH1D *histSimMult){
  
  //cout << "Event: " << event << "; Multiplicity: " << vert->getMult() << endl; //the run is faster if not used: for 10000 events, 6.56 vs 4.43 seconds
  //cout << "Event: " << event << "; zVert: " << vert->getPoint().Z() << endl;
  
  Int_t nHits = hits1L -> GetEntries();
  //cout << "Number of hits on a single layer: " << nHits << endl;
  
  histCandidates -> Reset();
  char name[20];
  char title[50];
  sprintf(name,  "hEvt%d",                                event);
  sprintf(title, "Reco vertices distribution - event %d", event);
  //TH1D* histCandidates = new TH1D(name, title, 1000, -13.5, 13.5);
  //histCandidates = new TH1D(name, title, 100, -13.5, 13.5);
  //  histCandidates->SetNameTitle(name,title); //the run is faster if not used: for 10000 events, 7.67 vs 6.56 seconds
    
  for (Int_t i=0; i<nHits; i++){ //loop over 1st layer's hits

    Point hit1L = *((Point*)hits1L->At(i)); //TObject* ---> Point* ---> Point
    
    for(Int_t j=0; j<nHits; j++){ //loop over 2nd layer's hits
      //e se n1L != n2L ==> mettere un cut!!
      Point hit2L = *((Point*)hits2L->At(j));
      if(kTRUE){//if(matchHits(hit1L, hit2L)){	//if(kTRUE){
	Tracklet trt = Tracklet(hit1L, hit2L);
	Double_t zCandidate = trt.extractVertex().Z();
	histCandidates -> Fill(zCandidate);
      }//end if
    }//end hit j loop
  }//end hit i loop

  Double_t zVertex = histCandidates->GetBinCenter(histCandidates->GetMaximumBin());
  histRecoVertices -> Fill(zVertex);
  histSimVertices  -> Fill(vert->getPoint().Z());
  histSimMult      -> Fill(vert->getMult());

}




//----------------------------------------------------------------------------------------------



//!!!! NOT WORKING
//gets simulation tree elements, puts then in arrays, returns the # of entries (events)
TTree* readTree(TClonesArray *hitsBP, TClonesArray *hits1L, TClonesArray *hits2L, Vertex *vert){

  //Open input sim file and tree
  TFile *sim_file = new TFile("../Sim/sim2results.root");
  TTree *tree = (TTree*)sim_file->Get("simTree");
  TBranch *bVert = tree->GetBranch("Vertex");
  TBranch *bBP = tree->GetBranch("HitsBP");
  TBranch *b1L = tree->GetBranch("Hits1L");
  TBranch *b2L = tree->GetBranch("Hits2L");
  bVert->SetAddress(&vert);
  bBP->SetAddress(&hitsBP);
  b1L->SetAddress(&hits1L);
  b2L->SetAddress(&hits2L);
  //tree -> GetEvent(0);
  //Int_t nHits = hits1L->GetEntries();
  //cout << "Number of hits on a single layer: " << nHits << endl;
  //  sim_file->Close();
  return tree;
}
