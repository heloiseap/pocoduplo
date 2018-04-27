#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define gamma 1
#define beta 1
#define b 1.0/2
#define a 1.0/4

#define FRANDOM (rand()/(RAND_MAX+1.0))  

double f(double x) {

	return -4*a*pow(x,3) + 2*b*x;
}

double ngaussian(void){  //Numerical Recipes 
  static int iset=0;
  static double gset;
  double fac,r,v1,v2;
  
  if (iset==0) {
    do {
      v1=2.0*FRANDOM-1.0;
      v2=2.0*FRANDOM-1.0;
      r=v1*v1+v2*v2;
    } 
    while (r>=1 || r==0.0);
    fac=sqrt(-2.0*log(r)/r);
    gset=v1*fac;
    iset=1;
    return v2*fac;
  }
  else {
    iset=0;
    return gset;
  }
}


double dW(double dt) {

	double r = ngaussian();  
	return sqrt(dt) * r;

}

double main() {

	int i;
	double x= 0, t=0, dt=0.0/gamma;
	double tp = t/gamma; //absorvendo gamma no t
	printf("%f\t%f\n", 0.0, x);
	srand(time(NULL));

	for(i=0;tp<100;i++) {

		x = (x + dt*f(x) + beta * dW(dt))/gamma;
		tp = dt*i;
		printf("%f\t%e\n", tp+dt, x);

	}

}