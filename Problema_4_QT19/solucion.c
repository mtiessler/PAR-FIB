/*
Cada vector tiene N ints.
Cada int ocupa 4B. 
Un vector ocupa N * 4B = 4000B.
Una linea de cache es de 64B.

Un vector ocupa por lo tanto: 
    4000B/64B = 62.5 Lineas de cache

Para que cada vector empiece en una línea distinta necesitamos 0.5 de padding = 32B = 8 ints

*/


#include <omp.h>

#define N 1000
#define CACHE_LINE 64
#define INT_SIZE 4
struct SoA {
    int a[N];
    int dummy_ab[8];// to complete
    int b[N];
    int dummy_bc[8];// to complete
    int c[N];
};
struct SoA dataElements;
//...
#pragma omp parallel
{
    unsigned int myId = omp_get_thread_num();
    unsigned int num_th = omp_get_num_threads();
    unsigned int BS = N/num_th;
    int lower = BS*myId; // to complete
    int upper = lower+BS; // to complete
    for (int i = lower, i < upper; i++)
        dataElements.c[i] = foo(i, dataElements.a[i], dataElements.b[i]);
}