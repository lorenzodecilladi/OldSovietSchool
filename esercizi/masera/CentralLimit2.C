#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <vector>
#endif


class Histo {
public:
  // Default constructor
  Histo():
    fH(),
    fSum(0.),
    fSum_n(0.){
    fH.SetDirectory(0); 
    cout<<"DEFAULT CONSTRUCTOR "<<endl;
  }

  // Standard constructor
  Histo(const char* name, const char* title, int n, double min, double max, unsigned int sum_n):
    fH(name, title, n, min, max),
    fSum(0.),
    fSum_n(sum_n) {
    fH.SetDirectory(0);
    cout<<"Standard constructor - this: "<<this<<endl;
  }

  // Public methods
  void Draw() {
    new TCanvas();
    fH.DrawCopy();
  }

  unsigned int GetMaxSum() {return fSum_n;}
  void Add(double x) {fSum += x;}
  void SetZero() {fSum = 0;}
  void FillInto() {fH.Fill(fSum);}

  // Data members
private:
  TH1D fH;
  double fSum;
  unsigned int fSum_n;

};

void CentralV2(int seed = 42) {
  const int max_count = 200000;

  std::vector<Histo> histos;
  cout<<"Sto per chiamare il primo pushback\n";
  histos.push_back(Histo("h1","h1",100,0.0,1.0,1));
  cout<<"Sto per chiamare il secondo pushback\n";
  histos.push_back(Histo("h2","h2",100,0.0,2.0,2));
  cout<<"Sto per chiamare il terzo pushback\n";
  histos.push_back(Histo("h3","h3",100,0.0,3.0,3));
  cout<<"Sto per chiamare il quarto pushback\n";
  histos.push_back(Histo("h300","h300",100,110.0,190.0,300));

  TRandom *rnd = new TRandom3(seed);

  for(int k = 0; k < max_count; k++) { //ciclo sulle entries degli istogrammi
    for(unsigned int i = 0; i < histos.size(); i++) { //ciclo sugli istogrammi
      histos[i].SetZero();
      for(unsigned int j = 0; j < histos[i].GetMaxSum(); j++) { //ciclo per la somma
        double x = std::fmod(rnd->Rndm()*0.4 + 0.8, 1.0);
        histos[i].Add(x);
      }
      histos[i].FillInto();
    }
  }

  for(unsigned int i = 0; i < histos.size(); i++) {
    cout<<"Disegno istogramma "<<i<<endl;
    histos[i].Draw();
  }
}

