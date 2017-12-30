/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ~ Macro for the VERTEX RECONSTRUCTION in a barrel detector ~
  ~ Authors:  Arianna Corrado                                ~
  ~           Lorenzo de Cilladi                             ~
  ~ Course:   TANS - 2017/2018                               ~
  ~                                                          ~
  ~ Last modified: 27/12/2017                                ~
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
//#include "Smearing.h"
#include "Tracklet.h"
#include "TMath.h"
#include "TClonesArray.h"
#include "TH1D.h"
#include "TF1.h"
#include "TStopwatch.h"

#endif


//--------------------------------------------
//---------- FUNCTION DECLARATION ------------

void reco(TString simfilePath);
//Bool_t eventAnalysis(Int_t event, TClonesArray *hits1L, TClonesArray *hits2L, Vertex *vert, TH1D *histRecoVertices, TH1D *histSimVertices, TH1D *histCandidates, TH1D *histSimMult, Double_t &residualZ, Double_t &zVertReco);
Bool_t eventAnalysis(Int_t event, TClonesArray *hits1L, TClonesArray *hits2L, Vertex *vert, TH1D *histRecoVertices, TH1D *histSimVertices, TH1D *histCandidates, TH1D *histSimMult, Double_t &residualZ, Point &recoVertex);
Int_t findMaximum(TH1* hist, Int_t minBin, Int_t maxBin);



//--------------------------------------------
//--------- FUNCTION IMPLEMENTATION ----------


