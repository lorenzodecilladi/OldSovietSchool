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
#include "TGraphErrors.h"
#include "TVectorD.h"

#endif


void combinedAnalysis(TString inputListFile){

  TStopwatch watch;
  watch.Start(kTRUE);

  //  TH2D  *histResolMult     = new TH2D("histResolMult", "Resolution vs Multiplicity", 51, -0.5, 50.5, 100, 0., 0.01);
  TH1D  *histResolMult     = new TH1D("histResolMult", "Resolution vs Multiplicity", 51, -0.5, 50.5);
  
  Double_t multArr[50];
  Double_t sMultArr[50] = {0.};
  Double_t resolArr[50];
  Double_t effArr[50];
  Double_t sEffArr[50];
  Double_t zGenArr[50]; //z generated
  Double_t sZGenArr[50]; //z generated
    
  ifstream in(inputListFile);
  if(!in){
    cout<<"[!]\n[!]\n[!]\n[!]Il file "<<inputListFile<<" non esiste!\n[!]\n[!]\n[!]"<<endl;
    return;
  }

  TString comment = "null";
  TString inFile;
  Int_t count = 0;

  in>>comment;
  
  while(in>>inFile){
    if(inFile=="break")break;
    
    cout << inFile << endl;

    //open input analysis file and tree
    TFile *analysis_file  = new TFile(inFile);
    if(analysis_file -> IsZombie()){
      cout << "File " << inFile << " not found!!" << endl;
      return;
    }

    Double_t mult = ((TH1D*)analysis_file->Get("histSimMult"))->GetMean(); //obviously, to be used only when "fixed" mult
    multArr[count] = mult;


    TH1D *histSimVertices = (TH1D*)analysis_file->Get("histSimVertices"); //[cm]
    histSimVertices->Fit("gaus");    
    Double_t zGen  = histSimVertices->GetFunction("gaus")->GetParameter(1);
    Double_t sZGen = histSimVertices->GetFunction("gaus")->GetParameter(2);
    zGenArr[count] = zGen;
    sZGenArr[count] = sZGen;

    
    
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

  TGraph  *grResolZGen = new TGraph(count, zGenArr, resolArr);
  grResolZGen->SetTitle("Resolution vs Generated Z");
  grResolZGen->GetXaxis()->SetTitle("Generated Z [cm]");
  grResolZGen->GetYaxis()->SetTitle("Resolution [cm]");
  grResolZGen->SetMarkerStyle(20);
  grResolZGen->SetMarkerSize(1.0);
  grResolZGen->SetMarkerColor(6);
  grResolZGen->Draw("APL");
  
  TGraph  *grResolMult = new TGraph(count, multArr, resolArr);
  grResolMult->SetTitle("Resolution vs Multiplicity");
  grResolMult->GetXaxis()->SetTitle("Multiplicity");
  grResolMult->GetYaxis()->SetTitle("Resolution [cm]");
  grResolMult->SetMarkerStyle(20);
  grResolMult->SetMarkerSize(1.0);
  grResolMult->SetMarkerColor(kRed);
  grResolMult->Draw("APL");

  TGraphErrors  *grEffMult = new TGraphErrors(count, multArr, effArr, sMultArr, sEffArr); //aggiungere errore
  grEffMult->SetTitle("Efficiency vs Multiplicity");
  grEffMult->GetXaxis()->SetTitle("Multiplicity");
  grEffMult->GetYaxis()->SetTitle("Efficiency");
  grEffMult->SetMarkerStyle(20);
  grEffMult->SetMarkerSize(1.0);
  grEffMult->SetMarkerColor(kBlue);
  grEffMult->Draw("APL");
  
  in.close();

  histResolMult->Write();
  grResolZGen->Write();
  grResolMult->Write();
  grEffMult->Write();
  combAnalysis_file->Write();
  combAnalysis_file->Close();
  
  watch.Stop();
  watch.Print();
}
