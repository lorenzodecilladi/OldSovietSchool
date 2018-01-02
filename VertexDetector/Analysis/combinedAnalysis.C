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

  //  TH2D  *histResolMult     = new TH2D("histResolMult", "Resolution vs Multiplicity", 51, -0.5, 50.5, 100, 0., 0.01);
  TH1D  *histResolMult     = new TH1D("histResolMult", "Resolution vs Multiplicity", 51, -0.5, 50.5);
  
  Double_t multArr[50];
  Double_t resolArr[50];
  Double_t effArr[50];
  Double_t sEffArr[50];
    
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
    //root > v->Print()
    
    double resol  = (*vec)[0];
    double sResol = (*vec)[1];
    resolArr[count] = sResol;

    double eff  = (*vec)[2];
    double sEff = (*vec)[3];
    effArr[count] = eff;
    sEffArr[count] = sEff;
    
    cout << "Multiplicity: " << mult << endl;
    cout << "Resolution: " << sResol << "; Efficiency: " << eff << endl;
    
    histResolMult->Fill(mult, sResol);    

    count++;
    analysis_file -> Close();
  }

  //crea file di output
  TFile *combAnalysis_file = new TFile("combAnalysis.root", "RECREATE");
  
  histResolMult -> DrawCopy();

  TGraph  *grResolMult = new TGraph(count, multArr, resolArr);
  grResolMult->SetTitle("Resolution vs Multiplicity");
  grResolMult->Draw("APL");

  TGraph  *grEffMult = new TGraph(count, multArr, effArr); //aggiungere errore
  grEffMult->SetTitle("Efficiency vs Multiplicity");
  grEffMult->Draw("APL");
  
  in.close();

  histResolMult->Write();
  grResolMult->Write();
  grEffMult->Write();
  combAnalysis_file->Write();
  combAnalysis_file->Close();
  
  watch.Stop();
  watch.Print();
}
