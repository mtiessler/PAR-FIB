#include <omp.h>

#pragma omp parallel private(i, index)
{
    int myId = omp_get_thread_num();
    int num_th = omp_get_num_threads();
    int BS = MAX_ELEM/num_th;
    int lower = myId * BS; 
    int upper = lower + BS; 
    
    if(myId == num_th-1) upper = MAX_ELEM;

    for(int i = 0; i < N; ++i)
    {
        index = hash(ToInsert[i], ST);
        if(((index/BS)%numprocs) == myId)
            insert_elem(ToInsert[i], index);
    }

}