#include "6502.c"
#include "../M6502Testing/pch.h"


int main() {
	Mem mem;
	CPU cpu;
	reset(&cpu, &mem);

	return 0;
}