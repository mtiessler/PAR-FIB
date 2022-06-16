#define N 1000
#define CACHE_LINE 64
#define INT_SIZE 4
struct AoS {
    int a;
    int b;
    int c;
};
struct AoS dataElements[N];
// ...
#pragma omp parallel
{
    int lower = //...; // to complete
    int upper = //...; // to complete
    int step = //...; // to complete
    for (int ii = lower; ii < upper; ii += //...) // to complete
        for (int i = ii; ...; ...) // to complete
            dataElements[i].c = foo(i, dataElements[i].a, dataElements[i].b);
}
// ...