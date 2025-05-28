#ifndef INSTR_H
#define INSTR_H

/*
 *  Syntax :
 *  ALL ARITHMETIC IS 8BIT
 *
 *  mov r1, r2 : moves r2 into r1
 *  movi r1, 100: moves 100 into r1
 *  mov r1, 0x300: loads from memory @ 0x300 into r1
 *  movi 0x300, 100 moves 100 into memory @ 0x300
 
 *  addi r1, 100: adds r1 and 100
 *  add r1, r2: adds r1 and r2
 *
 *  subi r1, 100: subs 100 from r1
 *  sub r1, r2: subs r2 from r1
 *
 *  imul r1, 100: multiplies r1 by 100
 *  mul r1, r2: multiplies r1 by r2
 *
 *  
 *
 *
 */


//moving op
#define MOV_RL  0x10    //literal -> register
#define MOV_RR  0x11    //register ->register
#define MOV_RM  0x12
#define MOV_MR  0x13
#define MOV_RPR 0x15    //register pointer -> memory

//arithmetic
#define ADDI    0x20
#define ADD     0x21
#define MUL     0x22
#define IMUL    0x23
#define SUB     0x24
#define SUBI    0x25
#define DIV     0x26
#define IDIV    0x27
#define INC     0x28
#define DEC     0x29
//stack
#define PUSH    0x30
#define PUSHI   0x31
#define POP     0x32
#define POPI    0x33
#define CALL    0x34
#define RET     0x35

//jmps and logic
#define TEST    0x40
#define TESTI   0x41
#define JZ      0x42
#define JNZ     0x43
#define JG      0x44
#define JGE     0x45
#define JL      0x46
#define JLE     0x47
#define JMP     0x48
#define LJMP    0x49

//bitwise
#define OR      0x50
#define ORI     0x51
#define AND     0x52
#define ANDI    0x53
#define XOR     0x54
#define XORI    0x55
#define NOT     0x56
#define LSH     0x57
#define LSHI    0x58
#define RSH     0x59
#define RSHI    0x5A

//kernel
#define INT     0x60
#define HALT    0x61

//flags
#define TZ  0x1
#define TGT 0x2
#define TLT 0x4
#define TGE ((TZ | TGT))
#define TLE ((TZ | TLT))

//arithmetic
#define INT_OVERFLOW(x) ( x > 32767 || x < -32768 )

#define JMP_FORWARD(x) ( (*(int16_t *)x) > 0 )

extern void InstMOVRL(struct CPU *cpu);
extern void InstMOVRR(struct CPU *cpu);
extern void InstMOVMR(struct CPU *cpu);
extern void InstMOVRM(struct CPU *cpu);
extern void InstMOVML(struct CPU *cpu);
extern void InstADDI(struct CPU *cpu);
extern void InstADD(struct CPU *cpu);
extern void InstPUSH(struct CPU *cpu);
extern void InstPOP(struct CPU *cpu);
extern void InstCALL(struct CPU *cpu);
extern void InstRET(struct CPU *cpu);
extern void InstMUL(struct CPU *cpu);
extern void InstIMUL(struct CPU *cpu);
extern void InstSUB(struct CPU *cpu);
extern void InstSUBI(struct CPU *cpu);
extern void InstDIV(struct CPU *cpu);
extern void InstIDIV(struct CPU *cpu);
extern void InstINC(struct CPU *cpu);
extern void InstDEC(struct CPU *cpu);
extern void InstTEST(struct CPU *cpu);
extern void InstTESTI(struct CPU *cpu);
extern void InstJZ(struct CPU *cpu);
extern void InstJNZ(struct CPU *cpu);
extern void InstJG(struct CPU *cpu);
extern void InstJGE(struct CPU *cpu);
extern void InstJL(struct CPU *cpu);
extern void InstJLE(struct CPU *cpu);
extern void InstJMP(struct CPU *cpu);

#endif

