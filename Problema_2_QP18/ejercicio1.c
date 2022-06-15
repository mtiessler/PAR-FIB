/*
Write an OpenMP parallel implementation of function iter_distribute that follows a Geometic
Cyclic Data Decomposition of the Input vector S. You should maximize the parallelism that your solution offers
minimizing the serialization that is introduced by synchronization, if any.
*/

#define N 1024*1024*1024
unsigned int S[N], D[N], C[256];
void iter_distribute(unsigned int *S, int n, unsigned int C[256], unsigned int *D) 
{
    unsigned int i, value;
    for (i=0; i<n; i++) {
        value = S[i]%256;
        D[C[value]] = S[i];
        C[value]++;
    }
}
void main() 
{
    ...
    preprocessing(S, C, N); // initialization of S and C
    ...
    int lock_c[N];
    for(int i = 0; i < N; ++i)
        omp_init_lock(lock_c[i]);
    
    iter_distribute(S, N, C, D);
    
    for(int i = 0; i < N; ++i)
        omp_destroy_lock(lock_c[i]);
    

}