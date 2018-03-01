#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include <time.h>
#include <sys/time.h>
#define BILLION  1000000000L;

int main() {
    int dims = 2;
    int n = 500000;
    int m = 200;
    int k = 5;
    srand(10811);
    
    // generate pseudo-random reference points
    double *ref_points[n];
    for (int i=0; i<n; i++)
        ref_points[i] = (double *)malloc(dims * sizeof(double));
    
    for(int i=0; i<n; i++)
        for(int j=0; j<dims; j++)
            ref_points[i][j] = 1.1*rand()*5000/RAND_MAX;
    
    // generate pseudo-random query points
    double *query_points[m];
    for (int i=0; i<m; i++)
        query_points[i] = (double *)malloc(dims * sizeof(double));
    
    for(int i=0; i<m; i++)
        for(int j=0; j<dims; j++)
            query_points[i][j] = 1.1*rand()*5000/RAND_MAX;
    
    // generate pseudo-random reference point outcomes
    double *outcome_points;
    outcome_points = (double*)malloc(sizeof(double)*n);
    
    for(int i=0; i<n; i++)
        outcome_points[i] = 1.1*rand()*500/RAND_MAX;
    
    struct timespec start, mid, end;
    //start timer;
    if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
        perror( "clock gettime" );
        exit( EXIT_FAILURE );
    }

    
    // calculate all distances between reference points and query points
    double **distances = many_to_many_distances(query_points, ref_points, m, n, dims);
    
    // stop timer
    if( clock_gettime( CLOCK_REALTIME, &mid) == -1 ) {
        perror( "clock gettime" );
        exit( EXIT_FAILURE );
    }
    double accum1=(mid.tv_sec-start.tv_sec)+(double)(mid.tv_nsec-start.tv_nsec)/BILLION;
    printf("Distance time: %lf s\n", accum1);
    
    //for (int i=0; i<4; i++)
    //    for (int j=0; j<2; j++)
    //        printf("distance %d %d %f \n", j, i, distances[j][i]);
    
    //for (int i=0; i<4; i++)
    //    printf("outcomes %d %f \n", i, outcome_points[i]);
    
    // calculate mean outcome of k nearest neighbours
    double* mean_outcome;
    mean_outcome = (double*)malloc(sizeof(double)*m);
    
    int* ranks;
    ranks = (int*)malloc(sizeof(double)*n);
    
    for (int i=0; i<m; i++){
        mean_outcome[i] = 0.0;
        ranks = quickargsort(distances[i], n, 2);    
        for (int j=0; j<k; j++)
            mean_outcome[i] += outcome_points[ranks[j]];
        
        mean_outcome[i] /= (double)k;
    }
    
    // stop timer
    if( clock_gettime( CLOCK_REALTIME, &end) == -1 ) {
        perror( "clock gettime" );
        exit( EXIT_FAILURE );
    }
    double accum2=(end.tv_sec-mid.tv_sec)+(double)(end.tv_nsec-mid.tv_nsec)/BILLION;
    printf("Sort time: %lf s\n", accum2);
    

    
    
    //print results
    //for (int i = 0; i<m; i++)
    //    printf("mean outcomes %f \n", mean_outcome[i]);
    
    //test_many_to_many_distances();
    //test_quickargsort();
    
    return 0;
}