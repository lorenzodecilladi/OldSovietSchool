/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ~ Macro for the VERTICES COMBINED ANALYSIS in a barrel detector     ~
  ~ Authors:  Arianna Corrado                                         ~
  ~           Lorenzo de Cilladi                                      ~
  ~ Course:   TANS - 2017/2018                                        ~
  ~                                                                   ~
  ~ Last modified: 22/01/2018                                         ~
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#if !defined(__CINT__) || defined(__MAKECINT__)

#include <Riostream.h>
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TMath.h"
#include "TH1D.h"
#include "TF1.h"
#include "TStopwatch.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TVectorD.h"

#endif


void combinedAnalysis(TString inputListFile = "inputFileList.txt",  TString outFileName = "combAnalysisFile.root"){

  TStopwatch watch;
  watch.Start(kTRUE);

  Double_t     multArr[50]; //multipliciy
  Double_t    sMultArr[50] = {0.};
  Double_t    resolArr[50]; //resolution
  Double_t   sResolArr[50];
  Double_t      effArr[50]; //efficiency
  Double_t     sEffArr[50];
  Double_t  eff1sigArr[50]; //efficiency (within 1 sigma)
  Double_t sEff1sigArr[50];
  Double_t     zGenArr[50]; //z generated
  Double_t    sZGenArr[50] = {0.};
    
  ifstream in(inputListFile);
  if(!in){
    cout << "\n[!]\n[!]File " << inputListFile << " not found!!\n[!]" << endl;
    return;
  }

  TString comment = "null";
  TString inFile;
  Int_t count = 0;
  in>>comment;
  
  while(in>>inFile){
    if(inFile=="break") break;
    cout << inFile << endl;

    //open input analysis file and tree
    TFile *analysis_file  = new TFile(inFile);
    if(analysis_file -> IsZombie()){
      cout << "\n[!]\n[!]File " << inFile << " not found!!\n[!]" << endl;
      return;
    }

    Double_t mult   = ((TH1D*)analysis_file->Get("histSimMult"))->GetMean();  //obviously, to be used only when "fixed" mult
    multArr[count]  = mult;

    TH1D *histSimVertices = (TH1D*)analysis_file->Get("histSimVertices"); //[cm]
    histSimVertices -> Fit("gaus");    
    Double_t zGen    = histSimVertices->GetFunction("gaus")->GetParameter(1);
    //Double_t sZGen   = histSimVertices->GetFunction("gaus")->GetParameter(2);
    zGenArr[count]   = zGen;
    //sZGenArr[count]  = sZGen;

    TVectorD *vec = (TVectorD*)analysis_file->Get("vec");
    
    double resol     = (*vec)[0];
    double sResol    = (*vec)[1];
    resolArr[count]  = resol;
    sResolArr[count] = sResol;

    double eff       = (*vec)[2];
    double sEff      = (*vec)[3];
    effArr[count]    = eff;
    sEffArr[count]   = sEff;

    double eff1sig      = (*vec)[4];
    double sEff1sig     = (*vec)[5];
    eff1sigArr[count]   = eff1sig;
    sEff1sigArr[count]  = sEff1sig;
    
    cout << "Multiplicity: " << mult << endl;
    cout << "Resolution: "   << resol << " +- " << sResol << endl;
    cout << "Efficiency: "   << eff   << " +- " << sEff   << endl;
    cout << "Efficiency (within 1 sigma): " << eff1sig << " +- " << sEff1sig << endl;
    
    //histResolMult->Fill(mult, resol);    

    count++;
    analysis_file -> Close();
  }

  //creates output file
  TFile *combAnalysis_file = new TFile(outFileName, "RECREATE");
  
  //histResolMult -> DrawCopy();

  TGraphErrors *grResolZGen = new TGraphErrors(count, zGenArr, resolArr, sZGenArr, sResolArr);
  grResolZGen -> SetName("ResolVsZGen");
  grResolZGen -> SetTitle("Resolution vs Generated Z");
  grResolZGen -> GetXaxis()->SetTitle("Generated Z [cm]");
  grResolZGen -> GetYaxis()->SetTitle("Resolution [cm]");
  grResolZGen -> SetMarkerStyle(20);
  grResolZGen -> SetMarkerSize(0.5);
  grResolZGen -> SetMarkerColor(6);
  grResolZGen -> SetLineColor(6);
  grResolZGen -> Draw("AP");
  
  TGraphErrors *grResolMult = new TGraphErrors(count, multArr, resolArr, sMultArr, sResolArr);
  grResolMult -> SetName("ResolVsMult");
  grResolMult -> SetTitle("Resolution vs Multiplicity");
  grResolMult -> GetXaxis()->SetTitle("Multiplicity");
  grResolMult -> GetYaxis()->SetTitle("Resolution [cm]");
  grResolMult -> SetMarkerStyle(20);
  grResolMult -> SetMarkerSize(0.5);
  grResolMult -> SetMarkerColor(kRed);
  grResolMult -> SetLineColor(kRed);
  grResolMult -> Draw("AP");

  TGraphErrors *grEffMult = new TGraphErrors(count, multArr, effArr, sMultArr, sEffArr);
  grEffMult   -> SetName("EffVsMult");
  grEffMult   -> SetTitle("Efficiency vs Multiplicity");
  grEffMult   -> GetXaxis()->SetTitle("Multiplicity");
  grEffMult   -> GetYaxis()->SetTitle("Efficiency");
  grEffMult   -> SetMarkerStyle(20);
  grEffMult   -> SetMarkerSize(0.5);
  grEffMult   -> SetMarkerColor(kBlue);
  grEffMult   -> SetLineColor(kBlue);
  grEffMult   -> Draw("AP");

  TGraphErrors *grEff1sigMult = new TGraphErrors(count, multArr, eff1sigArr, sMultArr, sEff1sigArr);
  grEff1sigMult   -> SetName("Eff1sigVsMult");
  grEff1sigMult   -> SetTitle("Efficiency (for particles generated within 1 sigma) vs Multiplicity");
  grEff1sigMult   -> GetXaxis()->SetTitle("Multiplicity");
  grEff1sigMult   -> GetYaxis()->SetTitle("Efficiency");
  grEff1sigMult   -> SetMarkerStyle(20);
  grEff1sigMult   -> SetMarkerSize(0.5);
  grEff1sigMult   -> SetMarkerColor(kBlue);
  grEff1sigMult   -> SetLineColor(kBlue);
  grEff1sigMult   -> Draw("AP");
  
  in.close();

  grResolZGen  ->Write();
  grResolMult  ->Write();
  grEffMult    ->Write();
  grEff1sigMult->Write();
  combAnalysis_file->Write();
  combAnalysis_file->Close();
  
  watch.Stop();
  watch.Print();
}
