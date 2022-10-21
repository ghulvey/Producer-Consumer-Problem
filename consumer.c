#include "sharedObj.h"


int main() {

    // Create a shared memory object with name
    int fd = shm_open(NAME, O_CREAT | O_RDWR, 0666);
    // Set size of shared memory object
    ftruncate(fd, SIZE);

    // Open and map shared memory object 
    int *share = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    
    if(share == MAP_FAILED){
        printf("Consumer: Mapping Failed\n");
        return 1;
    }

    // Open semaphores
    sem_t *full = sem_open(semFullName, O_CREAT, 0666, 0);
    sem_t *empty = sem_open(semEmptyName, O_CREAT, 0666, 1);
    sem_t  *mutex = sem_open(semMutexName, O_CREAT, 0666, 1);

    int loop = 10;

    printf("\n-CONSUMER PROCESS STARTED-\n");

    while(loop--) {

        // Wait for table to be full
        sem_wait(full);
        sleep(1);

        // Ensure no processes are in critical section
        sem_wait(mutex);
        
        // CRITICAL SECTION

        // Read integers from shared memory and caluclate the sum
        int result = share[0] + share[1];
        printf("items consumed: %d + %d = %d\n", share[0], share[1], result);
        
        // Leave critical section, signal empty
        sem_post(mutex);
        sem_post(empty);
    }

    printf("-CONSUMER PROCESS ENDED-\n");


   // Close and unlink semaphores
    sem_close(full);
    sem_close(empty);
    sem_close(mutex);

    sem_unlink(semFullName);
    sem_unlink(semEmptyName);
    sem_unlink(semMutexName);

    // Close the shared memory object
    munmap(share, SIZE);
    close(fd);
    shm_unlink(NAME);

    return 0;

}