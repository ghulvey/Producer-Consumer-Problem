#include "sharedObj.h"

int main() {

    // Create a shared memory object with name
    int fd = shm_open(NAME, O_CREAT | O_RDWR, 0666);
    // Set size of shared memory object
    ftruncate(fd, SIZE);

    // Open and map shared memory object 
    int *share = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    if(share == MAP_FAILED){
        printf("Producer: Mapping Failed\n");
        return 1;
    }

    // Open semaphores
    sem_t *full = sem_open(semFullName, O_CREAT, 0666, 0);
    sem_t *empty = sem_open(semEmptyName, O_CREAT, 0666, 1);
    sem_t *mutex = sem_open(semMutexName, O_CREAT, 0666, 1);

    
    int loop = 10;

    printf("\n-PRODUCER PROCESS STARTED-\n");

    while(loop--) {

        // Wait for table to be empty
        sem_wait(empty);
        sleep(1);

        // Ensure no processes are in critical section
        sem_wait(mutex);
        
        // CRITICAL SECTION

        // Store random integers in shared memory
        share[0] = rand() % 100;
        share[1] = rand() % 100;

        printf("items produced: %d + %d = ?\n", share[0], share[1]);

        // Leave critcial section, signal full
        sem_post(mutex);
        sem_post(full);
    }

    printf("-PRODUCER PROCESS ENDED-\n");
    
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