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



typedef uint8_t Byte;
typedef uint16_t Word;

typedef struct Mem {
    Byte Data[MaxMem];
} Mem;


typedef struct CPU {
    // info about registers [http://www.obelisk.me.uk/6502/registers.html]

    Word PC; // program counter
    Byte SP; // stack pointer

    Byte A, X, Y; // registers

    // status flags using bit fields
    Byte C : 1; // carry
    Byte Z : 1; // Zero
    Byte I : 1; // interrupt Disable
    Byte D : 1; // Decimal mode
    Byte B : 1; // Break command
    Byte O : 1; // Overflow
    Byte N : 1; // negative


} CPU;


static const uint8_t OPCODE_CYCLES[256] = {
    //  0  1   2   3   4   5   6   7   8  9   A   B   C   D   E  F
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  2,  0,  0,  0,  0, 0,  // 0
        0, 0,  0,  0,  0,  0,  0,  0,  6, 6,  6,  5,  0,  0,  0, 0,  // 1
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  2,  0,  0,  0,  0, 0,  // 2
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  // 3
        0, 0,  0,  0,  0,  0,  0,  0,  3, 4,  3,  4,  0,  0,  0, 0,  // 4
        0, 0,  0,  0,  0,  0,  0,  0,  3, 4,  3,  4,  0,  0,  0, 0,  // 5
        0, 0,  0,  0,  0,  0,  0,  0,  3, 4,  3,  4,  0,  0,  0, 0,  // 6
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  // 7
        0, 0,  0,  0,  0,  0,  0,  0,  0, 2,  2,  0,  0,  0,  0, 0,  // 8
        0, 0,  0,  0,  0,  0,  0,  0,  0, 5,  2,  4,  0,  0,  0, 0,  // 9
        0, 0,  0,  0,  0,  0,  0,  0,  2, 0,  2,  2,  0,  0,  0, 0,  // A
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  // B
        0, 0,  0,  0,  0,  0,  0,  0,  4, 0,  4,  4,  0,  0,  0, 0,  // C
        0, 0,  0,  0,  0,  0,  0,  0,  4, 5,  4,  4,  0,  0,  0, 0,  // D
        0, 0,  0,  0,  0,  0,  0,  0,  4, 0,  4,  4,  0,  0,  0, 0,  // E
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  // F

};