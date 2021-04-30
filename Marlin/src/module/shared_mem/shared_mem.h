#ifndef SHARED_MEM_H
#define SHARED_MEM_H

#include <stdio.h>

#define SHARED_MEM_1KB_COUNT    6
#define SHARED_MEM_SIZE         SHARED_MEM_1KB_COUNT*1024

extern volatile uint8_t shared_mem[SHARED_MEM_SIZE];

#endif