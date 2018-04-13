#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define gamma 1
#define beta 1
#define b 1
#define a 1

double f(double x) {

	return -4*a*pow(x,3) + 2*b*x;
}

double dW(double dt) {

	double r = rand();  
	return sqrt(dt) * r;

}

double main() {

	int i; // passos de tempo
	double x= 1, t, dt=0.01;
	printf("%f\t%f\n", 0.0, x);
	srand(time(NULL));

	for(i=0;t<100;i++) {

		t = dt*i;
		x = (x + dt*f(x) + beta * dW(dt))/gamma;
		printf("%f\t%e\n", t+dt, x);

	}

}