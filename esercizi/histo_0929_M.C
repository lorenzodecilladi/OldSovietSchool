#if !defined(__CINT__) || defined(__MAKECINT__)
#include<Riostream.h>
#include<TFile.h>
#include<TH1D.h>
#include<TCanvas.h>
#include<TAxis.h>

#endif
using namespace std;



//SOLUZIONE CHE USA std::vector

void func(const char* fimpName, const char *histName){
  ifstream in(fimpName);
  if(!in){
    cout << "Il file " << fimpName << " non esiste" << endl;
    return;
  }

  Double_t xmin=0., xmax=0;
  Double_t x;
  in>>x; //N.B.: questo programma dà un errore se il file è vuoto, si suppone che ci sia almeno un numero. Non è a prova di scemo!
  xmin=xmax=x;
  Int_t count = 1;
  vector <Double_t> v; //Qui sto usando i template, che sono tra parentesi acute. Faccio un vettore di Double_t.
  //vector alloca nell'heap, ma fa una danza di resize automatici del vector che impiega un po' di tempo macchina...!! 
  v.push_back(x);
  Bool_t toomuch = kFALSE; //kFALSE è, in ROOT, il valore false.
  const UInt_t limit = 10000; //Unsigned integer
  //Ci diamo un limite. abbiamo creato un vettore (che è dinamico), e se leggesimo un file con 1mld di numeri avremmo un vettore che occupa 8*1mld di byte, quindi 8Gb!!! troppo. Metto limite.
  
  while((in>>x) && !toomuch) //in>>x è TRUE se sono riuscito a leggere il numero
    {
      count++;
      v.push_back(x);

      if(x<xmin) xmin=x;
      if(x>xmax) xmax=x;

      if(v.size()>=limit)
	{
	  cout << "Warning: dimensione del vettore > " << limit << endl;
	  toomuch = kTRUE;
	}
    }
  
  
  TFile file(histName, "recreate");
  TH1D *hist;
  hist = new TH1D("hist", "histogram", 100, xmin-1, xmax+1);

  for(UInt_t i=0; i<v.size(); i++){
    count++;
    hist->Fill(v[i]);
  }
  /*
  for()while((in>>x)){
    count++;
    hist.Fill(x);
  }*/
  cout<<"Dati letti: "<< count<< endl;
  in.close();
  hist->DrawCopy();
  file.Write(); //scarica tutti gli oggetti di quella directory
  file.Close();
}
