/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ~ Macro for the simulation of a VERTEX DETECTOR           ~
  ~ Authors:  Arianna Corrado                               ~
  ~           Lorenzo de Cilladi                            ~
  ~ Course:   TANS - 2017/2018                              ~
  ~                                                         ~
  ~ Last modified: 22/01/2018                               ~
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


#if !defined(__CINT__) || defined(__MAKECINT__)

#include "Riostream.h"
#include "Particle.h"
#include "Vertex.h"
#include "Detector.h"
#include "Rootils.h"
#include "Math.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TClonesArray.h"
#include "TStopwatch.h"
#include "TString.h"
#include "TH1D.h"
#include "TH1F.h"

#endif



//------------------------------------------
//---------- FUNCTION DECLARATION ----------

void sim(TString outFileName = "simFile.root");
void hitMaker(UInt_t i, Vertex* vert, TClonesArray* ptrhitsBP, TClonesArray* ptrhits1L, TClonesArray* ptrhits2L, Bool_t msON, Bool_t inputEta, TH1F* histInputEta);
void noiseMaker(TClonesArray* ptrhits1L, TClonesArray* ptrhits2L, TString noiseOpt, Double_t par1, Double_t par2);
void printInfo(UInt_t nEvents, TString multOpt, Double_t par1, Double_t par2, Bool_t msON, Bool_t noiseON, Double_t zGenVertex, Bool_t inputEta, TString noiseOpt, Double_t noisePar1, Double_t noisePar2);
TH1F* getHistInputMult();
TH1F* getHistInputEta();



//--------------------------------------------
//---------- FUNCTION IMPLMENTATION ----------

//------------------ SIM ---------------------
void sim(TString outFileName){

  TStopwatch watch;
  watch.Start(kTRUE);

  //get sim parameters from config file 
  TString  comment      = "null";
  UInt_t   nEvents      = 10000;
  TString  multOpt      = "null";
  Double_t par1         = 0.;
  Double_t par2         = 0.;
  Bool_t   msON         = kTRUE;
  Bool_t   noiseON      = kTRUE;
  Double_t zGenVertex   = 0.;
  Bool_t   inputEta     = kFALSE;
  
  ifstream in("config.txt");
  if(!in){cout<<"[!]\n[!] Config file NOT FOUND!\n[!]"<<endl;
    return;}  
  in>>comment>>nEvents>>multOpt>>par1>>par2>>msON>>noiseON>>zGenVertex>>inputEta;
  in.close();

  //get noise parameters from noise config file
  TString  noiseComment = "null";
  TString  noiseOpt     = "null";
  Double_t noisePar1    =     0.;
  Double_t noisePar2    =     0.;

  ifstream inNoise("noiseConfig.txt");
  if(!inNoise){cout<<"[!]\n[!] Noise config file NOT FOUND!\n[!]"<<endl;
    return;}
  inNoise>>noiseComment>>noiseOpt>>noisePar1>>noisePar2;  
  inNoise.close();

  //print configuration info
  printInfo(nEvents, multOpt, par1, par2, msON, noiseON, zGenVertex, inputEta, noiseOpt, noisePar1, noisePar2);

 
  //multiplicity from input histogram distribution
  TH1F *histInputMult = new TH1F();
  if(multOpt == "hist") histInputMult = getHistInputMult();
  histInputMult -> SetDirectory(0);
  
  //pseudorapidity from input histogram distribution
  TH1F *histInputEta  = new TH1F();
  if(inputEta) histInputEta = getHistInputEta();
  histInputEta -> SetDirectory(0);

  
  //open file and tree to store simulated data  
  TFile *sim_file = new TFile(outFileName, "RECREATE");

  TTree *simTree  = new TTree("simTree", "Sim output tree");
  TClonesArray *ptrhitsBP = new TClonesArray("Point", 100);
  TClonesArray *ptrhits1L = new TClonesArray("Point", 100);
  TClonesArray *ptrhits2L = new TClonesArray("Point", 100);
  Vertex       *ptrvert   = new Vertex();
  TClonesArray& hitsBP = *ptrhitsBP;
  TClonesArray& hits1L = *ptrhits1L;
  TClonesArray& hits2L = *ptrhits2L;
  Vertex&       vert   = *ptrvert;  

  simTree->Branch("Vertex", &ptrvert  );
  simTree->Branch("HitsBP", &ptrhitsBP);
  simTree->Branch("Hits1L", &ptrhits1L);
  simTree->Branch("Hits2L", &ptrhits2L);

  TH1D *histSimMult      = new TH1D("histSimMult"    , "z Sim Multiplicities", 51          , -0.5 , 50.5); //bin size: 1
  histSimMult -> GetXaxis() -> SetTitle("multiplicity");
  histSimMult -> GetYaxis() -> SetTitle("counts");
  
  TH1D *histSimVertices  = new TH1D("histSimVertices", "z Sim Vertices"      , nEvents/100., -25.5, 25.5); //[cm]
  histSimVertices -> GetXaxis() -> SetTitle("z coord of sim verteices [cm]");
  histSimVertices -> GetYaxis() -> SetTitle("counts");


  for(UInt_t event=0; event<nEvents; event++){ //loop over events

    if(event%10000 == 0){cout << "Processing EVENT " << event << endl;}

    if     (multOpt == "gaus")    ptrvert = new Vertex("gaus"   , par1, par2, zGenVertex);
    else if(multOpt == "uniform") ptrvert = new Vertex("uniform", par1, par2, zGenVertex);
    else if(multOpt == "fixed")   ptrvert = new Vertex("fixed"  , par1      , zGenVertex);
    else if(multOpt == "hist")    ptrvert = new Vertex("hist", histInputMult, zGenVertex);
    else cout << "Invalid multiplicity option" << endl;

    UInt_t mult      = ptrvert -> getMult();
    histSimMult     -> Fill(mult);
    histSimVertices -> Fill(ptrvert -> getPoint().Z());

    //used for later evaluation of efficiency for particles generated within 1 sigma (alonz z)
    //UInt_t nSimEvents1sig = 0;
    //if(TMath::Abs(ptrvert->GetPoint().Z()) <= vres::sZv) //sZv is the sigma of the gaussian distribution for Vertex's z coord extraction
    //  {nSimEvents1sig++}
    //TVectorD vec(1);
    //vec[0] = nSimEvents1sig;    //resolution
    
    for(UInt_t i=0; i<mult; i++){ //loop over particles
      hitMaker(i, ptrvert, ptrhitsBP, ptrhits1L, ptrhits2L, msON, inputEta, histInputEta);
    }                             // end particles loop
    
    if(noiseON) noiseMaker(ptrhits1L, ptrhits2L, noiseOpt, noisePar1, noisePar2);    
    
    simTree   -> Fill();
    ptrhitsBP -> Clear();
    ptrhits1L -> Clear();
    ptrhits2L -> Clear();
    delete ptrvert;
  }//end events loop

  sim_file -> Write();
  sim_file -> Close();

  watch.Stop();
  watch.Print();  
}







