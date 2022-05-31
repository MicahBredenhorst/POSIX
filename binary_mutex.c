// 3b COMPLETED
// RUN:
// gcc binary_mutex.c -o binary_mutex 
// ./binary_mutex

#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>

#define NAME "SEMAPHORE"
#define SECS_TO_SLEEP 1
#define NSEC_TO_SLEEP 0

void* taskOne(void* arg);
void* taskTwo(void* arg);

int main(){
    pthread_t thread_1, thread_2;
    pthread_attr_t thread_attr;
    pthread_mutex_t mutex;

    // Set attributes to the default values
    pthread_attr_init(&thread_attr);

    // Init the mutex with default values
    pthread_mutex_init(&mutex, NULL);

    // Set scheduler to RR
    pthread_attr_setschedpolicy(&thread_attr, SCHED_RR);

    // Create the threads
    pthread_create(&thread_1, NULL, taskOne, &mutex);
    pthread_create(&thread_2, NULL, taskTwo, &mutex);

    // Wait for the threads to complete
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    // Destroy the mutex
    if(pthread_mutex_destroy(&mutex) != 0){
        perror("ERROR DESTORYING MUTEX: ");
    }
}

void* taskOne(void* arg){
    struct timespec remaining, request = {SECS_TO_SLEEP, NSEC_TO_SLEEP};
    pthread_mutex_t* mutex = arg;

    for(int i = 0; i < 5; i++){
        nanosleep(&request, &remaining);
        pthread_mutex_lock(mutex);
        printf("sectie 1\n");
        pthread_mutex_unlock(mutex);
    }
}

void* taskTwo(void* arg){
    struct timespec remaining, request = {SECS_TO_SLEEP, NSEC_TO_SLEEP};
    pthread_mutex_t* mutex = arg;

    for(int i = 0; i < 5; i++){
        nanosleep(&request, &remaining);
        pthread_mutex_lock(mutex);
        printf("sectie 2\n");
        pthread_mutex_unlock(mutex);
    }
}