/*

Group Number : 06
Date : 04/09/2025

Team details : 

Name : Swapnaneel Ray(Team Leader), Swarnendu Banerjee, Rahul Pandey
Roll : 002311001015, 002311001016, 002311001021

Assignment No : 5
Assignment Details : 
Consider a main process which creates three threads Th1, Th2, and Th3. The main
process also creates two random quantities (X, Y), both less than 10. These two
values will be placed by the main process in the shared memory (One variant of IPC
Primitive) that is accessible by all the three threads Th1, Th2 and Th3. The shared
memory will be created by the main process using shmat/shmget calls.

Input Description : 
 Enter the number of pairs (X,Y) 
Output Description : 
 The program prints the values of A,B and C after thread synchronization.

Compilation Command : 
 gcc A1_06_5.c -o out -pthread
Execution sequence : 
 ./out <no_of_pairs>

Output : 
------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status      
0x00000000 65544      adminpc    666        100        1          dest         
0x00000000 9          adminpc    600        524288     2          dest         
0x00000000 20         adminpc    600        524288     2          dest         
0x00001234 98346      adminpc    666        200        1                       


Index | X | Y | A=X*Y | B=2X+2Y+1 | C=B/A
-------------------------------------------------
    0 | 4 | 0 |      0 |           9 | 0.000000
    1 | 4 | 5 |     20 |          19 | 0.950000
    2 | 9 | 3 |     27 |          25 | 0.925926
    3 | 6 | 2 |     12 |          17 | 1.416667
    4 | 8 | 4 |     32 |          25 | 0.781250
    5 | 1 | 0 |      0 |           3 | 0.000000
    6 | 8 | 5 |     40 |          27 | 0.675000
    7 | 5 | 7 |     35 |          25 | 0.714286
    8 | 4 | 4 |     16 |          17 | 1.062500
    9 | 1 | 4 |      4 |          11 | 2.750000
*/

#include <stdlib.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

#define MAX_PAIRS 1000010

typedef struct {
    int X, Y, A, B;
    float C;
} Data;

Data *shared_data;
int pair_count;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_A_done = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_B_done = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_C_done = PTHREAD_COND_INITIALIZER;

int idx = 0;              // current idx being processed
int phase = 0;              // 0 = A phase, 1 = B phase, 2 = C phase
int threads_done = 0;       // count threads finished current phase

void wait_for_phase(int p) {
    while (phase != p)
        pthread_cond_wait(&cond_C_done, &mutex);
}

void signal_phase(int next_phase) {
    phase = next_phase;
    threads_done = 0;
    pthread_cond_broadcast(&cond_C_done);
}

void* compute_A(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex);
        while (phase != 0 && idx < pair_count)
            pthread_cond_wait(&cond_C_done, &mutex);
        if (idx >= pair_count) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        int i = idx;
        pthread_mutex_unlock(&mutex);

        // Compute A
        shared_data[i].A = shared_data[i].X * shared_data[i].Y;

        pthread_mutex_lock(&mutex);
        threads_done++;
        if (threads_done == 1) { // only thread A signals phase change
            phase = 1;
            pthread_cond_broadcast(&cond_C_done);
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* compute_B(void* arg) {
    for (;;) {
        pthread_mutex_lock(&mutex);
        while (phase != 1 && idx < pair_count)
            pthread_cond_wait(&cond_C_done, &mutex);
        if (idx >= pair_count) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        int i = idx;
        pthread_mutex_unlock(&mutex);

        // Compute B
        shared_data[i].B = 2 * shared_data[i].X + 2 * shared_data[i].Y + 1;

        pthread_mutex_lock(&mutex);
        threads_done++;
        if (threads_done == 2) { // thread B signals phase 2 when both A and B done
            phase = 2;
            pthread_cond_broadcast(&cond_C_done);
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* compute_C(void* arg) {
    	for (;;) {
        pthread_mutex_lock(&mutex);
        while (phase != 2 && idx < pair_count)
            pthread_cond_wait(&cond_C_done, &mutex);
        if (idx >= pair_count) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        int i = idx;
        pthread_mutex_unlock(&mutex);

        int A = shared_data[i].A;
        int B = shared_data[i].B;
        shared_data[i].C = (A != 0) ? ((float)B / (float)A) : 0.0f;

        pthread_mutex_lock(&mutex);
        threads_done++;
        if (threads_done == 3) { // all threads done this idx, move to next
            threads_done = 0;
            idx++;
            phase = 0;
            pthread_cond_broadcast(&cond_C_done);
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    // taking input from command line arguments
	if (argc != 2) {
        printf("Usage: %s <number_of_pairs>\n", argv[0]);
        return 1;
    }

    pair_count = atoi(argv[1]);
    if (pair_count <= 0 || pair_count > MAX_PAIRS) {
        printf("Please enter a number between 1 and %d\n", MAX_PAIRS);
        return 1;
    }

    // declaring key for the shared memory segment
    key_t key = 0x1234;
    // creating the memory segment using shmget
    int shmid = shmget(key, sizeof(Data) * pair_count, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        return 1;
    }

    shared_data = (Data*)shmat(shmid, NULL, 0);
    if (shared_data == (void*)-1) {
        perror("shmat failed");
        return 1;
    }
    int i;
    srand(time(NULL));
    system("ipcs -m");
    for ( i = 0; i < pair_count; i++) {
        shared_data[i].X = rand() % 10;
        shared_data[i].Y = rand() % 10;
        shared_data[i].A = 0;
        shared_data[i].B = 0;
        shared_data[i].C = 0.0f;
    }
    pthread_t th1, th2, th3;

    // creating 3 threads to compute A,B and C concurrently
    pthread_create(&th1, NULL, compute_A, NULL);
    pthread_create(&th2, NULL, compute_B, NULL);
    pthread_create(&th3, NULL, compute_C, NULL);

    // making sure main thread waits for the rest to complete
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);

    printf("\nIndex | X | Y | A=X*Y | B=2X+2Y+1 | C=B/A\n");
    printf("-------------------------------------------------\n");
    for ( i = 0; i < pair_count; i++) {
        printf("%5d | %d | %d | %6d | %11d | %.6f\n",
               i, shared_data[i].X, shared_data[i].Y,
               shared_data[i].A, shared_data[i].B, shared_data[i].C);
    }

    // cleaning up memory before exiting
    shmdt(shared_data);
    shmctl(shmid, IPC_RMID, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_A_done);
    pthread_cond_destroy(&cond_B_done);
    pthread_cond_destroy(&cond_C_done);
    return 0;
}


