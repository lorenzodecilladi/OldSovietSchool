#ifndef Utils_h
#define Utils_h

namespace utils{

  Double_t rndmUniform(Double_t min, Double_t max){
    Double_t x = gRandom -> Rndm();
    return x*(max-min) + min;
  }

  Double_t rndmGauss(Double_t mean, Double_t sigma){
    Double_t x = gRandom -> Gaus(mean, sigma);
    return x;
  }
  
  
}

#endif