//---------------- RECO ---------------------
void reco(TString simfilePath){

  TStopwatch watch;
  watch.Start(kTRUE);
  
  TClonesArray *hitsBP = new TClonesArray("Point", 100);     //hits on the Beam Pipe
  TClonesArray *hits1L = new TClonesArray("Point", 100);     //hits on the Layer 1
  TClonesArray *hits2L = new TClonesArray("Point", 100);     //hits on the Layer 2
  Vertex       *vert   = new Vertex();                       //vertex (object)

  //open tree from simulation output file
  TFile sim_file(simfilePath);
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
  TFile *reco_file = new TFile("recoFile.root", "RECREATE");
  
  //histograms to be filled with reco results
  TH1D *histCandidates   = new TH1D("histCandidates"  , "z Reco Candidates"   , 510         , -25.45, 25.55); //WITH match hits; bin size 1 mm
  TH1D *histRecoVertices = new TH1D("histRecoVertices", "z Reco Vertices"     , nEvents/200., -25.5, 25.5);
  TH1D *histSimVertices  = new TH1D("histSimVertices" , "z Sim Vertices"      , nEvents/200., -25.5, 25.5);
  TH1D *histSimMult      = new TH1D("histSimMults"    , "z Sim Multiplicities", 50          ,  0   , 50  );

  //init reco tree
  TTree *recoTree = new TTree("recoTree", "Reco output tree");
  Double_t residualZ;
  //Double_t zVertReco;
  Point recoVertex;
  recoTree->Branch("residualZ", &residualZ, "residualZ/D" );
  //  recoTree->Branch("zVertReco", &zVertReco, "zVertReco/D");
  recoTree->Branch("recoVertex", &recoVertex);
  
  //vertex reconstruction
  for(Int_t event=0; event<nEvents; event++){ //loop over events
    if(event%10000 == 0) {cout << "Processing EVENT " << event << endl;}
    tree -> GetEntry(event);
    //if vertex reco is successful, fill reco tree
    //    if(eventAnalysis(event, hits1L, hits2L, vert, histRecoVertices, histSimVertices, histCandidates, histSimMult, residualZ, zVertReco))
    if(eventAnalysis(event, hits1L, hits2L, vert, histRecoVertices, histSimVertices, histCandidates, histSimMult, residualZ, recoVertex))
      recoTree -> Fill();  
  } //end events loop

  
  //write results on reco file
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

//Bool_t eventAnalysis(Int_t event, TClonesArray *hits1L, TClonesArray *hits2L, Vertex *vert, TH1D *histRecoVertices, TH1D *histSimVertices, TH1D *histCandidates, TH1D *histSimMult, Double_t &residualZ, Double_t &zVertReco){
Bool_t eventAnalysis(Int_t event, TClonesArray *hits1L, TClonesArray *hits2L, Vertex *vert, TH1D *histRecoVertices, TH1D *histSimVertices, TH1D *histCandidates, TH1D *histSimMult, Double_t &residualZ, Point &recoVertex){
  
  Int_t nHits1L = hits1L -> GetEntries();
  Int_t nHits2L = hits2L -> GetEntries();
  Double_t zVertReco;
  
  histCandidates -> Reset();
  char name[20];
  char title[50];
  sprintf(name , "hEvt%d"                               , event);
  sprintf(title, "Reco vertices distribution - event %d", event);
  histCandidates->SetNameTitle(name,title);     //the run is faster if not used: for 10000 events, 7.67 vs 6.56 seconds

  std::vector<Double_t>vCand;       //vector to store z coord of vertex candidates
  Double_t sumCand = 0;
  Int_t   meanSize = 0;
  
  for (Int_t i=0; i<nHits1L; i++){              //loop over 1st layer's hits
    Point hit1L = *((Point*)hits1L->At(i));     //get hit on Layer 1  //TObject* ---> Point* ---> Point
    if(TMath::Abs(hit1L.Z()) > detector::length/2.) continue;    //geometry check: skip hits not on the detector

    for(Int_t j=0; j<nHits2L; j++){             //loop over 2nd layer's hits
      Point hit2L = *((Point*)hits2L->At(j));   //get hit on Layer 2
      if(TMath::Abs(hit2L.Z()) > detector::length/2.) continue;  //geometry check: skip hits not on the detector

                                                      //e se n1L != n2L ==> mettere un cut!!?????? non serve più...
      
      Tracklet trt = Tracklet(hit1L, hit2L);  //generate tracklet
      //if(trt.matchHits()){
      if(kTRUE){
	Double_t zCandidate = trt.extractVertex().Z();//extrapolate vertex (z coord)
	histCandidates -> Fill(zCandidate);     //fill vertex candidate hist
	vCand.push_back(zCandidate);
      }
      
    }//end hit 2L loop
  }//end hit 1L loop


  
  Double_t zVertSim = vert->getPoint().Z();
  histSimVertices  -> Fill(zVertSim);           //fill sim vertex hist (from sim, for comparison)
  histSimMult      -> Fill(vert->getMult());    //fill multiplicity hist (from sim)


  Int_t nbins = histCandidates->GetNbinsX();

  //look for peak in vertex candidates histogram
  Int_t binMax = findMaximum(histCandidates, 1, nbins -1);  //find highest bin in zCandidate hist
                                                            //DOBBIAMO PASSARE 2 ANZICHè 1?????
  Double_t yCandMax = histCandidates->GetBinContent(binMax); 
  Double_t xCandMax = histCandidates->GetBinCenter(binMax);
  Double_t thr = yCandMax/2.;
  //if(yCandMax<4.) return kFALSE; // --> no maximum ????????????????????????????????? NESSUN MASSIMO == TANTI MASSIMI!!!!!

  /*  if(event == 1499){
    cout << "nbins " << nbins << endl;
    cout << "binMax " << binMax << endl;
    cout << "xCandMax " << xCandMax << endl;
    cout << "yCandMax " << yCandMax << endl;
    cout << "thr " << thr << endl;
    cout << histCandidates->GetBinContent(histCandidates->GetXaxis()->FindBin(0.8)) << endl;
    }*/

  
  //look for multiple peaks to be excluded (vertex reco non-successful)
  Int_t binMaxL = findMaximum(histCandidates, 1, binMax-4); //DOBBIAMO PASSARE 2 ANZICHè 1????
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

  //compute z coord of the reconstructed vertex
  for(UInt_t i=0; i<vCand.size(); i++){
    if(vCand.at(i)>=xCandMax-0.1 && vCand.at(i)<=xCandMax+0.1){
      sumCand += vCand.at(i);
      meanSize++;
    }
  }
  
  Double_t zVertex = sumCand/meanSize;
  histRecoVertices -> Fill(zVertex);  //fill reco vertices histogram

  zVertReco = zVertex;
  residualZ = zVertReco - zVertSim;   //compute residual along z coord (to be used for resolution)
  recoVertex = Point(0., 0., zVertReco);
  Double_t szV = (1. + 2*detector::r1L/(detector::r2L-detector::r1L))*detector::smZhit; //smearing
  recoVertex.setsZ(szV);
  return kTRUE;
}


//-------- FIND HIGHEST BIN IN HISTOGRAM in a GIVEN RANGE --------- (TH1::GetMaximumBin() does not always work!!!)
Int_t findMaximum(TH1* hist, Int_t minBin, Int_t maxBin){
  Int_t nbins = maxBin - minBin +1;
  Int_t binMax = minBin; //evitiamo accumulo sul primo o ultimo bin delle entries fuori range: non passiamo 1?? dobbiamo mettere +1???
  for(Int_t i=minBin; i<maxBin; i++){
    if(hist->GetBinContent(i+1) > hist->GetBinContent(binMax))
      binMax = i+1;
  }
  return binMax;
}











//access a specific event in the tree: recoTree->GetEvent(0);
