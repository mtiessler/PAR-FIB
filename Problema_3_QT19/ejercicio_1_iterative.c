/*
Write an OpenMP parallel version of the process_vector function using an iterative task decomposition
strategy trying to maximize load balancing.
*/

#include <stdlib.h>
#include <omp.h>
#define N 423423 // numero inventado xd.
typedef struct Node {
    float value;
    int footprint; // initialized to value 0
    struct Node *next;
} List;
float compute_sequential (struct Node *p) {
    float sum = 0.0;
    int end = 0;
    while (p != NULL && end == 0) 
    {
        //!!! debemos fijarnos porque dos threads pueden acceder si no al mismo p
        #pragma omp atomic
        int x = ++p->footprint;
        
        if (x == 1) // to ensure value is accumulated only once
            sum = sum + heavy_calculation(p->value);
        else
            end = 1;
        p = p-> next;
    }
    return sum;
}

float process_vector (List *v[N]) {
    float res = 0.0;
    #pragma omp taskloop grainsize(1) reduction(+:res) 
    for (int i = 0; i < N; i++)
        res = res + compute_sequential (v[i]);
        return res;
    }

void main() {
    List *v[N];
    // initialize footprint to value 0
    // ...
    #pragma omp parallel
    #pragma omp single
    float total = process_vector (v);
// ...
}