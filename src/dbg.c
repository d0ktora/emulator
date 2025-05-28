#include "dbg.h"

static struct CPU *cpu;
static uint8_t buffPointer;

struct debugInfoReg registerNames[] = {
    {0, "XX"},
    {REG_R1, "R1 "},
    {REG_R2, "R2 "},
    {REG_R3, "R3 "},
    {REG_R4, "R4 "},
    {REG_R5, "R5 "},
    {REG_R6, "R6 "},
    {REG_R7, "R7 "},
    {REG_R8, "R8 "},
};

void initDebug(struct CPU *rcpu){
    cpu = rcpu;

    cpu->debug = 1;
    cpu->debugBuffer = malloc(5);
    if (!cpu->debugBuffer){
        panic("Dbg buffer allocation");
    }
    buffPointer = 0;
    memset(cpu->debugBuffer,0, 5);
}

void stepDebug(){
    step();
    debugFull();
    getchar();
}

void flushDebug(){
    buffPointer = 0;
    memset(cpu->debugBuffer,0, 5);
}

void debugInstruction(void *buff, uint8_t size){
    memcpy(cpu->debugBuffer + buffPointer, buff, size);
    buffPointer += size;
}

static const char *parseRegisterName(unsigned char id){
    size_t dbgInfoSize;

    dbgInfoSize = sizeof(registerNames) / sizeof(registerNames[0]);
    for (size_t i = 0; i < dbgInfoSize; i++){
        if (registerNames[i].regId == id){
            return registerNames[i].regName;
        }
    }
    return registerNames[0].regName;
}

static char *parseInstruction(void *inst){
    char *str;
    char *buffer;

    str = malloc(30);
    buffer = malloc(2);
    memset(str,0,20);

    buffer[0] = ((char *)inst)[0];
    switch(buffer[0]){
        case MOV_RL:
            strcpy(str, "MOVI ");
            buffer[0] = ((char *)inst)[1];
            strcat(str, parseRegisterName(buffer[0]));
            memcpy(buffer, inst + 2, 2);
            sprintf(str + strlen(str), " 0x%04hx", *((uint16_t *)buffer));
            break;
        case MOV_RR:
            strcpy(str, "MOV ");
            buffer[0] = ((char *)inst)[1];
            strcat(str, parseRegisterName(buffer[0]));
            buffer[0] = ((char *)inst)[2];
            strcat(str, parseRegisterName(buffer[0]));
            break;
        case MOV_RM:
            strcpy(str, "MOV ");
            buffer[0] = ((char *)inst)[1];
            strcat(str, parseRegisterName(buffer[0]));
            memcpy(buffer, inst + 2, 2);
            sprintf(str + strlen(str), " 0x%04hx", *((uint16_t *)buffer));
            break;
            break;
        case ADD:
            strcpy(str, "ADDI ");
            buffer[0] = ((char *)inst)[1];
            strcat(str, parseRegisterName(buffer[0]));
            memcpy(buffer, inst + 2, 2);
            sprintf(str + strlen(str), " 0x%04hx", *((uint16_t *)buffer));
            break;
        case ADDI:
            strcpy(str, "ADD ");
            buffer[0] = ((char *)inst)[1];
            strcat(str, parseRegisterName(buffer[0]));
            buffer[0] = ((char *)inst)[2];
            strcat(str, parseRegisterName(buffer[0]));
            break;
        case SUB:
            strcpy(str, "SUBI ");
            buffer[0] = ((char *)inst)[1];
            strcat(str, parseRegisterName(buffer[0]));
            buffer[0] = ((char *)inst)[2];
            strcat(str, parseRegisterName(buffer[0]));
            break;
        case SUBI:
            strcpy(str, "SUB ");
            buffer[0] = ((char *)inst)[1];
            strcat(str, parseRegisterName(buffer[0]));
            memcpy(buffer, inst + 2, 2);
            sprintf(str + strlen(str), " 0x%04hx", *((uint16_t *)buffer));
            break;
        case MUL:
            strcpy(str, "MUL ");
            buffer[0] = ((char *)inst)[1];
            strcat(str, parseRegisterName(buffer[0]));
            buffer[0] = ((char *)inst)[2];
            strcat(str, parseRegisterName(buffer[0]));
            break;
        case IMUL:
            strcpy(str, "IMUL ");
            buffer[0] = ((char *)inst)[1];
            strcat(str, parseRegisterName(buffer[0]));
            memcpy(buffer, inst + 2, 2);
            sprintf(str + strlen(str), " 0x%04hx", *((uint16_t *)buffer));
            break;
        case DIV:
            strcpy(str, "DIV ");
            buffer[0] = ((char *)inst)[1];
            strcat(str, parseRegisterName(buffer[0]));
            buffer[0] = ((char *)inst)[2];
            strcat(str, parseRegisterName(buffer[0]));
            break;
        case IDIV:
            strcpy(str, "IDIV ");
            buffer[0] = ((char *)inst)[1];
            strcat(str, parseRegisterName(buffer[0]));
            memcpy(buffer, inst + 2, 2);
            sprintf(str + strlen(str), " 0x%04hx", *((uint16_t *)buffer));
            break;
        case INC:
            strcpy(str, "INC ");
            buffer[0] = ((char *)inst)[1];
            strcat(str, parseRegisterName(buffer[0]));
            break;
        case DEC:
            strcpy(str, "DEC ");
            buffer[0] = ((char *)inst)[1];
            strcat(str, parseRegisterName(buffer[0]));
            break;
        case PUSH:
            strcpy(str, "PUSH ");
            buffer[0] = ((char *)inst)[1];
            strcat(str, parseRegisterName(buffer[0]));
            break;
        case POP:
            strcpy(str, "POP ");
            buffer[0] = ((char *)inst)[1];
            strcat(str, parseRegisterName(buffer[0]));
            break;
        case TESTI:
            strcpy(str, "TESTI ");
            buffer[0] = ((char *)inst)[1];
            strcat(str, parseRegisterName(buffer[0]));
            memcpy(buffer, inst + 2, 2);
            sprintf(str + strlen(str), " 0x%04hx", *((uint16_t *)buffer));
            break;
        case TEST:
            strcpy(str, "TEST ");
            buffer[0] = ((char *)inst)[1];
            strcat(str, parseRegisterName(buffer[0]));
            buffer[0] = ((char *)inst)[2];
            strcat(str, parseRegisterName(buffer[0]));
            break;
        case JMP:
            strcpy(str, "JMP ");
            buffer[0] = ((char *)inst)[1];
            memcpy(buffer, inst + 1, 2);
            sprintf(str + strlen(str), " 0x%04hx", *((uint16_t *)buffer));
            break;
        case JZ:
            strcpy(str, "JZ ");
            buffer[0] = ((char *)inst)[1];
            memcpy(buffer, inst + 1, 2);
            sprintf(str + strlen(str), " 0x%04hx", *((uint16_t *)buffer));
            break;
        case JNZ:
            strcpy(str, "JNZ ");
            buffer[0] = ((char *)inst)[1];
            memcpy(buffer, inst + 1, 2);
            sprintf(str + strlen(str), " 0x%04hx", *((uint16_t *)buffer));
            break;
        case JG:
            strcpy(str, "JG ");
            buffer[0] = ((char *)inst)[1];
            memcpy(buffer, inst + 1, 2);
            sprintf(str + strlen(str), " 0x%04hx", *((uint16_t *)buffer));
            break;
        case JGE:
            strcpy(str, "JGE ");
            buffer[0] = ((char *)inst)[1];
            memcpy(buffer, inst + 1, 2);
            sprintf(str + strlen(str), " 0x%04hx", *((uint16_t *)buffer));
            break;
        case JL:
            strcpy(str, "JL ");
            buffer[0] = ((char *)inst)[1];
            memcpy(buffer, inst + 1, 2);
            sprintf(str + strlen(str), " 0x%04hx", *((uint16_t *)buffer));
            break;
        case JLE:
            strcpy(str, "JLE ");
            buffer[0] = ((char *)inst)[1];
            memcpy(buffer, inst + 1, 2);
            sprintf(str + strlen(str), " 0x%04hx", *((uint16_t *)buffer));
            break;
        default:
            strcpy(str, "[!] Unrecognized instr");
            break;
    }
    free(buffer);
    return str; 
}

