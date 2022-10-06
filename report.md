# Parallel Odd-Even Transposition Sort

## Introduction

This project is applying an odd even transposition sorting algorithm with CUHKSZ cluster to break down a computational problem into several parallel tasks of a distributed system. According to the test results, the algorithm can apply the distributed memory of multiple nodes to sort the large dataset with the medium performance for parallel speed computing to solve the real world complex parallel and distributed computing system. In this case we use the MPI the communication and synchronization between the processors. The experiment is tested upon 8 nodes with <font Color=Red>XXXX </font>cores for various generated dataset. This work also shows experimental and theoretical comparison between sequential implementation and MPI parallel implementation.



## Background

#### The Odd-Even Transposition Sorting Algorithm

Odd-Even Transposition sort is a parallel sorting algorithm. It is based on the Bubble Sort technique for comparing pair wise and swapped when necessary. However these compare swaps is done in two phases: odd and even. Then it determines odd and even phase partner of the current process which has rank mpi_rank. It will need to know this in order to do the odd-even phase swaps. In this parallel sort function, it begins by allocating some memory needed later on for merging the local lists. Then, it determines the odd and even phase partner of the current process which has rank mpi_rank. If it has a process whose rank has two possible partners. It’s even phase partner will have a rank of mpi_rank - 1 where as it’s odd phase partner will have a rank of mpi_rank + 1. Similarly, a process whose rank is even will have an even phase partner with rank mpi_rank + 1 and an odd phase partner of rank mpi_rank -1. Next, we sort the local list using qsort . If the system wants to sort n elements in the dataset and p processes, then receives desire input from the user (number of process and processors). To optimize the processing time this research uses fast serial sorting algorithm like Quick Sort (qsort) because of its very good time complexity (O (n log n))









## Sequential and Parallel Implementation Method

#### Sequential 

The idea of sequential odd-even transposition sort is straightforward. Initially, we check each numbers in the odd position i of the array and ask them to compare via value for the next  value, which is the value of the $i + 1$ th number and swap with it if the number on the odd position has a smaller value . Then, we need to do the same thing on the numbers on the even position. We will repeat these two steps until the value is sorted. The sort won’t terminal until there is no swap occur, which means any the
number of no matter even or odd positions at the array, will larger than its previous value. Thus,
the whole array will be sorted.





#### Parallel

Instead of just separating the data into different nodes and do odd-even transposition sort,
we can actually abstract the idea of the sorting algorithm in a higher level and combine it
with other sorting algorithm. In this case, multiple data will be transferred between
processes and the rule of data transporting will follow the idea of odd-even sort.
Step 1: Process with rank 0 would pad data array to a size which is the multiple of the
number of processes. After that, rank 0 process would broadcast the size of number sent to
each process. Then processes will allocate a buffer twice of the size of data scattered from
rank 0 processes and put the data received from the beginning of the allocating position.
Step 2: This step is the sorting step. (1) Firstly, the process with odd rank number (say N)
would send data to the process with 1 smaller rank (N-1). The processes receiving data will
then put the received data on the latter half of the buffer it allocated (the first half will be the
data scattered to it). Then it (process rank N-1) will perform sorting on the whole data array
and send back the latter half of the sorting result to its successive process (rank N). (2) Next,
the even rank process (say N) will instead send its data to process with one smaller rank
(rank N-1). The process of rank N-1 will put the received data on the latter half of the data
buffer it allocated together with the first half occupied with its data. Then the process with
rank N-1 will perform sorting on the whole array and send back latter half of sorted data to
its successive one (rank N). After (1) and (2), the process will use reduce to check whether
data swap was appended in any process and broadcast the result to all the processes. If no
data swap happened, then processes will jump to step 3, otherwise, another sorting iteration
of (1) and (2) will be needed.
Step 3: The rank 0 process would gather the local data from all processes and strip the data
padded and copy the rest of data to the original array.



The termination condition for this program is still no swap occur. Since we
basically abstract the odd-even sort at higher level, we can actually treat every local array as a
single element as a whole, which then reduce the whole program as simple odd even sort just like
parallel version except that all process only contains one element. Also, all the number at one
local array will be sorted automatically after received the sorted sent data from its previous
process or when it sorted its number with the numbers from its successive process all together.
Thus, the number will be sorted when no swap occurrs.

**Flow chart: How mpi work to sort a 12-dim array with 4 processes**

![image-20221006175340436](C:\Users\zhouliang\AppData\Roaming\Typora\typora-user-images\image-20221006175340436.png)



