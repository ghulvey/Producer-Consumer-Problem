# Producer Consumer Problem

**CS 33211** - Programming Assignment 1

**Author:** Gavin Hulvey 

The producer generates items and puts items onto the table. The consumer will pick up items. The table can only hold two items at the same time. When the table is complete, the producer will wait. When there are no items, the consumer will wait. We use semaphores to synchronize producer and consumer.  Mutual exclusion should be considered. We use threads in the producer program and consumer program. Shared memory is used for the “table”.

## Run Instructions

The producer and consumer processes can be started in one of two ways, via gcc or Make

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
-CONSUMER PROCESS STARTED-

-PRODUCER PROCESS STARTED-
items produced: 77 in pos: 0
items produced: 35 in pos: 1
items consumed: 77 in pos: 0
items produced: 49 in pos: 0
items consumed: 35 in pos: 1
items produced: 27 in pos: 1
items consumed: 49 in pos: 0
items produced: 63 in pos: 0
items consumed: 27 in pos: 1
items produced: 26 in pos: 1
items consumed: 63 in pos: 0
items produced: 11 in pos: 0
items consumed: 26 in pos: 1
items consumed: 11 in pos: 0
items produced: 29 in pos: 1
items produced: 62 in pos: 0
items consumed: 29 in pos: 1
items consumed: 62 in pos: 0
items produced: 35 in pos: 1
-PRODUCER PROCESS ENDED-
items consumed: 35 in pos: 1
-CONSUMER PROCESS ENDED-
```

## Implementation

Note that `sleep(rand()%x)` was called in both process inside and outside of the critical section to demonstrate that processes are often out of sync. Without this the producer and consumer processes in this project are in near perfect sync.

### Shared Memory

Each process opens a shared memory object of the same name and size specified in the header file `sharedObj.h`. The shared memory is mapped to a `struct table` which has a buffer and the location of the next position to be produced to or consumed from. 

### Semaphores

The two process use three semaphores for synronization. Their names are defined in the header file `sharedObj.h`. 

```
sem_t *full = sem_open(semFullName, O_CREAT, 0666, 0);
sem_t *empty = sem_open(semEmptyName, O_CREAT, 0666, bufferSize);
sem_t *mutex = sem_open(semMutexName, O_CREAT, 0666, 1);
```

The `full` semaphore is triggered when the buffer contains data for the consumer to read. The `empty` semaphore is triggered when the buffer has room for items to be added. The `mutex` semaphore ensures mutual exclusion, it asserts that only one process can access the critical section in the case multiple consumer or producer process are running.

### Critical Section

In the producer process data is written to the shared table, and the `in` pointer is advanced to the next avalible space. In the consumer process data is read and outputted to the user from the shared table, and the `out` pointer is advanced to the next data value.

```
// Store random integers in shared memory
share->buffer[share->in] = rand() % 100;

// Advance in pointer
share->in = (share->in+1)%bufferSize;
```
