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


	TEST_EQ(cpu->Flag.N, N, nameN, hConsole);
	TEST_EQ(cpu->Flag.Z, Z, nameZ, hConsole);
}

/* Loading Tests */

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

void T_LDX_ZPY(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	int testValue = 0b0;
	int Z = 1;
	int N = 0;
	reset(cpu, mem);
	cpu->Y = 0xA3;
	mem->Data[0xFFFC] = INS_LDX_ZPY;
	mem->Data[0xFFFD] = 0x12;
	mem->Data[0xB5] = testValue;

	int cycles = 4;
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->X, testValue, "LDX_ZPY_X", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "LDX_ZPY");
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

void T_LDA_INDX(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	int testValue = 0b11000101;
	int Z = 0;
	int N = 1;
	reset(cpu, mem);
	cpu->X = 0x21;
	mem->Data[0xFFFC] = INS_LDA_INDX;
	mem->Data[0xFFFD] = 0xFD;
	mem->Data[0x1E] = 0x80;
	mem->Data[0x1F] = 0x12;
	mem->Data[0x1280] = testValue;

	int cycles = OPCODE_CYCLES[calcCycles(INS_LDA_INDX)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, testValue, "LDA_INDX_A", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "LDA_INDX");
	NEW_TEST();

}

void T_LDA_INDY(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	int testValue = 0b10000101;
	int Z = 0;
	int N = 1;
	reset(cpu, mem);
	cpu->Y = 0x21;
	mem->Data[0xFFFC] = INS_LDA_INDY;
	mem->Data[0xFFFD] = 0xFD;
	mem->Data[0xFD] = 0x80;
	mem->Data[0xFE] = 0x12;
	mem->Data[0x12A1] = testValue;

	int cycles = OPCODE_CYCLES[calcCycles(INS_LDA_INDY)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, testValue, "LDA_INDY_A", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "LDA_INDY");
	NEW_TEST();

}

/* Storing Tests */

void T_STA_ZP(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	int storeLocation = 0x32;
	reset(cpu, mem);
	cpu->A = 0x72;
	mem->Data[0xFFFC] = INS_STA_ZP;
	mem->Data[0xFFFD] = storeLocation;

	int cycles = OPCODE_CYCLES[calcCycles(INS_STA_ZP)];
	execute(&cycles, cpu, mem);

	TEST_EQ(mem->Data[storeLocation], cpu->A, "STA_ZP", hConsole);
	NEW_TEST();
}

void T_STX_ZP(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	int storeLocation = 0x23;
	reset(cpu, mem);
	cpu->X = 0x98;
	mem->Data[0xFFFC] = INS_STX_ZP;
	mem->Data[0xFFFD] = storeLocation;

	int cycles = OPCODE_CYCLES[calcCycles(INS_STX_ZP)];
	execute(&cycles, cpu, mem);

	TEST_EQ(mem->Data[storeLocation], cpu->X, "STX_ZP", hConsole);
	NEW_TEST();
}

void T_STY_ZP(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	int storeLocation = 0x32;
	reset(cpu, mem);
	cpu->Y = 0x72;
	mem->Data[0xFFFC] = INS_STY_ZP;
	mem->Data[0xFFFD] = storeLocation;

	int cycles = OPCODE_CYCLES[calcCycles(INS_STY_ZP)];
	execute(&cycles, cpu, mem);

	TEST_EQ(mem->Data[storeLocation], cpu->Y, "STY_ZP", hConsole);
	NEW_TEST();
}

void T_STA_ABS(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	uint16_t storeLocation = 0x3264;
	reset(cpu, mem);
	cpu->A = 0x72;
	mem->Data[0xFFFC] = INS_STA_ABS;
	mem->Data[0xFFFD] = (storeLocation << 8) >> 8;
	mem->Data[0xFFFE] = storeLocation >> 8;

	int cycles = OPCODE_CYCLES[calcCycles(INS_STA_ABS)];
	execute(&cycles, cpu, mem);

	TEST_EQ(mem->Data[storeLocation], cpu->A, "STA_ABS", hConsole);
	NEW_TEST();
}

