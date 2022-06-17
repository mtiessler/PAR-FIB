/*
Let’s assume that the minimum and maximum values stored in any element within the hash table are known
and kept in variables minval and maxval, respectively. 
Routine getbin returns the bin where a value is classified according to the number of bins (NBINS) 
and minval and maxval.
At the end of the computation each position in the histogram, a bin (or container), 
has to count the number of values found in the elements within the hash table for 
which function getbin returns the same value.

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