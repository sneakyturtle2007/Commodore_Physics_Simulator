#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define GRAV_CONST 6.6743E-11

typedef struct{
  double x; // Meters
  double y; // Meters
  double x_vel; // Meters/Second
  double y_vel; // Meters/Second
  double mass; // Kilograms
  int radius; // Meters
}Body;

typedef struct{
  int height;
  int width;
}Display;

#endif