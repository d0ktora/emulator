#include "memory.h"
#include "cpu.h"
#include "dbg.h"
#include "instructions.h"
#include "error.h"
#include "string.h"

int ptr;

void addMem(unsigned char x){
    segWrite(&x, BYTE, ptr, SEGCS); 
    ptr++;
}

int main(){
    void *memory = initMemory();
    if (memory == NULL){
        panic("Mem alloc");
    }

    struct CPU *cpu = initCPU(memory);
    ptr = 0;
    initDebug(cpu);
    
    addMem(MOV_RL);
    addMem(REG_R1);
    addMem(0x5);
    addMem(0x0);

    addMem(MOV_RL);
    addMem(REG_R2);
    addMem(2);
    addMem(0);

    addMem(INC);
    addMem(REG_R1);

    addMem(PUSH);
    addMem(REG_R1);

    addMem(PUSH);
    addMem(REG_R2);

    addMem(INC);
    addMem(REG_R2);

    addMem(POP);
    addMem(REG_R2);

    addMem(POP);
    addMem(REG_R2);

    addMem(SUBI);
    addMem(REG_R2);
    addMem(3);
    addMem(0);

    addMem(MUL);
    addMem(REG_R1);
    addMem(REG_R2);

    addMem(INC);
    addMem(REG_R1);

    addMem(TESTI);
    addMem(REG_R1);
    addMem(0x30);
    addMem(0x00);

    //loop back untill r1 is 0x30
    addMem(JLE);
    addMem(0xF7);
    addMem(0xFF);

    while(1){
        stepDebug();
    }

    return 0;
}
