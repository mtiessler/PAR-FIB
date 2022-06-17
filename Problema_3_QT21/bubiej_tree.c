#include <omp.h>

#define N (1<<29) // A power of 2 value
typedef struct {
    float max; float min;
} min_max_t;

min_max_t find_min_max_it(float *v, int n) {
    #pragma omp parallel
    #pragma omp single
    {
        min_max_t min_max;
        float max_duration = v[1]-v[0];
        float min_duration = v[1]-v[0];
        unsigned int numth = omp_get_num_threads();
        #pragma omp taskloop grainsize(n/numth) reduction(max: max_duration) reduction(min: min_duration)
        for (int i=2; i<n; i++) {
            float d = v[i] - v[i-1];
            if (d > max_duration) max_duration = d;
            if (d < min_duration) min_duration = d;
    }
        min_max.max = max_duration;
        min_max.min = min_duration;
        return min_max;
    }
    
}

min_max_t find_min_max_rec(float *v, int n, int depth) {
    min_max_t min_max, min_max1, min_max2;
    if (n==2) {
        min_max.max = v[1]-v[0]; min_max.min = v[1]-v[0];
    } else {
        int n2 = n/2; // n is power of 2
        if(!omp_in_final())
        {
            #pragma omp task shared(min_max1) final(depth>= MAX_DEPTH)
            min_max1 = find_min_max_rec(v, n2, depth+1);
            #pragma omp task shared(min_max2) final(depth>= MAX_DEPTH)
            min_max2 = find_min_max_rec(v+n2, n2, depth+1);
                
        }
        else
        {
            min_max1 = find_min_max_rec(v, n2, depth+1);
            min_max2 = find_min_max_rec(v+n2, n2, depth+1);
        }
        #pragma omp taskwait
        if (min_max1.min < min_max2.min) min_max.min = min_max1.min;
        else min_max.min = min_max2.min;
        if (min_max1.max > min_max2.max) min_max.max = min_max1.max;
        else min_max.max = min_max2.max;
    }
    return min_max;
}

int main() {
    min_max_t min_max_V1, min_max_V2;
    int v1[N], v2[N];
    min_max_V1 = find_min_max_it(v1, N);
    #pragma omp parallel
    #pragma omp single
    min_max_V2 = find_min_max_rec(v2, N, 0);
}
