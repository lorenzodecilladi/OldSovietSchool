#if !defined(__CINT__) || defined(__MAKECINT__)

#include "Riostream.h"
#include "Particle.h"
#include "Vertex.h"
//#include "Transport.h"
//#include "MultipleScattering.h"
#include "Detector.h"
#include "Rootils.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TClonesArray.h"
#include "TStopwatch.h"

#endif

using namespace detector;



void simNoFile(UInt_t nEvents, bool aripc){

  TStopwatch watch;
  watch.Start(kTRUE);
  
  
  for(UInt_t event=0; event<nEvents; event++){ //loop over events

    if(event%1000 == 0){cout << "Processing EVENT " << event << endl;}
    if(aripc && event>=35000){
      cout << "\nEvent " << event << " of "<< nEvents <<": too much for ari's pc. No more events processed!!\n" << endl;
      break;
    }

    vert = new Vertex("gaus", 20, 5);
    UInt_t mult = vert->getMult();
    
    for(UInt_t i=0; i<mult; i++){ //loop over particles
      
      Particle *part = new Particle(vert->getPoint(), i);
      
      part->transport(rBP);           //tansport to Beam Pipe
      part->multipleScattering();     //MS in Beam Pipe
      part->transport(r1L);           //tansport to 1st Layer
      part->multipleScattering();     //MS in 1L
      part->transport(r2L);           //tansport to 2nd Layer
      
      delete part;
    } // end particles loop

    delete vert;
  }//end events loop
  
  watch.Stop();
  watch.Print();
}
