// 1c COMPLETED
// RUN:
// gcc posix_periods.c -o posix_periods 
// ./posix_periods

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* print_information(void* args);

struct thread_args {
    int thread_index;
    int period;
};

int main(){
    pthread_t thread_1, thread_2;
    pthread_attr_t thread_attr;
    int period_1, period_2;
    struct timespec timespec_1, timespec_2;
    struct thread_args thread_1_args, thread_2_args;

    // init thread attributes with default values
    pthread_attr_init(&thread_attr);

    // Get period timing struct
    sched_rr_get_interval(thread_1, &timespec_1);
    sched_rr_get_interval(thread_2, &timespec_2);
    
    // Setup function arguments
    thread_1_args.thread_index = 1;
    thread_2_args.thread_index = 2;

    thread_1_args.period = period_1;
    thread_2_args.period = period_2;

    // Set the period timing:

    timespec_1.tv_sec = 0.5;
    timespec_2.tv_sec = 1.3;

    // Create threads
    pthread_create(&thread_1, NULL, print_information, &thread_1_args);
    pthread_create(&thread_2, NULL, print_information, &thread_2_args);

    // Wait for threads to finish (however they will never finish)
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
}

void* print_information(void* args){
    struct thread_args *struct_ptr = (struct thread_args*) args;
    while(1){
        printf("Thread: %d, period number: %d\n", struct_ptr->thread_index, struct_ptr->period);
        struct_ptr->period++;
    }
}