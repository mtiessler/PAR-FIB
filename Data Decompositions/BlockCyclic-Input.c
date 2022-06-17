#include <omp.h>

#pragma omp parallel private(i, index)
{
    int myId = omp_get_thread_num();
    int num_th = omp_get_num_threads();
    int BS = MAX_ELEM/num_th;
    int lower = myId * BS; 
    int upper = lower + BS; 
    
    if(myId == num_th-1) upper = MAX_ELEM;

    for(int ii = lower; i < N; ii+=num_th*BS)
    {
        for(int i = ii; i < min(upper, N); i++)
        {
            index = hash(ToInsert[i], ST);
            omp_set_lock(&lockT[index]);
            insert_elem(ToInsert[i], index);
            omp_unset_lock(&lockT[index]);
        }
    }
}