//------------------ PRINT CONFIGURATION INFO ---------------------
void printInfo(UInt_t nEvents, TString multOpt, Double_t par1, Double_t par2, Bool_t msON, Bool_t noiseON, Double_t zGenVertex, Bool_t inputEta, TString noiseOpt, Double_t noisePar1, Double_t noisePar2){

  cout   << "\n--- RUNNING VertexDetector SIM ---\n"  << endl;
  cout   << "\n---- Configuration parameters ----"  << endl;
  cout   << "Number of events = " << nEvents      << endl;
  cout   << "Multiplicity     = " << multOpt      << endl;
  if(multOpt == "gaus"){
    cout << "Mean             = " << par1         << endl;
    cout << "Sigma            = " << par2         << endl;
  }
  else if(multOpt == "uniform"){
    cout << "Min              = " << par1         << endl;
    cout << "Max              = " << par2         << endl;
  }
  else if(multOpt == "fixed"){
    cout << "Mult value       = " << par1         << endl;
  }
  cout   << "Mult Scattering  = " << msON         << endl;
  cout   << "Noise            = " << noiseON      << endl;
  cout   << "zGenVertex       = " << zGenVertex   << endl;

  if(inputEta)
    cout << "Pseudorapdity from input distribution." << endl;
  else cout << "Uniform pseudorapidity extraction in [-2.,2.]" << endl;
  
  if(noiseON){
    cout   << "\n----- Noise parameters -----------"  << endl;
    cout   << "Distribution of noise hits' number = "  << noiseOpt << endl;
    if(noiseOpt == "gaus"){
      cout << "Mean             = " << noisePar1    << endl;
      cout << "Sigma            = " << noisePar2    << endl;
    }
    else if(noiseOpt == "fixed"){ //noisePar2 must be 0.
      cout << "Number of hits   = " << noisePar1    << endl;
    }
  }
  else cout << "Noise OFF" << endl;

  cout << endl;
}



//----------- GET INPUT distribution for MULTIPLICITY -------------
//----------- from histogram hmul stored in kinem.root ------------
TH1F* getHistInputMult(){
  TFile *hist_file = new TFile("kinem.root");
  TH1F  *hMult     = (TH1F*)hist_file->Get("hmul");
  hMult     -> SetDirectory(0);
  hist_file -> Close();
  return hMult;
}


