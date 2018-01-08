/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ~ Macro for the VERTICES ANALYSIS in a barrel detector     ~
  ~ Authors:  Arianna Corrado                                ~
  ~           Lorenzo de Cilladi                             ~
  ~ Course:   TANS - 2017/2018                               ~
  ~                                                          ~
  ~ Last modified: 08/01/2018                                ~
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

#endif

//function definition
void analysis(TString simfilePath = "../Sim/simFile.root", TString recofilePath = "../Reco/recoFile.root", TString outFileName = "analysisFile.root");

//utils function (they will be deleted in the final version)
void exec();
void exec1();
void exec2();
void exec3();
void exec4();




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

  histSimVertices->Fit("gaus");
  Double_t meanZSimVert     = histSimVertices->GetFunction("gaus")->GetParameter(1);
  Double_t sigmaZSimVert    = histSimVertices->GetFunction("gaus")->GetParameter(2);

  //???????????????
  UInt_t   nSimEvents1sig   = 0;
  cout << "FIRST LOOP" << endl;
  for(UInt_t i=0; i<nSimEvents; i++){
    if(i%10000==0) cout<<"PROCESSING EVENT "<<i<<endl;
    simTree -> GetEvent(i); //aim of recoLabel: get only simulated events whose vertex was actually reconstructed
    Double_t zSimVert = simVert->getPoint().Z();
    if(zSimVert >= meanZSimVert-sigmaZSimVert && zSimVert <= meanZSimVert+sigmaZSimVert) nSimEvents1sig++;
  }
  cout << nSimEvents1sig << endl;

  Double_t zMinBin = histSimVertices->GetXaxis()->FindBin(meanZSimVert-sigmaZSimVert);
  Double_t zMaxBin = histSimVertices->GetXaxis()->FindBin(meanZSimVert+sigmaZSimVert);
  cout << histSimVertices->Integral(zMinBin, zMaxBin) << endl;

  
  
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
  TH1D  *histResidualZ      = new TH1D ("histResidualZ", "Residual in Z", nSimEvents/30., -0.10005, 0.10005);
  //uso nSimEvents così ho il controllo dell'ampiezza dei bins

  cout << "\nCreating " << outFileName << " ..." << endl;
  
  Double_t meanZGenerated   = histSimVertices -> GetMean(); //si può fare un fit e prendere il valor medio???
  Double_t mult             = histSimMult     -> GetMean(); //obviously, to be used only when "fixed" mult

  
  TVectorD vec(6);   //vector = (meanResZ, resol, eff, sEff)
  Double_t meanResZ; //mean residual in Z
  Double_t resol;    //resolution (sigma residual in Z)
  Double_t eff;      //efficiency
  Double_t sEff;     //uncertainty on eff
  Double_t eff1sig;  //efficiency for particles generated within 1 sigma
  Double_t sEff1sig;
  

  UInt_t nRecoEvents1sig    = 0;
  
  cout << "SECOND LOOP" <<endl;
  for(UInt_t i=0; i<nRecoEvents; i++){
    if(i%10000==0) cout<<"PROCESSING EVENT "<<i<<endl;
    
    recoTree -> GetEvent(i);
    Double_t zRecoVert = recoVert->Z();
    simTree  -> GetEvent(recoLabel); //aim of recoLabel: get only simulated events whose vertex was actually reconstructed
    Double_t zSimVert  = simVert->getPoint().Z();
    Double_t residualZ = zRecoVert - zSimVert;  //compute residual along z coord (to be used for resolution)
    histResidualZ -> Fill(residualZ);
    if(zSimVert >= meanZSimVert-sigmaZSimVert && zSimVert <= meanZSimVert+sigmaZSimVert) nRecoEvents1sig++;
  }
  cout << nRecoEvents1sig << endl;
  
  
  //Resolution
  histResidualZ->Fit("gaus");
  meanResZ  = histResidualZ->GetFunction("gaus")->GetParameter(1);
  resol = histResidualZ->GetFunction("gaus")->GetParameter(2);
  vec[0] = meanResZ;
  vec[1] = resol; 
  cout << "\nResidual mean = " << vec[0] * 10000 << " um; Resolution (residual sigma) = " << vec[1] * 10000 << " um"<< endl;

  //Efficiency
  eff    = (static_cast<Double_t>(nRecoEvents)/static_cast<Double_t>(nSimEvents));
  sEff   = (1/nSimEvents)*TMath::Sqrt(nRecoEvents*(1-nRecoEvents/nSimEvents));  //binomial error because numerator (nRecoEvents)
  vec[2] = eff;                                                                 //is a subset of denominatr (nSimEvents)
  vec[3] = sEff;
  cout << "Efficiency = " << vec[2] << " +- " << vec[3] << endl;

  //Efficiency for particles generated within 1 sigma
  eff1sig  = (static_cast<Double_t>(nRecoEvents1sig)/static_cast<Double_t>(nSimEvents1sig));
  sEff1sig = (1/nSimEvents1sig)*TMath::Sqrt(nRecoEvents1sig*(1-nRecoEvents1sig/nSimEvents1sig));
  vec[4]   = eff1sig;
  vec[5]   = sEff1sig;
  cout << "Efficiency (within 1 sigma) = " << vec[4] << " +- " << vec[5] << endl;
  
  cout << "\n---------------------------------------------------" << endl;
  
  vec.Write("vec");
  histSimMult      -> Write();
  histSimVertices  -> Write();
  histRecoVertices -> Write();
  histResidualZ    -> Write();

  analysis_file    -> ls();
  cout << "-----------------------------------------------------" << endl;
  
  analysis_file    -> Close();
  reco_file        -> Close();
  sim_file         -> Close();

  watch.Stop();
  watch.Print();
}

































