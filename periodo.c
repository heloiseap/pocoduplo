#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define gamma 1
#define beta 1
#define b 1
#define a 1/4

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

	int i, n=0;
	double x1=0, x2, t=0, dt=0.01, t1=0,T;
	srand(time(NULL));

	for(i=0;t<100;i++) {

		x2 = (x1 + dt*f(x1) + beta * dW(dt))/gamma;
		t = dt*i;
		
    if(x1<0 && x2>0 || x1>0 && x2<0) { //se tiver mudança de sinal
      
      n++;
      T = t - t1; //tempo atual menos o tempo da antiga mudança de sinal
      
      printf("%d\t%f\n", n, T);

      t1=t; //faz com que o tempo atual seja o começo do novo intervalo de contagem de periodos

    }

    x1=x2;

	}

}