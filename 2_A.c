#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/*
Name : Swapnaneel Ray (Team Leader), Swarnendu Banerjee, Rahul Pandey 
Roll : 002311001015, 002311001016, 002311001021
Team Number: 06
Date: 07/08/2025

Question: A. Signal Handling

Catch the signal ‘SIGINT’ and display “Ha Ha, Not Stopping”. Use ‘signal’ system call.
Always use “perror” to check the return status of a library/system call.

Execution Instructions : 

gcc A1_06_2A.c -o output
./output

Press Ctrl+C to send SIGINT signal
Press Ctrl+Z to suspend process

Input: N/A

Output:

adminpc@adminpc-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/Downloads/OS_Assignment_2TO8$ ./output 
^C Ha Ha, Not Stopping
^C Ha Ha, Not Stopping
^C Ha Ha, Not Stopping
^C Ha Ha, Not Stopping
^Z
[4]+  Stopped                 ./output

*/

// Function to handle SIGINT signal
void sig_int_handler(int sig) {
    printf(" Ha Ha, Not Stopping\n");
}

int main() {
    if (signal(SIGINT, sig_int_handler ) == SIG_ERR) {
        // Checking error using perror
	perror("Failure");
        exit(EXIT_FAILURE);
    }
    
    // Infinite loop so that program runs until we send signal
    while (1) {
	
    }

    return 0;
}