//function implementation
void exec(){
  analysis("../Sim/simFiles/sim0033.root", "../Reco/recoFilesMatch/reco0033m.root", "analysis0033m.root");
  analysis("../Sim/simFiles/sim0034.root", "../Reco/recoFilesMatch/reco0034m.root", "analysis0034m.root");
  analysis("../Sim/simFiles/sim0035.root", "../Reco/recoFilesMatch/reco0035m.root", "analysis0035m.root");
  analysis("../Sim/simFiles/sim0036.root", "../Reco/recoFilesMatch/reco0036m.root", "analysis0036m.root");
  analysis("../Sim/simFiles/sim0037.root", "../Reco/recoFilesMatch/reco0037m.root", "analysis0037m.root");
  analysis("../Sim/simFiles/sim0038.root", "../Reco/recoFilesMatch/reco0038m.root", "analysis0038m.root");
  analysis("../Sim/simFiles/sim0039.root", "../Reco/recoFilesMatch/reco0039m.root", "analysis0039m.root");
  analysis("../Sim/simFiles/sim0040.root", "../Reco/recoFilesMatch/reco0040m.root", "analysis0040m.root");
  analysis("../Sim/simFiles/sim0041.root", "../Reco/recoFilesMatch/reco0041m.root", "analysis0041m.root");
  analysis("../Sim/simFiles/sim0061.root", "../Reco/recoFilesMatch/reco0061m.root", "analysis0061m.root");
}

void exec1(){
  analysis("../Sim/simFiles/sim0042.root", "../Reco/recoFilesMatch/reco0042m.root", "analysis0042m.root");
  analysis("../Sim/simFiles/sim0043.root", "../Reco/recoFilesMatch/reco0043m.root", "analysis0043m.root");
  analysis("../Sim/simFiles/sim0044.root", "../Reco/recoFilesMatch/reco0044m.root", "analysis0044m.root");
  analysis("../Sim/simFiles/sim0045.root", "../Reco/recoFilesMatch/reco0045m.root", "analysis0045m.root");
  analysis("../Sim/simFiles/sim0046.root", "../Reco/recoFilesMatch/reco0046m.root", "analysis0046m.root");
  analysis("../Sim/simFiles/sim0047.root", "../Reco/recoFilesMatch/reco0047m.root", "analysis0047m.root");
  analysis("../Sim/simFiles/sim0048.root", "../Reco/recoFilesMatch/reco0048m.root", "analysis0048m.root");
  analysis("../Sim/simFiles/sim0049.root", "../Reco/recoFilesMatch/reco0049m.root", "analysis0049m.root");
  analysis("../Sim/simFiles/sim0050.root", "../Reco/recoFilesMatch/reco0050m.root", "analysis0050m.root");
  analysis("../Sim/simFiles/sim0062.root", "../Reco/recoFilesMatch/reco0062m.root", "analysis0062m.root");
}

