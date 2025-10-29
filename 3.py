"""
Date: 14/08/2025
Group: A1
Team Number: 6
Name : Swapnaneel Ray(Team Leader), Swarnendu Banerjee, Rahul Pandey
Roll : 002311001015, 002311001016, 002311001021

Question: Parallel Programming in Python
The objective of this assignment is to write a parallel program in Python
which will do Matrix Multiplication between two large Square Matrices with
unsigned integer elements.

Usage: 
 - To run: python3 A1_06_3.py <n> <cores> <mod> <print_switch>
 - To check CPU stats: sar -u -P ALL <interval> <count>

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
- Starting with 1 core and gradually increasing - 1, 2, 4, 8, 12

> python3 A1_06_3.py 4000 1 1000 0

Matrix Multiplication Completed in 68.6456 seconds

> sar -u -P ALL 10 2

Linux 6.8.0-65-generic (jusl) 	14/08/25 	_x86_64_	(12 CPU)

12:29:15 PM IST     CPU     %user     %nice   %system   %iowait    %steal     %idle
12:29:25 PM IST     all      8.39      0.00      0.13      0.03      0.00     91.46
12:29:25 PM IST       0      0.00      0.00      0.20      0.00      0.00     99.80
12:29:25 PM IST       1      0.00      0.00      0.10      0.00      0.00     99.90
12:29:25 PM IST       2     66.30      0.00      0.00      0.00      0.00     33.70
12:29:25 PM IST       3     33.70      0.00      0.00      0.00      0.00     66.30
12:29:25 PM IST       4      0.10      0.00      0.20      0.00      0.00     99.70
12:29:25 PM IST       5      0.10      0.00      0.00      0.00      0.00     99.90
12:29:25 PM IST       6      0.10      0.00      0.60      0.00      0.00     99.30
12:29:25 PM IST       7      0.00      0.00      0.00      0.00      0.00    100.00
12:29:25 PM IST       8      0.20      0.00      0.20      0.30      0.00     99.30
12:29:25 PM IST       9      0.10      0.00      0.10      0.00      0.00     99.80
12:29:25 PM IST      10      0.00      0.00      0.10      0.00      0.00     99.90
12:29:25 PM IST      11      0.00      0.00      0.00      0.00      0.00    100.00

12:29:25 PM IST     CPU     %user     %nice   %system   %iowait    %steal     %idle
12:29:35 PM IST     all      8.41      0.00      0.09      0.03      0.00     91.47
12:29:35 PM IST       0      0.10      0.00      0.10      0.10      0.00     99.70
12:29:35 PM IST       1      0.10      0.00      0.00      0.00      0.00     99.90
12:29:35 PM IST       2     18.42      0.00      0.00      0.00      0.00     81.58
12:29:35 PM IST       3     81.70      0.00      0.00      0.00      0.00     18.30
12:29:35 PM IST       4      0.10      0.00      0.00      0.00      0.00     99.90
12:29:35 PM IST       5      0.00      0.00      0.00      0.00      0.00    100.00
12:29:35 PM IST       6      0.00      0.00      0.60      0.00      0.00     99.40
12:29:35 PM IST       7      0.00      0.00      0.00      0.00      0.00    100.00
12:29:35 PM IST       8      0.10      0.00      0.10      0.10      0.00     99.70
12:29:35 PM IST       9      0.10      0.00      0.00      0.00      0.00     99.90
12:29:35 PM IST      10      0.10      0.00      0.30      0.10      0.00     99.50
12:29:35 PM IST      11      0.10      0.00      0.00      0.00      0.00     99.90

Average:        CPU     %user     %nice   %system   %iowait    %steal     %idle
Average:        all      8.40      0.00      0.11      0.03      0.00     91.47
Average:          0      0.05      0.00      0.15      0.05      0.00     99.75
Average:          1      0.05      0.00      0.05      0.00      0.00     99.90
Average:          2     42.37      0.00      0.00      0.00      0.00     57.63
Average:          3     57.70      0.00      0.00      0.00      0.00     42.30
Average:          4      0.10      0.00      0.10      0.00      0.00     99.80
Average:          5      0.05      0.00      0.00      0.00      0.00     99.95
Average:          6      0.05      0.00      0.60      0.00      0.00     99.35
Average:          7      0.00      0.00      0.00      0.00      0.00    100.00
Average:          8      0.15      0.00      0.15      0.20      0.00     99.50
Average:          9      0.10      0.00      0.05      0.00      0.00     99.85
Average:         10      0.05      0.00      0.20      0.05      0.00     99.70
Average:         11      0.05      0.00      0.00      0.00      0.00     99.95

> python3 A1_06_3.py 4000 2 1000 0

Matrix Multiplication Completed in 35.3030 seconds

> sar -u -P ALL 5 2
Linux 6.8.0-65-generic (jusl) 	14/08/25 	_x86_64_	(12 CPU)

12:33:56 PM IST     CPU     %user     %nice   %system   %iowait    %steal     %idle
12:34:01 PM IST     all     16.92      0.00      0.08      0.12      0.00     82.88
12:34:01 PM IST       0      0.40      0.00      0.40      0.40      0.00     98.79
12:34:01 PM IST       1      0.20      0.00      0.00      0.00      0.00     99.80
12:34:01 PM IST       2      0.80      0.00      0.20      0.60      0.00     98.40
12:34:01 PM IST       3      0.80      0.00      0.00      0.00      0.00     99.20
12:34:01 PM IST       4      0.20      0.00      0.20      0.00      0.00     99.60
12:34:01 PM IST       5      0.00      0.00      0.00      0.00      0.00    100.00
12:34:01 PM IST       6    100.00      0.00      0.00      0.00      0.00      0.00
12:34:01 PM IST       7      0.00      0.00      0.00      0.20      0.00     99.80
12:34:01 PM IST       8      0.20      0.00      0.20      0.20      0.00     99.40
12:34:01 PM IST       9      0.20      0.00      0.00      0.00      0.00     99.80
12:34:01 PM IST      10     78.60      0.00      0.00      0.00      0.00     21.40
12:34:01 PM IST      11     21.40      0.00      0.00      0.00      0.00     78.60

12:34:01 PM IST     CPU     %user     %nice   %system   %iowait    %steal     %idle
12:34:06 PM IST     all     16.78      0.00      0.08      0.07      0.00     83.07
12:34:06 PM IST       0      0.00      0.00      0.20      0.20      0.00     99.60
12:34:06 PM IST       1      0.00      0.00      0.00      0.00      0.00    100.00
12:34:06 PM IST       2      0.20      0.00      0.20      0.40      0.00     99.20
12:34:06 PM IST       3      0.00      0.00      0.00      0.00      0.00    100.00
12:34:06 PM IST       4      0.00      0.00      0.20      0.20      0.00     99.60
12:34:06 PM IST       5      0.20      0.00      0.00      0.00      0.00     99.80
12:34:06 PM IST       6     41.72      0.00      0.20      0.00      0.00     58.08
12:34:06 PM IST       7     58.32      0.00      0.00      0.00      0.00     41.68
12:34:06 PM IST       8      0.20      0.00      0.20      0.00      0.00     99.60
12:34:06 PM IST       9      0.40      0.00      0.00      0.00      0.00     99.60
12:34:06 PM IST      10     81.40      0.00      0.00      0.00      0.00     18.60
12:34:06 PM IST      11     18.76      0.00      0.00      0.00      0.00     81.24

Average:        CPU     %user     %nice   %system   %iowait    %steal     %idle
Average:        all     16.85      0.00      0.08      0.09      0.00     82.97
Average:          0      0.20      0.00      0.30      0.30      0.00     99.19
Average:          1      0.10      0.00      0.00      0.00      0.00     99.90
Average:          2      0.50      0.00      0.20      0.50      0.00     98.80
Average:          3      0.40      0.00      0.00      0.00      0.00     99.60
Average:          4      0.10      0.00      0.20      0.10      0.00     99.60
Average:          5      0.10      0.00      0.00      0.00      0.00     99.90
Average:          6     70.83      0.00      0.10      0.00      0.00     29.07
Average:          7     29.10      0.00      0.00      0.10      0.00     70.80
Average:          8      0.20      0.00      0.20      0.10      0.00     99.50
Average:          9      0.30      0.00      0.00      0.00      0.00     99.70
Average:         10     80.00      0.00      0.00      0.00      0.00     20.00
Average:         11     20.08      0.00      0.00      0.00      0.00     79.92

> python3 A1_06_3.py 4000 4 1000 0

Matrix Multiplication Completed in 17.1387 seconds

> sar -u -P ALL 5 2
Linux 6.8.0-65-generic (jusl) 	14/08/25 	_x86_64_	(12 CPU)

12:35:58 PM IST     CPU     %user     %nice   %system   %iowait    %steal     %idle
12:36:03 PM IST     all     33.46      0.00      0.13      0.05      0.00     66.36
12:36:03 PM IST       0     29.58      0.00      0.00      0.00      0.00     70.42
12:36:03 PM IST       1     70.74      0.00      0.00      0.00      0.00     29.26
12:36:03 PM IST       2      0.40      0.00      0.20      0.20      0.00     99.20
12:36:03 PM IST       3      0.00      0.00      0.00      0.00      0.00    100.00
12:36:03 PM IST       4     55.60      0.00      0.00      0.00      0.00     44.40
12:36:03 PM IST       5     44.42      0.00      0.20      0.00      0.00     55.38
12:36:03 PM IST       6      0.00      0.00      0.60      0.00      0.00     99.40
12:36:03 PM IST       7      0.00      0.00      0.00      0.00      0.00    100.00
12:36:03 PM IST       8    100.00      0.00      0.00      0.00      0.00      0.00
12:36:03 PM IST       9      0.20      0.00      0.20      0.00      0.00     99.60
12:36:03 PM IST      10      0.20      0.00      0.20      0.40      0.00     99.20
12:36:03 PM IST      11     99.80      0.00      0.20      0.00      0.00      0.00

12:36:03 PM IST     CPU     %user     %nice   %system   %iowait    %steal     %idle
12:36:08 PM IST     all     33.45      0.00      0.13      0.07      0.00     66.35
12:36:08 PM IST       0     42.37      0.00      0.00      0.00      0.00     57.63
12:36:08 PM IST       1     58.03      0.00      0.00      0.00      0.00     41.97
12:36:08 PM IST       2      0.20      0.00      0.40      0.00      0.00     99.40
12:36:08 PM IST       3      0.00      0.00      0.00      0.00      0.00    100.00
12:36:08 PM IST       4     94.39      0.00      0.00      0.00      0.00      5.61
12:36:08 PM IST       5      5.61      0.00      0.00      0.00      0.00     94.39
12:36:08 PM IST       6      0.00      0.00      0.80      0.00      0.00     99.20
12:36:08 PM IST       7      0.20      0.00      0.20      0.20      0.00     99.40
12:36:08 PM IST       8    100.00      0.00      0.00      0.00      0.00      0.00
12:36:08 PM IST       9      0.40      0.00      0.20      0.00      0.00     99.40
12:36:08 PM IST      10      0.20      0.00      0.00      0.60      0.00     99.20
12:36:08 PM IST      11    100.00      0.00      0.00      0.00      0.00      0.00

Average:        CPU     %user     %nice   %system   %iowait    %steal     %idle
Average:        all     33.45      0.00      0.13      0.06      0.00     66.36
Average:          0     35.98      0.00      0.00      0.00      0.00     64.02
Average:          1     64.39      0.00      0.00      0.00      0.00     35.61
Average:          2      0.30      0.00      0.30      0.10      0.00     99.30
Average:          3      0.00      0.00      0.00      0.00      0.00    100.00
Average:          4     74.97      0.00      0.00      0.00      0.00     25.03
Average:          5     25.07      0.00      0.10      0.00      0.00     74.83
Average:          6      0.00      0.00      0.70      0.00      0.00     99.30
Average:          7      0.10      0.00      0.10      0.10      0.00     99.70
Average:          8    100.00      0.00      0.00      0.00      0.00      0.00
Average:          9      0.30      0.00      0.20      0.00      0.00     99.50
Average:         10      0.20      0.00      0.10      0.50      0.00     99.20
Average:         11     99.90      0.00      0.10      0.00      0.00      0.00

> python3 A1_06_3.py 4000 8 1000 0

Matrix Multiplication Completed in 12.6142 seconds

> Linux 6.8.0-65-generic (jusl) 	14/08/25 	_x86_64_	(12 CPU)

12:38:29 PM IST     CPU     %user     %nice   %system   %iowait    %steal     %idle
12:38:32 PM IST     all     66.83      0.00      0.25      0.03      0.00     32.89
12:38:32 PM IST       0     66.56      0.00      0.00      0.00      0.00     33.44
12:38:32 PM IST       1     97.66      0.00      0.00      0.00      0.00      2.34
12:38:32 PM IST       2     13.76      0.00      0.34      0.34      0.00     85.57
12:38:32 PM IST       3     87.00      0.00      0.00      0.00      0.00     13.00
12:38:32 PM IST       4     21.14      0.00      0.00      0.00      0.00     78.86
12:38:32 PM IST       5     79.40      0.00      0.33      0.00      0.00     20.27
12:38:32 PM IST       6     99.34      0.00      0.66      0.00      0.00      0.00
12:38:32 PM IST       7    100.00      0.00      0.00      0.00      0.00      0.00
12:38:32 PM IST       8     59.67      0.00      0.33      0.00      0.00     40.00
12:38:32 PM IST       9     41.00      0.00      1.00      0.00      0.00     58.00
12:38:32 PM IST      10     41.67      0.00      0.33      0.00      0.00     58.00
12:38:32 PM IST      11     94.31      0.00      0.00      0.00      0.00      5.69

12:38:32 PM IST     CPU     %user     %nice   %system   %iowait    %steal     %idle
12:38:35 PM IST     all     66.85      0.00      0.06      0.08      0.00     33.01
12:38:35 PM IST       0      8.75      0.00      0.00      0.00      0.00     91.25
12:38:35 PM IST       1     91.67      0.00      0.00      0.00      0.00      8.33
12:38:35 PM IST       2     46.82      0.00      0.33      0.67      0.00     52.17
12:38:35 PM IST       3     53.33      0.00      0.00      0.33      0.00     46.33
12:38:35 PM IST       4      0.33      0.00      0.33      0.00      0.00     99.33
12:38:35 PM IST       5    100.00      0.00      0.00      0.00      0.00      0.00
12:38:35 PM IST       6    100.00      0.00      0.00      0.00      0.00      0.00
12:38:35 PM IST       7    100.00      0.00      0.00      0.00      0.00      0.00
12:38:35 PM IST       8    100.00      0.00      0.00      0.00      0.00      0.00
12:38:35 PM IST       9      0.67      0.00      0.00      0.00      0.00     99.33
12:38:35 PM IST      10    100.00      0.00      0.00      0.00      0.00      0.00
12:38:35 PM IST      11    100.00      0.00      0.00      0.00      0.00      0.00

Average:        CPU     %user     %nice   %system   %iowait    %steal     %idle
Average:        all     66.84      0.00      0.15      0.06      0.00     32.95
Average:          0     37.75      0.00      0.00      0.00      0.00     62.25
Average:          1     94.66      0.00      0.00      0.00      0.00      5.34
Average:          2     30.32      0.00      0.34      0.50      0.00     68.84
Average:          3     70.17      0.00      0.00      0.17      0.00     29.67
Average:          4     10.72      0.00      0.17      0.00      0.00     89.11
Average:          5     89.67      0.00      0.17      0.00      0.00     10.17
Average:          6     99.67      0.00      0.33      0.00      0.00      0.00
Average:          7    100.00      0.00      0.00      0.00      0.00      0.00
Average:          8     79.83      0.00      0.17      0.00      0.00     20.00
Average:          9     20.83      0.00      0.50      0.00      0.00     78.67
Average:         10     70.83      0.00      0.17      0.00      0.00     29.00
Average:         11     97.16      0.00      0.00      0.00      0.00      2.84

> python3 A1_06_3.py 4000 12 1000 0

Matrix Multiplication Completed in 11.4620 seconds

> Linux 6.8.0-65-generic (jusl) 	14/08/25 	_x86_64_	(12 CPU)

12:39:53 PM IST     CPU     %user     %nice   %system   %iowait    %steal     %idle
12:39:55 PM IST     all     99.63      0.00      0.37      0.00      0.00      0.00
12:39:55 PM IST       0     99.50      0.00      0.50      0.00      0.00      0.00
12:39:55 PM IST       1    100.00      0.00      0.00      0.00      0.00      0.00
12:39:55 PM IST       2     99.50      0.00      0.50      0.00      0.00      0.00
12:39:55 PM IST       3    100.00      0.00      0.00      0.00      0.00      0.00
12:39:55 PM IST       4     99.50      0.00      0.50      0.00      0.00      0.00
12:39:55 PM IST       5     99.50      0.00      0.50      0.00      0.00      0.00
12:39:55 PM IST       6     99.00      0.00      1.00      0.00      0.00      0.00
12:39:55 PM IST       7     99.50      0.00      0.50      0.00      0.00      0.00
12:39:55 PM IST       8     99.50      0.00      0.50      0.00      0.00      0.00
12:39:55 PM IST       9    100.00      0.00      0.00      0.00      0.00      0.00
12:39:55 PM IST      10    100.00      0.00      0.00      0.00      0.00      0.00
12:39:55 PM IST      11     99.50      0.00      0.50      0.00      0.00      0.00

12:39:55 PM IST     CPU     %user     %nice   %system   %iowait    %steal     %idle
12:39:57 PM IST     all     99.96      0.00      0.04      0.00      0.00      0.00
12:39:57 PM IST       0    100.00      0.00      0.00      0.00      0.00      0.00
12:39:57 PM IST       1    100.00      0.00      0.00      0.00      0.00      0.00
12:39:57 PM IST       2    100.00      0.00      0.00      0.00      0.00      0.00
12:39:57 PM IST       3    100.00      0.00      0.00      0.00      0.00      0.00
12:39:57 PM IST       4    100.00      0.00      0.00      0.00      0.00      0.00
12:39:57 PM IST       5    100.00      0.00      0.00      0.00      0.00      0.00
12:39:57 PM IST       6     99.50      0.00      0.50      0.00      0.00      0.00
12:39:57 PM IST       7    100.00      0.00      0.00      0.00      0.00      0.00
12:39:57 PM IST       8    100.00      0.00      0.00      0.00      0.00      0.00
12:39:57 PM IST       9    100.00      0.00      0.00      0.00      0.00      0.00
12:39:57 PM IST      10    100.00      0.00      0.00      0.00      0.00      0.00
12:39:57 PM IST      11    100.00      0.00      0.00      0.00      0.00      0.00

Average:        CPU     %user     %nice   %system   %iowait    %steal     %idle
Average:        all     99.79      0.00      0.21      0.00      0.00      0.00
Average:          0     99.75      0.00      0.25      0.00      0.00      0.00
Average:          1    100.00      0.00      0.00      0.00      0.00      0.00
Average:          2     99.75      0.00      0.25      0.00      0.00      0.00
Average:          3    100.00      0.00      0.00      0.00      0.00      0.00
Average:          4     99.75      0.00      0.25      0.00      0.00      0.00
Average:          5     99.75      0.00      0.25      0.00      0.00      0.00
Average:          6     99.25      0.00      0.75      0.00      0.00      0.00
Average:          7     99.75      0.00      0.25      0.00      0.00      0.00
Average:          8     99.75      0.00      0.25      0.00      0.00      0.00
Average:          9    100.00      0.00      0.00      0.00      0.00      0.00
Average:         10    100.00      0.00      0.00      0.00      0.00      0.00
Average:         11     99.75      0.00      0.25      0.00      0.00      0.00


- Running with small dimensions to display multiplication output
python3 test.py 3 1 10 1

Matrix Multiplication Completed in 0.0056 seconds

Matrix A:
[[9 6 9]
 [6 8 7]
 [9 2 5]]

Matrix B:
[[5 9 8]
 [3 4 4]
 [7 5 6]]

Resultant Matrix:
[[126 150 150]
 [103 121 122]
 [ 86 114 110]]

"""

