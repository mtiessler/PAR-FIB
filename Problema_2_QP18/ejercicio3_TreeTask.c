#include <omp.h>
#define N 1024*1024*1024
#define MAX_DEPTH 3

unsigned int S[N], D[N], C[256];
omp_lock_t lock_c[256];

void rec_distribute(unsigned int *S, int n, unsigned int C[256], unsigned int *D, int depth) {
    unsigned int i, value;
    unsigned int n2 = n/2;
    if (n==1) {
        value = S[0]%256;
        omp_set_lock(&lock_c[value]);
        D[C[value]] = S[0];
        C[value]++;
        omp_unset_lock(&lock_c[value]);
    } else {
        if(!omp_in_final())
        {
            #pragma omp task final (depth >= MAX_DEPTH)
            rec_distribute(S, n2, C, D, depth+1);
            #pragma omp task final (depth >= MAX_DEPTH)
            rec_distribute(&S[n2], n-n2, C, D, depth+1);
        }
        else 
        {
            rec_distribute(S, n2, C, D, depth+1);
            rec_distribute(&S[n2], n-n2, C, D, depth+1);
        }
        
    }
}

void main() {
// ...
    preprocessing(S, C, N); // initialization of S and C
//  init locks -- 
    #pragma omp parallel
    #pragma omp single
    rec_distribute(S, N, C, D, 0);
// destroy locks --
}