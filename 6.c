/*

Date: 11/09/2025
Group: A1
Team Number: 6
Name : Swapnaneel Ray(Team Leader), Swarnendu Banerjee, Rahul Pandey
Roll : 002311001015, 002311001016, 002311001021

Question: Parallel Programming using Thread
The objective of this assignment is to use thread programming to write a parallel program
which will do Matrix Multiplication between two large Square Matrices with
unsigned character elements.

Usage: 
 - To compile: gcc A1_06_6.c -pthread -o out
 - To run: ./out <n> <cores> <mod> <print_switch>
 - To check CPU stats: sar -u -P ALL <interval> <count>
 - To check process and thread listing: ps -elF | grep "out"

Command Line Arguments:
    To Run Program:
    - <n> : dimensions of the matrix of the form (n X n)
    - <cores> : number of CPU cores used
    - <mod> : upper limit of elements in matrix (each element is mod to this value)
    - <print_switch> : switch to control if matrices will be printed or not, 1 - matrices printed, 0 - not printed

    To Check CPU Status:
    - -u : used to print CPU utilisation status
    - -P ALL : the -p flag is used to specify which CPU to monitor. ALL means that we want to display stats for all cores
    - <interval> : specifies interval between each report
    - <count> : number of times report is to be printed

Output:
- Starting with 1 core and gradually increasing - 1, 6, 12


1 thread : 
./out 3000 1 10 0
Time taken for matrix multiplication with 1 threads: 46.81

ps -elF | grep out
0 S adminpc     6160    2947  0  80   0 -  2227 pipe_r   720   2 11:44 pts/0    00:00:00 grep --color=auto out

sar -u -P ALL 3 2
Linux 5.15.0-139-generic (adminpc-HP-Pro-Tower-280-G9-PCI-Desktop-PC) 	11/09/25 	_x86_64_	(12 CPU)

11:49:18 AM IST     CPU     %user     %nice   %system   %iowait    %steal     %idle
11:49:21 AM IST     all      5.55      0.00      0.39      0.00      0.00     94.06
11:49:21 AM IST       0      1.67      0.00      0.33      0.00      0.00     97.99
11:49:21 AM IST       1      0.00      0.00      0.00      0.00      0.00    100.00
11:49:21 AM IST       2      2.34      0.00      0.67      0.00      0.00     96.99
11:49:21 AM IST       3      0.00      0.00      0.00      0.00      0.00    100.00
11:49:21 AM IST       4     55.52      0.00      0.00      0.00      0.00     44.48
11:49:21 AM IST       5      0.00      0.00      0.00      0.00      0.00    100.00
11:49:21 AM IST       6      0.67      0.00      0.67      0.00      0.00     98.67
11:49:21 AM IST       7      0.00      0.00      0.34      0.00      0.00     99.66
11:49:21 AM IST       8      1.34      0.00      1.01      0.00      0.00     97.65
11:49:21 AM IST       9      1.00      0.00      1.33      0.00      0.00     97.67
11:49:21 AM IST      10      4.04      0.00      0.34      0.00      0.00     95.62
11:49:21 AM IST      11      0.00      0.00      0.00      0.00      0.00    100.00

11:49:21 AM IST     CPU     %user     %nice   %system   %iowait    %steal     %idle
11:49:24 AM IST     all      8.45      0.00      0.11      0.08      0.00     91.35
11:49:24 AM IST       0      0.33      0.00      0.66      0.66      0.00     98.34
11:49:24 AM IST       1      0.00      0.00      0.33      0.00      0.00     99.67
11:49:24 AM IST       2      0.00      0.00      0.00      0.00      0.00    100.00
11:49:24 AM IST       3      0.33      0.00      0.00      0.00      0.00     99.67
11:49:24 AM IST       4    100.00      0.00      0.00      0.00      0.00      0.00
11:49:24 AM IST       5      0.00      0.00      0.00      0.00      0.00    100.00
11:49:24 AM IST       6      0.34      0.00      0.00      0.00      0.00     99.66
11:49:24 AM IST       7      0.00      0.00      0.00      0.00      0.00    100.00
11:49:24 AM IST       8      0.00      0.00      0.00      0.00      0.00    100.00
11:49:24 AM IST       9      0.00      0.00      0.33      0.00      0.00     99.67
11:49:24 AM IST      10      0.00      0.00      0.00      0.33      0.00     99.67
11:49:24 AM IST      11      0.00      0.00      0.00      0.00      0.00    100.00

Average:        CPU     %user     %nice   %system   %iowait    %steal     %idle
Average:        all      7.00      0.00      0.25      0.04      0.00     92.71
Average:          0      1.00      0.00      0.50      0.33      0.00     98.17
Average:          1      0.00      0.00      0.17      0.00      0.00     99.83
Average:          2      1.17      0.00      0.33      0.00      0.00     98.49
Average:          3      0.17      0.00      0.00      0.00      0.00     99.83
Average:          4     77.83      0.00      0.00      0.00      0.00     22.17
Average:          5      0.00      0.00      0.00      0.00      0.00    100.00
Average:          6      0.50      0.00      0.33      0.00      0.00     99.16
Average:          7      0.00      0.00      0.17      0.00      0.00     99.83
Average:          8      0.67      0.00      0.50      0.00      0.00     98.83
Average:          9      0.50      0.00      0.83      0.00      0.00     98.67
Average:         10      2.01      0.00      0.17      0.17      0.00     97.65
Average:         11      0.00      0.00      0.00      0.00      0.00    100.00

6 threads: 

./out 3000 6 10 0
Time taken for matrix multiplication with 6 threads: 10.684007 seconds

ps -elF | grep out
0 S adminpc     6278    5051  0  80   0 -  2227 pipe_r   720   7 11:48 pts/1    00:00:00 grep --color=auto out

sar -u -P ALL 3 2
Linux 5.15.0-139-generic (adminpc-HP-Pro-Tower-280-G9-PCI-Desktop-PC) 	11/09/25 	_x86_64_	(12 CPU)

11:46:28 AM IST     CPU     %user     %nice   %system   %iowait    %steal     %idle
11:46:31 AM IST     all     26.57      0.00      0.22      0.06      0.00     73.16
11:46:31 AM IST       0     15.58      0.00      0.00      0.00      0.00     84.42
11:46:31 AM IST       1     41.18      0.00      0.65      0.00      0.00     58.17
11:46:31 AM IST       2      2.69      0.00      0.00      0.00      0.00     97.31
11:46:31 AM IST       3     50.00      0.00      0.00      0.00      0.00     50.00
11:46:31 AM IST       4      1.34      0.00      0.00      0.00      0.00     98.66
11:46:31 AM IST       5     49.50      0.00      0.00      0.67      0.00     49.83
11:46:31 AM IST       6     43.14      0.00      0.00      0.00      0.00     56.86
11:46:31 AM IST       7     10.96      0.00      1.66      0.00      0.00     87.38
11:46:31 AM IST       8     25.25      0.00      0.33      0.00      0.00     74.42
11:46:31 AM IST       9     28.86      0.00      0.00      0.00      0.00     71.14
11:46:31 AM IST      10     21.07      0.00      0.00      0.00      0.00     78.93
11:46:31 AM IST      11     29.00      0.00      0.00      0.00      0.00     71.00

11:46:31 AM IST     CPU     %user     %nice   %system   %iowait    %steal     %idle
11:46:34 AM IST     all     50.50      0.00      0.50      0.14      0.00     48.86
11:46:34 AM IST       0     28.43      0.00      0.00      0.67      0.00     70.90
11:46:34 AM IST       1     72.00      0.00      0.00      0.00      0.00     28.00
11:46:34 AM IST       2     43.14      0.00      0.00      0.00      0.00     56.86
11:46:34 AM IST       3     60.26      0.00      2.32      0.66      0.00     36.75
11:46:34 AM IST       4      0.00      0.00      0.33      0.00      0.00     99.67
11:46:34 AM IST       5    100.00      0.00      0.00      0.00      0.00      0.00
11:46:34 AM IST       6     89.37      0.00      0.00      0.00      0.00     10.63
11:46:34 AM IST       7     10.33      0.00      1.00      0.00      0.00     88.67
11:46:34 AM IST       8      2.66      0.00      1.33      0.33      0.00     95.68
11:46:34 AM IST       9     98.67      0.00      0.33      0.00      0.00      1.00
11:46:34 AM IST      10     25.67      0.00      0.33      0.00      0.00     74.00
11:46:34 AM IST      11     75.25      0.00      0.33      0.00      0.00     24.41

Average:        CPU     %user     %nice   %system   %iowait    %steal     %idle
Average:        all     38.53      0.00      0.36      0.10      0.00     61.02
Average:          0     21.91      0.00      0.00      0.33      0.00     77.76
Average:          1     56.44      0.00      0.33      0.00      0.00     43.23
Average:          2     22.99      0.00      0.00      0.00      0.00     77.01
Average:          3     55.15      0.00      1.16      0.33      0.00     43.36
Average:          4      0.67      0.00      0.17      0.00      0.00     99.16
Average:          5     74.79      0.00      0.00      0.33      0.00     24.87
Average:          6     66.33      0.00      0.00      0.00      0.00     33.67
Average:          7     10.65      0.00      1.33      0.00      0.00     88.02
Average:          8     13.95      0.00      0.83      0.17      0.00     85.05
Average:          9     63.94      0.00      0.17      0.00      0.00     35.89
Average:         10     23.37      0.00      0.17      0.00      0.00     76.46
Average:         11     52.09      0.00      0.17      0.00      0.00     47.75

12 threads :

./out 3000 12 10 0
Time taken for matrix multiplication with 12 threads: 9.861432 seconds

ps -elF | grep "out"
0 R adminpc    11534    5051  0  80   0 -  2227 pipe_r   648   2 12:50 pts/1    00:00:00 grep --color=auto out

sar -u -P ALL 3 2
Linux 5.15.0-139-generic (adminpc-HP-Pro-Tower-280-G9-PCI-Desktop-PC) 	11/09/25 	_x86_64_	(12 CPU)

12:49:55 PM IST     CPU     %user     %nice   %system   %iowait    %steal     %idle
12:49:58 PM IST     all     99.81      0.00      0.19      0.00      0.00      0.00
12:49:58 PM IST       0    100.00      0.00      0.00      0.00      0.00      0.00
12:49:58 PM IST       1    100.00      0.00      0.00      0.00      0.00      0.00
12:49:58 PM IST       2     99.67      0.00      0.33      0.00      0.00      0.00
12:49:58 PM IST       3    100.00      0.00      0.00      0.00      0.00      0.00
12:49:58 PM IST       4    100.00      0.00      0.00      0.00      0.00      0.00
12:49:58 PM IST       5    100.00      0.00      0.00      0.00      0.00      0.00
12:49:58 PM IST       6    100.00      0.00      0.00      0.00      0.00      0.00
12:49:58 PM IST       7     98.33      0.00      1.67      0.00      0.00      0.00
12:49:58 PM IST       8    100.00      0.00      0.00      0.00      0.00      0.00
12:49:58 PM IST       9     99.67      0.00      0.33      0.00      0.00      0.00
12:49:58 PM IST      10    100.00      0.00      0.00      0.00      0.00      0.00
12:49:58 PM IST      11    100.00      0.00      0.00      0.00      0.00      0.00

12:49:58 PM IST     CPU     %user     %nice   %system   %iowait    %steal     %idle
12:50:01 PM IST     all     99.67      0.00      0.33      0.00      0.00      0.00
12:50:01 PM IST       0    100.00      0.00      0.00      0.00      0.00      0.00
12:50:01 PM IST       1    100.00      0.00      0.00      0.00      0.00      0.00
12:50:01 PM IST       2    100.00      0.00      0.00      0.00      0.00      0.00
12:50:01 PM IST       3    100.00      0.00      0.00      0.00      0.00      0.00
12:50:01 PM IST       4    100.00      0.00      0.00      0.00      0.00      0.00
12:50:01 PM IST       5    100.00      0.00      0.00      0.00      0.00      0.00
12:50:01 PM IST       6    100.00      0.00      0.00      0.00      0.00      0.00
12:50:01 PM IST       7     95.99      0.00      4.01      0.00      0.00      0.00
12:50:01 PM IST       8    100.00      0.00      0.00      0.00      0.00      0.00
12:50:01 PM IST       9    100.00      0.00      0.00      0.00      0.00      0.00
12:50:01 PM IST      10    100.00      0.00      0.00      0.00      0.00      0.00
12:50:01 PM IST      11    100.00      0.00      0.00      0.00      0.00      0.00

Average:        CPU     %user     %nice   %system   %iowait    %steal     %idle
Average:        all     99.74      0.00      0.26      0.00      0.00      0.00
Average:          0    100.00      0.00      0.00      0.00      0.00      0.00
Average:          1    100.00      0.00      0.00      0.00      0.00      0.00
Average:          2     99.83      0.00      0.17      0.00      0.00      0.00
Average:          3    100.00      0.00      0.00      0.00      0.00      0.00
Average:          4    100.00      0.00      0.00      0.00      0.00      0.00
Average:          5    100.00      0.00      0.00      0.00      0.00      0.00
Average:          6    100.00      0.00      0.00      0.00      0.00      0.00
Average:          7     97.16      0.00      2.84      0.00      0.00      0.00
Average:          8    100.00      0.00      0.00      0.00      0.00      0.00
Average:          9     99.83      0.00      0.17      0.00      0.00      0.00
Average:         10    100.00      0.00      0.00      0.00      0.00      0.00
Average:         11    100.00      0.00      0.00      0.00      0.00      0.00

Result of matrix multiplication with print_switch on:

./out 3 1 10 1
Matrix A:
   9    1    8 
   1    6    2 
   6    1    7 

Matrix B:
   4    8    1 
   8    2    8 
   6    4    4 

Matrix C:
  92  106   49 
  64   28   57 
  74   78   42 

Time taken for matrix multiplication with 1 threads: 0.000515 seconds

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

// global matrix pointers
unsigned char **A, **B, **C;
int size, num_threads;

// worker function to multiply part of the matrix in thread
void *multiply(void *arg) {
    int thread_id = *(int *)arg;
    int rows_per_thread = size / num_threads;
    int start_row = thread_id * rows_per_thread;
    int end_row = (thread_id == num_threads - 1) ? size : start_row + rows_per_thread;

    for (int i = start_row; i < end_row; ++i) {
        for (int j = 0; j < size; ++j) {
            unsigned int sum = 0;
            for (int k = 0; k < size; ++k) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = (unsigned char)(sum % 256);  // To avoid overflow
        }
    }

    pthread_exit(NULL);
}

unsigned char **allocate_matrix(int n) {
    unsigned char **matrix = malloc(n * sizeof(unsigned char *));
    for (int i = 0; i < n; ++i)
        matrix[i] = malloc(n * sizeof(unsigned char));
    return matrix;
}

// function to initialize matrix with random values
void initialize_matrix(unsigned char **matrix, int n, int mod) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            matrix[i][j] = rand() % mod;
}

void print_matrix(unsigned char **matrix, int n, const char *name) {
    printf("Matrix %s:\n", name);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void free_matrix(unsigned char **matrix, int n) {
    for (int i = 0; i < n; ++i)
        free(matrix[i]);
    free(matrix);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <matrix_size> <num_threads> <mod_value> <print_switch>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    size = atoi(argv[1]);
    num_threads = atoi(argv[2]);
    int mod = atoi(argv[3]);
    int print_switch = atoi(argv[4]);
    int i;

    if (size < 1 || num_threads < 1 || mod < 1 || mod > 256) {
        fprintf(stderr, "Invalid arguments. Ensure size >=1, threads >=1, mod in (1-256).\n");
        exit(EXIT_FAILURE);
    }

    A = allocate_matrix(size);
    B = allocate_matrix(size);
    C = allocate_matrix(size);

    srand(time(NULL));
    initialize_matrix(A, size, mod);
    initialize_matrix(B, size, mod);

    if (print_switch) {
        print_matrix(A, size, "A");
        print_matrix(B, size, "B");
    }

    pthread_t threads[num_threads];
    int thread_ids[num_threads];

    struct timeval start, end;
    gettimeofday(&start, NULL);

    // create threads to multiply matrices parallely
    for (i = 0; i < num_threads; ++i) {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, multiply, &thread_ids[i]) != 0) {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }

    // make sure main thread waits for all other threads to finish
    for (i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&end, NULL);
    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;

    // print result if print_switch is on
    if (print_switch) {
        print_matrix(C, size, "C");
    }

    printf("Time taken for matrix multiplication with %d threads: %.6f seconds\n", num_threads, time_taken);

    // free up memory 
    free_matrix(A, size);
    free_matrix(B, size);
    free_matrix(C, size);

    return 0;
}

