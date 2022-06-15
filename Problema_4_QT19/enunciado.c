/*
Your parallel code should make sure that vectors are properly aligned in memory (i.e. each one starts
at the beginning of a cache line) in order to guarantee the proposed data decomposition; you can
assume that vector a is already aligned in memory. To simplify the problem, you can also assume that
the number of processors will always divide N perfectly. In particular you need to complete the lines
indicated and add extra code, if necessary. As indicated in the code, each integer element occupies 4
bytes of memory and a cache line is 64 bytes long.

*/

#include <omp.h>

#define N 1000
#define CACHE_LINE 64
#define INT_SIZE 4
struct SoA {
    int a[N];
    int dummy_ab[];// to complete
    int b[N];
    int dummy_bc[];// to complete
    int c[N];
};
struct SoA dataElements;
//...
#pragma omp parallel
{
    int lower = ...; // to complete
    int upper = ...; // to complete
    for (int i = lower, i < upper; i++)
        dataElements.c[i] = foo(i, dataElements.a[i], dataElements.b[i]);
}
// ...