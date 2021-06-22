#include "6502Declarations.h"
#include "6502Functions.h"



int main() {
    Mem mem;
    CPU cpu;
    reset(&cpu, &mem);
    // test program
    
    cpu.X = 0xFF;
    mem.Data[0xFFFC] = INS_LDA_ZX;
    mem.Data[0xFFFD] = 0x80;
    mem.Data[0x7F] = 0x72;

    // End Test
    int cycles = 4;
    execute(&cycles, &cpu, &mem);
    printf("A: %x\nX: %x\nY: %x\n", cpu.A, cpu.X, cpu.Y);
    return 0;
}
