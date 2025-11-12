/* 

Assignment_8T_A1_FIFO

Name : Swapnaneel Ray(Team Leader), Swarnendu Banerjee, Rahul Pandey
Roll : 002311001015, 002311001016, 002311001021
Team Number: 06
Date: 30/10/2025

Question 8: IPC using Named Pipe (FIFO)

Using the fork system call, create two Child Processes - Child1 and
Child2. Transfer 1GB file from the Parent Process to the Child1
Process using a FIFO. Lets call this FIFO as FIFO1. Now, the Child1
process should transfer the same file from the Child1 Process to the
Child2 Process using another FIFO. Let's call this FIFO as FIFO2.
And ultimately, the last transfer will take place from the Child2
process to the Parent process via FIFO3. Please note and print the
time required to do this triple transfer. Attach this output to the source
file as a comment.

Execution instructions:

gcc A1_06_8.c -o output
./output

Input: N/A

Output:

Transferring file through FIFO, from Parent to Child1, Child1 to Child2, Child2 to Parent
Child1 PID=7137
Child2 PID=7138
Child1 PID=7137
Child1 PID=7137
Child2 PID=7138
Child2 PID=7138
Child1 PID=7137. Transfer successful!
Child1 PID=7137
Child2 PID=7138. Transfer successful.
Child2 PID=7138
lrwx------ 1 user user 64 Oct 30 12:52 0 -> /dev/pts/0
lrwx------ 1 user user 64 Oct 30 12:52 0 -> /dev/pts/0
lrwx------ 1 user user 64 Oct 30 12:52 1 -> /dev/pts/0
lrwx------ 1 user user 64 Oct 30 12:52 1 -> /dev/pts/0
lrwx------ 1 user user 64 Oct 30 12:52 2 -> /dev/pts/0
lrwx------ 1 user user 64 Oct 30 12:52 2 -> /dev/pts/0
Transfer time: 0.625 seconds

Comparing the received file with original file
SUCCESS: Files are identical!

Listing all files:
-rw-rw-r-- 1 user user 1.0G Oct 30 12:36 A1_06_FILE
-rw-r--r-- 1 user user 1.0G Oct 30 12:52 RECEIVED_FILE
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#define FIFO1 "FIFO1"
#define FIFO2 "FIFO2"
#define FIFO3 "FIFO3"
#define SOURCE_FILE "A1_06_FILE"
#define DEST_FILE "RECEIVED_FILE"
#define BUFFER_SIZE (1024 * 1024)
#define FILE_SIZE (1024LL * 1024LL * 1024LL)

double get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

void create_test_file() {
    printf("Creating 1GB original file\n");
    system("dd if=/dev/urandom of=A1_06_FILE bs=1M count=1024 2>/dev/null");
    printf("Original file created.\n");
}

void create_fifos() {
    unlink(FIFO1);
    unlink(FIFO2);
    unlink(FIFO3);
   
    if (mkfifo(FIFO1, 0666) == -1 || mkfifo(FIFO2, 0666) == -1 || mkfifo(FIFO3, 0666) == -1) {
        perror("mkfifo failed");
        exit(1);
    }
}

ssize_t transfer_through_fifo(int fd_in, int fd_out, char *buffer) {
    ssize_t bytes_read, bytes_written;
    ssize_t total_bytes = 0;
   
    while ((bytes_read = read(fd_in, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = 0;
        while (bytes_written < bytes_read) {
            ssize_t result = write(fd_out, buffer + bytes_written, bytes_read - bytes_written);
            if (result == -1) {
                perror("write failed");
                return -1;
            }
            bytes_written += result;
        }
        total_bytes += bytes_read;
    }
   
    if (bytes_read == -1) {
        perror("read failed");
        return -1;
    }
   
    return total_bytes;
}

int main() {
    pid_t child1_pid, child2_pid, writer_pid;
    int status;
    double start_time, end_time, total_time;
    char *buffer;
   
    buffer = (char *)malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        perror("malloc failed");
        exit(1);
    }
   
    if (access(SOURCE_FILE, F_OK) != 0) {
        create_test_file();
    }
   
    create_fifos();
   
    system("ls -lh fifo1 fifo2 fifo3 test_file.dat 2>/dev/null");
    printf("\n");
   
    start_time = get_time();
   
    child1_pid = fork();
   
    if (child1_pid == -1) {
        perror("fork failed for child1");
        exit(1);
    }
   
    if (child1_pid == 0) {
        // CHILD1 PROCESS
        int fd_fifo1, fd_fifo2;
       
        printf("Child1 PID=%d\n", getpid());
        fd_fifo1 = open(FIFO1, O_RDONLY);
        if (fd_fifo1 == -1) {
            perror("Child1: open FIFO1 failed");
            exit(1);
        }
       
        printf("Child1 PID=%d\n", getpid());
        fd_fifo2 = open(FIFO2, O_WRONLY);
        if (fd_fifo2 == -1) {
            perror("Child1: open FIFO2 failed");
            exit(1);
        }
       
        printf("Child1 PID=%d\n", getpid());
        transfer_through_fifo(fd_fifo1, fd_fifo2, buffer);
       
        printf("Child1 PID=%d. Transfer successful!\n", getpid());
        close(fd_fifo1);
        close(fd_fifo2);
        free(buffer);
       
        printf("Child1 PID=%d\n", getpid());
        char cmd[100];
        snprintf(cmd, sizeof(cmd), "ls -l /proc/%d/fd/ 2>/dev/null | grep -v 'total'", getpid());
        system(cmd);
       
        exit(0);
    }
   
    // Create Child2
    child2_pid = fork();
   
    if (child2_pid == -1) {
        perror("fork failed for child2");
        exit(1);
    }
   
    if (child2_pid == 0) {
        // CHILD2 PROCESS
        int fd_fifo2, fd_fifo3;
       
        printf("Child2 PID=%d\n", getpid());
        fd_fifo2 = open(FIFO2, O_RDONLY);
        if (fd_fifo2 == -1) {
            perror("Child2: open FIFO2 failed");
            exit(1);
        }
       
        printf("Child2 PID=%d\n", getpid());
        fd_fifo3 = open(FIFO3, O_WRONLY);
        if (fd_fifo3 == -1) {
            perror("Child2: open FIFO3 failed");
            exit(1);
        }
       
        printf("Child2 PID=%d\n", getpid());
        transfer_through_fifo(fd_fifo2, fd_fifo3, buffer);
       
        printf("Child2 PID=%d. Transfer successful.\n", getpid());
        close(fd_fifo2);
        close(fd_fifo3);
        free(buffer);
       
        printf("Child2 PID=%d\n", getpid());
        char cmd[100];
        snprintf(cmd, sizeof(cmd), "ls -l /proc/%d/fd/ 2>/dev/null | grep -v 'total'", getpid());
        system(cmd);
       
        exit(0);
    }
   
    printf("Transferring file through FIFO, from Parent to Child1, Child1 to Child2, Child2 to Parent\n");
   
    // PARENT PROCESS - Fork to create writer process
    writer_pid = fork();
   
    if (writer_pid == -1) {
        perror("fork failed for writer");
        exit(1);
    }
   
    if (writer_pid == 0) {
        int fd_source = open(SOURCE_FILE, O_RDONLY);
        if (fd_source == -1) {
            perror("Writer: open source file failed");
            exit(1);
        }
       
        int fd_fifo1 = open(FIFO1, O_WRONLY);
        if (fd_fifo1 == -1) {
            perror("Writer: open FIFO1 failed");
            exit(1);
        }
       
        transfer_through_fifo(fd_source, fd_fifo1, buffer);
       
        close(fd_source);
        close(fd_fifo1);
        free(buffer);
        exit(0);
    }
   
    // parent process 
    int fd_fifo3 = open(FIFO3, O_RDONLY);
    if (fd_fifo3 == -1) {
        perror("Parent: open FIFO3 failed");
        exit(1);
    }
   
    int fd_dest = open(DEST_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_dest == -1) {
        perror("Parent: open destination file failed");
        exit(1);
    }
   
    transfer_through_fifo(fd_fifo3, fd_dest, buffer);
   
    close(fd_fifo3);
    close(fd_dest);
   
    // Wait for all child processes to complete
    waitpid(writer_pid, &status, 0);
    waitpid(child1_pid, &status, 0);
    waitpid(child2_pid, &status, 0);
   
    // End timing
    end_time = get_time();
    total_time = end_time - start_time;
   
    printf("Transfer time: %.3f seconds\n", total_time);
    printf("\n");
   
    printf("Comparing the received file with original file\n");
    int cmp_result = system("cmp A1_06_FILE RECEIVED_FILE");
   
    if (cmp_result == 0) {
        printf("SUCCESS: Files are identical!\n");
    } else {
        printf("ERROR: Files differ!\n");
    }
   
    printf("\nListing all files: \n");
    system("ls -lh A1_06_FILE RECEIVED_FILE");
   
    free(buffer);
    unlink(FIFO1);
    unlink(FIFO2);
    unlink(FIFO3);
   
    return 0;
}
