# Producer-Consumer-Problem

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
items produced: 83 + 86 = ?
items consumed: 83 + 86 = 169
items produced: 77 + 15 = ?
items consumed: 77 + 15 = 92
items produced: 93 + 35 = ?
items consumed: 93 + 35 = 128
items produced: 86 + 92 = ?
items consumed: 86 + 92 = 178
items produced: 49 + 21 = ?
items consumed: 49 + 21 = 70
items produced: 62 + 27 = ?
items consumed: 62 + 27 = 89
items produced: 90 + 59 = ?
items consumed: 90 + 59 = 149
items produced: 63 + 26 = ?
items consumed: 63 + 26 = 89
items produced: 40 + 26 = ?
items consumed: 40 + 26 = 66
items produced: 72 + 36 = ?
-PRODUCER PROCESS ENDED-
items consumed: 72 + 36 = 108
-CONSUMER PROCESS ENDED-
```