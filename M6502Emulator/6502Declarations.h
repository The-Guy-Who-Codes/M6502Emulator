#include <stdio.h>
#include <stdint.h>
#define MaxMem (1024 * 64) // defines the maximum amount of bytes the 6502 can handle in memory

/** opcodes */

// To Add New Instruction
// 1. Add opcode in Definition list below
// 2. Add number of cycles for instruction in OPCODES_CYCLES table
// 3. Add actual instruction in the switch statement in 6502Functions.h

// Loading
#define INS_LDA_IM 0xA9 // immediate
#define INS_LDA_ZP 0xA5 // Zero Page
#define INS_LDA_ZPX 0xB5 // Zero Page X
#define INS_LDA_ABS 0xAD // Absolute mode
#define INS_LDA_ABSX 0xBD // Absolute X
#define INS_LDA_ABSY 0xB9 // Absolute Y
#define INS_LDA_INDX 0xA1 // Indirect X
#define INS_LDA_INDY 0xB1 // Indirect Y

#define INS_LDX_IM 0xA2
#define INS_LDX_ZP 0xA6
#define INS_LDX_ZPY 0xB6
#define INS_LDX_ABS 0xAE
#define INS_LDX_ABSY 0xBE

#define INS_LDY_IM 0xA0
#define INS_LDY_ZP 0xA4
#define INS_LDY_ZPX 0xB4
#define INS_LDY_ABS 0xAC
#define INS_LDY_ABSX 0xBC

// Storing
#define INS_STA_ZP 0x85
#define INS_STA_ABS 0x8D
#define INS_STA_ZPX 0x95
#define INS_STA_ABSX 0x9D
#define INS_STA_ABSY 0x99
#define INS_STA_INDX 0x81
#define INS_STA_INDY 0x91

#define INS_STX_ZP 0x86
#define INS_STX_ABS 0x8E
#define INS_STX_ZPY 0x96

#define INS_STY_ZP 0x84
#define INS_STY_ABS 0x8C
#define INS_STY_ZPX 0x94

// Register Transfers
#define INS_TAX_IMP 0xAA // copy Accumulator to the X register
#define INS_TAY_IMP 0xA8 // A --> X
#define INS_TXA_IMP 0x8A // X --> A
#define INS_TYA_IMP 0x98 // Y --> A

// Stack Operations
#define INS_TSX_IMP 0xBA // copies contents of stack register into X register
#define INS_TXS_IMP 0x9A // X --> SP

#define INS_PHA_IMP 0x48 // push A to stack
#define INS_PHP_IMP 0x08 // push processor status flags to the stack
#define INS_PLA_IMP 0x68 // pull accmulator from stack
#define INS_PLP_IMP 0x28 // pull status flags from stack

// Logical Operations
#define INS_AND_IM 0x29 // Logical AND with immediate addressing
#define INS_AND_ZP 0x25
#define INS_AND_ZPX 0x35
#define INS_AND_ABS 0x2D
#define INS_AND_ABSX 0x3D
#define INS_AND_ABSY 0x39
#define INS_AND_INDX 0x21
#define INS_AND_INDY 0x31

#define INS_EOR_IM 0x49 
#define INS_EOR_ZP 0x45 
#define INS_EOR_ZPX 0x55 
#define INS_EOR_ABS 0x4D 
#define INS_EOR_ABSX 0x5D 
#define INS_EOR_ABSY 0x59 
#define INS_EOR_INDX 0x41 
#define INS_EOR_INDY 0x51 

#define INS_ORA_IM 0x09
#define INS_ORA_ZP 0x05 
#define INS_ORA_ZPX 0x15 
#define INS_ORA_ABS 0x0D 
#define INS_ORA_ABSX 0x1D 
#define INS_ORA_ABSY 0x19 
#define INS_ORA_INDX 0x01 
#define INS_ORA_INDY 0x11

#define INS_BIT_ZP 0x24
#define INS_BIT_ABS 0x2C

// Jumps and Calls
#define INS_JMP_ABS 0x4C
#define INS_JMP_IND 0x6C

#define INS_JSR_ABS 0x20

#define INS_RTS_IMP 0x60

// Incriments and Decriments
#define INS_INC_ZP 0xE6
#define INS_INC_ZPX 0xF6
#define INS_INC_ABS 0xEE
#define INS_INC_ABSX 0xFE




typedef uint8_t Byte;
typedef uint16_t Word;

typedef struct Mem {
    Byte Data[MaxMem];
} Mem;


struct StatusFlags {


    // status flags using bit fields
    Byte C : 1; // carry (least significant bit)
    Byte Z : 1; // Zero
    Byte I : 1; // interrupt Disable
    Byte D : 1; // Decimal mode
    Byte B : 1; // Break command
    Byte O : 1; // Overflow
    Byte N : 1; // negative
    Byte Ign : 1; // ignore (this is the most sinificant bit)

};

typedef struct CPU {
    // info about registers [http://www.obelisk.me.uk/6502/registers.html]

    Word PC; // program counter
    Byte SP; // stack pointer

    Byte A, X, Y; // registers

    union {

        Byte PS; // Processor status
        struct StatusFlags Flag;

    };
    

    


} CPU;


static const uint8_t OPCODE_CYCLES[256] = {
    //  0  1   2   3   4   5   6   7   8  9   A   B   C   D   E  F
        0, 0,  6,  0,  0,  0,  6,  0,  0, 0,  2,  0,  0,  0,  0, 0,  // 0
        6, 5,  6,  5,  6,  5,  0,  0,  6, 6,  6,  5,  0,  0,  0, 0,  // 1
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  2,  0,  0,  0,  0, 0,  // 2
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  // 3
        0, 0,  3,  0,  0,  0,  0,  0,  3, 4,  3,  4,  0,  0,  0, 0,  // 4
        3, 4,  3,  4,  3,  4,  0,  0,  3, 4,  3,  4,  0,  0,  0, 0,  // 5
        0, 0,  0,  0,  0,  0,  0,  0,  3, 4,  3,  4,  0,  0,  5, 6,  // 6
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  // 7
        3, 0,  4,  0,  3,  0,  4,  0,  0, 2,  2,  0,  0,  0,  0, 0,  // 8
        2, 4,  2,  4,  2,  4,  0,  0,  0, 5,  2,  4,  0,  0,  0, 0,  // 9
        0, 0,  0,  0,  0,  0,  0,  0,  2, 2,  2,  2,  0,  0,  0, 0,  // A
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  // B
        0, 0,  4,  0,  3,  0,  5,  0,  4, 0,  4,  4,  0,  0,  0, 0,  // C
        4, 4,  4,  4,  4,  4,  0,  0,  4, 5,  4,  4,  0,  0,  0, 0,  // D
        0, 0,  0,  0,  0,  0,  0,  0,  4, 0,  4,  4,  0,  0,  6, 7,  // E
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  // F

};