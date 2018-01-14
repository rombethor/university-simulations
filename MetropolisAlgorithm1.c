/*
 ============================================================================
 Name        : MetropolisAlgorithm1.c
 Author      : 
 Version     :
 Copyright   : Copyright, Danesque Dynamics 2013
 Description : Hello World in C, Ansi-style
 ============================================================================

Monte Carlo of the Gaussian System.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define BETA 10
#define N 5

double P(double x, double y)
{
	return exp(-BETA*(pow(y,2)-pow(x,2)));
}

int metropolis_update(double *x)
{
	double r = (double)rand()/RAND_MAX;
	double a = 0.1;
	double y = (*x)-2*a*r+a;
	double p = P(*x, y);
	if(p>1 || r<p)
	{
		*x = y;
		return 1;
	}
	return 0;
}

int main(void) {

	double x=0;			//element of the Markov Chain
	int acceptance = 0;	//The count of accepted metro updates
	double x2tot, xtot; //running total of x^2 and x
	double x2av, xav2;  //<x^2> and <x>^2 respectively
	x2tot = 0; xtot=0;	//initialised

	srand(time(NULL));	//Seeding the random numbers as best as possible

	//Itterations of the metropolis algorithm
	int i, h;
	//Thermalisation Code - var h = half of remaining sweeps
	for( h = 0; h<2; h++)
	{
	   for( i = 0; i<N; i++)
	   {
	        metropolis_update(&x);
		x2tot += pow(x,2.0);
		xtot += x;
		printf("%lf \n",x);
	   }
        }

	//Calculate the averages
	x2av = x2tot/(double)N;			 //<x^2>
	xav2 = pow(xtot,2.0)/(double)N;	 //<x>^2

	printf("------------\n");
	printf("\n <x^2> : %lf\n <x>^2 : %lf \n",x2av, xav2);

	printf("\n <x^2> - <x>^2 = %lf\n", x2av-xav2); 

	return EXIT_SUCCESS;
}
