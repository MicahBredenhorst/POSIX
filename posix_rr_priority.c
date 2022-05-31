// 1b COMPLETED
// RUN:
// gcc posix_rr_priority.c -o posix_rr_priority 
// ./posix_rr_priority

#include <pthread.h>
#include <stdio.h>

void* taskOne();    // infinite
void* taskTwo();    // infinite
void* taskThree();  // finite
void* taskFour();   // finite

int main(){
    pthread_t thread_1, thread_2, thread_3, thread_4;
    pthread_attr_t thread_attr_rr_high, thread_attr_rr;
    struct sched_param param;

    // Init default attributes for the thread 
    pthread_attr_init(&thread_attr_rr_high);
    pthread_attr_init(&thread_attr_rr);

    // Set the scheduling policy to round robin
    pthread_attr_setschedpolicy(&thread_attr_rr_high, SCHED_RR);
    pthread_attr_setschedpolicy(&thread_attr_rr, SCHED_RR);

    // Get the current priority
    pthread_attr_getschedparam(&thread_attr_rr_high, &param);
    
    // Set high policy for thread_3 and thread_4
    param.sched_priority = 20;

    // Create threads with the sepcified attributes and methods
    pthread_create(&thread_1, &thread_attr_rr, taskOne, NULL);
    pthread_create(&thread_2, &thread_attr_rr, taskTwo, NULL); 
    pthread_create(&thread_3, &thread_attr_rr_high, taskThree, NULL);
    pthread_create(&thread_4, &thread_attr_rr_high, taskFour, NULL); 

    // Destroy configuration since it is no longer needed
    pthread_attr_destroy(&thread_attr_rr_high);
    pthread_attr_destroy(&thread_attr_rr);

    // wait for thread_3 and thread_4 to end.
    pthread_join(thread_3, NULL);
    pthread_join(thread_4, NULL);

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
}

void* taskOne(){
    int i,j,m,n;
    while(1)
    {
        for(i=0;i<5;i++)
        {
            for(j=1;j<=8;j++)
            {
                printf("taak 1 %i\n",j);
                for (m=0;m<=1000;m++)
                    for(n=0;n<=10000;n++);
            }
        }
    }
}

void* taskTwo(){
    int i,j,m,n;
    while(1)
    {
        for(i=0;i<5;i++)
        {
            for(j=1;j<=8;j++)
            {
                printf("taak 2 %i\n",j);
                for (m=0;m<=1000;m++)
                    for(n=0;n<=10000;n++);
            }
        }
    }
}

void* taskThree(){
    int i,j,m,n;
    for(i=0;i<5;i++)
    {
        for(j=1;j<=8;j++)
        {
            printf("taak 3 %i\n",j);
            for (m=0;m<=1000;m++)
                for(n=0;n<=10000;n++);
        }
    }

}

void* taskFour(){
    int i,j,m,n;
    for(i=0;i<5;i++)
    {
        for(j=1;j<=8;j++)
        {
            printf("taak 4 %i\n",j);
            for (m=0;m<=1000;m++)
                for(n=0;n<=10000;n++);
        }
    }
}