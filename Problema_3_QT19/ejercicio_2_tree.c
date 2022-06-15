/*
Write an OpenMP parallel version of process_vector_rec function following a divide and conquer
task decomposition strategy and using the following sequential recursive version of process_vector
*/
#include <stdlib.h>
#include <omp.h> 

#define N 423423 // numero inventado xd.
#define MIN_SIZE 342 // numero inventado xd.
typedef struct Node {
    float value;
    int footprint; // initialized to value 0
    struct Node *next;
} List;

float process_vector_rec (List *v[N], int n) {
    float res = 0.0;
    if (n <= MIN_SIZE)
        for (int i = 0; i < n; i++)
            res = res + compute_sequential (v[i]);
    else {
        int n2 = n / 2;
        #pragma omp task shared(res1)
        float res1 = process_vector_rec (v, n2);
        #pragma omp task shared(res2)
        float res2 = process_vector_rec (v+n2, n-n2);
        #pragma omp taskwait
        res = res1 + res2;
    }
    return res;
}
int main() {
    List *v[N];
//...
    #pragma omp parallel
    #pragma omp single
    float total = process_vector_rec (v, N);
//...
}