// 1a COMPLETE
// RUN:
// gcc posix_rr.c -o posix_rr 
// ./posix_rr

#include <pthread.h>
#include <stdio.h>

void* taskOne();
void* taskTwo();
void* taskThree();
void* taskFour();

int main(){
    pthread_t thread_1, thread_2, thread_3, thread_4;
    pthread_attr_t thread_attr;

    // Init default attributes for the thread 
    pthread_attr_init(&thread_attr);

    // Set the scheduling policy to round robin
    pthread_attr_setschedpolicy(&thread_attr, SCHED_RR);
    
    // Create threads with the specified attributes and methods
    pthread_create(&thread_1, &thread_attr, taskOne, NULL);
    pthread_create(&thread_2, &thread_attr, taskTwo, NULL);
    pthread_create(&thread_3, &thread_attr, taskThree, NULL);
    pthread_create(&thread_4, &thread_attr, taskFour, NULL);

    // Destroy configuration since it is no longer needed
    pthread_attr_destroy(&thread_attr);

    // Wait for the threads to complete (they never will)
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
    pthread_join(thread_3, NULL);
    pthread_join(thread_4, NULL);
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
    while(1)
    {
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
}

void* taskFour(){
    int i,j,m,n;
    while(1)
    {
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
}