#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef _SHAREDOBJ_H
#define _SHAREDOBJ_H

static const int SIZE = sizeof(int)*2;
static const char* NAME = "ProdConsumnProb";
static const char* semFullName = "fullA";
static const char* semEmptyName = "emptyA";

#endif
