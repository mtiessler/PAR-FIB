/*
Write an alternative OpenMP parallel implementation of function iter_distribute that follows
a Geometric Block Data Decomposition of the Output vector C. Consequently, each thread uses and updates
only a part of C, and then, will only write to a part of D, depending of the part of C the thread works with.
Your parallel implementation has to ensure a proper load balance of the data distribution (i.e. no more than 1
element of difference) and maximize the parallelism that your solution offers minimizing the serialization that
is introduced by synchronization, if any.
*/

#include <omp.h>
#define N 1024*1024*1024
unsigned int S[N], D[N], C[256];

void iter_distribute(unsigned int *S, int n, unsigned int C[256], unsigned int *D) 
{
    unsigned int i, value;
    #pragma omp parallel private(i, value)
    {
        //1) myId & num_threads
        unsigned int myId = omp_get_thread_num();
        unsigned int num_threads = omp_get_num_threads();
        //2) Calcular BS, Lower & upper
        unsigned int BS = N/num_threads;
        unsigned int lower = myId * BS;
        unsigned int upper = lower + BS; 
        if (myId == num_threads - 1) 
            upper = N; 
        // al ser Output iteramos por todo y tan solo vamos comprobando si VALUE (indice) esta en el bloque
        for (i=0; i<n; i++) {
            value = S[i]%256;
            if((value >= lower) && (value < upper))
            {
                D[C[value]] = S[i];
                C[value]++;
            }
            
        }
    }
    
}
void main() 
{
    // ...
    preprocessing(S, C, N); // initialization of S and C
    // ...
    iter_distribute(S, N, C, D);
    // ...
}