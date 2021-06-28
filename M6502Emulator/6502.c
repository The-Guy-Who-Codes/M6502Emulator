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
    T_LDA_ZPX(&cpu, &mem, hConsole);
    T_LDY_ZPX(&cpu, &mem, hConsole);
    T_LDX_ZPY(&cpu, &mem, hConsole);
    T_LDA_ABS(&cpu, &mem, hConsole);
    T_LDX_ABS(&cpu, &mem, hConsole);
    T_LDY_ABS(&cpu, &mem, hConsole);
    T_LDA_ABSX(&cpu, &mem, hConsole);
    T_LDY_ABSX(&cpu, &mem, hConsole);
    T_LDA_ABSY(&cpu, &mem, hConsole);
    T_LDX_ABSY(&cpu, &mem, hConsole);
    T_LDA_INDX(&cpu, &mem, hConsole);
    T_LDA_INDY(&cpu, &mem, hConsole);

    T_STA_ZP(&cpu, &mem, hConsole);
    T_STX_ZP(&cpu, &mem, hConsole);
    T_STY_ZP(&cpu, &mem, hConsole);
    T_STA_ABS(&cpu, &mem, hConsole);
    T_STX_ABS(&cpu, &mem, hConsole);
    T_STY_ABS(&cpu, &mem, hConsole);
    T_STA_ZPX(&cpu, &mem, hConsole);
    T_STY_ZPX(&cpu, &mem, hConsole);
    T_STX_ZPY(&cpu, &mem, hConsole);
    T_STA_ABSX(&cpu, &mem, hConsole);
    T_STA_ABSY(&cpu, &mem, hConsole);

    return 0;
}
