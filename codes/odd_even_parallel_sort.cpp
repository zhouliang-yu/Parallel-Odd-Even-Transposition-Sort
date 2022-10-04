#include <mpi.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <chrono>


int merge_sort(int n, int* a){
    int b[n];
    domerge_sort(a, 0, n, b);
    return 0;
}

int domerge_sort(int *a, int start, int end, int *b){
    if ((end - start) <= 1) return 0;

    int mid = (end+start)/2;
    domerge_sort(a, start, mid, b);
    domerge_sort(a, mid,   end, b);
    merge(&(a[start]), mid-start, &(a[mid]), end-mid, &(b[start]));
    for (int i=start; i<end; i++)
        a[i] = b[i];

    return 0;

}


void printstat(int rank, int iter, char *txt, int *la, int n) {
    printf("[%d] %s iter %d: <", rank, txt, iter);
    for (int j=0; j<n-1; j++)
        printf("%6.3lf,",la[j]);
    printf("%6.3lf>\n", la[n-1]);
}

void MPI_Pairwise_Exchange(int localn, int *locala, int sendrank, int recvrank,
                           MPI_Comm comm) {

    /*
     * the sending rank just sends the data and waits for the results;
     * the receiving rank receives it, sorts the combined data, and returns
     * the correct half of the data.
     */
    int rank;
    int remote[localn];
    int all[2*localn];
    const int mergetag = 1;
    const int sortedtag = 2;

    MPI_Comm_rank(comm, &rank);
    if (rank == sendrank) {
        MPI_Send(locala, localn, MPI_INT, recvrank, mergetag, MPI_COMM_WORLD);
        MPI_Recv(locala, localn, MPI_INT, recvrank, sortedtag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else {
        MPI_Recv(remote, localn, MPI_INT, sendrank, mergetag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        merge(locala, localn, remote, localn, all);

        int theirstart = 0, mystart = localn;
        if (sendrank > rank) {
            theirstart = localn;
            mystart = 0;
        }
        MPI_Send(&(all[theirstart]), localn, MPI_INT, sendrank, sortedtag, MPI_COMM_WORLD);
        for (int i=mystart; i<mystart+localn; i++)
            locala[i-mystart] = all[i];
    }
}


int main (int argc, char **argv){

    MPI_Init(&argc, &argv); 

    int rank;
    int p;//number of processes
    comm = MPI_COMM_WORLD;
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

    /* TODO BEGIN
        Implement parallel odd even transposition sort
        Code in this block is not a necessary. 
        Replace it with your own code.
        Useful MPI documentation: https://rookiehpc.github.io/mpi/docs
    */

    int local_n = global_n / p; // number of elements allocated to each process
    int local_a[local_n]; // local array

    MPI_Scatter(elements, local_n, MPI_INT, local_a, local_n, MPI_INT, 0, comm); // distribute elements to each process
    merge_sort(local_n, local_a);
    
    int i;
    //odd-even part
    for (i = 1; i <= p; i++) {

        printstat(rank, i, "before", local_a, local_n);

        if ((i + rank) % 2 == 0) {  // means i and rank have same nature
            if (rank < p - 1) {
                MPI_Pairwise_Exchange(local_n, local_a, rank, rank + 1, comm);
            }
        } else if (p > 0) {
            MPI_Pairwise_Exchange(local_n , local_a, rank - 1, rank, comm);
        }

    }

    printstat(rank, i-1, "after", local_a, local_n);


    MPI_Gather(my_element, local_n, MPI_INT, sorted_elements, local_n, MPI_INT, 0, MPI_COMM_WORLD); // collect result from each process
    
    /* TODO END */

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


