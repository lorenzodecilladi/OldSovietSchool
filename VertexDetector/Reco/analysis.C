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

#endif


void analysis(TString simfilePath, TString recofilePath){

  TStopwatch watch;
  watch.Start(kTRUE);

  //open sim file and tree
  TFile   *sim_file  = new TFile(simfilePath);
  TTree   *simTree   = (TTree*)sim_file -> Get("simTree");
  Vertex  *simVert   = new Vertex();
  TBranch *bSimVert  = simTree -> GetBranch("Vertex");
  bSimVert -> SetAddress(&simVert);
  TH1D    *histSimMult      = (TH1D*)sim_file->Get("histSimMult"); //bin always == 1
  TH1D    *histSimVertices  = (TH1D*)sim_file->Get("histSimVertices"); //[cm]
  
  UInt_t nSimEvents  = simTree -> GetEntries();

  
  //open reco file and tree
  TFile   *reco_file = new TFile(recofilePath);
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
  TFile *analysis_file    = new TFile("analysisFile.root", "RECREATE");
  TH1D  *histResidualZ    = new TH1D("histResidualZ", "Residual in Z", nSimEvents/30., -0.10005, 0.10005);
  //uso nSimEvents così ho il controllo dell'ampiezza dei bins
  
  Double_t meanZGenerated = histSimVertices -> GetMean(); //si può fare un fit e prendere il valor medio
  Double_t mult           = histSimMult     -> GetMean(); //obviously, to be used only when "fixed" mult

  TNamed  resol( "resol", "resolution");
  TNamed sResol("sResol","sResolution");     //uncertainty on resolution
  TNamed    eff(   "eff", "efficiency");     //efficiency
  TNamed   sEff(  "sEff","sEfficiency");     //uncertainty on efficiency

  
  //oppure facciamo un vector che ha (resol, sResol, eff, sEff)
  //Double_t resol;    //resolution
  //Double_t sResol;   //uncertainty on resolution
  //Double_t eff;      //efficiency
  //Double_t sEff;     //uncertainty on efficiency
  //TEfficiency *pEff;
  
  
  for(UInt_t i=0; i<nRecoEvents; i++){
    if(i%1000==0) cout<<"PROCESSING EVENT "<<i<<endl;
    
    recoTree -> GetEvent(i);
    Double_t zRecoVert = recoVert->Z();
    simTree  -> GetEvent(recoLabel);
    Double_t zSimVert  = simVert ->getPoint().Z();
    Double_t residualZ = zRecoVert - zSimVert;   //compute residual along z coord (to be used for resolution)
    histResidualZ -> Fill(residualZ);
  }
  
  
  //Resolution
  histResidualZ -> Fit("gaus");
  resol.SetUniqueID(  histResidualZ->GetFunction("gaus")->GetParameter(1));
  sResol.SetUniqueID( histResidualZ->GetFunction("gaus")->GetParameter(2));

  //Efficiency //to be checked again
  Double_t effTemp = static_cast<Double_t>(nRecoEvents/nSimEvents);
  eff.SetUniqueID( effTemp);
  sEff.SetUniqueID(TMath::Sqrt(nSimEvents*effTemp*(1-effTemp)));

  //resol = histResidualZ->GetFunction("gaus")->GetParameter(1);  
  //sResol = histResidualZ->GetFunction("gaus")->GetParameter(2);
  //eff = static_cast<Double_t>(nRecoEvents/nSimEvents);
  //sEff = TMath::Sqrt(nSimEvents*eff*(1-eff));  
  //pEff = new TEfficiency(histRecoVertices, histSimVertices);

  
  resol.Write("resolution");
  sResol.Write("sResolution");
  eff.Write("efficiency");
  sEff.Write("sEfficiency");  
  
  histSimMult      -> Write();
  histSimVertices  -> Write();
  histRecoVertices -> Write();
  histResidualZ    -> Write();


  analysis_file -> ls();
  analysis_file -> Close();
  reco_file     -> Close();
  sim_file      -> Close();

  watch.Stop();
  watch.Print();
}
