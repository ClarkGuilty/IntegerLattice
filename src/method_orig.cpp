#include <algorithm>  // round()
#include </usr/include/complex.h>

#include "defines.h"
#include "init_conditions.h"
#include "iterators.h"
#include "poisson1D.h"
#include "fftw3.h"
#include "save.h"

using namespace std;


#ifndef METHOD_MEMSAVE

double lattice[NX][NVX]; // lattice (distribution function f)
double rho[NX];          // density
double acc[NX];          // acceleration


//Testing energy conservation. -J
double total_K = 0;
double total_U = 0;
double U0;



/** Original Integer Lattice Algorithm
 */
void run_simulation() {
  
  int shift;
  double x_phys, vx_phys;
  
  double deltaId;
  FILE *fileEnergy = fopen("./energyEvolution.dat","w+"); //File to print energy values
//   char *filename = (char*) malloc(200* sizeof(char));
  
  // Set the initial conditions
  for ( int x = 0; x < NX; x++ ) 
    for ( int vx = 0; vx < NVX; vx++ ) {
      
      x_phys  = -L + (1.0 * x + 0.5) * DX;
      vx_phys = -V + (1.0 * vx + 0.5) * DVX;

      lattice[x][vx] = get_init_f(x_phys,vx_phys);
    }
  save(lattice, 0);


  // Main Loop
  for ( int t = 0; t < NT; t++ )  {
    
      
    
     
//     sprintf(filename, "./m%ddensity%d.dat", NX,t);
//     FILE *density = fopen(filename,"w+"); //File to print the Fourier Coefficients.
    // get density
    for ( int x = 0; x < NX; x++ ) {
     rho[x] = 0.0;
     for ( int vx = 0; vx < NVX; vx++ )   rho[x] += lattice[x][vx];
     rho[x] *= DVX;
//      fprintf(density,"%f\n",rho[x]);
    }
    
    //Updating energy -J
    total_K = 0; 
    for ( int x = 0; x < NX; x++ ) {
    for ( int vx = 0; vx < NVX; vx++ ) {
      vx_phys = -V + (1.0 * vx + 0.5) * DVX;
	  total_K += 0.5*lattice[x][vx]*vx_phys*vx_phys;
	    }
    }
    total_K *= DX * DVX;
    // get acceleration
    poisson1D(rho, acc, total_U);
    fprintf(fileEnergy, "%f;%f\n", total_K, total_U-U0); //Print energy before updating the Lattice -J
    // kick
    for ( int x = 0; x < NX; x++ ) {
      shift = ( NVX - (int) round( DT * acc[x] / DVX ) ) % NVX;
      rotate( row_begin(lattice,x), row_entry(lattice,x,shift), row_end(lattice,x) );
    }
    
    // drift
    for ( int vx = 0; vx < NVX; vx++ ) {
      vx_phys = -V + (1.0 * vx + 0.5) * DVX;
      shift = ( NX - (int) round( DT * vx_phys / DX ) ) % NX;
      rotate( col_begin(lattice,vx), col_entry(lattice,vx,shift), col_end(lattice,vx) );
    }
    
    // Save output as HDF5
    if(((t+1) % OUTPUTEVERY) == 0)
      save(lattice, t+1);
    
    
    
  }
  fclose(fileEnergy);
}

#endif
