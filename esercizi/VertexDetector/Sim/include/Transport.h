#ifndef Transport_h
#define Transport_h

#include "Particle.h"


Point transport(Particle part, Double_t R);

Double_t time(Particle part, Double_t R);

//Parametri dell'eq parametrica della retta-traiettoria
Double_t c1(Direction dir);
Double_t c2(Direction dir);
Double_t c3(Direction dir);
 
#endif

