#include "memory.h"
#include "cpu.h"
#include "instructions.h"
#include "error.h"
#include "stdlib.h"
#include "string.h"

void InstMOVRL(struct CPU *cpu){
    void *b1, *b2, *b3;
    
    b1 = fetch();
    b2 = fetch16();
    b3 = parseRegister(*(char*)b1);
    if(!b3){
        panic("Unrecognized register in MOVRL");
    }
    memcpy(b3, b2, WORD);

    free(b1);
    free(b2);
}

void InstMOVRR(struct CPU *cpu){
    void *b1, *b2, *b3, *b4; 

    b1 = fetch();
    b2 = fetch();
     
    b3 = parseRegister(*(char*)b1);
    b4 = parseRegister(*(char*)b2);
    if(!b3 || !b4){
        panic("Unrecognized register in MOVRR");
    }
    memcpy(b3, b4, WORD);
    free(b1);
    free(b2);
}

void InstMOVMR(struct CPU *cpu){
   void *b1, *b2, *b3;

    b1 = fetch16();
    b2 = fetch();

    b3 = parseRegister(*(char*)b2);
    if(!b3){
        panic("Unrecognized register in MOVRM");
    }
    segWrite(b3, WORD, *(uint16_t *)b3, SEGDS);
    free(b1);
    free(b2);
}

void InstMOVRM(struct CPU *cpu){
   void *b1, *b2, *b3; 

    b1 = fetch();
    b2 = fetch16();

    b3 = parseRegister(*(char *)b1);
    if(!b3){
        panic("Unrecognized register in MOVMR");
    }
    memcpy(b3, b2, WORD);
    free(b1);
    free(b2);

}

void InstMOVRPR(struct CPU*cpu){
    void *b1, *b2, *b3, *b4;

    b1 = fetch();
    b2 = fetch();

    b3 = parseRegister(*(char *)b1);
    if(!b3){
        panic("Unrecognized register in MOVMR");
    }
    b4 = parseRegister(*(char *)b2);
    if(!b4){
        panic("Unrecognized register in MOVMR");
    }
    
    segWrite(b4, WORD, *(uint16_t *)b3, SEGDS);
}

//Arithmetic
void InstADDI(struct CPU *cpu){
    void *b1, *b2, *b3; 
    int result;

    b1 = fetch();
    b2 = fetch();
    
    b3 = parseRegister(*(char*)b2);
    if(!b3){
        panic("Unrecognized register in ADDLR");
    }
    
    result =  (*(regsz *)b3 + *(int16_t *)b2);
    cpu->registers.ac = result;
    if( INT_OVERFLOW(result) ){
        panic("int overflow");
    }

    free(b1);
    free(b2);
}

void InstADD(struct CPU *cpu){
    void *b1, *b2, *b3, *b4; 
    int result;
    
    b1 = fetch();
    b2 = fetch();
    
    b3 = parseRegister(*(char*)b1);
    b4 = parseRegister(*(char*)b2);
    if(!b3 || !b4){
        panic("Unrecognized register in ADDR");
    }
    result =  (*(regsz *)b3 + *(regsz *)b4);
    cpu->registers.ac = result;
    if( INT_OVERFLOW(result) ){
        panic("int overflow");
    }
    free(b1);
    free(b2);
}

void InstMUL(struct CPU *cpu){
    void *b1, *b2, *b3, *b4; 
    int result;
    
    b1 = fetch();
    b2 = fetch();
    
    b3 = parseRegister(*(char*)b1);
    b4 = parseRegister(*(char*)b2);
    if(!b3 || !b4){
        panic("Unrecognized register in MULR");
    }
    result =  (*(regsz *)b3 * *(regsz *)b4);
    cpu->registers.ac = result;
    if( INT_OVERFLOW(result) ){
        panic("int overflow");
    }
    
    free(b1);
    free(b2);
}

