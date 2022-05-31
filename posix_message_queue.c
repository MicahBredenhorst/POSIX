// 2a completed
// RUN:
// gcc posix_message_queue.c -o posix_message_queue 
// ./posix_message_queue

#include <pthread.h>
#include <stdio.h>
#include <fcntl.h>        
#include <sys/stat.h>        
#include <mqueue.h>
#include <errno.h>
#include <stdlib.h>

#define QUEUE_NAME "/queue_1"
#define QUEUE_BUFFER_SIZE 50
#define QUEUE_PERMISSIONS 0777

void* send(void* args);
void* receive(void* args);
void fill(int* buffer);

int main(){
    pthread_t thread_1, thread_2;

    // Create the threads
    pthread_create(&thread_1, NULL, send, NULL);
    pthread_create(&thread_2, NULL, receive, NULL);

    // Wait for the threads to finish
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
}

void* send(void* args){
    mqd_t queue_server;
    
    // Create and open the message queue for sending the integer array
    queue_server = mq_open(QUEUE_NAME, O_WRONLY | O_CREAT, QUEUE_PERMISSIONS, NULL);
    if(queue_server == -1){
        perror("ERROR while creating sender: ");
    }

    // fill the integer array with 50 integers
    int buffer[QUEUE_BUFFER_SIZE];
    for(int x = 0; x < QUEUE_BUFFER_SIZE; x++){
        buffer[x] = x + 1;
    }

    // Send the message
    if(mq_send(queue_server, (char *) &buffer, sizeof(buffer), 0) == -1){
        perror("ERROR while sending: ");
    };

    printf("DONE SENDING\n");

    // Close the message queue
    mq_close(queue_server);
}

void* receive(void* args){
    mqd_t queue_client; 

    // Create and open the message queue for receiving the integer array.
    queue_client = mq_open(QUEUE_NAME, O_RDONLY, QUEUE_PERMISSIONS);
    if(queue_client == -1){
        perror("ERROR while creating receiver: ");
    }

    // Get the size for the message queue
    struct mq_attr attr;
    mq_getattr(queue_client, &attr);

    int buffer[QUEUE_BUFFER_SIZE];

    // Read the message 
    unsigned int priority = 0;
    if(mq_receive(queue_client, (char *) &buffer, attr.mq_msgsize, &priority) == -1){
        perror("ERROR while receiving: ");
    }

    // Loop through the buffer
    for(int x = 0; x < QUEUE_BUFFER_SIZE; x++){
        printf("MSG INDEX %d: %d\n", x, buffer[x]);
    }

    printf("DONE READING\n");

    // Close the message queue
    mq_close(queue_client);
}