void T_STX_ABS(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	uint16_t storeLocation = 0xA234;
	reset(cpu, mem);
	cpu->X = 0xFF;
	mem->Data[0xFFFC] = INS_STX_ABS;
	mem->Data[0xFFFD] = (storeLocation << 8) >> 8;
	mem->Data[0xFFFE] = storeLocation >> 8;

	int cycles = OPCODE_CYCLES[calcCycles(INS_STX_ABS)];
	execute(&cycles, cpu, mem);

	TEST_EQ(mem->Data[storeLocation], cpu->X, "STX_ABS", hConsole);
	NEW_TEST();
}

void T_STY_ABS(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	uint16_t storeLocation = 0xFF65;
	reset(cpu, mem);
	cpu->Y = 0xCD;
	mem->Data[0xFFFC] = INS_STY_ABS;
	mem->Data[0xFFFD] = (storeLocation << 8) >> 8;
	mem->Data[0xFFFE] = storeLocation >> 8;

	int cycles = OPCODE_CYCLES[calcCycles(INS_STY_ABS)];
	execute(&cycles, cpu, mem);

	TEST_EQ(mem->Data[storeLocation], cpu->Y, "STY_ABS", hConsole);
	NEW_TEST();
}

void T_STA_ZPX(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	Byte storeLocation = 0x42;
	reset(cpu, mem);
	cpu->A = 0xCD;
	cpu->X = 0x21;
	mem->Data[0xFFFC] = INS_STA_ZPX;
	mem->Data[0xFFFD] = storeLocation;

	int cycles = OPCODE_CYCLES[calcCycles(INS_STA_ZPX)];
	execute(&cycles, cpu, mem);

	TEST_EQ(mem->Data[storeLocation + cpu->X], cpu->A, "STA_ZPX", hConsole);
	NEW_TEST();
}

void T_STY_ZPX(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	Byte storeLocation = 0x42;
	reset(cpu, mem);
	cpu->Y = 0xCD;
	cpu->X = 0x21;
	mem->Data[0xFFFC] = INS_STY_ZPX;
	mem->Data[0xFFFD] = storeLocation;

	int cycles = OPCODE_CYCLES[calcCycles(INS_STY_ZPX)];
	execute(&cycles, cpu, mem);

	TEST_EQ(mem->Data[storeLocation + cpu->X], cpu->Y, "STY_ZPX", hConsole);
	NEW_TEST();
}

void T_STX_ZPY(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	Byte storeLocation = 0x42;
	reset(cpu, mem);
	cpu->X = 0xCD;
	cpu->Y = 0x21;
	mem->Data[0xFFFC] = INS_STX_ZPY;
	mem->Data[0xFFFD] = storeLocation;

	int cycles = OPCODE_CYCLES[calcCycles(INS_STX_ZPY)];
	execute(&cycles, cpu, mem);

	TEST_EQ(mem->Data[storeLocation + cpu->Y], cpu->X, "STX_ZPY", hConsole);
	NEW_TEST();
}

void T_STA_ABSX(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	uint16_t storeLocation = 0x3264;
	reset(cpu, mem);
	cpu->A = 0x72;
	cpu->X = 0xA3;
	mem->Data[0xFFFC] = INS_STA_ABSX;
	mem->Data[0xFFFD] = (storeLocation << 8) >> 8;
	mem->Data[0xFFFE] = storeLocation >> 8;

	int cycles = OPCODE_CYCLES[calcCycles(INS_STA_ABSX)];
	execute(&cycles, cpu, mem);

	TEST_EQ(mem->Data[storeLocation + cpu->X], cpu->A, "STA_ABSX", hConsole);
	NEW_TEST();
}

void T_STA_ABSY(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	uint16_t storeLocation = 0xF2A4;
	reset(cpu, mem);
	cpu->A = 0x42;
	cpu->Y = 0xA3;
	mem->Data[0xFFFC] = INS_STA_ABSY;
	mem->Data[0xFFFD] = (storeLocation << 8) >> 8;
	mem->Data[0xFFFE] = storeLocation >> 8;

	int cycles = OPCODE_CYCLES[calcCycles(INS_STA_ABSY)];
	execute(&cycles, cpu, mem);

	TEST_EQ(mem->Data[storeLocation + cpu->Y], cpu->A, "STA_ABSY", hConsole);
	NEW_TEST();
}

void T_STA_INDX(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	int storeLocation = 0x8012;

	reset(cpu, mem);
	cpu->X = 0x21;
	mem->Data[0xFFFC] = INS_STA_INDX;
	mem->Data[0xFFFD] = 0xFD;
	mem->Data[0x1E] = (storeLocation << 8) >> 8;
	mem->Data[0x1F] = storeLocation >> 8;

	int cycles = OPCODE_CYCLES[calcCycles(INS_STA_INDX)];
	execute(&cycles, cpu, mem);

	TEST_EQ(mem->Data[storeLocation], cpu->A, "STA_INDX", hConsole);
	NEW_TEST();

}

