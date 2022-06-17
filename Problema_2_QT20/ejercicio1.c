/*
A task decomposition based on the use of explicit tasks which incurs low task management
overhead. 
The solution must minimize synchronization overheads and maximize spatial locality in the
accesses to vector
*/
#define CACHE_LINE_BYTES 64 // 64 bytes per cache line
#define HT_SIZE 1048576
#define NBINS 128
typedef struct {
    int value;
    elem * next;
} elem;
elem * HashTable[HT_SIZE], p; // 8 bytes per pointer
int Histogram[NBINS], bin, i, value; // 4 bytes per integer
// ...
for (i=0; i<HT_SIZE; i++) {
    p = HashTable[i];
    while ( p != NULL ) {
        value = p->value;
        bin = getbin(value, minval, maxval, NBINS);
        Histogram[bin]++;
        p = p->next;
    }
}