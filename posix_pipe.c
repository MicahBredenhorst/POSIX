// 2b COMPLETED
// RUN:
// gcc posix_pipe.c -o posix_pipe
// ./posix_pipe

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

void* send();
void* receive();
void fill(int* buffer);
void read_buffer(int* buffer);


#define BUFFER_SIZE 200
#define NUMBER_RANGE 50

struct thread_args {
    int* fildes;
};

int main()
{
    int fildes[2];  // File descriptor, which rever to the read and write ends of the pipe.
    pthread_t thread_1, thread_2;
    struct thread_args args;
    
    // Add args 
    args.fildes = fildes;

    // Create and validate an interprocess channel
    if(pipe(fildes) == -1){
        perror("ERROR PIPE: ");
    }

    pthread_create(&thread_1, NULL, send, &args);
    pthread_create(&thread_2, NULL, receive, &args);

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
}

void* send(void* args)
{
    struct thread_args *struct_ptr = (struct thread_args*) args;

    // Fill the buffer with 50 integers
    int buffer[NUMBER_RANGE];
    int input_data = 1;
    for(int i = 0; i < NUMBER_RANGE; i++){
        buffer[i] = input_data;
        input_data++;
    }

    // Send the contents over the pipe
    write(struct_ptr->fildes[1], buffer, BUFFER_SIZE);
    close(struct_ptr->fildes[1]); // close write pipe ouput
}

void* receive(void* args)
{
    struct thread_args *struct_ptr = (struct thread_args*) args;

    // Read the contents of the pipe
    int buffer_out[NUMBER_RANGE];
    read(struct_ptr->fildes[0], buffer_out, BUFFER_SIZE);
    close(struct_ptr->fildes[0]); // close read pipe end 

    // Read the contents of the buffer
    read_buffer(buffer_out);
    printf("END_RECEIVE\n");
}

void read_buffer(int* buffer)
{
    for(int x = 0; x < NUMBER_RANGE; x++){
        printf("MSG INDEX %d: %d\n", x, buffer[x]);
    }
}