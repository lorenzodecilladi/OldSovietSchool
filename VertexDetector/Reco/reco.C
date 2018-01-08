/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ~ Macro for the VERTEX RECONSTRUCTION in a barrel detector ~
  ~ Authors:  Arianna Corrado                                ~
  ~           Lorenzo de Cilladi                             ~
  ~ Course:   TANS - 2017/2018                               ~
  ~                                                          ~
  ~ Last modified: 30/12/2017                                ~
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


#if !defined(__CINT__) || defined(__MAKECINT__)

#include <Riostream.h>
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "Detector.h"
#include "Point.h"
#include "Vertex.h"
#include "Tracklet.h"
#include "TMath.h"
#include "TClonesArray.h"
#include "TH1D.h"
#include "TF1.h"
#include "TStopwatch.h"

#endif


//--------------------------------------------
//---------- FUNCTION DECLARATION ------------

void exec();
void reco(TString simfilePath = "../Sim/simFile.root", TString outFileName = "recoFile.root");
Bool_t eventAnalysis(Int_t event, TClonesArray *hits1L, TClonesArray *hits2L, Vertex *vert, TH1D *histRecoVertices, TH1D *histCandidates, Point &recoVertex);
Bool_t findPeak(TH1D* histCandidates, Double_t &xCandMad);
Int_t findMaximum(TH1* hist, Int_t minBin, Int_t maxBin);



//--------------------------------------------
//--------- FUNCTION IMPLEMENTATION ----------

void exec(){
  reco("../Sim/simFiles/sim0033.root", "reco0033m.root");
  reco("../Sim/simFiles/sim0034.root", "reco0034m.root");
  reco("../Sim/simFiles/sim0035.root", "reco0035m.root");
  reco("../Sim/simFiles/sim0036.root", "reco0036m.root");
  reco("../Sim/simFiles/sim0037.root", "reco0037m.root");
  reco("../Sim/simFiles/sim0038.root", "reco0038m.root");
  reco("../Sim/simFiles/sim0039.root", "reco0039m.root");
  reco("../Sim/simFiles/sim0040.root", "reco0040m.root");
  reco("../Sim/simFiles/sim0041.root", "reco0041m.root");
}

void exec1(){
  reco("../Sim/simFiles/sim0042.root", "reco0042m.root");
  reco("../Sim/simFiles/sim0043.root", "reco0043m.root");
  reco("../Sim/simFiles/sim0044.root", "reco0044m.root");
  reco("../Sim/simFiles/sim0045.root", "reco0045m.root");
  reco("../Sim/simFiles/sim0046.root", "reco0046m.root");
  reco("../Sim/simFiles/sim0047.root", "reco0047m.root");
  reco("../Sim/simFiles/sim0048.root", "reco0048m.root");
  reco("../Sim/simFiles/sim0049.root", "reco0049m.root");
  reco("../Sim/simFiles/sim0050.root", "reco0050m.root");
}

void exec2(){
  reco("../Sim/simFiles/sim0054.root", "reco0054m.root");
  reco("../Sim/simFiles/sim0055.root", "reco0055m.root");
  reco("../Sim/simFiles/sim0056.root", "reco0056m.root");
  reco("../Sim/simFiles/sim0057.root", "reco0057m.root");
  reco("../Sim/simFiles/sim0058.root", "reco0058m.root");
  reco("../Sim/simFiles/sim0059.root", "reco0059m.root");
  reco("../Sim/simFiles/sim0060.root", "reco0060m.root");
}



//---------------- RECO ---------------------
void reco(TString simfilePath, TString outFileName){

  TStopwatch watch;
  watch.Start(kTRUE);
  
  TClonesArray *hitsBP = new TClonesArray("Point", 100);     //hits on the Beam Pipe
  TClonesArray *hits1L = new TClonesArray("Point", 100);     //hits on the Layer 1
  TClonesArray *hits2L = new TClonesArray("Point", 100);     //hits on the Layer 2
  Vertex       *vert   = new Vertex();                       //vertex (object)

  //open tree from simulation output file
  TFile sim_file(simfilePath);
  if(sim_file.IsZombie()){
    cout << "File " << simfilePath << " not found!!" << endl;
    return;
  }
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


  //open file to store reconstruction output
  TFile *reco_file = new TFile(outFileName, "RECREATE");
  
  //histograms to be filled with reco results
  TH1D *histCandidates   = new TH1D("histCandidates"  , "z Reco Candidates"   , 510         , -25.45, 25.55); //WITH match hits; bin size 1 mm
  TH1D *histRecoVertices = new TH1D("histRecoVertices", "z Reco Vertices"     , nEvents/100., -25.5, 25.5);

  
  //init reco tree
  TTree *recoTree = new TTree("recoTree", "Reco output tree");
  Point recoVertex;
  UInt_t recoLabel;
  recoTree->Branch("recoVertex", &recoVertex);
  recoTree->Branch("recoLabel", &recoLabel, "recoLabel/I");
  
  //vertex reconstruction
  for(Int_t event=0; event<nEvents; event++){ //loop over events
    if(event%10000 == 0) {cout << "Processing EVENT " << event << endl;}
    tree -> GetEntry(event);
    //if vertex reco is successful, fill reco tree
    if(eventAnalysis(event, hits1L, hits2L, vert, histRecoVertices, histCandidates, recoVertex)){
      recoLabel = event;
      recoTree -> Fill();
    }
  } //end events loop

  
  //write results on reco file
  histCandidates   -> Write(); //only the last one, as an example
  histRecoVertices -> Write();
  recoTree         -> Write();

  reco_file -> ls();
  reco_file -> Close();
  sim_file.Close();

  watch.Stop();
  watch.Print();
}