import numpy as np
import multiprocessing as mp
import sys
import time

# function to multiply some rows of A with matrix B
def worker(start, end, A, B, queue):
    result = np.dot(A[start:end], B)
    queue.put((start, result))

# function to multiply matrices parallely 
def parallel_mat_multiplication(A, B, cores):
    n = A.shape[0]
    # distributing rows equally to each core
    chunk_size = n // cores
    processes = []
    queue = mp.Queue()

    for i in range(cores):
        start_row = i * chunk_size
        if i != cores - 1 : 
            end_row = (i+1)*chunk_size
        else :
            end_row = n
        # initialising new process, running the worker method defined above
        p = mp.Process(target=worker, args=(start_row, end_row, A, B, queue))
        # storing the process in list of processes, and starting it
        processes.append(p)
        p.start()

    result = np.zeros((n, n), dtype=np.uint32)
    # taking result from each core and storing it
    for core in range(cores):
        start, partial = queue.get()
        rows_in_chunk = partial.shape[0]
        for i in range(rows_in_chunk):
            for j in range(n):
                result[start + i, j] = partial[i, j]

    for p in processes:
        p.join() # ensure that current process waits for all other processes to complete

    return result


# exiting if valid command line arguments are not provided
if len(sys.argv) != 5:
    print("Arguements : <n> <cores> <max_v> <print>")
    sys.exit(1)

# creating two random matrices using dimensions and mod value from command line
mat1 = np.random.randint(0, int(sys.argv[3]), size=(int(sys.argv[1]), int(sys.argv[1])), dtype=np.uint32)
mat2 = np.random.randint(0, int(sys.argv[3]), size=(int(sys.argv[1]), int(sys.argv[1])), dtype=np.uint32)

# recording start time
start_time = time.perf_counter()

result = parallel_mat_multiplication(mat1, mat2, int(sys.argv[2]))

# recording end time
end_time = time.perf_counter()

print(f"\nMatrix Multiplication Completed in {end_time - start_time:.4f} seconds\n")

# printing output only if print_switch is set to 1
if sys.argv[4] == '1':
    print("Matrix A:")
    print(mat1)
    print("\nMatrix B:")
    print(mat2)
    print("\nResultant Matrix:")
    print(result)


