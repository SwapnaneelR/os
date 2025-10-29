#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

long long Total_1 = 100000, Total_2 = 100000, Total_3 = 100000;
pthread_mutex_t m1, m2, m3;

void *worker_1(){
	while(1){
		int random_val = rand() % 11;
		int choice = rand() % 2;

		if(choice == 1){
			pthread_mutex_lock(&m1);
			pthread_mutex_lock(&m2);
			Total_1 -= random_val;
			Total_2 += random_val; 
			pthread_mutex_unlock(&m2);
			pthread_mutex_unlock(&m1);
		}else{
			pthread_mutex_lock(&m1);
			pthread_mutex_lock(&m3);
			Total_1 -= random_val;
			Total_3 += random_val;
			pthread_mutex_unlock(&m3);
			pthread_mutex_unlock(&m1);
		}
	}
	return NULL;
}

void *worker_2(){
	while(1){
		int random_val = rand() % 21;
		int choice = rand() % 2;

		if(choice == 1){
			pthread_mutex_lock(&m1);
			pthread_mutex_lock(&m2);
			Total_2 -= random_val; 
			Total_1 += random_val;
			pthread_mutex_unlock(&m2);
			pthread_mutex_unlock(&m1);
		}else{
			pthread_mutex_lock(&m2);
			pthread_mutex_lock(&m3);
			Total_2 -= random_val;
			Total_3 += random_val;
			pthread_mutex_unlock(&m3);
			pthread_mutex_unlock(&m2);
		}
	}
	return NULL;
}

void *worker_3(){
	while(1){
		int random_val = rand() % 31;
		int choice = rand() % 2;

		if(choice == 1){
			pthread_mutex_lock(&m1);
			pthread_mutex_lock(&m3);
			Total_3 -= random_val;
			Total_1 += random_val; 
			pthread_mutex_unlock(&m3);
			pthread_mutex_unlock(&m1);
		}else{
			pthread_mutex_lock(&m2);
			pthread_mutex_lock(&m3);
			Total_3 -= random_val;
			Total_2 += random_val;
			pthread_mutex_unlock(&m3);
			pthread_mutex_unlock(&m2);
		}
	}
	return NULL;
}

void *worker_4(){
	while(1){
		pthread_mutex_lock(&m1);
		pthread_mutex_lock(&m2);
		pthread_mutex_lock(&m3);
		printf("Total_1 = %10lld\tTotal_2 = %10lld\tTotal_3 = %10lld\tGrand_Total = %10lld\n",Total_1, Total_2, Total_3, (Total_1 + Total_2 + Total_3));
		pthread_mutex_unlock(&m1);
		pthread_mutex_unlock(&m2);
		pthread_mutex_unlock(&m3);
	}
	return NULL;
}

int main(){
	pthread_t Th1, Th2, Th3, Th4;

	pthread_mutex_init(&m1, NULL);
	pthread_mutex_init(&m2, NULL);
	pthread_mutex_init(&m3, NULL);

	pthread_create(&Th1, NULL, worker_1, NULL);
	pthread_create(&Th2, NULL, worker_2, NULL);
	pthread_create(&Th3, NULL, worker_3, NULL);
	pthread_create(&Th4, NULL, worker_4, NULL);

	pthread_join(Th1, NULL);	
	pthread_join(Th2, NULL);	
	pthread_join(Th3, NULL);
	pthread_join(Th4, NULL);

	pthread_mutex_destroy(&m1);
	pthread_mutex_destroy(&m2);
	pthread_mutex_destroy(&m3);

	return 0;
}
