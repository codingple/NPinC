
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
extern void recusive_NP2 ();

// structure of city
typedef struct city{
	char name[MAX_CITYNAME];
	double x;
	double y;
}city;


// argument ( The most promising region, current index of region, The entire feasible region,
// Number of iteration, current feasible region, The length of cfr, city_num, starting time)
void recusive_NP ( city *cmpr, int reg, city *TER, int *iteration, city *cfr, int M, int city_num, double time_s){

	int i;
	int j;
	int k;
	int tmp;
	int *check_overlap;
	int *check_overlap2;
	double dis;
	city *cmpr2; // current most promising region
	city *cfr2; // current feasible region in next iteration
	city *sol;
	city pindex;

	// create array for making solution
	sol = (city*)malloc(sizeof(city) * city_num);
	cmpr2 = (city*)malloc(sizeof(city) * city_num);

	// current feasible region
	cfr2 = (city*)malloc(sizeof(city) * (M-1));

	// create array for checking overlap and init this array
	check_overlap = (int*)malloc(sizeof(int) * M);
	check_overlap2 = (int*)malloc(sizeof(int) * city_num);


	while(1){

		/******************** NP algorithm ********************/
		// number of iterations of all
		i = *iteration;
		i++;
		*iteration = i;
		printf("///// %d's iteration ////////////////////////////////////////\n\n", *iteration);


		// sampling and estimate the promising index
		dis = 0;
		i=0;
		j=0;
		k=0;
		tmp=0;
		init_array( check_overlap, M);
		init_array( check_overlap2, M);

		printf("Index of region : %d\n\n", reg);


		for ( i=0; i<reg; i++)
			sol[i] = cmpr[i];


		// in the most promising region
		for( i=0; i<M; i++){
			sol[reg] = cfr[i];
			check_overlap[i] = 1;

			// sampling
			for( j=reg+1; j<city_num; j++){

				while (1){
					tmp = rand() % M;
					if ( check_overlap[tmp] != 1){
						sol[j] = cfr[tmp];
						check_overlap[tmp] = 1;
						break;
					}
				}
			}

			for( j=0; j<city_num; j++)
				printf("%s  ", sol[j].name);
			printf("  %f", total_cost( sol, city_num ));
			printf("\n");

			// estimate the promising index
			if ( total_cost( sol, city_num ) <= dis ){
				dis = total_cost( sol, city_num );
				pindex = cfr[i];
			}

			else if ( dis == 0 ){
				dis = total_cost( sol, city_num );
				pindex = cfr[i];
			}

			init_array( check_overlap, M);

		}


		// in the surrounding region
		// number of solutions
		for( i=0; i<(city_num - M); i++){

			// sampling
			// number of cities
			for( j=0; j<(city_num); j++){

				while (1){
					tmp = rand() % city_num;
					if ( check_overlap2[tmp] != 1){
						sol[j] = TER[tmp];
						check_overlap2[tmp] = 1;
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
							init_array( check_overlap2, city_num);
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
				free(cmpr2);
				free(cfr2);
				free(check_overlap);
				free(check_overlap2);

				sol = NULL;
				cmpr2 = NULL;
				cfr2 = NULL;
				check_overlap = NULL;
				check_overlap2 = NULL;

				return;
			}

			init_array( check_overlap2, city_num);

		}



		// Current feasible region in next iteration
		j = 0;
		for ( i=0; i<M; i++){
			if( strcmp(cfr[i].name, pindex.name) != 0 ){
				cfr2[j] = cfr[i];
				j++;
			}
		}

		// The most Promising region
		for ( i=0; i<reg; i++)
			cmpr2[i] = cmpr[i];
		cmpr2[reg] = pindex;

		printf("\nThe most promising Index : %s , Cost : %f\n\n", pindex.name, dis);
		printf("**************************************************\n\n\n");



		/******************** NP algorithm ********************/

		// Maximum depth
		if ( M-1 == 1 )
			recusive_NP2 (cmpr2, reg+1, TER, iteration, cfr2, M-1, city_num, time_s);

		else
			recusive_NP (cmpr2, reg+1, TER, iteration, cfr2, M-1, city_num, time_s);

	}//end of while(1)

}