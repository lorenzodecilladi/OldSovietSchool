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
#include "TMath.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TF1.h"
#include "TStopwatch.h"
#include "TGraph.h"
#include "TVectorD.h"

#endif


void combinedAnalysis(TString inputListFile){

  TStopwatch watch;
  watch.Start(kTRUE);

  //crea file di output
  TFile *combAnalysis_file = new TFile("combAnalysis.root", "RECREATE");
    //  TH2D  *histResolVsMult     = new TH2D("histResolVsMult", "Resolution vs Multiplicity", 51, -0.5, 50.5, 100, 0., 0.01);
  TH1D  *histResolVsMult     = new TH1D("histResolVsMult", "Resolution vs Multiplicity", 51, -0.5, 50.5);

  Double_t multArr[50];
  Double_t resolArr[50];
    
  ifstream in(inputListFile);
  if(!in){
    cout<<"Il file "<<inputListFile<<" non esiste "<<endl;
    return;
  }
  

  TString inFile;
  Int_t count = 0;
  
  while(in>>inFile){
    cout << inFile << endl;

    //open input analysis file and tree
    TFile *analysis_file  = new TFile(inFile);
    if(analysis_file -> IsZombie()){
      cout << "File " << inFile << " not found!!" << endl;
      return;
    }

    Double_t mult = ((TH1D*)analysis_file->Get("histSimMult"))->GetMean(); //obviously, to be used only when "fixed" mult
    multArr[count] = mult;
    
    TVectorD *vec = (TVectorD*)analysis_file->Get("vec");

    //cout << "ok" << endl;
    //return;

    //root > v->Print()
    double resol  = (*vec)[0];
    double sResol = (*vec)[1];
    resolArr[count] = sResol;
    cout << "Multiplicity: " << mult << "; sResolution: " << sResol << endl;

    double eff  = (*vec)[2];
    double sEff = (*vec)[3];
    //    histResolVsMult->Fill(mult, sResol);
    histResolVsMult->Fill(mult, sResol);    

    count++;
    analysis_file -> Close();
  }
  
  histResolVsMult -> DrawCopy();

  TGraph  *grResolVsMult = new TGraph(count, multArr, resolArr);
  grResolVsMult->Draw();
  
  in.close();

  grResolVsMult->Write();
  combAnalysis_file->Write();
  combAnalysis_file->Close();
  

/*
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

  


  
  //oppure facciamo un vector che ha (resol, sResol, eff, sEff)
  //Double_t resol;    //resolution
  //Double_t sResol;   //uncertainty on resolution
  //Double_t eff;      //efficiency
  //Double_t sEff;     //uncertainty on efficiency
  //TEfficiency *pEff;
  
  
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

  */

  watch.Stop();
  watch.Print();
}
