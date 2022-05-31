// 2c COMPLETED
// RUN:
// gcc posix_shared_memory.c -o posix_shared_memory
// ./posix_shared_memory

#include <sys/mman.h>
#include <pthread.h>
#include <stdio.h>
#include <fcntl.h> 
#include <sys/stat.h>
#include <unistd.h>

void* read_from_memory();
void* write_to_memory();

#define NAME "shared_memory"
#define DATA_SIZE 50

int main()
{
    pthread_t thread_1, thread_2;
        
    // Create the threads
    pthread_create(&thread_1, NULL, write_to_memory, NULL);
    pthread_create(&thread_2, NULL, read_from_memory, NULL);

    // Wait for the threads to complete
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    // Unlink
    shm_unlink(NAME);
}

void* write_to_memory()
{   

    // Open the shared memory in write mode
    int shm_desc = shm_open(NAME, O_CREAT | O_EXCL | O_RDWR, 0600);
    if(shm_desc == -1){
        perror("ERROR - WRITER - SHM_OPEN: ");
    }

    // Truncate a shm_desc to lenght DATA_SIZE.
    ftruncate(shm_desc, DATA_SIZE);

    // Create a new mapping in virtual space
    int *data = (int *)mmap(0, DATA_SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm_desc, 0);
    printf("Mapped address: %p\n", data);

    for(int i = 0; i < DATA_SIZE; i++){
        data[i] = i + 1;
    }
    
    printf("DATA WRITTEN TO SHARED MEMORY\n");

    // Remove mapping
    munmap(data, DATA_SIZE);

    // Shut the object
    close(shm_desc);
}

void* read_from_memory()
{
    // Open the shared memory in read mode
    int shm_desc = shm_open(NAME, O_RDONLY, 0666);
    if(shm_desc == -1){
        perror("ERROR - READER - SHM_OPEN: ");
    }
    // Create a new mapping in virtual space
    int *data = (int *)mmap(0, DATA_SIZE, PROT_READ, MAP_SHARED, shm_desc, 0);
    printf("Mapped address: %p\n", data);

    printf("READ DATA FROM SHARED MEMORY:\n");
    for(int i = 0; i < DATA_SIZE; i++){
        printf("%d\n", data[i]);
    }

    // Remove mapping
    munmap(data, DATA_SIZE);

    // Shut the object
    close(shm_desc);
}