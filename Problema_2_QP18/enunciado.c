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
    iter_distribute(S, N, C, D);
    ...
}