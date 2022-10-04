# Parallel Odd-Even Transposition Sort

## Introduction

This project is applying an odd even transposition sorting algorithm with CUHKSZ cluster to break down a computational problem into several parallel tasks of a distributed system. According to the test results, the algorithm can apply the distributed memory of multiple nodes to sort the large dataset with the medium performance for parallel speed computing to solve the real world complex parallel and distributed computing system. In this case we use the MPI the communication and synchronization between the processors. The experiment is tested upon 8 nodes with <font Color=Red>XXXX </font>cores for various generated dataset. This work also shows experimental and theoretical comparison between sequential implementation and MPI parallel implementation.



## Background

#### The Odd-Even Transposition Sorting Algorithm

Odd-Even Transposition sort is a parallel sorting algorithm. It is based on the Bubble Sort technique for comparing pair wise and swapped when necessary. However these compare swaps is done in two phases: odd and even. Then it determines odd and even phase partner of the current process which has rank mpi_rank. It will need to know this in order to do the odd-even phase swaps. In this parallel sort function, it begins by allocating some memory needed later on for merging the local lists. Then, it determines the odd and even phase partner of the current process which has rank mpi_rank. If it has a process whose rank has two possible partners. It’s even phase partner will have a rank of mpi_rank - 1 where as it’s odd phase partner will have a rank of mpi_rank + 1. Similarly, a process whose rank is even will have an even phase partner with rank mpi_rank + 1 and an odd phase partner of rank mpi_rank -1. Next, we sort the local list using qsort . If the system wants to sort n elements in the dataset and p processes, then receives desire input from the user (number of process and processors). To optimize the processing time this research uses fast serial sorting algorithm like Quick Sort (qsort) because of its very good time complexity (O (n log n))









## Sequential and Parallel Implementation Method

#### Sequential 









#### Parallel







## Experiments

### Sequential 









#### Parallel 







## Reproduce the Experiments









## Conclusions











## Reference 











## Apendix




