void InstIMUL(struct CPU *cpu){
    void *b1, *b2, *b3;
    int result;

    b1 = fetch();
    b2 = fetch16();
    
    b3 = parseRegister(*(char*)b2);
    if(!b3){
        panic("Unrecognized register in MULRL");
    }
    result =  (*(regsz *)b3 * *(regsz *)b2);
    cpu->registers.ac = result;
    if( INT_OVERFLOW(result) ){
        panic("int overflow");
    }
    free(b1);
    free(b2);
}
////

void InstSUB(struct CPU *cpu){
    void *b1, *b2, *b3, *b4; 
    int result;

    b1 = fetch();
    b2 = fetch();
    
    b3 = parseRegister(*(char*)b1);
    b4 = parseRegister(*(char*)b2);
    if(!b3 || !b4){
        panic("Unrecognized register in SUBR");
    }
    result =  (*(regsz *)b3 - *(regsz *)b4);
    cpu->registers.ac = result;
    if( INT_OVERFLOW(result) ){
        panic("int overflow");
    }
    free(b1);
    free(b2);
}

void InstSUBI(struct CPU *cpu){
    void *b1, *b2, *b3;
    int result;

    b1 = fetch();
    b2 = fetch16();
    
    b3 = parseRegister(*(char*)b1);
    if(!b3){
        panic("Unrecognized register in SUBRL");
    }
    result =  (*(regsz *)b3 - *(int16_t *)b2);
    cpu->registers.ac = result;
    if( INT_OVERFLOW(result) ){
        panic("int overflow");
    }
    free(b1);
    free(b2);
}

//
//

void InstDIV(struct CPU *cpu){
    void *b1, *b2, *b3, *b4; 
    int result;
    
    b1 = fetch();
    b2 = fetch16();
    
    b3 = parseRegister(*(char*)b1);
    b4 = parseRegister(*(char*)b2);
    if(!b3 || !b4){
        panic("Unrecognized register in DIVR");
    }

    result =  (*(regsz *)b3 / *(int16_t *)b2);
    cpu->registers.ac = result;
    if( INT_OVERFLOW(result) ){
        panic("int overflow");
    }
    free(b1);
    free(b2);
}

void InstIDIV(struct CPU *cpu){
    void *b1, *b2, *b3;
    
    b1 = fetch();
    b2 = fetch();
    
    b3 = parseRegister(*(char*)b1);
    if(!b3){
        panic("Unrecognized register in DIVRL");
    }
    cpu->registers.ac =  (*(uint8_t *)b3 / *(uint8_t *)b2);
    free(b1);
    free(b2);
}


void InstINC(struct CPU *cpu){
    void *b1, *b2; 

    b1 = fetch();
    
    b2 = parseRegister(*(char*)b1);
    if(!b2){
        panic("Unrecognized register in INC");
    }
    *(regsz *)b2 = *(regsz *)b2 + 1;

    free(b1);
}

void InstDEC(struct CPU *cpu){
    void *b1, *b2; 

    b1 = fetch();
    
    b2 = parseRegister(*(char*)b1);
    if(!b2){
        panic("Unrecognized register in DEC");
    }
    *(regsz *)b2 = *(regsz *)b2 - 1;

    free(b1);
}

void InstPUSH(struct CPU *cpu){
   void *b1, *b3; 

    b1 = fetch();
    
    b3 = parseRegister(*(char*)b1);
    if(!b3){
        panic("Unrecognized register in PUSH");
    }
    if (!STACK_BOUNDS( cpu->registers.sp ) ){
        panic("Stack overflow");
    }
    segWrite(b3, WORD, STACK(cpu), SEGSS);
    STACK_INC(cpu);
    free(b1);
}

