// Block
int thread_to_be_assigned(int row, int num_rows, int num_procs)
{
    unsigned int BS = num_rows/num_procs;
    return row/BS;

}

// Cyclic
int thread_to_be_assigned(int row, int num_rows, int num_procs) {
return (row % num_procs);
}

// Block - Cyclic
int thread_to_be_assigned(int row, int num_rows, int num_procs)
{
    unsigned int BS = num_rows/num_procs;
    return (row/BS)%num_procs;

}