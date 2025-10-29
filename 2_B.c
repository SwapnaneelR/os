/*

Team details:

Name : Swapnaneel Ray(Team Leader), Swarnendu Banerjee, Rahul Pandey
Roll : 002311001015, 002311001016, 002311001021
Team Number: 06
Date: 07/08/2025

Question: 2B. IPC using Named Pipe (FIFO)

Using the fork system call, create a Child Process.. Transfer 1GB file
from the Parent Process to Child Process using a FIFO. Now, transfer
the same file from the Child Process to the Parent Process using
another FIFO. Now, compare the two files(use cmp or diff command)
to make sure that the same file has returned back. Also, print the time
required to do this double transfer. Attach this output to the source file
as a comment.

Execution instructions:

To create 1GB File:
dd if=/dev/urandom of=A1_06_2B_1GB_File bs=64M count=16 iflag=fullblock

gcc A1_06_2B.c -o output
./output

To Check size of file: stat A1_06_2B_1GB_FILE

Input: N/A

Output :

Time taken: 1.837 seconds
Running cmp
Files are identical

Listing large file and FIFOs:
-rw-rw-r-- 1 adminpc adminpc 1073741824 Aug  7 17:32 A1_06_2B_1GB_FILE
prw-rw-r-- 1 adminpc adminpc          0 Aug  7 18:00 FIFO1
prw-rw-r-- 1 adminpc adminpc          0 Aug  7 18:00 FIFO2
-rw-rw-r-- 1 adminpc adminpc 1073741824 Aug  7 18:00 PARENT_TO_CHILD
-rw-rw-r-- 1 adminpc adminpc 1073741824 Aug  7 18:00 RECEIVED


stat A1_06_2B_1GB_FILE
  File: A1_06_2B_1GB_FILE
  Size: 1073741824	Blocks: 2097160    IO Block: 4096   regular file

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 8192

int main(){
    // Create FIFOs
    if (mkfifo("FIFO1", 0666) == -1 && errno != EEXIST){
        perror("Error in mkfifo FIFO1");
        exit(EXIT_FAILURE);
    }
    if (mkfifo("FIFO2", 0666) == -1 && errno != EEXIST){
        perror("Error in mkfifo FIFO2");
        exit(EXIT_FAILURE);
    }
    struct timeval start, end;
    gettimeofday(&start, NULL); // Start timer

	// creating child process using fork syscall
    pid_t pid = fork();
	if (pid < 0){
        perror("Error in creating fork");
        exit(EXIT_FAILURE);
    }
    // child process
    if (pid == 0){
        int fd_in = open("FIFO1", O_RDONLY);
        if (fd_in < 0){
            perror("Error in child open FIFO1");
            exit(EXIT_FAILURE);
        }

        int fd_tmp = open("PARENT_TO_CHILD", O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (fd_tmp < 0){
            perror("Error in PARENT_TO_CHILD open");
            exit(EXIT_FAILURE);
        }

        char buf[BUF_SIZE];
        ssize_t n;
        while ((n = read(fd_in, buf, BUF_SIZE)) > 0){
            if (write(fd_tmp, buf, n) != n){
                perror("Error in child");
                exit(EXIT_FAILURE);
            }
        }
        close(fd_in);
        close(fd_tmp);
        fd_tmp = open("PARENT_TO_CHILD", O_RDONLY);
        int fd_out = open("FIFO2", O_WRONLY);
        if (fd_out < 0){
            perror("Error in PARENT_TO_CHILD open FIFO2");
            exit(EXIT_FAILURE);
        }

        while ((n = read(fd_tmp, buf, BUF_SIZE)) > 0){
            if (write(fd_out, buf, n) != n){
                perror("Error in PARENT_TO_CHILD write FIFO2");
                exit(EXIT_FAILURE);
            }
        }
        close(fd_tmp);
        close(fd_out);
    }
    // Parent Process
    // read from original file and then write to FIFO1 for child to read, then read from FIFO2
    else{
        int fd_orig = open("A1_06_2B_1GB_FILE", O_RDONLY);
        
	if (fd_orig < 0){
            perror("Error while opening file in parent");
            exit(EXIT_FAILURE);
        }

        int fd_FIFO1 = open("FIFO1", O_WRONLY);
        if (fd_FIFO1 < 0)
            perror("Error while opening FIFO1 in parent");

        char buf[BUF_SIZE];
        ssize_t n;
        while ((n = read(fd_orig, buf, BUF_SIZE)) > 0){
            if (write(fd_FIFO1, buf, n) != n){
                perror("Error in parent write FIFO1");
                exit(EXIT_FAILURE);
            }
        }
        close(fd_orig);
        close(fd_FIFO1);

        int fd_FIFO2 = open("FIFO2", O_RDONLY);
        int fd_recv = open("RECEIVED", O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (fd_recv < 0){
            perror("Error in parent open RECEIVED");
            exit(EXIT_FAILURE);
        }

        while ((n = read(fd_FIFO2, buf, BUF_SIZE)) > 0){
            if (write(fd_recv, buf, n) != n){
                perror("Error in parent write RECEIVED");
                exit(EXIT_FAILURE);
            }
        }

        close(fd_FIFO2);
        close(fd_recv);

        gettimeofday(&end, NULL);

        double elapsed = (end.tv_sec - start.tv_sec) +
                         (end.tv_usec - start.tv_usec) / 1e6;

        printf("Time taken: %.3f seconds\n", elapsed);
	printf("Running cmp \n");
        system("cmp A1_06_2B_1GB_FILE RECEIVED && echo 'Files are identical' || echo 'Files differ'");
        printf("\nListing large file and FIFOs:\n");
        system("ls -l A1_06_2B_1GB_FILE RECEIVED PARENT_TO_CHILD FIFO1 FIFO2");
    }

    return 0;
}