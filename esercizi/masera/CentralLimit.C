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
    fH(NULL),
    fSum(0.),
    fSum_n(0.){ 
    cout<<"DEFAULT CONSTRUCTOR "<<endl;
  }

  // Standard constructor
  Histo(const char* name, const char* title, int n, double min, double max, unsigned int sum_n):
    fH(NULL),
    fSum(0.),
    fSum_n(sum_n) {
    fH = new TH1D(name, title, n, min, max);
    fH->SetDirectory(0);
    cout<<"Standard constructor - this: "<<this<<endl;
  }

  // Copy constructor
  Histo(const Histo& source):
    fH(NULL),
    fSum(source.fSum),
    fSum_n(source.fSum_n){
    cout<<"COPY CONSTRUCTOR this: "<<this<<" source: "<<&source<<endl;
    if(source.fH){
      fH=new TH1D(*(source.fH));
      fH->SetDirectory(0);
    }
  }

  // Assignment operator
  Histo& operator=(const Histo& source){
    if(this == &source) return *this;
    cout<<"ASSIGNMENT OPERATOR "<<this<<endl;
    this->~Histo();
    new(this) Histo(source);
    cout<<"ASSIGNMENT OPERATOR 2 "<<this<<endl;
    return *this;
  }

  // Destructor
  ~Histo(){ 
    cout<<"DESTRUCTOR - this "<<this<<endl;
    if(fH)delete fH;
  }

  // Public methods
  void Draw() {
    new TCanvas();
    fH->DrawCopy();
  }

  unsigned int GetMaxSum() {return fSum_n;}
  void Add(double x) {fSum += x;}
  void SetZero() {fSum = 0;}
  void FillInto() {fH->Fill(fSum);}

  // Data members
private:
  TH1D* fH;
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

