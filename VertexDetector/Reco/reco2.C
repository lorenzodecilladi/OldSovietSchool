/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ~ Macro for the VERTEX RECONSTRUCTION in a barrel detector ~
  ~ Authors:  Arianna Corrado                                ~
  ~           Lorenzo de Cilladi                             ~
  ~ Course:   TANS - 2017/2018                               ~
  ~                                                          ~
  ~ Last modified: 18/12/2017                                ~
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//errore binomiALe sull'efficienza perché il numeratore (numero di eventi riostruiti) è un sottogruppo del denominatore (numero di eventi generati)

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
#include "TF1.h"
#include "TStopwatch.h"

#endif


//--------------------------------------------
//---------- FUNCTION DECLARATION ------------

void   reco2();
Bool_t   eventAnalysis(Int_t event, TClonesArray *hits1L, TClonesArray *hits2L, Vertex *vert, TH1D *histRecoVertices, TH1D *histSimVertices, TH1D *histCandidates, TH1D *histSimMult, Double_t &residualZ, Double_t &zVertReco);
Int_t findMaximum(TH1* hist, Int_t minBin, Int_t maxBin);



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


  //open reco file
  TFile *reco_file = new TFile("reco2results.root", "RECREATE");
  
  //histograms to be filled with reco analysis results
  TH1D *histCandidates   = new TH1D("histCandidates"  , "z Reco Candidates"   , 510         , -25.45, 25.55); //WITH match hits; bin size 1 mm
  TH1D *histRecoVertices = new TH1D("histRecoVertices", "z Reco Vertices"     , nEvents/200., -25.5, 25.5);
  TH1D *histSimVertices  = new TH1D("histSimVertices" , "z Sim Vertices"      , nEvents/200., -25.5, 25.5);
  TH1D *histSimMult      = new TH1D("histSimMults"    , "z Sim Multiplicities", 50          ,  0   , 50  );

  //open reco tree
  TTree *recoTree = new TTree("recoTree", "Reco output tree");
  Double_t residualZ;
  Double_t zVertReco;
  recoTree->Branch("residualZ", &residualZ, "residualZ/D" );
  recoTree->Branch("zVertReco", &zVertReco, "zVertReco/D");
  
  for(Int_t event=0; event<nEvents; event++){ //loop over events
    tree -> GetEntry(event);
    if(eventAnalysis(event, hits1L, hits2L, vert, histRecoVertices, histSimVertices, histCandidates, histSimMult, residualZ, zVertReco))
      recoTree -> Fill();
    
  } //end events loop
  
  recoTree->GetEvent(0);
  cout << residualZ << endl;

  //write results on reco file
  //TFile *reco_file = new TFile("reco2results.root", "RECREATE"); 
  histCandidates   -> Write(); //only the last one, as an example
  histRecoVertices -> Write();
  histSimVertices  -> Write();
  histSimMult      -> Write();
  recoTree         -> Write();

  reco_file -> ls();
  reco_file -> Close();
  sim_file.Close();

  watch.Stop();
  watch.Print();
}



//--------EVENT ANALYSIS------------

Bool_t eventAnalysis(Int_t event, TClonesArray *hits1L, TClonesArray *hits2L, Vertex *vert, TH1D *histRecoVertices, TH1D *histSimVertices, TH1D *histCandidates, TH1D *histSimMult, Double_t &residualZ, Double_t &zVertReco){

  if(event%1000 == 0) {cout << "Processing EVENT " << event << endl;}
  
  Int_t nHits1L = hits1L -> GetEntries();
  Int_t nHits2L = hits2L -> GetEntries();

  //cout << nHits << endl;
  
  histCandidates -> Reset();
  char name[20];
  char title[50];
  sprintf(name,  "hEvt%d",                                event);
  sprintf(title, "Reco vertices distribution - event %d", event);
  histCandidates->SetNameTitle(name,title); //the run is faster if not used: for 10000 events, 7.67 vs 6.56 seconds

  std::vector<Double_t>vCand;
  Double_t sumCand = 0;
  Int_t meanSize = 0;
  
  for (Int_t i=0; i<nHits1L; i++){ //loop over 1st layer's hits

    Point hit1L = *((Point*)hits1L->At(i)); //TObject* ---> Point* ---> Point
    if(TMath::Abs(hit1L.Z())>detector::length/2.) continue;
    for(Int_t j=0; j<nHits2L; j++){ //loop over 2nd layer's hits
      //e se n1L != n2L ==> mettere un cut!!
      Point hit2L = *((Point*)hits2L->At(j));
      if(TMath::Abs(hit2L.Z())>detector::length/2.) continue;
      if(kTRUE){
      //if(matchHits(hit1L, hit2L)){
	Tracklet trt = Tracklet(hit1L, hit2L);
	Double_t zCandidate = trt.extractVertex().Z();
	histCandidates -> Fill(zCandidate);
	vCand.push_back(zCandidate);
      }//end if
    }//end hit 2L loop
  }//end hit 1L loop

  
  Double_t zVertSim = vert->getPoint().Z();
  histSimVertices  -> Fill(zVertSim);
  histSimMult      -> Fill(vert->getMult());


  
  Int_t nbins = histCandidates->GetNbinsX();

  Int_t binMax = findMaximum(histCandidates, 1, nbins -1);
  Double_t yCandMax = histCandidates->GetBinContent(binMax);
  Double_t xCandMax = histCandidates->GetBinCenter(binMax);
  Double_t thr = yCandMax/2.;
  if(yCandMax<thr) return kFALSE; // --> no maximum

  /*  if(event == 1499){
    cout << "nbins " << nbins << endl;
    cout << "binMax " << binMax << endl;
    cout << "xCandMax " << xCandMax << endl;
    cout << "yCandMax " << yCandMax << endl;
    cout << "thr " << thr << endl;
    cout << histCandidates->GetBinContent(histCandidates->GetXaxis()->FindBin(0.8)) << endl;
    }*/
  
  Int_t binMaxL = findMaximum(histCandidates, 1, binMax-4);
  Double_t yCandMaxL = histCandidates->GetBinContent(binMaxL);
  Double_t xCandMaxL = histCandidates->GetBinCenter(binMaxL);
  if(yCandMaxL>=thr){
    //histCandidates->GetXaxis()->SetRange(1,nbins);
    if(event<400) histCandidates->DrawCopy();
    return kFALSE;}
  
  Int_t binMaxR = findMaximum(histCandidates, binMax+4, nbins -1);
  Double_t yCandMaxR = histCandidates->GetBinContent(binMaxR);
  Double_t xCandMaxR = histCandidates->GetBinCenter(binMaxR);
  if(yCandMaxR>=thr) return kFALSE;
  

  for(UInt_t i=0; i<vCand.size(); i++){
    if(vCand.at(i)>=xCandMax-0.1 && vCand.at(i)<=xCandMax+0.1){
      sumCand += vCand.at(i);
      meanSize++;
    }
  }

  Double_t zVertex = sumCand/meanSize;
  histRecoVertices -> Fill(zVertex);

  zVertReco = zVertex;
  residualZ = zVertReco - zVertSim;
  
  return kTRUE;
}



Int_t findMaximum(TH1* hist, Int_t minBin, Int_t maxBin){
  Int_t nbins = maxBin - minBin +1;
  Int_t binMax = minBin; //evitiamo accumulo 
  for(Int_t i=minBin; i<maxBin; i++){
    if(hist->GetBinContent(i+1) > hist->GetBinContent(binMax))
      binMax = i+1;
  }
  return binMax;
}