void T_STA_INDY(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {
	int storeLocation = 0x5476;

	reset(cpu, mem);
	cpu->Y = 0x21;
	mem->Data[0xFFFC] = INS_LDA_INDY;
	mem->Data[0xFFFD] = 0xFD;
	mem->Data[0xFD] = (storeLocation << 8) >> 8;
	mem->Data[0xFE] = storeLocation >> 8;

	int cycles = OPCODE_CYCLES[calcCycles(INS_LDA_INDY)];
	execute(&cycles, cpu, mem);

	TEST_EQ(mem->Data[storeLocation + cpu->Y], cpu->A, "LDA_INDY_A", hConsole);
	NEW_TEST();

}

/* Register Transfer Tests */

void T_TXA_IMP(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	cpu->X = 0b0;
	int Z = 1;
	int N = 0;
	mem->Data[0xFFFC] = INS_TXA_IMP;

	int cycles = OPCODE_CYCLES[calcCycles(INS_TXA_IMP)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, cpu->X, "TXA_IMP", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "TXA_IMP");
	NEW_TEST();

}

void T_TYA_IMP(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	cpu->Y = 0b00010101;
	int Z = 0;
	int N = 0;
	mem->Data[0xFFFC] = INS_TYA_IMP;

	int cycles = OPCODE_CYCLES[calcCycles(INS_TYA_IMP)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, cpu->Y, "TYA_IMP", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "TYA_IMP");
	NEW_TEST();

}

void T_TAX_IMP(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	cpu->A = 0b10110101;
	int Z = 0;
	int N = 1;
	mem->Data[0xFFFC] = INS_TAX_IMP;

	int cycles = OPCODE_CYCLES[calcCycles(INS_TAX_IMP)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->X, cpu->A, "TAX_IMP", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "TAX_IMP");
	NEW_TEST();

}

void T_TAY_IMP(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	cpu->A = 0b10011111;
	int Z = 0;
	int N = 1;
	mem->Data[0xFFFC] = INS_TAY_IMP;

	int cycles = OPCODE_CYCLES[calcCycles(INS_TAY_IMP)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->Y, cpu->A, "TAY_IMP", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "TAY_IMP");
	NEW_TEST();

}



/* Stack Operation Tests */

void T_TSX_IMP(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	cpu->X = 0b10001111;
	int Z = 0;
	int N = 1;
	mem->Data[0xFFFC] = INS_TSX_IMP;

	int cycles = OPCODE_CYCLES[calcCycles(INS_TSX_IMP)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->X, cpu->SP, "TSX_IMP", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "TXS_IMP");
	NEW_TEST();

}

void T_TXS_IMP(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	cpu->X = 0x21;
	mem->Data[0xFFFC] = INS_TXS_IMP;

	int cycles = OPCODE_CYCLES[calcCycles(INS_TXS_IMP)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->X, cpu->SP, "TXS_IMP", hConsole);
	NEW_TEST();

}

void T_PHA_IMP(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	cpu->A = 0x21;
	mem->Data[0xFFFC] = INS_PHA_IMP;

	int cycles = OPCODE_CYCLES[calcCycles(INS_PHA_IMP)];
	execute(&cycles, cpu, mem);

	TEST_EQ(mem->Data[0x01FF], cpu->A, "PHA_IMP", hConsole);
	NEW_TEST();

}

void T_PHP_IMP(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	cpu->Flag.C = 1;
	cpu->Flag.Z = 1;
	cpu->Flag.I = 1;
	cpu->Flag.D = 1;
	cpu->Flag.B = 1;
	cpu->Flag.O = 0;
	cpu->Flag.N = 1;

	mem->Data[0xFFFC] = INS_PHP_IMP;

	int cycles = OPCODE_CYCLES[calcCycles(INS_PHP_IMP)];
	execute(&cycles, cpu, mem);

	TEST_EQ(mem->Data[0x01FF], cpu->PS, "PHP_IMP", hConsole);
	NEW_TEST();

}

void T_PLA_IMP(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	mem->Data[0xFFFC] = INS_PLA_IMP;
	mem->Data[0x0100] = 0b10010011;
	int Z = 0;
	int N = 1;

	int cycles = OPCODE_CYCLES[calcCycles(INS_PLA_IMP)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, mem->Data[0x0100], "PLA_IMP", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "PLA_IMP");
	NEW_TEST();

}

void T_PLP_IMP(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
#if 0
	cpu->Flag.C = 1;
	cpu->Flag.Z = 1;
	cpu->Flag.I = 1;
	cpu->Flag.D = 1;
	cpu->Flag.B = 1;
	cpu->Flag.O = 0;
	cpu->Flag.N = 1;
#endif
	cpu->PS = 0;
	mem->Data[0xFFFC] = INS_PLP_IMP;
	mem->Data[0x0100] = 0b10101110;

	int cycles = OPCODE_CYCLES[calcCycles(INS_PLP_IMP)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->Flag.N, 0, "PLP_IMP_N", hConsole);
	TEST_EQ(cpu->Flag.O, 1, "PLP_IMP_O", hConsole);
	TEST_EQ(cpu->Flag.B, 0, "PLP_IMP_B", hConsole);
	TEST_EQ(cpu->Flag.D, 1, "PLP_IMP_D", hConsole);
	TEST_EQ(cpu->Flag.I, 1, "PLP_IMP_I", hConsole);
	TEST_EQ(cpu->Flag.Z, 1, "PLP_IMP_Z", hConsole);
	TEST_EQ(cpu->Flag.C, 0, "PLP_IMP_C", hConsole);

	NEW_TEST();

}

/* Logical Operations Tests */

void T_AND_IM(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	Byte value1 = 0b10010011;
	Byte value2 = 0b10010110;
	cpu->A = value1;
	mem->Data[0xFFFC] = INS_AND_IM;
	mem->Data[0xFFFD] = value2;
	
	// flags for after the operation
	int Z = 0;
	int N = 1;

	int cycles = OPCODE_CYCLES[calcCycles(INS_AND_IM)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, value1 & value2, "AND_IM", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "AND_IM");
	NEW_TEST();

}

void T_AND_ZP(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	Byte value1 = 0b10101010;
	Byte value2 = 0b01010101;
	cpu->A = value1;
	mem->Data[0xFFFC] = INS_AND_ZP;
	mem->Data[0xFFFD] = 0x32;
	mem->Data[0x32] = value2;

	// flags for after the operation
	int Z = 1;
	int N = 0;

	int cycles = OPCODE_CYCLES[calcCycles(INS_AND_ZP)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, value1 & value2, "AND_ZP", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "AND_ZP");
	NEW_TEST();

}

void T_AND_ZPX(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	Byte value1 = 0b11101010;
	Byte value2 = 0b01011101;
	cpu->A = value1;
	cpu->X = 0x21;
	mem->Data[0xFFFC] = INS_AND_ZPX;
	mem->Data[0xFFFD] = 0x32;
	mem->Data[0x53] = value2;

	// flags for after the operation
	int Z = 0;
	int N = 0;

	int cycles = OPCODE_CYCLES[calcCycles(INS_AND_ZPX)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, value1 & value2, "AND_ZPX", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "AND_ZPX");
	NEW_TEST();

}

void T_AND_ABS(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	Byte value1 = 0b11101010;
	Byte value2 = 0b11011101;
	cpu->A = value1;
	mem->Data[0xFFFC] = INS_AND_ABS;
	mem->Data[0xFFFD] = 0x32;
	mem->Data[0xFFFE] = 0x31;
	mem->Data[0x3132] = value2;

	// flags for after the operation
	int Z = 0;
	int N = 1;

	int cycles = OPCODE_CYCLES[calcCycles(INS_AND_ABS)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, value1 & value2, "AND_ABS", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "AND_ABS");
	NEW_TEST();

}

void T_AND_ABSX(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	Byte value1 = 0b11101010;
	Byte value2 = 0b11011101;
	cpu->A = value1;
	cpu->X = 0x21;
	mem->Data[0xFFFC] = INS_AND_ABSX;
	mem->Data[0xFFFD] = 0x32;
	mem->Data[0xFFFE] = 0x31;
	mem->Data[0x3153] = value2;

	// flags for after the operation
	int Z = 0;
	int N = 1;

	int cycles = OPCODE_CYCLES[calcCycles(INS_AND_ABSX)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, value1 & value2, "AND_ABSX", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "AND_ABSX");
	NEW_TEST();

}

void T_AND_ABSY(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	Byte value1 = 0b11101010;
	Byte value2 = 0b11011101;
	cpu->A = value1;
	cpu->Y = 0x21;
	mem->Data[0xFFFC] = INS_AND_ABSY;
	mem->Data[0xFFFD] = 0x32;
	mem->Data[0xFFFE] = 0x31;
	mem->Data[0x3153] = value2;

	// flags for after the operation
	int Z = 0;
	int N = 1;

	int cycles = OPCODE_CYCLES[calcCycles(INS_AND_ABSY)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, value1 & value2, "AND_ABSY", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "AND_ABSY");
	NEW_TEST();

}

void T_AND_INDX(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	Byte value1 = 0b11101010;
	Byte value2 = 0b11011101;
	cpu->A = value1;
	cpu->X = 0x02;
	mem->Data[0xFFFC] = INS_AND_INDX;
	mem->Data[0xFFFD] = 0x30;
	mem->Data[0x32] = 0x31;
	mem->Data[0x33] = 0x54;
	mem->Data[0x5431] = value2;

	// flags for after the operation
	int Z = 0;
	int N = 1;

	int cycles = OPCODE_CYCLES[calcCycles(INS_AND_INDX)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, value1 & value2, "AND_INDX", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "AND_INDX");
	NEW_TEST();

}

void T_AND_INDY(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	Byte value1 = 0b11101010;
	Byte value2 = 0b11011101;
	cpu->A = value1;
	cpu->Y = 0x02;
	mem->Data[0xFFFC] = INS_AND_INDY;
	mem->Data[0xFFFD] = 0x32;
	mem->Data[0x32] = 0x31;
	mem->Data[0x33] = 0x54;
	mem->Data[0x5433] = value2;

	// flags for after the operation
	int Z = 0;
	int N = 1;

	int cycles = OPCODE_CYCLES[calcCycles(INS_AND_INDY)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, value1 & value2, "AND_INDY", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "AND_INDY");
	NEW_TEST();

}

void T_EOR_IM(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	Byte value1 = 0b10010011;
	Byte value2 = 0b10010110;
	cpu->A = value1;
	mem->Data[0xFFFC] = INS_EOR_IM;
	mem->Data[0xFFFD] = value2;

	// flags for after the operation
	int Z = (value1 ^ value2) == 0 ? 1 : 0;
	int N = (((value1 ^ value2) & (1 << 7)) >> 7);

	int cycles = OPCODE_CYCLES[calcCycles(INS_EOR_IM)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, value1 ^ value2, "EOR_IM", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "EOR_IM");
	NEW_TEST();

}

void T_EOR_ZP(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	Byte value1 = 0b10101010;
	Byte value2 = 0b01010101;
	cpu->A = value1;
	mem->Data[0xFFFC] = INS_EOR_ZP;
	mem->Data[0xFFFD] = 0x32;
	mem->Data[0x32] = value2;

	// flags for after the operation
	int Z = (value1 ^ value2) == 0 ? 1 : 0;
	int N = (((value1 ^ value2) & (1 << 7)) >> 7);

	int cycles = OPCODE_CYCLES[calcCycles(INS_EOR_ZP)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, value1 ^ value2, "EOR_ZP", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "EOR_ZP");
	NEW_TEST();

}

void T_EOR_ZPX(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	Byte value1 = 0b11101010;
	Byte value2 = 0b01011101;
	cpu->A = value1;
	cpu->X = 0x21;
	mem->Data[0xFFFC] = INS_EOR_ZPX;
	mem->Data[0xFFFD] = 0x32;
	mem->Data[0x53] = value2;

	// flags for after the operation
	int Z = (value1 ^ value2) == 0 ? 1 : 0;
	int N = (((value1 ^ value2) & (1 << 7)) >> 7);

	int cycles = OPCODE_CYCLES[calcCycles(INS_EOR_ZPX)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, value1 ^ value2, "EOR_ZPX", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "EOR_ZPX");
	NEW_TEST();

}

void T_EOR_ABS(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	Byte value1 = 0b11101010;
	Byte value2 = 0b11011101;
	cpu->A = value1;
	mem->Data[0xFFFC] = INS_EOR_ABS;
	mem->Data[0xFFFD] = 0x32;
	mem->Data[0xFFFE] = 0x31;
	mem->Data[0x3132] = value2;

	// flags for after the operation
	int Z = (value1 ^ value2) == 0 ? 1 : 0;
	int N = (((value1 ^ value2) & (1 << 7)) >> 7);

	int cycles = OPCODE_CYCLES[calcCycles(INS_EOR_ABS)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, value1 ^ value2, "EOR_ABS", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "EOR_ABS");
	NEW_TEST();

}

void T_EOR_ABSX(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	Byte value1 = 0b11101010;
	Byte value2 = 0b11011101;
	cpu->A = value1;
	cpu->X = 0x21;
	mem->Data[0xFFFC] = INS_EOR_ABSX;
	mem->Data[0xFFFD] = 0x32;
	mem->Data[0xFFFE] = 0x31;
	mem->Data[0x3153] = value2;

	// flags for after the operation
	int Z = (value1 ^ value2) == 0 ? 1 : 0;
	int N = (((value1 ^ value2) & (1 << 7)) >> 7);

	int cycles = OPCODE_CYCLES[calcCycles(INS_EOR_ABSX)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, value1 ^ value2, "EOR_ABSX", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "EOR_ABSX");
	NEW_TEST();

}

void T_EOR_ABSY(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	Byte value1 = 0b11101010;
	Byte value2 = 0b11011101;
	cpu->A = value1;
	cpu->Y = 0x21;
	mem->Data[0xFFFC] = INS_EOR_ABSY;
	mem->Data[0xFFFD] = 0x32;
	mem->Data[0xFFFE] = 0x31;
	mem->Data[0x3153] = value2;

	// flags for after the operation
	int Z = (value1 ^ value2) == 0 ? 1 : 0;
	int N = (((value1 ^ value2) & (1 << 7)) >> 7);

	int cycles = OPCODE_CYCLES[calcCycles(INS_EOR_ABSY)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, value1 ^ value2, "EOR_ABSY", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "EOR_ABSY");
	NEW_TEST();

}

void T_EOR_INDX(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	Byte value1 = 0b11101010;
	Byte value2 = 0b11011101;
	cpu->A = value1;
	cpu->X = 0x02;
	mem->Data[0xFFFC] = INS_EOR_INDX;
	mem->Data[0xFFFD] = 0x30;
	mem->Data[0x32] = 0x31;
	mem->Data[0x33] = 0x54;
	mem->Data[0x5431] = value2;

	// flags for after the operation
	int Z = (value1 ^ value2) == 0 ? 1 : 0;
	int N = (((value1 ^ value2) & (1 << 7)) >> 7);

	int cycles = OPCODE_CYCLES[calcCycles(INS_EOR_INDX)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, value1 ^ value2, "EOR_INDX", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "EOR_INDX");
	NEW_TEST();

}

void T_EOR_INDY(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	Byte value1 = 0b11101010;
	Byte value2 = 0b11011101;
	cpu->A = value1;
	cpu->Y = 0x02;
	mem->Data[0xFFFC] = INS_EOR_INDY;
	mem->Data[0xFFFD] = 0x32;
	mem->Data[0x32] = 0x31;
	mem->Data[0x33] = 0x54;
	mem->Data[0x5433] = value2;

	// flags for after the operation
	int Z = (value1 ^ value2) == 0 ? 1 : 0;
	int N = (((value1 ^ value2) & (1 << 7)) >> 7);

	int cycles = OPCODE_CYCLES[calcCycles(INS_EOR_INDY)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, value1 ^ value2, "EOR_INDY", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "EOR_INDY");
	NEW_TEST();

}

void T_ORA_IM(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	Byte value1 = 0b10010011;
	Byte value2 = 0b10010110;
	cpu->A = value1;
	mem->Data[0xFFFC] = INS_ORA_IM;
	mem->Data[0xFFFD] = value2;

	// flags for after the operation
	int Z = (value1 | value2) == 0 ? 1 : 0;
	int N = (((value1 | value2) & (1 << 7)) >> 7);

	int cycles = OPCODE_CYCLES[calcCycles(INS_ORA_IM)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, value1 | value2, "ORA_IM", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "ORA_IM");
	NEW_TEST();

}

void T_ORA_ZP(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	Byte value1 = 0b10101010;
	Byte value2 = 0b01010101;
	cpu->A = value1;
	mem->Data[0xFFFC] = INS_ORA_ZP;
	mem->Data[0xFFFD] = 0x32;
	mem->Data[0x32] = value2;

	// flags for after the operation
	int Z = (value1 | value2) == 0 ? 1 : 0;
	int N = (((value1 | value2) & (1 << 7)) >> 7);

	int cycles = OPCODE_CYCLES[calcCycles(INS_ORA_ZP)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, value1 | value2, "ORA_ZP", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "ORA_ZP");
	NEW_TEST();

}

void T_ORA_ZPX(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	Byte value1 = 0b11101010;
	Byte value2 = 0b01011101;
	cpu->A = value1;
	cpu->X = 0x21;
	mem->Data[0xFFFC] = INS_ORA_ZPX;
	mem->Data[0xFFFD] = 0x32;
	mem->Data[0x53] = value2;

	// flags for after the operation
	int Z = (value1 | value2) == 0 ? 1 : 0;
	int N = (((value1 | value2) & (1 << 7)) >> 7);

	int cycles = OPCODE_CYCLES[calcCycles(INS_ORA_ZPX)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, value1 | value2, "ORA_ZPX", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "ORA_ZPX");
	NEW_TEST();

}

void T_ORA_ABS(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	Byte value1 = 0b11101010;
	Byte value2 = 0b11011101;
	cpu->A = value1;
	mem->Data[0xFFFC] = INS_ORA_ABS;
	mem->Data[0xFFFD] = 0x32;
	mem->Data[0xFFFE] = 0x31;
	mem->Data[0x3132] = value2;

	// flags for after the operation
	int Z = (value1 | value2) == 0 ? 1 : 0;
	int N = (((value1 | value2) & (1 << 7)) >> 7);

	int cycles = OPCODE_CYCLES[calcCycles(INS_ORA_ABS)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, value1 | value2, "ORA_ABS", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "ORA_ABS");
	NEW_TEST();

}

void T_ORA_ABSX(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	Byte value1 = 0b11101010;
	Byte value2 = 0b11011101;
	cpu->A = value1;
	cpu->X = 0x21;
	mem->Data[0xFFFC] = INS_ORA_ABSX;
	mem->Data[0xFFFD] = 0x32;
	mem->Data[0xFFFE] = 0x31;
	mem->Data[0x3153] = value2;

	// flags for after the operation
	int Z = (value1 | value2) == 0 ? 1 : 0;
	int N = (((value1 | value2) & (1 << 7)) >> 7);

	int cycles = OPCODE_CYCLES[calcCycles(INS_ORA_ABSX)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, value1 | value2, "ORA_ABSX", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "ORA_ABSX");
	NEW_TEST();

}

void T_ORA_ABSY(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	Byte value1 = 0b11101010;
	Byte value2 = 0b11011101;
	cpu->A = value1;
	cpu->Y = 0x21;
	mem->Data[0xFFFC] = INS_ORA_ABSY;
	mem->Data[0xFFFD] = 0x32;
	mem->Data[0xFFFE] = 0x31;
	mem->Data[0x3153] = value2;

	// flags for after the operation
	int Z = (value1 | value2) == 0 ? 1 : 0;
	int N = (((value1 | value2) & (1 << 7)) >> 7);

	int cycles = OPCODE_CYCLES[calcCycles(INS_ORA_ABSY)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, value1 | value2, "ORA_ABSY", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "ORA_ABSY");
	NEW_TEST();

}

void T_ORA_INDX(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	Byte value1 = 0b11101010;
	Byte value2 = 0b11011101;
	cpu->A = value1;
	cpu->X = 0x02;
	mem->Data[0xFFFC] = INS_ORA_INDX;
	mem->Data[0xFFFD] = 0x30;
	mem->Data[0x32] = 0x31;
	mem->Data[0x33] = 0x54;
	mem->Data[0x5431] = value2;

	// flags for after the operation
	int Z = (value1 | value2) == 0 ? 1 : 0;
	int N = (((value1 | value2) & (1 << 7)) >> 7);

	int cycles = OPCODE_CYCLES[calcCycles(INS_ORA_INDX)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, value1 | value2, "ORA_INDX", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "ORA_INDX");
	NEW_TEST();

}

void T_ORA_INDY(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);
	Byte value1 = 0b11101010;
	Byte value2 = 0b11011101;
	cpu->A = value1;
	cpu->Y = 0x02;
	mem->Data[0xFFFC] = INS_ORA_INDY;
	mem->Data[0xFFFD] = 0x32;
	mem->Data[0x32] = 0x31;
	mem->Data[0x33] = 0x54;
	mem->Data[0x5433] = value2;

	// flags for after the operation
	int Z = (value1 | value2) == 0 ? 1 : 0;
	int N = (((value1 | value2) & (1 << 7)) >> 7);

	int cycles = OPCODE_CYCLES[calcCycles(INS_ORA_INDY)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->A, value1 | value2, "ORA_INDY", hConsole);
	TestLoadFlags(cpu, hConsole, Z, N, "ORA_INDY");
	NEW_TEST();

}