void InstPOP(struct CPU *cpu){
   void *b1, *b2, *b3; 

    b1 = fetch();
    b3 = parseRegister(*(char*)b1);
    if(!b3){
        panic("Unrecognized register in POP");
    }
    STACK_DEC(cpu);
    if (!STACK_BOUNDS( cpu->registers.sp ) ){
        panic("Stack overflow");
    }
    b2 = segRead(WORD, STACK(cpu), SEGSS);
    memcpy(b3, b2, WORD);
    free(b1);
    free(b2);
}

void InstCALL(struct CPU *cpu){
   void *b1;

    segWrite(&cpu->registers.r1, WORD, STACK(cpu),SEGSS);
    STACK_INC(cpu);                           
    segWrite(&cpu->registers.r2, WORD,STACK(cpu),SEGSS);
    STACK_INC(cpu);                          
    segWrite(&cpu->registers.r3, WORD,STACK(cpu),SEGSS);
    STACK_INC(cpu);                         
    segWrite(&cpu->registers.r3, WORD,STACK(cpu),SEGSS);
    STACK_INC(cpu);                        
    segWrite(&cpu->registers.r4, WORD,STACK(cpu),SEGSS);
    STACK_INC(cpu);                          
    segWrite(&cpu->registers.r5, WORD,STACK(cpu),SEGSS);
    STACK_INC(cpu);                          
    segWrite(&cpu->registers.r6, WORD,STACK(cpu),SEGSS);
    STACK_INC(cpu);                          
    segWrite(&cpu->registers.r7, WORD,STACK(cpu),SEGSS);
    STACK_INC(cpu);                         
    segWrite(&cpu->registers.r8, WORD,STACK(cpu),SEGSS);
    STACK_INC(cpu);                        
    segWrite(&cpu->registers.bp, WORD,STACK(cpu),SEGSS);
    STACK_INC(cpu);                       
    segWrite(&cpu->registers.ip, WORD,STACK(cpu),SEGSS);
    STACK_INC(cpu);

    b1 = fetch16();
    cpu->registers.ip = *(uint16_t *)b1;
    free(b1);
    cpu->registers.bp = cpu->registers.sp;
}

void InstRET(struct CPU *cpu){
    void *b1;

    cpu->registers.sp = cpu->registers.bp;

    STACK_DEC(cpu);
    b1 = segRead(WORD, STACK(cpu), SEGSS);
    memcpy(&cpu->registers.ip, b1, 2);
    free(b1);
    
    STACK_DEC(cpu);
    b1 = segRead(WORD, STACK(cpu), SEGSS);
    memcpy(&cpu->registers.bp, b1, 2);
    free(b1);
    
    STACK_DEC(cpu);
    b1 = segRead(WORD, STACK(cpu), SEGSS);
    memcpy(&cpu->registers.r8, b1, 2);
    free(b1);
    
    STACK_DEC(cpu);
    b1 = segRead(WORD, STACK(cpu), SEGSS);
    memcpy(&cpu->registers.r7, b1, 2);
    free(b1);
    
    STACK_DEC(cpu);
    b1 = segRead(WORD, STACK(cpu), SEGSS);
    memcpy(&cpu->registers.r6, b1, 2);
    free(b1);
    
    STACK_DEC(cpu);
    b1 = segRead(WORD, STACK(cpu), SEGSS);
    memcpy(&cpu->registers.r5, b1, 2);
    free(b1);
    
    STACK_DEC(cpu);
    b1 = segRead(WORD, STACK(cpu), SEGSS);
    memcpy(&cpu->registers.r4, b1, 2);
    free(b1);
    
    STACK_DEC(cpu);
    b1 = segRead(WORD, STACK(cpu), SEGSS);
    memcpy(&cpu->registers.r3, b1, 2);
    free(b1);
    
    STACK_DEC(cpu);
    b1 = segRead(WORD, STACK(cpu), SEGSS);
    memcpy(&cpu->registers.r2, b1, 2);
    free(b1);
    
    STACK_DEC(cpu);
    b1 = segRead(WORD, STACK(cpu), SEGSS);
    memcpy(&cpu->registers.r1, b1, 2);
    free(b1);
}

