#ifndef MultipleScattering_h
#define MultipleScattering_h

#include "Particle.h"


Direction multipleScattering(Particle part);

//Double_t matrix(Direction dir)[3][3];

Direction rotation(Direction dir0, Direction dir1);

 
#endif

