/*
Finally, we have created a recursive divide–and–conquer sequential version of previous code. Write
an OpenMP parallel code for function rec_distribute and main program adding the necessary code and
directives to implement a recursive tree task decomposition. Your parallel code should include a cut–off mechanism
based on recursion depth, allowing parallel recursive calls for depths smaller than MAX_DEPTH. Your
parallel code should minimize the serialization that is introduced by synchronization, if any.

*/

#define N 1024*1024*1024
unsigned int S[N], D[N], C[256];
void rec_distribute(unsigned int *S, int n, unsigned int C[256], unsigned int *D) {
    unsigned int i, value;
    unsigned int n2 = n/2;
    if (n==1) {
        value = S[0]%256;
        D[C[value]] = S[0];
        C[value]++;
    } else {
        rec_distribute(S, n2, C, D);
        rec_distribute(&S[n2], n-n2, C, D);
    }
}

void main() {
// ...
    preprocessing(S, C, N); // initialization of S and C
// ...
    rec_distribute(S, N, C, D);
// ...
}