void InstTESTI(struct CPU *cpu)
{
    void *b1, *b2, *b3;

    b1 = fetch();
    b2 = fetch16();

    b3 = parseRegister(FETCHB(b1));
    if(!b3){
        panic("Unrecognized register in POP");
    }
    TEST_FLUSH(); 
    if( FETCHW(b3) > FETCHW(b2) ){
        TEST_SET( TGT );
    } else if( FETCHW(b3) < FETCHW(b2) ) {
        TEST_SET( TLT );
    } else {
        TEST_SET( TZ );
    }

    free(b1);
    free(b2);
}

void InstTEST(struct CPU *cpu)
{
    void *b1, *b2, *b3, *b4;

    b1 = fetch();
    b2 = fetch();

    b3 = parseRegister(FETCHB(b1) );
    if(!b3){
        panic("Unrecognized register in TEST"); 
    } 

    b4 = parseRegister(FETCHB(b2) ); 
    if(!b4){
        panic("Unrecognized register in TEST");
    }
    
    TEST_FLUSH(); 
    if( FETCHW(b3) > FETCHW(b4) ){
        TEST_SET( TGT );
    } else if( FETCHW(b3) < FETCHW(b4) ) {
        TEST_SET( TLT );
    } else {
        TEST_SET( TZ );
    }

    free(b1);
    free(b2);
}

void InstJZ(struct CPU *cpu)
{
    void *b1;

    b1 = fetch16();
    if( TEST_ISSET( TZ ) ){
        if( JMP_FORWARD(b1) ){
            INCREMENT_IP(cpu, FETCHW(b1));
        } else {
            DECREMENT_IP(cpu, FETCHW(b1));
        }
    }

    free(b1);
}

void InstJNZ(struct CPU *cpu)
{
    void *b1;

    b1 = fetch16();
    if( !TEST_ISSET( TZ ) ){
        if( JMP_FORWARD(b1) ){
            INCREMENT_IP(cpu, FETCHW(b1));
        } else {
            DECREMENT_IP(cpu, FETCHW(b1));
        }
    }

    free(b1);
}


void InstJG(struct CPU *cpu)
{
    void *b1;

    b1 = fetch16();
    if( TEST_ISSET( TGT ) ){
        if( JMP_FORWARD(b1) ){
            INCREMENT_IP(cpu, FETCHW(b1));
        } else {
            DECREMENT_IP(cpu, FETCHW(b1));
        }
    }

    free(b1);
}

void InstJGE(struct CPU *cpu)
{
    void *b1;

    b1 = fetch16();
    if( TEST_ISSET( TGE ) ){
        if( JMP_FORWARD(b1) ){
            INCREMENT_IP(cpu, FETCHW(b1));
        } else {
            DECREMENT_IP(cpu, FETCHW(b1));
        }
    }

    free(b1);
}

void InstJL(struct CPU *cpu)
{
    void *b1;

    b1 = fetch16();
    if( TEST_ISSET( TLT ) ){
        if( JMP_FORWARD(b1) ){
            INCREMENT_IP(cpu, FETCHW(b1));
        } else {
            DECREMENT_IP(cpu, FETCHW(b1));
        }
    }

    free(b1);
}

void InstJLE(struct CPU *cpu)
{
    void *b1;

    b1 = fetch16();
    if( TEST_ISSET( TLE ) ){
        if( JMP_FORWARD(b1) ){
            INCREMENT_IP(cpu, FETCHW(b1));
        } else {
            DECREMENT_IP(cpu, FETCHW(b1));
        }
    }

    free(b1);
}

void InstJMP(struct CPU *cpu)
{
    void *b1;

    b1 = fetch16();
    if( JMP_FORWARD(b1) ){
        INCREMENT_IP(cpu, FETCHW(b1));
    } else {
        DECREMENT_IP(cpu, FETCHW(b1));
    }

    free(b1);
}