void T_BIT_ZP(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);

	cpu->A = 0b10010010;
	mem->Data[0xFFFC] = INS_BIT_ZP;
	mem->Data[0xFFFD] = 0x32;
	mem->Data[0x32] = 0b10010010;

	// flags for after the operation
	int Z = 0;
	int N = 1;
	int O = 0;

	int cycles = OPCODE_CYCLES[calcCycles(INS_BIT_ZP)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->Flag.N, N, "BIT_ZP_N", hConsole);
	TEST_EQ(cpu->Flag.Z, Z, "BIT_ZP_Z", hConsole);
	TEST_EQ(cpu->Flag.O, O, "BIT_ZP_O", hConsole);
	NEW_TEST();

}

void T_BIT_ABS(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);

	cpu->A = 0b10101010;
	mem->Data[0xFFFC] = INS_BIT_ABS;
	mem->Data[0xFFFD] = 0x32;
	mem->Data[0x32] = 0b01010101;

	// flags for after the operation
	int Z = 1;
	int N = 0;
	int O = 1;

	int cycles = OPCODE_CYCLES[calcCycles(INS_BIT_ABS)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->Flag.N, N, "BIT_ABS_N", hConsole);
	TEST_EQ(cpu->Flag.Z, Z, "BIT_ABS_Z", hConsole);
	TEST_EQ(cpu->Flag.O, O, "BIT_ABS_O", hConsole);
	NEW_TEST();

}

