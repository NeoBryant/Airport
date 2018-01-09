#ifndef _Random
#define _Random

#include <limits.h> 
#include <cmath> 
#include <time.h>  
class Random
{
	int seed;  
    int multiplier;
    int add_on; 
public:
	Random();
	int reseed();
	double random_real(void);
	int poisson(double mean);
};

#endif