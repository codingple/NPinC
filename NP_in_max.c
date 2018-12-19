
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define MAX_CITYS 100
#define MAX_CITYNAME 10

extern double distance ();
extern void init_array();
extern double total_cost();

// structure of city
typedef struct city{
	char name[MAX_CITYNAME];
	double x;
	double y;
}city;


// for maximum depth
void recusive_NP2 ( city *cmpr, int reg, city *TER, int *iteration, city *cfr, int M, int city_num, double time_s){

	int i=0;
	int j=0;
	int k=0;
	int tmp=0;
	int *check_overlap;
	double dis;
	double time_e;
	city *sol;
	city pindex;

	// create array for making solution
	sol = (city*)malloc(sizeof(city) * city_num);

	// create array for checking overlap and init this array
	check_overlap = (int*)malloc(sizeof(int) * city_num);


	/******************** NP algorithm ********************/
	// number of iterations of all
	i = *iteration;
	i++;
	*iteration = i;
	printf("///// %d's iteration ////////////////////////////////////////\n\n", *iteration);


	// sampling and estimate the promising index
	dis = 0;
	init_array( check_overlap, city_num);

	printf("[MAXIMUMDEPTH]Index of region : %d\n\n", reg);



	for ( i=0; i<reg; i++)
		sol[i] = cmpr[i];


	// in the most promising region
	sol[city_num-1] = cfr[0];

	for( j=0; j<city_num; j++)
		printf("%s  ", sol[j].name);
	printf("  %f", total_cost( sol, city_num ));
	printf("\n");

	dis = total_cost( sol, city_num );
	pindex = cfr[0];


	// in the surrounding region
	// number of solutions
	for( i=0; i<(city_num - M); i++){

		// sampling
		// number of cities
		for( j=0; j<(city_num); j++){

			while (1){
				tmp = rand() % city_num;
				if ( check_overlap[tmp] != 1){
					sol[j] = TER[tmp];
					check_overlap[tmp] = 1;
					break;
				}
			}

			// check for excluding promising region
			if ( j == (reg-1) ){
				for( k=0; k<reg; k++){

					// if any element is different, break the iteration
					if( strcmp(sol[k].name, cmpr[k].name) != 0 )
						break;
					// when the surrounding region is same with the current most promising region
					if ( k == (reg-1) ){
						j = -1;
						init_array( check_overlap, city_num);
					}
				}
			}// end of check for excluding promising region

		}

		for( j=0; j<city_num; j++)
			printf("%s  ", sol[j].name);
		printf("  %f", total_cost( sol, city_num ));
		printf("\n");


		// backtracking
		if ( total_cost( sol, city_num ) <= dis ){
			printf("\n\n!!!!!!!!!!!!!!!!!!!!!!!\n");
			printf("       Backtracking");
			printf("\n!!!!!!!!!!!!!!!!!!!!!!!\n\n");

			free(sol);
			free(check_overlap);
			sol = NULL;
			check_overlap = NULL;
			return;
		}

		init_array( check_overlap, city_num);

	}


	printf("\nThe most promising Index : %s , Cost : %f\n\n", pindex.name, dis);
	printf("**************************************************\n\n\n");


	// end of algorithm
	cmpr[city_num-1] = pindex;
	printf("Finish---------------------------------------------\n");


	for( j=0; j<(city_num-1); j++)
		printf("%s  ", cmpr[j].name);
	printf("  %f", total_cost( cmpr, city_num ));
	printf("\n");
	printf("---------------------------------------------\n");

	// processing time
	time_e = clock();
	printf("%fÃÊ\n", (time_e - time_s) / 1000 );

	exit(1);





	/******************** NP algorithm ********************/



}