//-----------GET HIST INPUT ETA --------------
//----------- GET INPUT distribution for PSEUDORAPIDITY eta -------
//----------- from histogram heta stored in kinem.root ------------
//----------- and selects the range [-2.; 2.] for eta  ------------
TH1F* getHistInputEta(){
  TFile *hist_file = new TFile("kinem.root");
  TH1F  *hEta1     = (TH1F*)hist_file->Get("heta");
  hEta1     -> SetDirectory(0);
  hist_file -> Close();
  
  TAxis   *xaxis = hEta1 -> GetXaxis();
  Double_t step  = xaxis -> GetBinWidth(1);
  Int_t    b1    = xaxis -> FindBin(-2.);
  Int_t    b2    = xaxis -> FindBin(2.);
  Double_t xLow  = xaxis -> GetBinLowEdge(b1);
  Double_t xHigh = xaxis -> GetBinUpEdge(b2);
  Int_t    nBins = b2-b1+1;
  Double_t step2 = (xHigh-xLow)/nBins;
  TH1F    *hEta2 = new TH1F("hEta2","#eta distribution 2",nBins,xLow,xHigh);
  Int_t j = 1;
  for(Int_t i=b1; i<=b2; i++) hEta2 -> SetBinContent(j++, hEta1->GetBinContent(i));
  //  hEta1 -> Draw();
  hEta2 -> SetLineColor(2);
  //  hEta2 -> Draw("same");
  return hEta2;
}





//---------------- HITMAKER ------------------
void hitMaker(UInt_t i, Vertex* ptrvert, TClonesArray* ptrhitsBP, TClonesArray* ptrhits1L, TClonesArray* ptrhits2L, Bool_t msON, Bool_t inputEta, TH1F* histInputEta){

  Particle *part = new Particle();
  if(inputEta){ *part = Particle(ptrvert->getPoint(), histInputEta, i);}  //pseudorapidity from input distribution
  else{         *part = Particle(ptrvert->getPoint(), i);              }  //uniform pseudorapidity in [-2.; 2.]
  
  part -> transport(detector::rBP);          //transport to Beam Pipe
  new((*ptrhitsBP)[i]) Point( part->getPoint() );
  
  if(msON) part -> multipleScattering();     //MS in Beam Pipe

  part -> transport(detector::r1L);          //tansport BP -> Layer1
  Int_t i1L = ptrhits1L -> GetEntries();

  Point hit1L = part->getPoint();
  hit1L.smearing(detector::r1L);             //smearing on Layer1
  if(TMath::Abs(hit1L.Z())<=detector::length/2.) new((*ptrhits1L)[i1L]) Point(hit1L);  //geometry check and storage

  if(msON) part -> multipleScattering();     //MS in Layer1

  part -> transport(detector::r2L);          //transport Layer1 -> Layer2
  Int_t i2L = ptrhits2L -> GetEntries();

  Point hit2L = part->getPoint();  
  hit2L.smearing(detector::r2L);             //smearing on Layer 2
  if(TMath::Abs(hit2L.Z())<=detector::length/2.) new((*ptrhits2L)[i2L]) Point(hit2L);  //geometry check and storage

  delete part;
}



//---------------- NOISEMAKER ------------------
void noiseMaker(TClonesArray* ptrhits1L, TClonesArray* ptrhits2L, TString noiseOpt, Double_t par1, Double_t par2){
  
  Int_t size1L = ptrhits1L->GetEntries();
  Int_t size2L = ptrhits2L->GetEntries();
  Int_t temp;
  
  //noise hits on Layer1 (cylindric uniform extraction)
  if(noiseOpt=="fixed") temp = static_cast<Int_t>(par1);
  else if(noiseOpt=="gaus"){
    do{temp = static_cast<Int_t>(rootils::rndmGaus(par1, par2));}
    while(temp<0 || temp>100);
  }
  else{
    cout << "[!] Invalid noise option!" << endl;
    return;
  }
  
  UInt_t nNoiseHits1L = temp+size1L<=100 ? temp : 100-size1L;
  for(UInt_t i=0; i<nNoiseHits1L; i++){
    Double_t z   = rootils::rndmUniform(-detector::length/2., detector::length/2.);
    Double_t phi = rootils::rndmUniform(0, 2*math::pi);
    new((*ptrhits1L)[size1L+i]) Point(detector::r1L*TMath::Cos(phi), detector::r1L*TMath::Sin(phi), z);
  }
  
  //noise hits on Layer2 (cylindric uniform extraction)
  if(noiseOpt=="fixed") temp = static_cast<Int_t>(par1);
  else if(noiseOpt=="gaus"){
    do{temp = static_cast<Int_t>(rootils::rndmGaus(par1, par2));}
    while(temp<0 || temp>100);
  }
  else{cout << "[!] Invalid noise option!" << endl;}
  UInt_t nNoiseHits2L = temp+size2L<=100 ? temp : 100-size2L;
  
  for(UInt_t i=0; i<nNoiseHits2L; i++){
    Double_t z   = rootils::rndmUniform(-detector::length/2., detector::length/2.);
    Double_t phi = rootils::rndmUniform(0, 2*math::pi);
    new((*ptrhits2L)[size2L+i]) Point(detector::r2L*TMath::Cos(phi), detector::r2L*TMath::Sin(phi), z);
  }
}


























/*
  //come accedere all'i-esimo elemento di un TClonesArray

  Point* ptrhit = (Point*)ptrhitsBP->At(i);   //accedo al puntatore Point* dell'elemento i del TClonsArray
  Point* ptrhit = (Point*)(*ptrhitsBP).At(i); //altro modo
  Point hit = *( ptrhit ); //per accedere all'oggetto Point vero e proprio devo ancora dereferenziare vedere come funziona
*/
