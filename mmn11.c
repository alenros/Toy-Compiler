#include <stdio.h>			
#include <math.h>			//used for cos(x);

#define ACCURACY pow(10,-6) 		//Accuracy of result. 10^(-accuracy)

#define ABSOLUTE(x) x>0?x:-x		//Absolute value macro.

#ifndef M_PI
#define M_PI 3.14159265358979323846	//define pie to max of long double if not defined
#endif

double my_cos(double);
double facto(int);
double modulus(double a, double b);

int main()
{
	double x;
	printf("Please enter the number to cos \n");
	scanf("%lf",&x);
	x=modulus(x,M_PI); //cosine defined for xER, repetitive over 2PI, in order to avoid calculating hugh numbers modulu is used.
	printf("my_cos says:%lf \n",my_cos(modulus(x,M_PI)));
	printf("math.h says:%lf \n",cos(x));

	return(0);
}

double my_cos(double x)			//returns the cosine of x using taylor's series
{
	double part=1;			//the next sum of the taylor series
	double thecos=1;		//the sum of parts

	for (int i=1; ABSOLUTE(part)>ACCURACY; i++)	
					//calculate sums till the sum falls below ACCURACY
	{				
		part=(pow(-1,i)*pow(x,2*i)/facto((2*i)));
		thecos+=part;
	}
return (thecos);
}

double modulus(double a, double b)	//modulu function for doubles. returns(a%b)
{
int result = ( a / b );			//calculating the int part
return a - ( result ) * b;
}

double facto(int n)			//return the factorial(n)
{
double sum=1;				//sums the factorial process. init:!1=1
for (;n>0;n--)				//calculate factorial from n to 1
	sum*=n;
return sum;
}
