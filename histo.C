#if !defined(__CINT__) || defined(__MAKECINT__)
#include<Riostream.h>
#include<TFile.h>
#include<TH1D.h>
#include<TCanvas.h>
#include<TAxis.h>

#endif
using namespace std;



void func(const char* fimpName, const char *histName){
  ifstream in(fimpName);
  if(!in){
    cout << "Il file " << fimpName << " non esiste" << endl;
    return;
  }
  
  TFile file(histName, "recreate");
  //  TH1D hist("hist", "histogram", 100, 0, 10);
  int count=0;
  double x, min, max;
  in>>x;
  min = x;
  max = x;
  while((in>>x)){
    if (x<min) min=x;
    if (x>max) max=x;
  }
  //hist.SetBins(100, min, max);
  //hist.SetAxisRange(min, max);
  cout<<"min: "<<min<<endl;
  cout<<"max: "<<max<<endl;
  TH1D hist("hist", "histogram", 100, min, max);
  in.clear();
  in.seekg(0,ios::beg);
  while((in>>x)){
    count++;
    hist.Fill(x);
  }
  cout<<"Dati letti: "<< count<< endl;
  in.close();
  hist.DrawCopy();
  file.Write(); //scarica tutti gli oggetti di quella directory
  file.Close();
}
