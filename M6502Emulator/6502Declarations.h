#include <stdio.h>
#include <stdint.h>
#define MaxMem (1024 * 64) // defines the maximum amount of bytes the 6502 can handle in memory

/** opcodes    */

// To Add New Instruction
// 1. Add opcode in Definition list below
// 2. Add number of cycles for instruction in OPCODES_CYCLES table
// 3. Add actual instruction in the switch statement in 6502Functions.h

// Loading
#define INS_LDA_IM 0xA9 // immediate
#define INS_LDA_ZP 0xA5 // Zero Page
#define INS_LDA_ZX 0xB5 // Zero Page X

#define INS_LDX_IM 0xA2
#define INS_LDX_ZP 0xA6

#define INS_LDY_IM 0xA0
#define INS_LDY_ZP 0xA4
#define INS_LDY_ZX 0xB4




typedef uint8_t Byte;
typedef uint16_t Word;

typedef struct Mem {
    Byte Data[MaxMem];
} Mem;


typedef struct CPU {
    // info about registers [http://www.obelisk.me.uk/6502/registers.html]

    Word PC; // program counter
    Word SP; // stack pointer

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


static const uint8_t OPCODES_CYCLES[256] = {
    //  0  1   2   3   4   5   6   7   8  9   A   B   C   D   E  F
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  2,  0,  0,  0,  0, 0,  // 0
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  // 1
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  2,  0,  0,  0,  0, 0,  // 2
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  // 3
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  3,  4,  0,  0,  0, 0,  // 4
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  3,  4,  0,  0,  0, 0,  // 5
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  3,  0,  0,  0,  0, 0,  // 6
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  // 7
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  // 8
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  2,  0,  0,  0,  0, 0,  // 9
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  // A
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  // B
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  // C
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  // D
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  // E
        0, 0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  // F

};