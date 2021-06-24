#pragma warning(disable : 4996)

#include "TestingModule.h"

void TestLoadFlags(struct CPU* cpu, HANDLE* hConsole, int Z, int N, char* prefix) {
	char nameN[9];
	strcat(strcpy(nameN, prefix), "_N");

	char nameZ[9];
	strcat(strcpy(nameZ, prefix), "_Z");


	TEST_EQ(cpu->N, N, nameN, hConsole);
	TEST_EQ(cpu->Z, Z, nameZ, hConsole);
}

// example test

void T_LDA_IM(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	// value which is going to be tested is in correct location	
	int testValue = 0b10011001;
	int Z = 0;
	int N = 1;
	// reset memory so that there are no prexisting conflicts
	reset(cpu, mem);
	// set up memory for test to work
	mem->Data[0xFFFC] = INS_LDA_IM;
	mem->Data[0xFFFD] = testValue;

	int cycles = 2;
	execute(&cycles, cpu, mem);

	// test that the test has performed correctly
	TEST_EQ(cpu->A, testValue, "LDA_IM_A", hConsole);
	// tests for the correct flags in the LDA sequence
	TestLoadFlags(cpu, hConsole, Z, N, "LDA_IM");
	// Separates new tests
	NEW_TEST();
	
}


void T_LDX_IM(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	int testValue = 0b00011001;
	int Z = 0;
	int N = 0;
	reset(cpu, mem);
	mem->Data[0xFFFC] = INS_LDX_IM;
	mem->Data[0xFFFD] = testValue;

	int cycles = 2;
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->X, testValue, "LDX_IM_X", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "LDX_IM");
	NEW_TEST();

}

void T_LDY_IM(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	int testValue = 0b11011001;
	int Z = 0;
	int N = 1;
	reset(cpu, mem);
	mem->Data[0xFFFC] = INS_LDY_IM;
	mem->Data[0xFFFD] = testValue;

	int cycles = 2;
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->Y, testValue, "LDY_IM_Y", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "LDY_IM");
	NEW_TEST();

}

void T_LDA_ZP(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	int testValue = 0b11011001;
	int Z = 0;
	int N = 1;
	reset(cpu, mem);
	mem->Data[0xFFFC] = INS_LDA_ZP;
	mem->Data[0xFFFD] = 0x72;
	mem->Data[0x72] = testValue;

	int cycles = 3;
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, testValue, "LDA_ZP_A", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "LDA_ZP");
	NEW_TEST();

}

void T_LDX_ZP(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	int testValue = 0b11011001;
	int Z = 0;
	int N = 1;
	reset(cpu, mem);
	mem->Data[0xFFFC] = INS_LDX_ZP;
	mem->Data[0xFFFD] = 0x72;
	mem->Data[0x72] = testValue;

	int cycles = 3;
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->X, testValue, "LDX_ZP_X", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "LDX_ZP");
	NEW_TEST();

}

void T_LDY_ZP(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	int testValue = 0;
	int Z = 1;
	int N = 0;
	reset(cpu, mem);
	mem->Data[0xFFFC] = INS_LDY_ZP;
	mem->Data[0xFFFD] = 0x64;
	mem->Data[0x64] = testValue;

	int cycles = 3;
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->Y, testValue, "LDY_ZP_Y", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "LDY_ZP");
	NEW_TEST();

}

void T_LDA_ZX(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	int testValue = 0x54;
	int Z = 0;
	int N = 0;
	reset(cpu, mem);
	cpu->X = 0b10101010; 
	mem->Data[0xFFFC] = INS_LDA_ZX;
	mem->Data[0xFFFD] = 0b01010101;
	mem->Data[0xFF] = testValue;

	int cycles = 4;
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, testValue, "LDA_ZX_A", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "LDA_ZX");
	NEW_TEST();

}

void T_LDY_ZX(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	int testValue = 0b10010011;
	int Z = 0;
	int N = 1;
	reset(cpu, mem);
	cpu->X = 0xA3;
	mem->Data[0xFFFC] = INS_LDY_ZX;
	mem->Data[0xFFFD] = 0x12;
	mem->Data[0xB5] = testValue;

	int cycles = 4;
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->Y, testValue, "LDY_ZX_Y", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "LDY_ZX");
	NEW_TEST();

}