void debugFull(){

    uint16_t x;
    char *parseInstr;
    system("clear");
    puts("REGISTERS ------");

    printf("ip: 0x%04hx  ac: 0x%04hx\n", cpu->registers.ip, cpu->registers.ac);
    printf("sp: 0x%04hx  bp: 0x%04hx\n", cpu->registers.sp, cpu->registers.bp);
    printf("r1: 0x%04hx  r2: 0x%04hx\n", cpu->registers.r1, cpu->registers.r2);
    printf("r3: 0x%04hx  r4: 0x%04hx\n", cpu->registers.r3, cpu->registers.r4);
    printf("r5: 0x%04hx  r6: 0x%04hx\n", cpu->registers.r5, cpu->registers.r6);
    printf("r7: 0x%04hx  r8: 0x%04hx\n", cpu->registers.r7, cpu->registers.r8);
    printf("ts: 0x%04hx\n", cpu->registers.ts);
    printf("Memory start :%llx\n", (unsigned long long)MEMORY);
    printf("Memory end :%llx\n", (unsigned long long)MEMORY + MEMORY_SIZE); 
    printf("Stack start :%llx\n", (unsigned long long)(MEMORY + SEGSS)); 
    puts("STACK ------");
    for(int i = 20; i >= 2; i -= 2){
        memcpy(&x, MEMORY + SEGSS + SEGMENT_SIZE - i - 1, 2); 
        printf("%p : %hx\n", MEMORY + SEGSS + SEGMENT_SIZE - i - 1, x); 
    }
    parseInstr = parseInstruction(cpu->debugBuffer);
    printf("LAST INSTRUCTION :%s\n",parseInstr);
    free(parseInstr);
    
    return;

}
