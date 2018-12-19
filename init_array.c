#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>


// initialize array for only check_overlap
void init_array( int *arr, int M){
	int i;

	for( i=0; i<M; i++)
		arr[i] = 0;
}