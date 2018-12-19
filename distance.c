#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define MAX_CITYNAME 10

typedef struct city{
	char name[MAX_CITYNAME];
	double x;
	double y;
}city;


// estimate distance among two cities
double distance (city a, city b){
	double result;
	double res_x;
	double res_y;

	res_x = ((a.x) - (b.x)) * ((a.x) - (b.x));
	res_y = ((a.y) - (b.y)) * ((a.y) - (b.y));

	result = sqrt( res_x + res_y );

	return (result);

}


// estimate total cost in a solution
double total_cost (city *arr, int M){
	double result = 0.0;
	int i = 0;

	while ( i != (M-1) ){
		result += distance ( arr[i], arr[i+1] );
		i++;
	}

	return ( result );
}