## Program Execution with 20-dim Array Demo

This program highly rely on the template with its standard execution ways.

#### Sequential Odd Even Transposition Sort 

To compile the sequential version sort. 

```bash
g++ odd_even_sequential_sort.cpp -o ssort
```



To run the sequential sort program

```bash
./ssort $number_of_elements_to_sort $path_to_input_file # Replace $variable with your own value.
```



For example,



```bash
./ssort 10000 ./test_data/10000a.in
```

The program will generate an output file called `10000a.in.seq.out` in `./test_data`.



#### Parallel Odd Even Transposition Sort


**Compile**

Use mpic++ to compile it .

```
mpic++ odd_even_parallel_sort.cpp -o psort
```

**Run**

```
salloc -n8 -p Debug # allocate cpu for your task
mpirun -np 8 ./psort $number_of_elements_to_sort $path_to_input_file # Replace $variable with your own value.
```

For example, to sort `./test_data/10000a.in` generated before, we can use

```
salloc -n8 -p Debug # allocate cpu for your task
mpirun -np 8 ./psort 10000 ./test_data/10000a.in
```

The program will generate an output file called `10000a.in.parallel.out` in `./test_data`.


#### Test data generator
test_data_generator.cpp is a test data generator. Please do not modify it. To use it, you should first compile it.

```bash
g++ test_data_generator.cpp -o gen
this operation will produce an executable named as gen.
```
Then, specify the number of elements to be sorted, and the file name.
```bash
./gen $number_of_elements_to_sort $save_file_name # Replace $variable with your own value.
```

For example, to generate a dataset with 10000 elements and name it as ./test_data/10000a.in,

```bash
./gen 10000 ./test_data/10000a.in
```
Then you will find 10000a.in in ./test_data directory.

You can generate many datasets and use them to test your program.



#### Check the correctness of your program

`check_sorted.cpp` is a tool for you to check if your sorting reuslt is correct.

To use it, first you should compile it,

```
g++ check_sorted.cpp -o check
```

Then you can utilize it by

```
./check $number_of_elements_to_sort $path_to_output_file
```

For example, if we want to check the output file `./test_data/10000a.in.parallel.out`, you can use

```
./check 10000 ./test_data/10000a.in.parallel.out
```

The output will be like (but not identical):

```
Sorted
```

#### 20-dim array demo

the randomly generated 20-dim at `./test_data/`20a.in is initially

![image-20221006175708034](C:\Users\zhouliang\AppData\Roaming\Typora\typora-user-images\image-20221006175708034.png)



**Sequential version**

we sort the array sequentially by 

```
./ssort 20 ./test_data/20a.in
```



the output information is:

![p1Sut.png](https://i.imgtg.com/2022/10/06/p1Sut.png)

after sequential sort the sorted array is 

![p16Er.png](https://i.imgtg.com/2022/10/06/p16Er.png)

We can check the correctness by:
```
./check 20 ./test_data/20a.in.seq.out
```



it prints out sorted

![p18IM.png](https://i.imgtg.com/2022/10/06/p18IM.png)



#### MPI Version with 4 Processes

the array after sort is 

[![pNz6G.png](https://i.imgtg.com/2022/10/06/pNz6G.png)](https://imgtg.com/image/pNz6G)



the output information is

[![pNxDM.png](https://i.imgtg.com/2022/10/06/pNxDM.png)](https://imgtg.com/image/pNxDM)







## Performance Analysis

#### Sequential case

**Time Complexity**

Given that the size of data array is N. At the worst case, if the biggest data is set in the first
place, it needs N swaps to swap it to the last position. And we have totally $N$ number
which means we may at most $N*N$ swap to put every data in right place. Therefore, the
time complexity is $O(N^2 )$.



## Parallel 

**Time Complexity**

In our implementation, the sorting algorithm that we use is merge sort. The merge sort algorithm uses a divide and conquer strategy to sort its elements. For an array with length $N$, and $p$ is the process number. 

The complexity for each process to communicate is $O(1)$, as we need $N$ iteration to complete sorting, then the total cost on communication is $O(N)$. When we call gather in the MPI programming. The rank 0 process gather each data located at other scattered process. This would cost $O(N)$ time complexity. The total time cost on merge sort is $O(Nlog\frac{N}{p})$ .  Totally the time complexity reduced to $O(Nlog\frac{N}{p})$. 

## Experiments





## Conclusions









## Appendix


































