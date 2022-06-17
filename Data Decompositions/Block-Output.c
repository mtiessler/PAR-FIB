#include <omp.h>


#pragma omp parallel private(index, i)
{
    unsigned int myId = omp_get_thread_num();
    unsigned int num_th = omp_get_num_threads();
    unsigned int BS = N/num_th;
    unsigned int lower = myId * BS; 
    unsigned int upper = lower + BS;
    
    if(myId == (num_th-1)) upper = N; 

    for(int i = 0; i < N; ++i)
    {
        index = hash(ToInsert[i], ST);
        if(index>= lower && index < upper)
        {
            insert_elem(ToInsert[i], index);
        }
    }


} 