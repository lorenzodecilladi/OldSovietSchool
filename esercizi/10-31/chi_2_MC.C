#if !defined(__CINT__) || defined(__MAKECINT__)
#include<Riostream.h>
#include <TF1.h>
#include <TFile.h>
#include <TH1D.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TStopwatch.h>
#endif


//=================================================
//============= FUNCTION DECLARATION ==============

//double poisson(double *x, double *par);
double chi2(double *x, double *mu, int N); //evaluates chi2
double rootInversion(TF1* funcPtr);
Double_t chi2PDF(Double_t *x,Double_t *par); //PDF Chi2




//=================================================
//===================== MAIN ======================
void chi_2_MC(const int nrep = 100, bool highBg = kFALSE){              //nrep = number of repetitions

  TStopwatch timer;
  timer.Start();
  
  //--------------------------------------------
  //---------------- Background ----------------
  const int nDoF = 12;                     //number of DoF = nbins of background histogram

  TCanvas *c1    = new TCanvas();
  c1->cd();
  TH1D *histData = new TH1D("histData","Istogramma dati osservati",nDoF,0.,24.);
  TF1  *teoBg    = new TF1();              //expected background
  
  double data[nDoF] = {1., 3., 1., 4., 3., 5., 2., 1., 1., 0., 1., 3.}; //"observed" data
  double mu[nDoF];                         //expected values  

  double multBg  = 1.;                     //background multiplier
  if(highBg == kTRUE){
    multBg = 1000.;
    teoBg    = new TF1("teoBg", "1000*0.169*(10-0.01*x)",0.,24.);       //expected background
  }
  else teoBg    = new TF1("teoBg", "0.169*(10-0.01*x)",0.,24.);         //expected background

  
  for(int i=0; i<nDoF; i++){
    data[i]  =  multBg*data[i];
    histData->  Fill(2*i+1,data[i]);
    mu[i]    =  multBg*0.169*(10-0.01*(2*i+1));
  }
  histData -> Draw("hist");
  teoBg    -> Draw("same");



  //--------------------------------------------
  //------------ CHI2 observed data ------------
  
  TCanvas *c2     = new TCanvas();
  c2->Divide(1,2);
  c2->cd(1);

  double chi2Data = chi2(data,mu,nDoF);     //(observed data, expected values, nDoF)
  cout << "Chi2 from observed data: " << chi2Data <<endl;  
  TLine *lineChi2 = new TLine(chi2Data, 0, chi2Data, nrep/10);
  lineChi2 -> SetLineColor(kOrange-2);
  lineChi2 -> SetLineWidth(3);


  
  //--------------------------------------------
  //--------------- CHI2 MC data ---------------

  double minChi2     = 0.;
  double maxChi2     = 60.;
  int nbinsChi2      = 30;
  double binSizeChi2 = (maxChi2-minChi2)/nbinsChi2;
  TH1D *histChi2     = new TH1D("histChi2","Istogramma chi2 MC",nbinsChi2,minChi2,maxChi2);
  double dataMC[nDoF];
  //TF1 *fPoisson      = new TF1("fPoisson", poisson, 0., mu[0]+10, 1);

  
  for(int j=0; j<nrep; j++){                //loop over experiment repetitions
    for(int i=0; i<nDoF; i++){              //loop over data histogram's bins
      dataMC[i] = gRandom->Poisson(mu[i]);  //MC extraction
                                            //fPoisson->SetParameter(0, mu[i]);    //questo è problematico, è lentissimo!
                                            //dataMC[i] = rootInversion(fPoisson);
    }
    histChi2->Fill(chi2(dataMC,mu,nDoF));
                                            //if(j%100000==0)cout<<"Processing event " << j << endl;
  }
  histChi2->SetMarkerStyle(22);
  histChi2->SetMarkerSize(1.5);
  histChi2->Draw("hist");
  
  TF1 *pearson = new TF1("pearson", chi2PDF, 0., 60., 2);
  double totIntegral = binSizeChi2*histChi2->Integral(0, nbinsChi2);
  pearson -> SetParameter(0, nDoF);
  pearson -> SetParameter(1, totIntegral);
  cout << histChi2->Integral(0, nbinsChi2) << endl;
  
  pearson -> Draw("same");
  lineChi2 -> Draw("same");

  c2->cd(2);
  gPad->SetLogy();
  histChi2->Draw("hist");
  pearson -> Draw("same");
  lineChi2 -> Draw("same");
			  
			  
			  
  //--------------------------------------------
  //----------------- P-value ------------------
  
  int binOfChi2Data = histChi2->GetXaxis()->FindBin(chi2Data);
  double pIntegral = binSizeChi2*histChi2->Integral(binOfChi2Data, nbinsChi2);
  double pValue = pIntegral/totIntegral;
  cout << "P-value: " << pValue << "\n" << endl;
  
  
  
  timer.Stop();
  timer.Print();
}




//=================================================
//============ FUNCTION IMPLEMENTATION ============

double chi2(double *x, double *mu, int N){
  double chiSquare = 0.;
  for(int i=0; i<N; i++)
    chiSquare += (x[i] - mu[i])*(x[i] - mu[i])/(mu[i]);
  return chiSquare;
}


/*
double poisson(double *x, double *par){
  double n = x[0];
  double lambda= par[0];
  //double pMax=par[1];

  //return pow(lambda,n)/TMath::Gamma(n)*TMath::Exp();
  return TMath::Exp(n*(TMath::Log(lambda/n)+1)-lambda);  
  //return TMath::Poisson(n,lambda);
}
*/

/*
//ROOT NUMERICAL INVERSION
double rootInversion(TF1* funcPtr){

  //funcPtr.SetParameter(0, fParam);  
  return funcPtr->GetRandom();
}
*/

Double_t chi2PDF(Double_t *x,Double_t *par)
{
  // Chisquare density distribution for nrFree degrees of freedom
  
  Double_t nrFree = par[0];
  Double_t Int = par[1];
  Double_t chi2 = x[0];
  
  if (chi2 > 0) {
    Double_t lambda = nrFree/2.;
    Double_t norm = TMath::Gamma(lambda)*TMath::Power(2.,lambda);
    return Int*TMath::Power(chi2,lambda-1)*TMath::Exp(-0.5*chi2)/norm;
  } else
    return 0.0;
}
