// 3a COMPLETED
// RUN:
// gcc binary_semafoor.c -o binary_semafoor 
// ./binary_semafoor

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
void* taskOne();
void* taskTwo();

sem_t *semaphore;

int main()
{
    pthread_t thread_1, thread_2;
    pthread_attr_t thread_attr;

    semaphore = sem_open(NAME, O_CREAT | O_EXCL, 0644, 1);

    // Init as a binary semaphore
    sem_init(semaphore, 0, 1);

    // Set attributes to the default values
    pthread_attr_init(&thread_attr);

    // Set scheduler to RR
    pthread_attr_setschedpolicy(&thread_attr, SCHED_RR);

    // Create the threads
    pthread_create(&thread_1, NULL, taskOne, NULL);
    pthread_create(&thread_2, NULL, taskTwo, NULL);

    // Wait for the threads to complete
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    // Destroy the semaphore
    sem_destroy(semaphore);
    sem_unlink(NAME);
}

void* taskOne(){
    struct timespec remaining, request = {SECS_TO_SLEEP, NSEC_TO_SLEEP};

    for(int i = 0; i < 5; i++){
        nanosleep(&request, &remaining);
        sem_wait(semaphore);

        // Critical section
        printf("sectie 1\n");

        sem_post(semaphore);
    }
}

void* taskTwo(){
    struct timespec remaining, request = {SECS_TO_SLEEP, NSEC_TO_SLEEP};

    for(int i = 0; i < 5; i++){
        nanosleep(&request, &remaining);
        sem_wait(semaphore);

        // Critical section
        printf("sectie 2\n");

        sem_post(semaphore);
    }

}