# Producer-Consumer-Problem
CS 33211 - Programming Assignment 1


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
