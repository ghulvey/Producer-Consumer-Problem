#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#ifndef _SHAREDOBJ_H
#define _SHAREDOBJ_H

static const int bufferSize = 2;

struct table {
    int buffer[2];
    int in;
    int out;
};

static const int SIZE = sizeof(struct table);
static const char* NAME = "ProdConsumnProb";
static const char* semFullName = "full";
static const char* semEmptyName = "empty";
static const char* semMutexName = "mutex";



#endif
