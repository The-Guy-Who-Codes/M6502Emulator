#pragma warning(disable : 4996)

#include "TestingModule.h"

int calcCycles(uint8_t opcode) {
	uint8_t index = 0;
	index += (opcode << 4);
	index += (opcode >> 4);
	return index;
}

void TestLoadFlags(struct CPU* cpu, HANDLE* hConsole, int Z, int N, char* prefix) {
	char nameN[20];
	strcat(strcpy(nameN, prefix), "_N");

	char nameZ[20];
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

void T_LDA_ZPX(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	int testValue = 0x54;
	int Z = 0;
	int N = 0;
	reset(cpu, mem);
	cpu->X = 0b10101010; 
	mem->Data[0xFFFC] = INS_LDA_ZPX;
	mem->Data[0xFFFD] = 0b01010101;
	mem->Data[0xFF] = testValue;

	int cycles = 4;
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, testValue, "LDA_ZPX_A", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "LDA_ZPX");
	NEW_TEST();

}

void T_LDY_ZPX(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	int testValue = 0b10010011;
	int Z = 0;
	int N = 1;
	reset(cpu, mem);
	cpu->X = 0xA3;
	mem->Data[0xFFFC] = INS_LDY_ZPX;
	mem->Data[0xFFFD] = 0x12;
	mem->Data[0xB5] = testValue;

	int cycles = 4;
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->Y, testValue, "LDY_ZPX_Y", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "LDY_ZPX");
	NEW_TEST();

}

void T_LDA_ABS(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	int testValue = 0b01010011;
	int Z = 0;
	int N = 0;
	reset(cpu, mem);
	mem->Data[0xFFFC] = INS_LDA_ABS;
	mem->Data[0xFFFD] = 0x12;
	mem->Data[0xFFFE] = 0x43;
	mem->Data[0x4312] = testValue;

	int cycles = 4;
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, testValue, "LDA_ABS_A", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "LDA_ABS");
	NEW_TEST();

}

void T_LDX_ABS(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	int testValue = 0b11010011;
	int Z = 0;
	int N = 1;
	reset(cpu, mem);
	mem->Data[0xFFFC] = INS_LDX_ABS;
	mem->Data[0xFFFD] = 0xAB;
	mem->Data[0xFFFE] = 0xCD;
	mem->Data[0xCDAB] = testValue;

	int cycles = 4;
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->X, testValue, "LDX_ABS_X", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "LDX_ABS");
	NEW_TEST();

}

void T_LDY_ABS(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	int testValue = 0b0;
	int Z = 1;
	int N = 0;
	reset(cpu, mem);
	mem->Data[0xFFFC] = INS_LDY_ABS;
	mem->Data[0xFFFD] = 0x21;
	mem->Data[0xFFFE] = 0x69;
	mem->Data[0x6921] = testValue;

	int cycles = 4;
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->Y, testValue, "LDY_ABS_Y", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "LDY_ABS");
	NEW_TEST();

}

void T_LDA_ABSX(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	int testValue = 0b01011111;
	int Z = 0;
	int N = 0;
	reset(cpu, mem);
	cpu->X = 0x12;
	mem->Data[0xFFFC] = INS_LDA_ABSX;
	mem->Data[0xFFFD] = 0x21;
	mem->Data[0xFFFE] = 0x69;
	mem->Data[0x6933] = testValue;

	int cycles = 4;
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, testValue, "LDA_ABSX_A", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "LDA_ABSX");
	NEW_TEST();

}

void T_LDY_ABSX(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	int testValue = 0b11011111;
	int Z = 0;
	int N = 1;
	reset(cpu, mem);
	cpu->X = 0x2;
	mem->Data[0xFFFC] = INS_LDY_ABSX;
	mem->Data[0xFFFD] = 0xFE;
	mem->Data[0xFFFE] = 0x69;
	mem->Data[0x6A00] = testValue;

	int cycles = 4;
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->Y, testValue, "LDY_ABSX_Y", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "LDY_ABSX");
	NEW_TEST();

}

void T_LDA_ABSY(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	int testValue = 0b01111111;
	int Z = 0;
	int N = 0;
	reset(cpu, mem);
	cpu->Y = 0xAA;
	mem->Data[0xFFFC] = INS_LDA_ABSY;
	mem->Data[0xFFFD] = 0x21;
	mem->Data[0xFFFE] = 0x69;
	mem->Data[0x69CB] = testValue;

	int cycles = 4;
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, testValue, "LDA_ABSY_A", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "LDA_ABSY");
	NEW_TEST();

}

void T_LDX_ABSY(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	int testValue = 0b11111111;
	int Z = 0;
	int N = 1;
	reset(cpu, mem);
	cpu->Y = 0x21;
	mem->Data[0xFFFC] = INS_LDX_ABSY;
	mem->Data[0xFFFD] = 0x33;
	mem->Data[0xFFFE] = 0x80;
	mem->Data[0x8054] = testValue;

	int cycles = OPCODE_CYCLES[calcCycles(INS_LDX_ABSY)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->X, testValue, "LDX_ABSY_X", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "LDX_ABSY");
	NEW_TEST();

}