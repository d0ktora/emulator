#include "memory.h"
#include "error.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

static void *memory = NULL;

void *initMemory(){
    if(memory){
        panic("Memory already allocated");
    }
    memory = malloc(MEMORY_SIZE);
    if(!memory){
        panic("Memory alloc");
    }

    return memory;
}

void segWrite(void *buff, int size, int offset, int seg){
    void *dest;

    dest = (void *)((uint64_t)memory + seg + offset);
    memcpy(dest, buff, (size_t)size);
}

void *segRead(int size, int offset, int seg){
    void *src;
    void *buffer;

    src = (void *)((uint64_t)memory + seg + offset);
    
    buffer = malloc(size);
    if (!buffer){
        panic("Read memory error");
    }

    memcpy(buffer, src, (size_t)size);

    return buffer;
}
