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

void reco();
//void readTree();
//legge il tree
//copia i branches in TClonesArray, che prende in argomento
/*
void readTree(TClonesArray *_hits1L, TClonesArray *_hits2L){
  
  //  TClonesArray *hitsBP = new TClonesArray("Point", 100);
  TClonesArray *hits1L = new TClonesArray("Point", 100);
  TClonesArray *hits2L = new TClonesArray("Point", 100);
  // Vertex *vert = new Vertex();

  //Open input sim file and tree
  TFile sim_file("../Sim/sim_file.root");
  TTree *tree = (TTree*)sim_file.Get("simTree");
  //TFile reco_file("reco_file.root", "RECREATE");
  //TBranch *bVert = tree->GetBranch("Vertex");
  //TBranch *bBP = tree->GetBranch("HitsBP");
  TBranch *b1L = tree->GetBranch("Hits1L");
  TBranch *b2L = tree->GetBranch("Hits2L");

  //Branch address definition
  //bVert->SetAddress(&vert);
  //bBP->SetAddress(&hitsBP);
  b1L->SetAddress(&hits1L);
  b2L->SetAddress(&hits2L);

  Int_t nEvents = tree->GetEntries();

  for(Int_t i=0; i<nEvents; i++){
    _hits1L[i] = 
  }
  !!!problema: e per tutti gli eventi?????
}
*/
//void eventAnalysis(Int_t event, TTree* tree, TH1D* histRecoVertices, TH1D* histSimVertices);



void reco(){
  
  TClonesArray *hitsBP = new TClonesArray("Point", 100);
  TClonesArray *hits1L = new TClonesArray("Point", 100);
  TClonesArray *hits2L = new TClonesArray("Point", 100);
  Vertex *vert = new Vertex();

  //Open input sim file and tree
  TFile sim_file("../Sim/sim_file.root");
  TTree *tree = (TTree*)sim_file.Get("simTree");
  //TFile reco_file("reco_file.root", "RECREATE");
  TBranch *bVert = tree->GetBranch("Vertex");
  TBranch *bBP = tree->GetBranch("HitsBP");
  TBranch *b1L = tree->GetBranch("Hits1L");
  TBranch *b2L = tree->GetBranch("Hits2L");

  //Branch address definition
  bVert->SetAddress(&vert);
  bBP->SetAddress(&hitsBP);
  b1L->SetAddress(&hits1L);
  b2L->SetAddress(&hits2L);

  Int_t nEvents = tree->GetEntries();
  //TClonesArray *histArray = new TClonesArray("TH1D", nEvents);
  char name[20];
  char title[50];
  
  TFile reco_file("reco_file.root", "RECREATE");
  //TH1D* histCandidates = new TH1D("histCandidates", "histCandidates", 1000, -13.5, 13.5);
  TH1D *histCandidates;
  TH1D *histRecoVertices = new TH1D("histRecoVertices", "z Reconstructed Vertices", nEvents/50., -13.5, 13.5);
  TH1D *histSimVertices = new TH1D("histSimVertices", "z Sim Vertices", nEvents/50., -13.5, 13.5);

  
  for(Int_t event=0; event<nEvents; event++){       //for over events
    //eventAnalysis(event, tree, histRecoVertices, histSimVertices);

    tree->GetEntry(event);
    cout << "Event: " << event << "; Multiplicity: " << vert->getMult() << endl;

    Int_t nHits = hits1L->GetEntries();
    cout << "Number of hits on a single layer: " << nHits << endl;

    sprintf(name,"hEvt%d",event);
    sprintf(title,"Reco vertices distribution - event %d",event);
    //TH1D* histCandidates = new TH1D(name, title, 1000, -13.5, 13.5);
    //histCandidates->SetNameTitle(name,title);
    histCandidates = new TH1D(name, title, nEvents/10., -13.5, 13.5);

    //Point *tst=(Point*)hits1L->At(0);
    //cout<<"Punto "<<0<<" sul 1L: x, y, z = "<<tst->X()<<"; "<<tst->Y()<<"; "<<tst->Z()<<endl;

    for (Int_t i=0; i<nHits; i++){ //loop over 1st layer's hits
      Point hit1L=*((Point*)hits1L->At(i)); //TObject* ---> Point* ---> Point
      //Point hit1L = ((Point*)hits1L)[i]; RIP++
      
      for(Int_t j=0; j<nHits; j++){ //loop over 2nd layer's hits
	Point hit2L=*((Point*)hits2L->At(j));

	//if(kTRUE){
	if(matchHits(hit1L, hit2L)){
	  Tracklet trt = Tracklet(hit1L, hit2L);
	  Double_t zCandidate = trt.extractVertex().Z();
	  histCandidates->Fill(zCandidate);
	}//end if
      }//end hit j loop
    }//end hit i loop
    Double_t zVertex = histCandidates->GetBinCenter(histCandidates->GetMaximumBin());
    histRecoVertices->Fill(zVertex);
    histSimVertices->Fill(vert->getPoint().Z());

  }//end event loop

  histCandidates->Write(); //only the last one, as an example
  histRecoVertices->Write();
  histSimVertices->Write();
  sim_file.Close();
  reco_file.Close();
}




