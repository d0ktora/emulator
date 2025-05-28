#include "memory.h"
#include "cpu.h"
#include "dbg.h"
#include "instructions.h"
#include "error.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

static struct CPU *cpu;

struct CPU *initCPU(void *memory){
    cpu = (struct CPU *)malloc(CPU_SIZE);

    if (cpu != NULL){
        memset(cpu, 0, CPU_SIZE);
    } else {
        panic("CPU alloc");
    }
    
    cpu->registers.sp = SEGMENT_SIZE - 3;
    cpu->registers.bp = SEGMENT_SIZE - 3;

    cpu->memory = memory;

    return cpu;
}

regsz *parseRegister(char regid){
    switch((unsigned char)regid){
        case REG_IP:
            return &cpu->registers.ip;
        case REG_AC:
            return &cpu->registers.ac;
        case REG_SP:
            return &cpu->registers.sp;
        case REG_BP:
            return &cpu->registers.bp;
        case REG_R1:
            return &cpu->registers.r1;
        case REG_R2:
            return &cpu->registers.r2;
        case REG_R3:
            return &cpu->registers.r3;
        case REG_R4:
            return &cpu->registers.r4;
        case REG_R5:
            return &cpu->registers.r5;
        case REG_R6:
            return &cpu->registers.r6;
        case REG_R7:
            return &cpu->registers.r7;
        case REG_R8:
            return &cpu->registers.r8;
        default:
            return 0;
    }
}

void *fetch(){
    void *buff;

    buff = segRead(BYTE, CIP(cpu), SEGCS);
    if(!buff){
        panic("Fetching");
    }
    debugInstruction(buff, BYTE);
    INCREMENT_IP(cpu, BYTE);
    return buff;
}

void *fetch16(){
    void *buff;

    buff = segRead(WORD, CIP(cpu), SEGCS);
    if(!buff){
        panic("Fetching");
    }
    debugInstruction(buff, WORD);
    INCREMENT_IP(cpu, WORD);
    return buff;
}

void step(){
    void *b1;

    flushDebug();

    if(!cpu->state){
        b1 = fetch();
        cpu->state = *(uint8_t *)b1;
        free(b1);
    }

    switch(cpu->state){
        case MOV_RL:
            InstMOVRL(cpu);
            break;

        case MOV_RR:
            InstMOVRR(cpu);
            break;

        case MOV_RM:
            InstMOVMR(cpu);
            break;

        case MOV_MR:
            InstMOVRM(cpu);
            break;

        case ADD: 
            InstADD(cpu);
            break;

        case ADDI:
            InstADDI(cpu);
            break;   

        case MUL:
            InstMUL(cpu);
            break;
        
        case IMUL:
            InstIMUL(cpu);
            break;

        case SUB:
            InstSUB(cpu);
            break;
        
        case SUBI:
            InstSUBI(cpu);
            break;
        
        case IDIV:
            InstIDIV(cpu);
            break;
        
        case DIV:
            InstDIV(cpu);
            break;
        
        case INC:
            InstINC(cpu);
            break;
        
        case DEC:
            InstDEC(cpu);
            break;

        case PUSH:
            InstPUSH(cpu);
            break;

        case PUSHI:
            InstPUSH(cpu);
            break;

        case POP:
            InstPOP(cpu);
            break;

        case CALL:
            InstCALL(cpu);
            break;

        case RET:
            InstRET(cpu);
            break;
        
        case JMP:
            InstJMP(cpu);
            break;
        case JZ:
            InstJZ(cpu);
            break;
        case JNZ:
            InstJNZ(cpu);
            break;
        case JG:
            InstJG(cpu);
            break;
        case JGE:
            InstJGE(cpu);
            break;
        case JL:
            InstJL(cpu);
            break;
        case JLE:
            InstJLE(cpu);
            break;
        case TEST:
            InstTEST(cpu);
            break;
        case TESTI:
            InstTESTI(cpu);
            break;
        default:
            printf("Error @ ip 0x%04hx\n", cpu->registers.ip);
            panic("Unrecognized opcode");
    }
    cpu->state = 0;

}
