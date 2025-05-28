#ifndef DBG_H
#define DBG_H

#include "cpu.h"
#include "memory.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "error.h"
#include "instructions.h"

#define MEMORY cpu->memory

void initDebug(struct CPU *rcpu);
void debugFull();
void stepDebug();
void flushDebug();
void debugInstruction(void *buff, uint8_t size);

struct debugInfoReg {
    uint16_t   regId;
    const char  *regName;
};


#endif

