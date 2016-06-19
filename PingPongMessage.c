#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mpi.h"
#include "stdafx.h"

int main(int argc, char* argv[])
{
	int rank, size;
	int lowerBound = 0;
	int upperBound = 512;
	int step = 32;
	char* message;
	char* recv;
	clock_t tmp, start_time, end_time;
	float timer_overhead, total_time;
	float communication_time[100];

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

    for (int i = lowerBound; i <= upperBound; i += step)
    {
        if (rank == 0)
		{ 
			message = (char*) malloc(i);
			recv = (char*

			// Start the clock
			tmp = clock();
			start_time = clock();

			// Send Messages
			MPI_Send(&message, i, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
			MPI_Recv(&message, i, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			free (message);

			// Calculate and display time for message passing
			end_time = clock();
			timer_overhead = (((float)start_time - (float)tmp) / 1000000.0F ) * 1000;
			timer_overhead = start_time - tmp ;
			total_time = (((float)end_time - (float)start_time) / 1000000.0F ) * 1000 - timer_overhead ;
			communication_time[i] = total_time / 2 ;
			printf("Run with %d byte message - %0.5f milliseconds", (i * step + lowerBound), communication_time);
		} 
		else if (rank == 1) 
		{
			MPI_Recv(&message, i, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Send(&message, i, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
		}
	}

	MPI_Finalize();
	return 0;
}
