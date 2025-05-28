#!/usr/bin/python3
registers = {
"r1":0x93,
"r2":0x94,
"r3":0x95,
"r4":0x96,
"r5":0x97,
"r6":0x98,
"r7":0x99,
"r8":0x9A
}
jmpinstr = {

"JZ"     : 0x42 ,
"JNZ"    : 0x43 ,
"JG"     : 0x44 ,
"JGE"    : 0x45 ,
"JL"     : 0x46 ,
"JLE"     : 0x47 ,
"JMP"     : 0x48 ,
"CALL"   : 0x32 ,
}
z1 = {

"INC"    : 0x28 ,
"DEC"    : 0x29 ,
"PUSH"   : 0x30 ,
"POP"    : 0x31 ,
"RET"    : 0x33 ,
"LJMP"   : 0x49 ,
"INT"    : 0x60 ,
"HALT"   : 0x61 ,
}
zz = {
"MOVI"   : 0x10 ,   
"MOV"    : 0x11 ,   
"MOV_RM" : 0x12 ,
"MOV_MR" : 0x13 ,
"MOV_LM" : 0x14 ,   
"MOV_RPM": 0x15 ,   
"MOV_LRP": 0x16 ,   
"ADDI" : 0x20 ,
"ADD" : 0x21 ,
"MUL" : 0x22 ,
"IMUL" : 0x23 ,
"SUB" : 0x24 ,
"SUBI" : 0x25 ,
"DIV" : 0x26 ,
"IDIV" : 0x27 ,
"TEST": 0x40 ,
"TESTI": 0x41 ,
"OR"     : 0x50 ,
"ORI"    : 0x51 ,
"AND"    : 0x52 ,
"ANDI"   : 0x53 ,
"XOR"    : 0x54 ,
"XORI"   : 0x55 ,
"NOT"    : 0x56 ,
"LSH"    : 0x57 ,
"LSHI"   : 0x58 ,
"RSH"    : 0x59 ,
"RSHI"   : 0x5A ,
}

def get_instr(x):
    if x in zz:
        return [zz[x], 2]
    elif x in z1:
        return [z1[x], 1]
    elif x in jmpinstr:
        return [jmpinstr[x],3]
    else:
        return [0,0]
