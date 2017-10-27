#include "Riostream.h"
#include "TBranch.h"
#include "TClonesArray.h"
#include "TFile.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TTree.h"

#include "Varie.h"

void Albero(){
  // File di output per i dati generati dal Monte Carlo e TTree
  TFile fileoutput("AlberoDati.root", "RECREATE");
  TTree *alberello = new TTree("quercia", "Tree di Racca e Sauda");

  // Hit sul primo rivelatore
  TClonesArray *PuntatoreRiv1 = new TClonesArray("Punto", 100);
  TClonesArray &IndPuntRiv1 = *PuntatoreRiv1;
  
  // Hit sul secondo rivelatore
  TClonesArray *PuntatoreRiv2 = new TClonesArray("Punto", 100);
  TClonesArray &IndPuntRiv2 = *PuntatoreRiv2;

  // Vertice della collisione
  
}
