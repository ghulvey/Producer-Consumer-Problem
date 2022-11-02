# Producer Consumer Problem

**CS 33211** - Programming Assignment 1

**Author:** Gavin Hulvey 

**Assignment Description:** The producer generates items and puts items onto the table. The consumer will pick up items. The table can only hold two items at the same time. When the table is complete, the producer will wait. When there are no items, the consumer will wait. We use semaphores to synchronize producer and consumer.  Mutual exclusion should be considered. We use threads in the producer program and consumer program. Shared memory is used for the “table”.

## Run Instructions

This project can be dowloaded using git. The producer and consumer processes can be started in one of two ways, via gcc or Make

### Cloning the Repository

Run the following commands after changing to your desired directory to store the repository. Note: the name `Producer-Consumer-Problem` can be changed to any name of your choosing, this will be the folder where the repository will be contained.

```
git clone https://github.com/ghulvey/Producer-Consumer-Problem.git Producer-Consumer-Problem
cd Producer-Consumer-Problem
```

### Starting with gcc

Enter each of the following commands on a terminal in the code directory

```
gcc producer.c -pthread -lrt -o producer
gcc consumer.c -pthread -lrt -o consumer
./producer & ./consumer &
```

### Starting with Make

Run one of the following commands based on your needs
- `make` or `make compileRun` compile and start the processes
- `make compile` only compile the code
- `make run` run previously compiled code
- `make clean` deletes the executable files

## Sample Output

```
-PRODUCER PROCESS STARTED-

-CONSUMER PROCESS STARTED-
item produced: 52 in pos: 0
item consumed: 52 in pos: 0
item produced: 84 in pos: 1
item produced: 49 in pos: 0
item consumed: 84 in pos: 1
item consumed: 49 in pos: 0
item produced: 20 in pos: 1
item consumed: 20 in pos: 1
item produced: 99 in pos: 0
item produced: 26 in pos: 1
item consumed: 99 in pos: 0
item consumed: 26 in pos: 1
item produced: 4 in pos: 0
item produced: 80 in pos: 1
item consumed: 4 in pos: 0
item produced: 1 in pos: 0
item consumed: 80 in pos: 1
item consumed: 1 in pos: 0
item produced: 35 in pos: 1
-PRODUCER PROCESS ENDED-
item consumed: 35 in pos: 1
-CONSUMER PROCESS ENDED-
```

## Implementation

Note that `sleep(rand()%x)` was called in both process inside and outside of the critical section to demonstrate that processes are often out of sync. Without this the producer and consumer processes in this project are in near perfect sync.

The producer process will produce 10 items to shared memory. The consumer will read 10 items from shared memory. The data being exchanged by the two processes are random integers. As the producer generates items the value is outputted to the user as well as its position in shared memory. As the consumer reads items it outputs the item as well as its table postion. The text `produced` and `consumed` diferentiate the processes, for example the producer will never print `consumer`. 

### Shared Memory

Each process opens a shared memory object of the same name and size specified in the header file `sharedObj.h`. The shared memory is mapped to a `struct table` which has a buffer and the location of the next position to be produced to or consumed from. 

```
// Create a shared memory object with name
int fd = shm_open(NAME, O_CREAT | O_RDWR, 0666);
    
// Set size of shared memory object
ftruncate(fd, SIZE);
    
// Open and map shared memory object 
struct table *share = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
```

### Semaphores

The two process use three semaphores for synronization. Their names are defined in the header file `sharedObj.h`. 

```
sem_t *full = sem_open(semFullName, O_CREAT, 0666, 0);
sem_t *empty = sem_open(semEmptyName, O_CREAT, 0666, bufferSize);
sem_t *mutex = sem_open(semMutexName, O_CREAT, 0666, 1);
```

The `full` semaphore is triggered when the buffer contains data for the consumer to read. The `empty` semaphore is triggered when the buffer has room for items to be added. The `mutex` semaphore ensures mutual exclusion, it asserts that only one process can access the critical section in the case multiple consumer or producer process are running.

### Synchronization

The producer process is allways allowed to enter the critical section before the consumer. The following is the semaphore code for the prodcuer:

```
sem_wait(empty); // Wait for table to have space
sem_wait(mutex); // Ensure no processes are in critical section
// CRITICAL SECTION
sem_post(mutex); // Exit the critical section, allow other processes to enter
sem_post(full); // Table has data, let the consumer read
```

The semaphore code for the consumer process is essentially the same, except `empty` and `full` are switched.

### Critical Section

In the producer process data is written to the shared table, and the `in` pointer is advanced to the next avalible space. In the consumer process data is read and outputted to the user from the shared table, and the `out` pointer is advanced to the next data value.

```
// Store random integers in shared memory
share->buffer[share->in] = rand() % 100;

// Advance in pointer
share->in = (share->in+1)%bufferSize;
```

### Clean Up

All the semaphores are closed and unlinked. This reduces errors when the program is reexecuted.

```
sem_close(x);
sem_unlink(x);
```

The shared memory object is also closed.

```
munmap(share, SIZE);
close(fd);
shm_unlink(NAME);
```

## Video Demo
https://user-images.githubusercontent.com/19355415/199373599-ab2d370f-1fd0-4215-837e-e02fe3ca9b26.mp4