/* Jumps and Calls Tests */

void T_JMP_ABS(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);

	mem->Data[0xFFFC] = INS_JMP_ABS;
	mem->Data[0xFFFD] = 0x32;
	mem->Data[0xFFFE] = 0x21;


	int cycles = OPCODE_CYCLES[calcCycles(INS_JMP_ABS)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->PC, 0x2132, "BIT_JMP", hConsole);
	NEW_TEST();

}

void T_JMP_IND(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);

	mem->Data[0xFFFC] = INS_JMP_IND;
	mem->Data[0xFFFD] = 0x32;
	mem->Data[0xFFFE] = 0x21;
	mem->Data[0x2132] = 0xF4;
	mem->Data[0x2133] = 0x43;

	int cycles = OPCODE_CYCLES[calcCycles(INS_JMP_IND)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->PC, 0x43F4, "BIT_IND", hConsole);
	NEW_TEST();

}

void T_JSR_IND(struct CPU* cpu, struct Mem* mem, HANDLE* hConsole) {

	reset(cpu, mem);

	mem->Data[0xFFFC] = INS_JSR_ABS;
	mem->Data[0xFFFD] = 0x32;
	mem->Data[0xFFFE] = 0x21; // 0x2132
	mem->Data[0x2132] = INS_LDA_IM;
	mem->Data[0x2133] = 0b10110011;
	mem->Data[0x2134] = INS_AND_IM;
	mem->Data[0x2135] = 0b10110011;
	mem->Data[0x2136] = INS_STA_ABS;
	mem->Data[0x2137] = 0x32;
	mem->Data[0x2138] = 0x54; // 0x5432
	mem->Data[0x2139] = INS_RTS_IMP;



	int cycles = OPCODE_CYCLES[calcCycles(INS_JSR_ABS)] + OPCODE_CYCLES[calcCycles(INS_LDA_IM)] + OPCODE_CYCLES[calcCycles(INS_AND_IM)] + OPCODE_CYCLES[calcCycles(INS_STA_ABS)] + OPCODE_CYCLES[calcCycles(INS_RTS_IMP)];
	execute(&cycles, cpu, mem);

	TEST_EQ(cpu->PC, 0xFFFF, "JSR_RTS_PC", hConsole);
	TEST_EQ(mem->Data[0x5432], 0xB3, "JSR_RTS_AND", hConsole);
	NEW_TEST();

}