#include <stdlib.h>

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
        float res1 = process_vector_rec (v, n2);
        float res2 = process_vector_rec (v+n2, n-n2);
        res = res1 + res2;
    }
    return res;
}
int main() {
    List *v[N];
//...
    float total = process_vector_rec (v, N);
//...
}