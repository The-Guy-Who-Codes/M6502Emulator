

static inline void memInit(struct Mem* mem) { // initialises memory by resetting all memory values to 0
    for (int i = 0; i < MaxMem; i++) {
        mem->Data[i] = 0;
    }
}

static inline void reset(struct CPU* cpu, struct Mem* mem) { // resets the state of the CPU as it were to be booted
    cpu->PC = 0xFFFC; // the reset vector in memory for the 6502 [https://www.c64-wiki.com/wiki/Reset_(Process)] 
    cpu->SP = 0x00FF;
    cpu->D = 0; // clear decimal flag
    cpu->C = cpu->Z = cpu->I = cpu->B = cpu->O = cpu->N = 0; // clear all flag registers
    memInit(mem);
}

static inline Byte fetchByte(uint32_t* cycles, struct Mem* mem, struct CPU* cpu) {
    Byte Data = mem->Data[cpu->PC]; // fetches byte which PC is pointing to
    cpu->PC++; // increment PC
    (*cycles)--; // decriments cycle counter as fetching takes 1 cycle
    return Data;
}

static inline Byte readByte(uint32_t* cycles, struct Mem* mem, struct CPU* cpu, Byte Address) {
    Byte Data = mem->Data[Address]; // fetches byte which PC is pointing to
    (*cycles)--; // decriments cycle counter as fetching takes 1 cycle
    return Data;
}

static inline void setLoadFlags(CPU* cpu, Byte* regValue) {
    cpu->Z = (regValue == 0); // set if A == 0
    cpu->N = (((*regValue) & (1 << 7)) >> 7);
    //cpu->N = (cpu->A & 0b10000000) > 0; // set if Bit 7 of A is set
}

void execute(uint32_t* cycles, struct CPU* cpu, struct Mem* mem) {
    while (*cycles > 0) {
        Byte Instruction = fetchByte(cycles, mem, cpu);
        switch (Instruction) {

            // data from [http://www.obelisk.me.uk/6502/instructions.html]

        case INS_LDA_IM: {
            Byte Value = fetchByte(cycles, mem, cpu);
            cpu->A = Value;
            setLoadFlags(cpu, &cpu->A);
        } break;

        case INS_LDX_IM: {
            Byte Value = fetchByte(cycles, mem, cpu);
            cpu->X = Value;
            setLoadFlags(cpu, &cpu->X);
        } break;

        case INS_LDY_IM: {
            Byte Value = fetchByte(cycles, mem, cpu);
            cpu->Y = Value;
            setLoadFlags(cpu, &cpu->Y);
        } break;
    
        case INS_LDA_ZP: {
            Byte ZPAddress = fetchByte(cycles, mem, cpu);
            cpu->A = readByte(cycles, mem, cpu, ZPAddress);
            setLoadFlags(cpu, &cpu->A);
        } break;
        
        case INS_LDX_ZP: {
            Byte ZPAddress = fetchByte(cycles, mem, cpu);
            cpu->X = readByte(cycles, mem, cpu, ZPAddress);
            setLoadFlags(cpu, &cpu->X);
        } break;

        case INS_LDY_ZP: {
            Byte ZPAddress = fetchByte(cycles, mem, cpu);
            cpu->Y = readByte(cycles, mem, cpu, ZPAddress);
            setLoadFlags(cpu, &cpu->Y);
        } break;

        case INS_LDA_ZX: {
            Byte ZPAddress = fetchByte(cycles, mem, cpu);
            ZPAddress += cpu->X;
            (*cycles)--; // offset for the addition operation
            cpu->A = readByte(cycles, mem, cpu, ZPAddress);
            setLoadFlags(cpu, &cpu->A);
        } break;

        case INS_LDY_ZX: {
            Byte ZPAddress = fetchByte(cycles, mem, cpu);
            ZPAddress += cpu->X;
            (*cycles)--;
            cpu->Y = readByte(cycles, mem, cpu, ZPAddress);
            setLoadFlags(cpu, &cpu->Y);
        } break;

        default: printf("[ERROR]: Instruction Not Handled: %d\n", Instruction); break;
        }
    }
}