/*
void eventAnalysis(Int_t event, TTree* tree, TH1D* histRecoVertices, TH1D* histSimVertices){

  tree->GetEntry(event);
    cout << "Event: " << event << "; Multiplicity: " << vert->getMult() << endl;

    Int_t nHits = hits1L->GetEntries();
    cout << "Number of hits on a single layer: " << nHits << endl;

    sprintf(name,"hEvt%d",event);
    sprintf(title,"Reco vertices distribution - event %d",event);
    //TH1D* histCandidates = new TH1D(name, title, 1000, -13.5, 13.5);
    //histCandidates->SetNameTitle(name,title);
    histCandidates = new TH1D(name, title, nEvents/10., -13.5, 13.5);

    //Point *tst=(Point*)hits1L->At(0);
    //cout<<"Punto "<<0<<" sul 1L: x, y, z = "<<tst->X()<<"; "<<tst->Y()<<"; "<<tst->Z()<<endl;

    for (Int_t i=0; i<nHits; i++){ //loop over 1st layer's hits
      Point hit1L=*((Point*)hits1L->At(i)); //TObject* ---> Point* ---> Point
      //Point hit1L = ((Point*)hits1L)[i]; RIP++
      
      for(Int_t j=0; j<nHits; j++){ //loop over 2nd layer's hits
	Point hit2L=*((Point*)hits2L->At(j));

	//if(kTRUE){
	if(matchHits(hit1L, hit2L)){
	  Tracklet trt = Tracklet(hit1L, hit2L);
	  Double_t zCandidate = trt.extractVertex().Z();
	  histCandidates->Fill(zCandidate);
	}//end if
      }//end hit j loop
    }//end hit i loop
    Double_t zVertex = histCandidates->GetBinCenter(histCandidates->GetMaximumBin());
    histRecoVertices->Fill(zVertex);
    histSimVertices->Fill(vert->getPoint().Z());
}


*/


  //tree->Fill();
  
  /*
   for(Int_t event=0; event<tree->GetEntries(); event++){
    tree->GetEvent(event); //POWER!!!!
    cout<<"Evento "<<event<<"; Molteplicita= "<<vert->getMult()<<endl;
    cout<<"X,Y,Z = "<<vert->getPoint().X()<<"; "<<vert->getPoint().Y()<<"; "<<vert->getPoint().Z()<<endl;
    Int_t num=hitsBP->GetEntries();
    cout<<"Numero di elementi nel TClonesArray della BP "<<num<<endl;
    for (Int_t j=0; j<num; j++){
      Point *tst=(Point*)hitsBP->At(j);
      cout<<"Punto "<<j<<" sulla BP: x, y, z = "<<tst->X()<<"; "<<tst->Y()<<"; "<<tst->Z()<<endl;
    }

  }
  */
