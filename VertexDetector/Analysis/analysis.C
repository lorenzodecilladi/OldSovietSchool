/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ~ Macro for the VERTICES ANALYSIS in a barrel detector     ~
  ~ Authors:  Arianna Corrado                                ~
  ~           Lorenzo de Cilladi                             ~
  ~ Course:   TANS - 2017/2018                               ~
  ~                                                          ~
  ~ Last modified: 30/12/2017                                ~
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
#include "Tracklet.h"
#include "TMath.h"
#include "TClonesArray.h"
#include "TH1D.h"
#include "TF1.h"
#include "TStopwatch.h"
#include "TVectorD.h"

#endif


void analysis(TString simfilePath, TString recofilePath, TString outFileName){

  TStopwatch watch;
  watch.Start(kTRUE);

  //open sim file and tree
  TFile   *sim_file  = new TFile(simfilePath);
  if(sim_file -> IsZombie()){
    cout << "File " << simfilePath << " not found!!" << endl;
    return;
  }
  TTree   *simTree   = (TTree*)sim_file -> Get("simTree");
  Vertex  *simVert   = new Vertex();
  TBranch *bSimVert  = simTree -> GetBranch("Vertex");
  bSimVert -> SetAddress(&simVert);
  TH1D    *histSimMult      = (TH1D*)sim_file->Get("histSimMult"); //bin always == 1
  TH1D    *histSimVertices  = (TH1D*)sim_file->Get("histSimVertices"); //[cm]
  
  UInt_t nSimEvents  = simTree -> GetEntries();

  
  //open reco file and tree
  TFile   *reco_file = new TFile(recofilePath);
  if(reco_file -> IsZombie()){
    cout << "File " << recofilePath << " not found!!" << endl;
    return;
  }
  TTree   *recoTree  = (TTree*)reco_file -> Get("recoTree");
  Point   *recoVert  = new Point();
  UInt_t  recoLabel;
  TBranch *bRecoVert = recoTree -> GetBranch("recoVertex");
  TBranch *bRecoLabel= recoTree -> GetBranch("recoLabel");
  bRecoVert -> SetAddress(&recoVert);
  bRecoLabel-> SetAddress(&recoLabel);
  TH1D    *histRecoVertices  = (TH1D*)reco_file->Get("histRecoVertices"); //[cm]
  
  UInt_t nRecoEvents = recoTree -> GetEntries();

  
  //crea file analisi
  TFile *analysis_file    = new TFile(outFileName, "RECREATE");
  TH1D  *histResidualZ    = new TH1D("histResidualZ", "Residual in Z", nSimEvents/30., -0.10005, 0.10005);
  //uso nSimEvents così ho il controllo dell'ampiezza dei bins
  
  Double_t meanZGenerated = histSimVertices -> GetMean(); //si può fare un fit e prendere il valor medio
  Double_t mult           = histSimMult     -> GetMean(); //obviously, to be used only when "fixed" mult

  //vector = (resol, sResol, eff, sEff)
  TVectorD vec(4);
  Double_t resol;    //resolution
  Double_t sResol;   //uncertainty on resolution
  Double_t eff;      //efficiency (TEfficiency ??)
  Double_t sEff;     //uncertainty on efficiency
  
  
  for(UInt_t i=0; i<nRecoEvents; i++){
    if(i%10000==0) cout<<"PROCESSING EVENT "<<i<<endl;
    
    recoTree -> GetEvent(i);
    Double_t zRecoVert = recoVert->Z();
    simTree  -> GetEvent(recoLabel);
    Double_t zSimVert  = simVert ->getPoint().Z();
    Double_t residualZ = zRecoVert - zSimVert;   //compute residual along z coord (to be used for resolution)
    histResidualZ -> Fill(residualZ);
  }
  
  
  //Resolution
  histResidualZ -> Fit("gaus");
  resol  = histResidualZ->GetFunction("gaus")->GetParameter(1);
  sResol = histResidualZ->GetFunction("gaus")->GetParameter(2);
  vec[0] = resol;
  vec[1] = sResol;
 
  cout << "\nResolution = " << vec[0] * 10000 << " um; sigma = " << vec[1] * 10000 << " um"<< endl;

  
  //Efficiency //to be checked again
  eff = (static_cast<Double_t>(nRecoEvents)/static_cast<Double_t>(nSimEvents));
  sEff = TMath::Sqrt(nSimEvents*eff*(1-eff));
  vec[2] = eff;
  vec[3] = sEff;

  cout << "Efficiency = " << vec[2] << " +- " << vec[3] << endl;

  
  vec.Write("vec");
  histSimMult      -> Write();
  histSimVertices  -> Write();
  histRecoVertices -> Write();
  histResidualZ    -> Write();

  cout << "\n---------------------------------------------------" << endl;
  analysis_file -> ls();
  cout << "---------------------------------------------------" << endl;
  
  analysis_file -> Close();
  reco_file     -> Close();
  sim_file      -> Close();

  watch.Stop();
  watch.Print();
}