//--------EVENT ANALYSIS------------
Bool_t eventAnalysis(Int_t event, TClonesArray *hits1L, TClonesArray *hits2L, Vertex *vert, TH1D *histRecoVertices, TH1D *histCandidates, Point &recoVertex){
  
  Int_t nHits1L = hits1L -> GetEntries();
  Int_t nHits2L = hits2L -> GetEntries();

  //funzione??
  histCandidates -> Reset();
  char name[20];
  char title[50];
  sprintf(name , "hEvt%d"                               , event);
  sprintf(title, "Reco vertices distribution - event %d", event);
  histCandidates->SetNameTitle(name,title);     //the run is faster if not used: for 10000 events, 7.67 vs 6.56 seconds

  std::vector<Double_t>vCand;       //vector to store z coord of vertex candidates

 
  for (Int_t i=0; i<nHits1L; i++){                               //loop over Layer1's hits
    Point hit1L = *((Point*)hits1L->At(i));                      //get hit on Layer 1  //TObject* ---> Point* ---> Point
    if(TMath::Abs(hit1L.Z()) > detector::length/2.) continue;    //geometry check: skip hits not on the detector

    for(Int_t j=0; j<nHits2L; j++){                              //same on Layer2
      Point hit2L = *((Point*)hits2L->At(j));                   
      if(TMath::Abs(hit2L.Z()) > detector::length/2.) continue; 

      Tracklet trt = Tracklet(hit1L, hit2L);                     //generate tracklet
      if(trt.matchHits()){
      //if(kTRUE){
	Double_t zCandidate = trt.extractVertex().Z();           //extrapolate vertex (z coord)
	histCandidates -> Fill(zCandidate);                      //fill vertex candidate hist
	vCand.push_back(zCandidate);
      }
    }//end hit 2L loop
  }//end hit 1L loop


  Double_t xCandMax;
  if(!findPeak(histCandidates, xCandMax)) return kFALSE;

  //compute z coord of the reconstructed vertex
  Double_t sumCand = 0;
  Int_t   meanSize = 0;
  for(UInt_t i=0; i<vCand.size(); i++){
    if(vCand.at(i)>=xCandMax-0.1 && vCand.at(i)<=xCandMax+0.1){
      sumCand += vCand.at(i);
      meanSize++;
    }
  }

  
  Double_t zRecoVert = sumCand/meanSize;
  histRecoVertices -> Fill(zRecoVert);  //fill reco vertices histogram

  recoVertex = Point(0., 0., zRecoVert);
  Double_t szV = 0.01; //deviazione standard?? //(1. + 2*detector::r1L/(detector::r2L-detector::r1L))*detector::smZhit; //smearing
  recoVertex.setsZ(szV);

  return kTRUE;
}







//find peak of hist candidates...if it exists and is unique!!
Bool_t findPeak(TH1D* histCandidates, Double_t &xCandMax){
  
  Int_t nbins = histCandidates->GetNbinsX();
  
  //look for peak in vertex candidates histogram
  Int_t binMax = findMaximum(histCandidates, 1, nbins -1);  //find highest bin in zCandidate hist
  
  xCandMax = histCandidates->GetBinCenter(binMax);
  Double_t yCandMax = histCandidates->GetBinContent(binMax); 
  Double_t thr = yCandMax/2.;
  
  //look for multiple peaks to be excluded (vertex reco non-successful)
  Int_t binMaxL = findMaximum(histCandidates, 1, binMax-4); 
  Double_t yCandMaxL = histCandidates->GetBinContent(binMaxL);
  Double_t xCandMaxL = histCandidates->GetBinCenter(binMaxL);
  if(yCandMaxL>=thr){
  //  if(event<400) histCandidates->DrawCopy();
    return kFALSE;}

  Int_t binMaxR = findMaximum(histCandidates, binMax+4, nbins -1);
  Double_t yCandMaxR = histCandidates->GetBinContent(binMaxR);
  Double_t xCandMaxR = histCandidates->GetBinCenter(binMaxR);
  if(yCandMaxR>=thr) return kFALSE;

  return kTRUE;
}






//-------- FIND HIGHEST BIN IN HISTOGRAM in a GIVEN RANGE --------- (TH1::GetMaximumBin() does not always work!!!)
Int_t findMaximum(TH1* hist, Int_t minBin, Int_t maxBin){
  Int_t binMax = minBin+1; //evitiamo accumulo sul primo o ultimo bin delle entries fuori range
  for(Int_t i=minBin; i<maxBin; i++){
    if(hist->GetBinContent(i+1) > hist->GetBinContent(binMax))
      binMax = i+1;
  }
  return binMax;
}











//access a specific event in the tree: recoTree->GetEvent(0);
