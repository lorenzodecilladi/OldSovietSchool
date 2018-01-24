/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ~ Macro for the VERTICES ANALYSIS in a barrel detector     ~
  ~ Authors:  Arianna Corrado                                ~
  ~           Lorenzo de Cilladi                             ~
  ~ Course:   TANS - 2017/2018                               ~
  ~                                                          ~
  ~ Last modified: 22/01/2018                                ~
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#if !defined(__CINT__) || defined(__MAKECINT__)

#include <Riostream.h>
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "Point.h"
#include "Vertex.h"
#include "TMath.h"
#include "TH1D.h"
#include "TF1.h"
#include "TStopwatch.h"
#include "TVectorD.h"
#include "TCanvas.h"

#endif

//function definition
void analysis(TString simfilePath = "../Sim/simFile.root", TString recofilePath = "../Reco/recoFile.root", TString outFileName = "analysisFile.root");


//function implementation
void analysis(TString simfilePath, TString recofilePath, TString outFileName){

  TStopwatch watch;
  watch.Start(kTRUE);

  //open sim file and tree
  TFile   *sim_file         = new TFile(simfilePath);
  if(sim_file -> IsZombie()){
    cout << "File " << simfilePath << " not found!!" << endl;
    return;
  }
  TTree   *simTree          = (TTree*)sim_file -> Get("simTree");
  Vertex  *simVert          = new Vertex();
  TBranch *bSimVert         = simTree -> GetBranch("Vertex");
  bSimVert -> SetAddress(&simVert);
  TH1D    *histSimMult      = (TH1D*)sim_file  -> Get("histSimMult");       //bin size always == 1
  TH1D    *histSimVertices  = (TH1D*)sim_file  -> Get("histSimVertices");   //[cm]

  UInt_t   nSimEvents       = simTree -> GetEntries();                      //number of simulated events

  TCanvas *c1 = new TCanvas("c1", "c1");
  histSimVertices->Fit("gaus");
  Double_t meanZSimVert     = histSimVertices->GetFunction("gaus")->GetParameter(1);
  Double_t sigmaZSimVert    = histSimVertices->GetFunction("gaus")->GetParameter(2);

  UInt_t   nSimEvents1sig   = 0;

  for(UInt_t i=0; i<nSimEvents; i++){
    if(i%50000==0) cout<<"PROCESSING EVENT "<<i<<endl;
    simTree -> GetEvent(i);
    Double_t zSimVert = simVert->getPoint().Z();
    if(zSimVert >= meanZSimVert-sigmaZSimVert && zSimVert <= meanZSimVert+sigmaZSimVert) nSimEvents1sig++;
  }
  
  //open reco file and tree
  TFile   *reco_file        = new TFile(recofilePath);
  if(reco_file -> IsZombie()){
    cout << "File " << recofilePath << " not found!!" << endl;
    return;
  }
  TTree   *recoTree         = (TTree*)reco_file -> Get("recoTree");
  Point   *recoVert         = new Point();
  UInt_t  recoLabel;
  TBranch *bRecoVert        = recoTree -> GetBranch("recoVertex");
  TBranch *bRecoLabel       = recoTree -> GetBranch("recoLabel");
  bRecoVert  -> SetAddress(&recoVert);
  bRecoLabel -> SetAddress(&recoLabel);
  TH1D    *histRecoVertices = (TH1D*)reco_file  -> Get("histRecoVertices"); //[cm]
  
  UInt_t nRecoEvents        = recoTree -> GetEntries();                     //number of reconstructed events

  
  //creates analysis file
  TFile *analysis_file      = new TFile(outFileName, "RECREATE");
  TH1D  *histResidualZ      = new TH1D ("histResidualZ", "Residual in Z", nSimEvents/100., -0.10005, 0.10005);
  histResidualZ -> GetXaxis() -> SetTitle("residual = zRecoVertex - zSimVertex [cm]");
  histResidualZ -> GetYaxis() -> SetTitle("counts");

  cout << "\nCreating " << outFileName << " ..." << endl;
  
  Double_t meanZGenerated   = histSimVertices -> GetMean();
  Double_t mult             = histSimMult     -> GetMean();

  Double_t meanResZ; //mean residual in Z
  TVectorD vec(6);   //vector = (resol, sResol, eff, sEff, eff1sig, sEff1sig)
  Double_t resol;    //resolution (sigma residual in Z)
  Double_t sResol;
  Double_t eff;      //efficiency
  Double_t sEff;     //uncertainty on eff
  Double_t eff1sig;  //efficiency for particles generated within 1 sigma
  Double_t sEff1sig;
  

  UInt_t nRecoEvents1sig    = 0;
  
  for(UInt_t i=0; i<nRecoEvents; i++){
    if(i%50000==0) cout<<"PROCESSING EVENT "<<i<<endl;
    
    recoTree -> GetEvent(i);
    Double_t zRecoVert = recoVert->Z();
    simTree  -> GetEvent(recoLabel); //aim of recoLabel: get only simulated events whose vertex was actually reconstructed
    Double_t zSimVert  = simVert->getPoint().Z();
    Double_t residualZ = zRecoVert - zSimVert;  //compute residual along z coord (to be used for resolution)
    histResidualZ -> Fill(residualZ);
    if(zSimVert >= meanZSimVert-sigmaZSimVert && zSimVert <= meanZSimVert+sigmaZSimVert) nRecoEvents1sig++;
  }
  
  
  //Resolution
  histResidualZ->Fit("gaus");
  meanResZ = histResidualZ->GetFunction("gaus")->GetParameter(1);
  resol    = histResidualZ->GetFunction("gaus")->GetParameter(2);
  sResol   = histResidualZ->GetFunction("gaus")->GetParError(2);
  vec[0]   = resol;
  vec[1]   = sResol; 
  cout << "\nResolution (residual sigma) = " << vec[0] * 10000 << " +- " << vec[1] * 10000 << " um"<< endl;

  //Efficiency
  eff      = (static_cast<Double_t>(nRecoEvents)/static_cast<Double_t>(nSimEvents));
  sEff     = (1/static_cast<Double_t>(nSimEvents))*TMath::Sqrt(static_cast<Double_t>(nRecoEvents)*(1-static_cast<Double_t>(nRecoEvents)/static_cast<Double_t>(nSimEvents)));  //binomial error because numerator (nRecoEvents)
  vec[2]   = eff;                                                                 //is a subset of denominatr (nSimEvents)
  vec[3]   = sEff;
  cout << "Efficiency = " << vec[2] << " +- " << vec[3] << endl;

  //Efficiency for particles generated within 1 sigma
  eff1sig  = (static_cast<Double_t>(nRecoEvents1sig)/static_cast<Double_t>(nSimEvents1sig));
  sEff1sig = (1/static_cast<Double_t>(nSimEvents1sig))*TMath::Sqrt(static_cast<Double_t>(nRecoEvents1sig)*(1-static_cast<Double_t>(nRecoEvents1sig)/static_cast<Double_t>(nSimEvents1sig)));
  vec[4]   = eff1sig;
  vec[5]   = sEff1sig;
  cout << "Efficiency (within 1 sigma) = " << vec[4] << " +- " << vec[5] << endl;
  
  cout << "\n---------------------------------------------------" << endl;
  
  vec.Write("vec");
  histSimMult      -> Write();
  histSimVertices  -> Write();
  histRecoVertices -> Write();
  histResidualZ    -> Write();
  
  c1               -> Close();
  cout << "\n...output written in " << outFileName << "\n" << endl;
  analysis_file    -> Close();
  reco_file        -> Close();
  sim_file         -> Close();

  watch.Stop();
  watch.Print();

}









