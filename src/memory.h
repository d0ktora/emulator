#ifndef MEMORY_DEF
#define MEMORY_DEF

#include <stdint.h>

#define SEGMENT_SIZE 65535
#define MEMORY_SIZE SEGMENT_SIZE * 4

#define SEGCS       SEGMENT_SIZE * 0 
#define SEGDS       SEGMENT_SIZE * 1
#define SEGSS       SEGMENT_SIZE * 2
#define SEGES       SEGMENT_SIZE * 3

void *initMemory();

void segWrite(void *buff, int size, int offset, int seg);
void *segRead(int size, int offset, int seg);

#endif
