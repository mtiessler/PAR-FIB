/*

Each element of vector dataElements occupies 12 bytes (3 integer elements).
 
To avoid false sharing we should assign to each processor a number of consecutive elements that fit in a number
of complete cache lines. 

In this case this is mcm(12, 64) = 192 (minimum common multiple), which
corresponds to 16 elements.


Complete the code above in order to implement 
a geometric block-cyclic data decomposition.

*/

#include <omp.h>
#define N 1000
#define CACHE_LINE 64
#define INT_SIZE 4
struct AoS {
    int a;
    int b;
    int c;
};
struct AoS dataElements[N];
// ...
#pragma omp parallel
{
    unsigned int myId = omp_get_thread_num();
    unsigned int num_procs = omp_get_num_threads();
    int BS = 16; //la bubi es una crack <3<3<3
    int lower = BS*myId;  //<3<3
    int upper = N;
    int step = num_procs*BS;
    for (int ii = lower; ii < upper; ii += step) // to complete
        for (int i = ii; i  < min(ii+BS, N); i++) // to complete
            dataElements[i].c = foo(i, dataElements[i].a, dataElements[i].b);
}
// ...