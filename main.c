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
void recusive_NP ();

// structure of city
typedef struct city{
	char name[MAX_CITYNAME];
	double x;
	double y;
}city;

int main (void){

	FILE *file;
	city TER[MAX_CITYS]; // The Entire Region
	int i=0;
	int j=0;
	int iteration=0;
	int reg=0; // index of current changing city
	int city_num=0; // Number of the citys
	int M=0;
	int tmp=0;
	int *check_overlap;
	double time_s; // check the processing time
	double dis;
	char c[MAX_CITYNAME];
	city start; // a starting city
	city *cmpr; // current most promising region
	city *cfr; // current feasible region
	city *cfr2; // current feasible region in next iteration
	city *sol;
	city pindex;


	// start timer
	time_s = clock();

	// for random sampling
	srand(time(NULL));


	// open file
	printf("Reading the file...\n");
	file = fopen("citys.txt", "r");

	if ( file == NULL ){
		printf("error\n");
		return 0;
	}


	// set starting city
	// first line of the file is a starting city
	fscanf(file, "%s", start.name);

	fscanf(file, "%s", c);
	start.x = atof(c);

	fscanf(file, "%s", c);
	start.y = atof(c);


	// store citys from text
	while ( !feof( file ) ){
		fscanf(file, "%s", TER[i].name);

		fscanf(file, "%s", c);
		TER[i].x = atof(c);

		fscanf(file, "%s", c);
		TER[i].y = atof(c);

		i++;
	}
	city_num = i;
	M = city_num;

	fclose(file);
	printf("finish\n\n");


	// check citys
	printf("Starting city ----------\n");
	printf("%s  %f  %f\n", start.name, start.x, start.y);
	printf("----------***\n\n");

	printf("Citys ----------\n");
	i = 0;
	while ( i != M){
		printf("%s  %f  %f\n", TER[i].name, TER[i].x, TER[i].y);
		i++;
	}
	printf("----------***\n\n");


	// create array for making solution
	sol = (city*)malloc(sizeof(city) * city_num);
	cmpr = (city*)malloc(sizeof(city) * M);

	// current feasible region
	cfr = (city*)malloc(sizeof(city) * M);
	cfr2 = (city*)malloc(sizeof(city) * (M-1));

	for( i=0; i<M; i++)
		cfr[i] = TER[i];


	while ( 1 ){

		/******************** NP algorithm ********************/
		iteration++; // number of iterations of all
		printf("///// %d's iteration ////////////////////////////////////////\n\n", iteration);


		// sampling and estimate the promising index
		dis = 0;
		// create array for checking overlap and init this array
		check_overlap = (int*)malloc(sizeof(int) * M);
		init_array( check_overlap, M);

		printf("Index of region : %d\n\n", reg);

		for( i=0; i<M; i++){
			sol[reg] = cfr[i];
			check_overlap[i] = 1;

			// sampling
			for( j=reg+1; j<M; j++){

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

		// Current feasible region in next iteration
		j = 0;
		for ( i=0; i<M; i++){
			if( strcmp(cfr[i].name, pindex.name) != 0 ){
				cfr2[j] = cfr[i];
				j++;
			}
		}

		// The most Promising region
		cmpr[reg] = pindex;

		printf("\nThe most promising Index : %s , Cost : %f\n\n", pindex.name, dis);
		printf("**************************************************\n\n\n");


		/******************** NP algorithm ********************/

		recusive_NP (cmpr, reg+1, TER, &iteration, cfr2, M-1, city_num, time_s);

	}//end of while(1)

	return 0;
}