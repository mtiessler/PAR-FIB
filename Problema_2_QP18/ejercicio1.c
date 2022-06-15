/*
Write an OpenMP parallel implementation of function iter_distribute that follows a Geometic
Cyclic Data Decomposition of the Input vector S. You should maximize the parallelism that your solution offers
minimizing the serialization that is introduced by synchronization, if any.
*/
#include <omp.h>

#define N 1024*1024*1024
unsigned int S[N], D[N], C[256];
void iter_distribute(unsigned int *S, int n, unsigned int C[256], unsigned int *D) 
{
    omp_lock_t lock_c[N];
    //1) Inicializamos
    for(int i = 0; i < N; ++i)
        omp_init_lock(&lock_c[i]);
    

    unsigned int i, value;

    //2) Region paralela
    #pragma omp parallel private(i, value)
    {
        for (i=0; i<n; i++) {
            //2.1) Calculamos indice
            value = S[i]%256;
            //2.2) Bloqueamos con lock
            omp_set_lock(&lock_c[i]);
            //2.3) Realizamos tareas necesarias
            D[C[value]] = S[i];
            C[value]++;
            //2.4) Desbloqueamos
            omp_unset_lock(&lock_c[i]);
        }
    }

    for(int i = 0; i < N; ++i)
        omp_destroy_lock(&lock_c[i]);
    
    
}
void main() 
{
    //...
    preprocessing(S, C, N); // initialization of S and C
    //...

    iter_distribute(S, N, C, D);

    

}