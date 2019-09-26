#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>
#include <mpi.h>

int main(){

struct timeval start, end;
int numOfIter = 1;

/* ver. 1: sequential access */

gettimeofday(&start, NULL);

printf("Hello World Serial\n");

gettimeofday(&end, NULL);

printf("v1: %lf us\n", (((end.tv_sec * 1000000 + end.tv_usec)	- (start.tv_sec * 1000000 + start.tv_usec)))*1.0/numOfIter);

/* end */

/* ver. 2: OpenMP */

gettimeofday(&start, NULL);

#pragma omp parallel 
{
	int core_id = omp_get_thread_num();
  int core_tot = omp_get_num_threads();

  printf("Hello World from core %d from %d\n", core_id, core_tot);
  #pragma omp barrier
}
gettimeofday(&end, NULL);

printf("v2: %lf us\n", (((end.tv_sec * 1000000 + end.tv_usec)	- (start.tv_sec * 1000000 + start.tv_usec)))*1.0/numOfIter);

/* end */

/* ver. 3: MPI */

MPI_Init(NULL, NULL);
		int world_size;
		MPI_Comm_size(MPI_COMM_WORLD, &world_size);

		int world_rank;
		MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

		char node_name[MPI_MAX_PROCESSOR_NAME];
		int name_len;
		MPI_Get_processor_name(node_name, &name_len);

gettimeofday(&start, NULL);

printf("Hello World from node %s process %d from %d\n", node_name, world_rank, world_size);

MPI_Barrier(MPI_COMM_WORLD);
gettimeofday(&end, NULL);

printf("v3: %lf us\n", (((end.tv_sec * 1000000 + end.tv_usec)	- (start.tv_sec * 1000000 + start.tv_usec)))*1.0/numOfIter);

/* end */
MPI_Finalize();
return 0;
}