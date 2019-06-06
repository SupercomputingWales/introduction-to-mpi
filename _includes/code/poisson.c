/* a serial code for Poisson equation */

/* contact seyong.kim81@gmail.com for comments and questions */


#include <stdio.h>
#include <math.h>

#define MAX 100


double poisson_step( 
    float u[MAX+2][MAX+2],
    float unew[MAX+2][MAX+2],
    float rho[MAX+2][MAX+2],
    float hsq
  ){
  double unorm;

  // Calculate one timestep
  for( int j=1; j <= MAX; j++){
    for( int i=1; i <= MAX; i++){
        float difference = u[i-1][j] + u[i+1][j] + u[i][j-1] + u[i][j+1];
	    unew[i][j] =0.25*( difference - hsq*rho[i][j] );
    }
  }

  // Find the difference compared to the previous time step
  unorm = 0.0;
  for( int j = 1;j <= MAX; j++){
    for( int i = 1;i <= MAX; i++){
      float diff = unew[i][j]-u[i][j];
      unorm +=diff*diff;
    }
  }

  // Overwrite u with the new field
  for( int j = 1;j <= MAX;j++){
    for( int i = 1;i <= MAX;i++){
      u[i][j] = unew[i][j];
    }
  }

  return unorm;
}



int main(int argc, char** argv) {

  int i, j;
  float u[MAX+2][MAX+2], unew[MAX+2][MAX+2], rho[MAX+2][MAX+2];
  float h, hsq;
  double unorm, residual;

  /* Set up parameters */
  h = 0.1;
  residual = 1e-5;

  /* Run Setup */
  hsq = h*h;

  // Initialise the u and rho field to 0 
  for(j=0; j <= MAX+1; j++){
    for(i=0; i <= MAX+1; i++) {
      u[j][i] = 0.0;
      rho[j][i] = 0.0;
    }
  }
  
  // Create a start configuration with the field
  // u=10 at x=0
  for(j = 0;j <= MAX+1; j++)
    u[j][0] = 10.0;


  // Run iterations until the field reaches an equilibrium
  do {
    
    unorm = poisson_step( u, unew, rho, hsq );

  } while( sqrt(unorm) > sqrt(residual) );

  printf("Run completed with residue %g\n", unorm);

}