#include "Riostream.h"
#include "MultipleScattering.h"
#include "Detector.h"
#include "Rootils.h"
#include "Math.h"

Direction multipleScattering(Particle part){

  //SR lab
  //direction before scattering
  Direction dir0 = part.getDirection(); //get c1, c2, c3 before scattering

  //SR con apici
  //estrazione gaussiana theta e flat??? di phi
  Double_t phi1 = dir0.phi();
  //Double_t phi1 = rootils::rndmUniform(0., 2*math::pi);
  Double_t theta1 = rootils::rndmGaus(0., detector::thetaSpace);

  //otteniamo direzione dopo scattering nel SR con apici (sempre dei c)
  //riportiamo nel SR del laboratorio (sempre i coefficienti c)

  //  Double_t rotMatrix[3][3] = matrix(dir0);
  Direction dir1 = Direction(theta1, phi1);

  return rotation(dir0, dir1);
}


Direction rotation(Direction dir0, Direction dir1){ //prende la direzione iniziale nel SR del lab e quella dopo lo scattering nel SR della particella
  
  Double_t mat[3][3];
  Double_t _theta = dir0.theta();
  Double_t _phi = dir0.phi();
  
  mat[0][0] = -TMath::Sin(_phi);
  mat[0][1] = -TMath::Cos(_phi)*TMath::Cos(_theta);
  mat[0][2] =  TMath::Cos(_phi)*TMath::Sin(_theta);
  mat[1][0] =  TMath::Cos(_phi);
  mat[1][1] = -TMath::Sin(_phi)*TMath::Cos(_theta);
  mat[1][2] =  TMath::Sin(_phi)*TMath::Sin(_theta);
  mat[2][0] =  0.;
  mat[2][1] =  TMath::Sin(_theta);
  mat[2][2] =  TMath::Cos(_theta);

  
  Double_t cP[3] = {dir1.c1(), dir1.c2(), dir1.c3()}; //P particle S.R.

  Double_t c1L = 0, c2L = 0, c3L = 0.; //c1, c2, c3 dopo lo scattering nel SR del laboratorio
  
  for(int i=0; i<3; i++){
    c1L += mat[0][i]*cP[i];
    c2L += mat[1][i]*cP[i];
    c3L += mat[2][i]*cP[i];
  }
  
  return Direction(c1L, c2L, c3L);
}