void exec2(){
  analysis("../Sim/simFiles/sim0051.root", "../Reco/recoFilesMatch/reco0051m.root", "analysis0051m.root");
  analysis("../Sim/simFiles/sim0052.root", "../Reco/recoFilesMatch/reco0052m.root", "analysis0052m.root");
  analysis("../Sim/simFiles/sim0053.root", "../Reco/recoFilesMatch/reco0053m.root", "analysis0053m.root");
  analysis("../Sim/simFiles/sim0054.root", "../Reco/recoFilesMatch/reco0054m.root", "analysis0054m.root");
  analysis("../Sim/simFiles/sim0055.root", "../Reco/recoFilesMatch/reco0055m.root", "analysis0055m.root");
  analysis("../Sim/simFiles/sim0056.root", "../Reco/recoFilesMatch/reco0056m.root", "analysis0056m.root");
  analysis("../Sim/simFiles/sim0057.root", "../Reco/recoFilesMatch/reco0057m.root", "analysis0057m.root");
  analysis("../Sim/simFiles/sim0058.root", "../Reco/recoFilesMatch/reco0058m.root", "analysis0058m.root");
  analysis("../Sim/simFiles/sim0059.root", "../Reco/recoFilesMatch/reco0059m.root", "analysis0059m.root");
  analysis("../Sim/simFiles/sim0060.root", "../Reco/recoFilesMatch/reco0060m.root", "analysis0060m.root");
}

void exec3(){
  analysis("../Sim/simFiles/sim0013.root", "../Reco/recoFilesMatch/reco0013m.root", "analysis0013m.root");
  analysis("../Sim/simFiles/sim0015.root", "../Reco/recoFilesMatch/reco0015m.root", "analysis0015m.root");
  analysis("../Sim/simFiles/sim0017.root", "../Reco/recoFilesMatch/reco0017m.root", "analysis0017m.root");
  analysis("../Sim/simFiles/sim0019.root", "../Reco/recoFilesMatch/reco0019m.root", "analysis0019m.root");
  analysis("../Sim/simFiles/sim0021.root", "../Reco/recoFilesMatch/reco0021m.root", "analysis0021m.root");
  analysis("../Sim/simFiles/sim0023.root", "../Reco/recoFilesMatch/reco0023m.root", "analysis0023m.root");
  analysis("../Sim/simFiles/sim0025.root", "../Reco/recoFilesMatch/reco0025m.root", "analysis0025m.root");
  analysis("../Sim/simFiles/sim0027.root", "../Reco/recoFilesMatch/reco0027m.root", "analysis0027m.root");
  analysis("../Sim/simFiles/sim0029.root", "../Reco/recoFilesMatch/reco0029m.root", "analysis0029m.root");
  analysis("../Sim/simFiles/sim0031.root", "../Reco/recoFilesMatch/reco0031m.root", "analysis0031m.root"); 
}

void exec4(){
  analysis("../Sim/simFiles/sim0014.root", "../Reco/recoFilesMatch/reco0014m.root", "analysis0014m.root");
  analysis("../Sim/simFiles/sim0016.root", "../Reco/recoFilesMatch/reco0016m.root", "analysis0016m.root");
  analysis("../Sim/simFiles/sim0018.root", "../Reco/recoFilesMatch/reco0018m.root", "analysis0018m.root");
  analysis("../Sim/simFiles/sim0020.root", "../Reco/recoFilesMatch/reco0020m.root", "analysis0020m.root");
  analysis("../Sim/simFiles/sim0022.root", "../Reco/recoFilesMatch/reco0022m.root", "analysis0022m.root");
  analysis("../Sim/simFiles/sim0024.root", "../Reco/recoFilesMatch/reco0024m.root", "analysis0024m.root");
  analysis("../Sim/simFiles/sim0026.root", "../Reco/recoFilesMatch/reco0026m.root", "analysis0026m.root");
  analysis("../Sim/simFiles/sim0028.root", "../Reco/recoFilesMatch/reco0028m.root", "analysis0028m.root");
  analysis("../Sim/simFiles/sim0030.root", "../Reco/recoFilesMatch/reco0030m.root", "analysis0030m.root");
  analysis("../Sim/simFiles/sim0032.root", "../Reco/recoFilesMatch/reco0032m.root", "analysis0032m.root"); 
}


