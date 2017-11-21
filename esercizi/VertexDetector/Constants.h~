



//forse conviene creare classe/struct/namespace con tutte le costanti

Double_t sZv = 5.33; //cm    sigma Z vertex
Double_t sXv = 0.01; //cm    sigma X vertex
Double_t sYv = 0.01; //cm    sigma Y vertex

Double_t rBP = 3.;   //cm    R Beam Pipe
Double_t tBP = 0.08; //cm    thickness Beam Pipe

Double_t r1L = 4.;   //cm    R 1st Layer
Double_t t1L = 0.02; //cm    thickness 1st Layer

Double_t r2L = 7.;   //cm    R 2nd Layer
Double_t t2L = 0.02; //cm    thickness 2nd Layer

Double_t length = 27.; //cm

Double_t etaMin = -2.; // pseudorapidity acceptance  
Double_t etaMax = 2.;

Double_t sZhit = 0.012; //cm  smearing Z direction  (120 #mum)
Double_t sRhit = 0.003; //cm  smearing r#phi direction (30 #mum)



//forse conviene creare classi con generatori numeri casuali (si chiama gRandom solo lì)

/*
Int_t rndmInt(Int_t min = 0, Int_t max = 50){
  Double_t x = gRandom -> Rndm();
  x = x*(max-min) + min;
  return (Int_t)x; //in realtà così non mi da quasi mai 50!!
} //forse melio fare cast quando lo uso, non a prescindere, altrimenti 1000 funzioni

Double_t rndmDouble(Double_t min, Double_t max){
  Double_t x = gRandom -> Rndm();
  return x*(max-min) + min;
}

*/

Double_t rndmUniform(Double_t min, Double_t max){
  Double_t x = gRandom -> Rndm();
  return x*(max-min) + min;
}

Double_t rndmGauss(Double_t mean, Double_t sigma){
  Double_t x = gRandom -> Gaus(mean, sigma);
  return x;
}
