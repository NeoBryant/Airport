#include <limits.h> 
#include "Random.hpp" 
#include <cmath> 
#include <time.h>  
Random::Random() {
	seed = time(NULL)%INT_MAX;  
	//seed = 1;
    multiplier = 2743;
    add_on = 5923; 
}   
int Random::reseed() {
	  seed = seed*multiplier + add_on;  
	  return seed; 
}   
double Random::random_real() {  
	double max = INT_MAX + 1.0;  
	double temp = reseed();  
	if (temp < 0)temp = temp + max;  
	return temp/max; 
}   
int Random::poisson(double mean) {  
	double limit = exp(-mean);  
	double product = random_real();  
	int count = 0;  
	while(product > limit)  {   
		count++;   
		product *=random_real();  
	}  
	return count; 
} 
