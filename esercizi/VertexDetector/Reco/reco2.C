/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ~ Macro for the VERTEX RECONSTRUCTION in a barrel detector ~
  ~ Authors:  Arianna Corrado                                ~
  ~           Lorenzo de Cilladi                             ~
  ~ Course:   TANS - 2017/2018                               ~
  ~                                                          ~
  ~ Last modified: 18/12/2017                                ~
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

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


//--------------------------------------------
//---------- FUNCTION DECLARATION ------------

void   reco2();
void   eventAnalysis(Int_t event, TClonesArray *hits1L, TClonesArray *hits2L, Vertex *vert, TH1D *histRecoVertices, TH1D *histSimVertices, TH1D *histCandidates, TH1D *histSimMult);



//--------------------------------------------
//--------- FUNCTION IMPLEMENTATION ----------


//---------------- RECO2 ---------------------
void reco2(){

  TStopwatch watch;
  watch.Start(kTRUE);
  
  TClonesArray *hitsBP = new TClonesArray("Point", 100);
  TClonesArray *hits1L = new TClonesArray("Point", 100);
  TClonesArray *hits2L = new TClonesArray("Point", 100);
  Vertex       *vert   = new Vertex();

  //open sim tree
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

  //histograms to be filled with analysis results
  //TH1D *histCandidates   = new TH1D("histCandidates"  , "z Reco Candidates"   , 1020       , -25.5, 25.5); //NO match hits; bin size 500 um
  TH1D *histCandidates   = new TH1D("histCandidates"  , "z Reco Candidates"   , 2550       , -25.5, 25.5); //WITH match hits; bin size 200 um
  TH1D *histRecoVertices = new TH1D("histRecoVertices", "z Reco Vertices"     , nEvents/200., -25.5, 25.5);
  TH1D *histSimVertices  = new TH1D("histSimVertices" , "z Sim Vertices"      , nEvents/200., -25.5, 25.5);
  TH1D *histSimMult      = new TH1D("histSimMults"    , "z Sim Multiplicities", 50         ,  0   , 50  );

  for(Int_t event=0; event<nEvents; event++){ //loop over events
    tree -> GetEntry(event);
    eventAnalysis(event, hits1L, hits2L, vert, histRecoVertices, histSimVertices, histCandidates, histSimMult);
  } //end events loop

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

  if(event%1000 == 0) {cout << "Processing EVENT " << event << endl;}
  
  Int_t nHits = hits1L -> GetEntries();
  
  histCandidates -> Reset();
  char name[20];
  char title[50];
  sprintf(name,  "hEvt%d",                                event);
  sprintf(title, "Reco vertices distribution - event %d", event);
  histCandidates->SetNameTitle(name,title); //the run is faster if not used: for 10000 events, 7.67 vs 6.56 seconds
    
  for (Int_t i=0; i<nHits; i++){ //loop over 1st layer's hits

    Point hit1L = *((Point*)hits1L->At(i)); //TObject* ---> Point* ---> Point
    
    for(Int_t j=0; j<nHits; j++){ //loop over 2nd layer's hits
      //e se n1L != n2L ==> mettere un cut!!
      Point hit2L = *((Point*)hits2L->At(j));
      //if(kTRUE){
      if(matchHits(hit1L, hit2L)){
	Tracklet trt = Tracklet(hit1L, hit2L);
	Double_t zCandidate = trt.extractVertex().Z();
	histCandidates -> Fill(zCandidate);
	/*if(event == 99967){
	cout << "hit1L = " << hit1L.Z() << endl;
	cout << "hit2L = " << hit2L.Z() << endl;
	cout << "z candidate = " << zCandidate << endl;
	}*/
      }//end if
    }//end hit 2L loop
  }//end hit 1L loop

  Double_t zVertex = histCandidates->GetBinCenter(histCandidates->GetMaximumBin());
  
  histRecoVertices -> Fill(zVertex);
  histSimVertices  -> Fill(vert->getPoint().Z());
  histSimMult      -> Fill(vert->getMult());

}
