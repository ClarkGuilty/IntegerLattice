#ifndef INIT_CONDITIONS_H
#define INIT_CONDITIONS_H
#include <math.h>
// double get_init_f(double x, double vx);

/** set the initial condition - speedier inline version */
inline double get_init_f(double x, double vx) {
  return exp( -vx * vx * 25.1327412287 ) * ( 1.0 + 0.03 * cos( M_PI * x / L / L ) ) * 2.82842712475;
}

#endif
