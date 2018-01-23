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

//utils function (they will be deleted in the final version)
void exec();
void exec1();
void exec2();
void exec3();



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
  analysis_file    -> Close();
  reco_file        -> Close();
  sim_file         -> Close();

  watch.Stop();
  watch.Print();

}


























void exec(){
  analysis("../Sim/simFiles/sim0080.root", "../Reco/recoFilesMatch/reco0080.root", "analysis0080.root");
  analysis("../Sim/simFiles/sim0081.root", "../Reco/recoFilesMatch/reco0081.root", "analysis0081.root");
  analysis("../Sim/simFiles/sim0082.root", "../Reco/recoFilesMatch/reco0082.root", "analysis0082.root");
  analysis("../Sim/simFiles/sim0083.root", "../Reco/recoFilesMatch/reco0083.root", "analysis0083.root");
  analysis("../Sim/simFiles/sim0084.root", "../Reco/recoFilesMatch/reco0084.root", "analysis0084.root");
}

void exec1(){
  analysis("../Sim/simFiles/sim0085.root", "../Reco/recoFilesMatch/reco0085.root", "analysis0085.root");
  analysis("../Sim/simFiles/sim0086.root", "../Reco/recoFilesMatch/reco0086.root", "analysis0086.root");
  analysis("../Sim/simFiles/sim0087.root", "../Reco/recoFilesMatch/reco0087.root", "analysis0087.root");
  analysis("../Sim/simFiles/sim0088.root", "../Reco/recoFilesMatch/reco0088.root", "analysis0088.root");
  analysis("../Sim/simFiles/sim0089.root", "../Reco/recoFilesMatch/reco0089.root", "analysis0089.root");
}

void exec2(){
  analysis("../Sim/simFiles/sim0090.root", "../Reco/recoFilesMatch/reco0090.root", "analysis0090.root");
  analysis("../Sim/simFiles/sim0091.root", "../Reco/recoFilesMatch/reco0091.root", "analysis0091.root");
  analysis("../Sim/simFiles/sim0092.root", "../Reco/recoFilesMatch/reco0092.root", "analysis0092.root");
  analysis("../Sim/simFiles/sim0093.root", "../Reco/recoFilesMatch/reco0093.root", "analysis0093.root");
  analysis("../Sim/simFiles/sim0094.root", "../Reco/recoFilesMatch/reco0094.root", "analysis0094.root");
}


void exec3(){
  analysis("../Sim/simFiles/sim0070.root", "../Reco/recoFilesMatch/reco0070.root", "analysis0070.root");
  analysis("../Sim/simFiles/sim0071.root", "../Reco/recoFilesMatch/reco0071.root", "analysis0071.root");
  analysis("../Sim/simFiles/sim0072.root", "../Reco/recoFilesMatch/reco0072.root", "analysis0072.root");
  analysis("../Sim/simFiles/sim0073.root", "../Reco/recoFilesMatch/reco0073.root", "analysis0073.root");
  analysis("../Sim/simFiles/sim0074.root", "../Reco/recoFilesMatch/reco0074.root", "analysis0074.root");
  analysis("../Sim/simFiles/sim0075.root", "../Reco/recoFilesMatch/reco0075.root", "analysis0075.root");
  analysis("../Sim/simFiles/sim0076.root", "../Reco/recoFilesMatch/reco0076.root", "analysis0076.root");
  analysis("../Sim/simFiles/sim0077.root", "../Reco/recoFilesMatch/reco0077.root", "analysis0077.root");
  analysis("../Sim/simFiles/sim0078.root", "../Reco/recoFilesMatch/reco0078.root", "analysis0078.root");
  analysis("../Sim/simFiles/sim0079.root", "../Reco/recoFilesMatch/reco0079.root", "analysis0079.root");
}
