#include <omp.h>
#define N 34243

#pragma omp parallel private(index, i)
{
    unsigned int myId = omp_get_thread_num();
    unsigned int num_th = omp_get_num_threads();
    
    for(int i = 0; i < N; ++i)
    {
        index = hash(ToInsert[i], ST);
        if((index%num_th) == myId)
        {
            insert_elem(ToInsert[i], index);
        }
    }

}