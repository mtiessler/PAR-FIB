#include <omp.h>
#define N 34243

#pragma omp parallel private(index, i)
{
    unsigned int myId = omp_get_thread_num();
    unsigned int num_th = omp_get_num_threads();
    for (int i = myId; i < N; i+=num_th)
    {
        index = hash(ToInsert[i], ST);
        omp_set_lock(&lockTable[index]);
        insert_elem(ToInsert[i], index);
        omp_unset_lock(&lockTable[index]);

    }
}