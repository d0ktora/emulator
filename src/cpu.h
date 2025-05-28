#ifndef CPU_DEF
#define CPU_DEF

#include "stdint.h"
#define CORES
//define register values
#define REG_IP 0x91
#define REG_AC 0x92
#define REG_R1 0x93
#define REG_R2 0x94
#define REG_R3 0x95
#define REG_R4 0x96
#define REG_R5 0x97
#define REG_R6 0x98
#define REG_R7 0x99
#define REG_R8 0x9A
#define REG_SP 0x9B
#define REG_BP 0x9C
#define REG_TS 0x9D

#define BYTE    1
#define WORD    2

#define STATE(cpu) (cpu->state)
#define CIP(cpu) ((uint16_t)cpu->registers.ip)
#define INCREMENT_IP(z, x) (z->registers.ip += x)
#define DECREMENT_IP(z, x) (z->registers.ip += x)
#define ACCU(cpu) (cpu->registers.ac)

#define STACK_SIZE SEGMENT_SIZE
#define STACK_INC(cpu) (cpu->registers.sp -= 2)
#define STACK_DEC(cpu) (cpu->registers.sp += 2)
#define STACK_BOUNDS(x) ( x <= (STACK_SIZE - 2))
#define STACK(cpu) (cpu->registers.sp)

#define TEST_FLUSH() (cpu->registers.ts &= 0)
#define TEST_SET(x) (cpu->registers.ts |= x)
#define TEST_ISSET(x) (cpu->registers.ts & x)

#define FETCHB(x) ( (*(char*)x) )
#define FETCHW(x) ( (*(int16_t *)x) )

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint16_t regsz;

struct CPU *initCPU(void *memory);
void step();
regsz *parseRegister(char regid);
void *fetch();
void *fetch16();

#define CPU_SIZE sizeof(struct CPU)

struct REGISTERS {
    uint16  ip;    //inst pointer
    regsz   ac;    //accumulator
    uint16  sp;    //stack
    uint16  bp;    //frame
    regsz   ts;    //test
                   
    regsz   r1;    
    regsz   r2;
    regsz   r3;
    regsz   r4;
    regsz   r5;
    regsz   r6;
    regsz   r7;
    regsz   r8;
};

struct CPU {
    struct REGISTERS registers;
    regsz state;

    void *memory;
    char *debugBuffer;
    uint8_t debug; 
};

#endif
