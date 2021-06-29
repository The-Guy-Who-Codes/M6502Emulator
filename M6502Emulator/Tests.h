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