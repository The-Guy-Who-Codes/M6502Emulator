#include "6502Declarations.h"
#include "6502Functions.h"
#include "Tests.h"


int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    Mem mem;
    CPU cpu;
    reset(&cpu, &mem);
#if 0
    // test program
    
    cpu.X = 0xFF;
    mem.Data[0xFFFC] = INS_LDA_ZX;
    mem.Data[0xFFFD] = 0x80;
    mem.Data[0x7F] = 0x72;

    // End Test
    int cycles = 4;
    execute(&cycles, &cpu, &mem);
    printf("A: %x\nX: %x\nY: %x\n", cpu.A, cpu.X, cpu.Y);
#endif
    T_LDA_IM(&cpu, &mem, hConsole);
    T_LDX_IM(&cpu, &mem, hConsole);
    T_LDY_IM(&cpu, &mem, hConsole);
    T_LDA_ZP(&cpu, &mem, hConsole);
    T_LDX_ZP(&cpu, &mem, hConsole);
    T_LDY_ZP(&cpu, &mem, hConsole);
    T_LDA_ZX(&cpu, &mem, hConsole);


    return 0;
}
