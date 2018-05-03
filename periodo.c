#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define gamma 1
#define beta sqrt(2*Temp)
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

	int i,h=0,n=100;
	srand(time(NULL));
  double T=0,Tq=0, Temp;

  for(Temp=0.05;Temp<=1.5;Temp+=0.01) {

    double T=0, Tq=0;
  
  
    for(h=1;h<=n;h++) { 

      double x1=-1, x2, t=0, dt=0.01;

    	for(i=0;;i++) { //n limitado pra sempre fazer 100 historias

    		x2 = (x1 + dt*f(x1) + beta * dW(dt))/gamma;
    		t = dt*i/gamma;
    		
        if(x1*x2<0) { //se tiver mudança de sinal
          
          T += t; //tempo atual menos o tempo da antiga mudança de sinal
          Tq += pow(t,2);
          break;
        }

        x1=x2;

    	}


    }

    double erro = sqrt((Tq/n -pow(T/n,2))/n);

    printf("%f\t%f\t%f\n", Temp, T/n, erro);
  
  }
}

