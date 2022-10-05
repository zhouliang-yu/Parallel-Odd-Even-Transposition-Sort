#include <mpi.h>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <chrono>


int Get_Partner(int my_rank, int phase) {
	if (phase % 2 == 0) {
		if (my_rank % 2 == 0) {
			return my_rank - 1;
		}
		else {
			return my_rank + 1;
		}
	}
	else {
		if (my_rank % 2 == 0) {
			return my_rank + 1;
		}
		else {
			return my_rank - 1;
		}
	}
}


void Merge_Low(int A[], int B[], int local_n) {
	int* a = new int[local_n];		
	int p_a = 0, p_b = 0, i = 0;	
	while (i < local_n) {
		if (A[p_a] < B[p_b]) {
			a[i++] = A[p_a++];
		}
		else {
			a[i++] = B[p_b++];
		}
	}
	for (i = 0; i < local_n; i++) {
		A[i] = a[i];
	}
	delete[] a;
}
 
void Merge_High(int A[], int B[], int local_n) {
	int p_a = local_n - 1, p_b = local_n - 1, i = local_n - 1;
	int* a = new int[local_n];
	while (i >= 0) {
		if (A[p_a] > B[p_b]) {
			a[i--] = A[p_a--];
		}
		else {
			a[i--] = B[p_b--];
		}
	}
	for (i = 0; i < local_n; i++) {
		A[i] = a[i];
	}
	delete[] a;
}


int main (int argc, char **argv){

    MPI_Init(&argc, &argv); 

    int rank;
    int p;//number of processes
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &p); // get the number of processes
    MPI_Comm_rank(comm, &rank);  //get the rank of the current processes

    int global_n; // number of elements to be sorted
    
    global_n = atoi(argv[1]); // convert command line argument to global_n

    int elements[global_n]; // store elements
    int sorted_elements[global_n]; // store sorted elements
	
    if (rank == 0) { // read inputs from file (master process)
        std::ifstream input(argv[2]);
        int element;
        int i = 0;
        while (input >> element) {
            elements[i] = element;
            i++;
        }
        std::cout << "actual number of elements:" << i << std::endl;
    }

	
    std::chrono::high_resolution_clock::time_point t1;
    std::chrono::high_resolution_clock::time_point t2;
    std::chrono::duration<double> time_span;
    if (rank == 0){ 
        t1 = std::chrono::high_resolution_clock::now(); // record time
    }

    //show if 20-dim sample
    if (global_n == 20 && rank == 0){
        std::cout << "the input sample is:";
        for (int i = 0; i < 20; i++){
            std::cout << elements[i];
            std::cout << " "; 
        }
        std::cout << std::endl;
    }

    /* TODO BEGIN
        Implement parallel odd even transposition sort
        Code in this block is not a necessary. 
        Replace it with your own code.
        Useful MPI documentation: https://rookiehpc.github.io/mpi/docs
    */

    int local_n = global_n / p; // number of elements allocated to each process
    int local_a[local_n]; // local array

    MPI_Scatter(elements, local_n, MPI_INT, local_a, local_n, MPI_INT, 0, comm); // distribute elements to each process
    
    std::sort(local_a, local_a + local_n);
    
    int* new_data = new int[local_n];
    for (int i = 0; i < p; i++) {
		// get the pid of the process to swap data with
		int partner = Get_Partner(rank, i);
		// valid pid
		if (partner != -1 && partner != p) {
			// swap data
			MPI_Sendrecv(local_a, local_n, MPI_INT, partner, 0, new_data, local_n, MPI_INT, partner, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			if (rank > partner) {
				Merge_High(local_a, new_data, local_n);
			}
			else {
				Merge_Low(local_a, new_data, local_n);
			}
		}
	}
 


    MPI_Gather(local_a, local_n, MPI_INT, sorted_elements, local_n, MPI_INT, 0, MPI_COMM_WORLD); // collect result from each process
    
    /* TODO END */

    //show if 20-dim sample
    if (global_n == 20 && rank == 0){
        std::cout << "the outout after sort is:";
        for (int i = 0; i < 20; i++){
            std::cout << sorted_elements[i];
            std::cout << " "; 
        }
        std::cout << std::endl;
    }

    if (rank == 0){ // record time (only executed in master process)
        t2 = std::chrono::high_resolution_clock::now();  
        time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
        std::cout << "Student ID: " << "120040077" << std::endl; // replace it with your student id
        std::cout << "Name: " << "Zhouliang_YU" << std::endl; // replace it with your name
        std::cout << "Assignment 1" << std::endl;
        std::cout << "Run Time: " << time_span.count() << " seconds" << std::endl;
        std::cout << "Input Size: " << global_n << std::endl;
        std::cout << "Process Number: " << p << std::endl; 
    }

    if (rank == 0){ // write result to file (only executed in master process)
        std::ofstream output(argv[2]+std::string(".parallel.out"), std::ios_base::out);
        for (int i = 0; i < global_n; i++) {
            output << sorted_elements[i] << std::endl;
        }
    }
    
    MPI_Finalize();
    
    return 0;
}

