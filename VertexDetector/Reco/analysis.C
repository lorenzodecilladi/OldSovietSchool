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
  UInt_t  label;
  TBranch *bRecoVert = recoTree -> GetBranch("recoVertex");
  TBranch *bLabel    = recoTree -> GetBranch("label");
  bRecoVert -> SetAddress(&recoVert);
  bLabel    -> SetAddress(&label);
  TH1D    *histRecoVertices  = (TH1D*)reco_file->Get("histRecoVertices"); //[cm]
  
  UInt_t nRecoEvents = recoTree -> GetEntries();

  
  //crea file analisi
  TFile *analysis_file    = new TFile("analysisFile.root", "RECREATE");
  TH1D  *histResidualZ    = new TH1D("histResidualZ", "Residual in Z", nSimEvents/30., -0.10005, 0.10005);
  //uso nSimEvents così ho il controllo dell'ampiezza dei bins
  
  Double_t meanZGenerated = histSimVertices -> GetMean(); //si può fare un fit e prendere il valor medio
  Double_t mult           = histSimMult     -> GetMean(); //obviously, to be used only when "fixed" mult

  TNamed resol("resol","resolution");
  
  //Double_t resol;    //resolution
  Double_t sResol;   //uncertainty on resolution
  Double_t eff;      //efficiency
  //TEfficiency *pEff; 
  Double_t sEff;     //uncertainty on efficiency
  

  for(UInt_t i=0; i<nSimEvents; i++){
    if(i%1000==0) cout<<"PROCESSING EVENT "<<i<<endl;
    simTree->GetEvent(i);

    if(i<nRecoEvents){
      recoTree->GetEvent(i);
      Double_t zRecoVert = recoVert->Z();
      simTree->GetEvent(label);
      Double_t zSimVert = simVert->getPoint().Z();
      Double_t residualZ = zRecoVert - zSimVert;   //compute residual along z coord (to be used for resolution)
      histResidualZ -> Fill(residualZ);
    }
  }

  //resolution
  histResidualZ -> Fit("gaus");
  //resol = histResidualZ->GetFunction("gaus")->GetParameter(1);


  resol.SetUniqueID(histResidualZ->GetFunction("gaus")->GetParameter(1));
  resol.Write("resolution");

  
  //sResol = histResidualZ->GetFunction("gaus")->GetParameter(2);

  //pEff = new TEfficiency(histRecoVertices, histSimVertices);
  //eff = static_cast<Double_t>(nRecoEvents/nSimEvents);
  //sEff = TMath::Sqrt(nSimEvents*eff*(1-eff));

  //efficiency
  //efficienza= recoTree-GetEntries()/simTree->GetEnries(); oppure sul branch degli zeta

  histSimMult      -> Write();
  histSimVertices  -> Write();
  histRecoVertices -> Write();
  histResidualZ    -> Write();

  //cout << "allright" << endl;
  //return;


  //resol.Write();
  //sResol.Write();
  //eff.Write();
  //sEff.Write();

  analysis_file -> ls();
  analysis_file -> Close();
  reco_file     -> Close();
  sim_file      -> Close();
  
}
