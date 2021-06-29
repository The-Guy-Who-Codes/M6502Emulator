

static inline void memInit(struct Mem* mem) { // initialises memory by resetting all memory values to 0
    for (int i = 0; i < MaxMem; i++) {
        mem->Data[i] = 0;
    }
}

static inline void reset(struct CPU* cpu, struct Mem* mem) { // resets the state of the CPU as it were to be booted
    cpu->PC = 0xFFFC; // the reset vector in memory for the 6502 [https://www.c64-wiki.com/wiki/Reset_(Process)] 
    cpu->SP = 0x0100;
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

static inline Byte readByte(uint32_t* cycles, struct Mem* mem, struct CPU* cpu, Word Address){
    Byte Data = mem->Data[Address]; // fetches byte which PC is pointing to
    (*cycles)--; // decriments cycle counter as fetching takes 1 cycle
    return Data;
}

static inline Word fetchWord(uint32_t* cycles, struct Mem* mem, struct CPU* cpu) {
    Word Data = mem->Data[cpu->PC];
    cpu->PC++;
    (*cycles)--;
    Data += mem->Data[cpu->PC] << 8; // this is due to the 6502 being little endian (i.e. LSB being stored first)
    cpu->PC++;
    (*cycles)--;
    return Data;
}

static inline Word readWord(uint32_t* cycles, struct Mem* mem, struct CPU* cpu, Word Address) {
    Word Data = mem->Data[Address + 1] << 8;
    (*cycles)--;
    Data += mem->Data[Address];
    (*cycles)--;
    return Data;
}

static inline void pageCrossedAddCycle(uint32_t* cycles, Word AddressOriginal, Word Address2) {
    if ((AddressOriginal >> 8) != (Address2 >> 8)) {
        (*cycles)++;
    }
}

static inline void setLoadFlags(CPU* cpu, Byte* regValue) {
    cpu->Z = (*regValue) == 0 ? 1 : 0; // set if A == 0 
    cpu->N = (((*regValue) & (1 << 7)) >> 7); // set if Bit 7 of A is set
}

static inline Byte ZPX(uint32_t* cycles, Mem* mem, CPU* cpu) {
    Byte ZPAddress = fetchByte(cycles, mem, cpu);
    ZPAddress += cpu->X;
    (*cycles)--;
    return ZPAddress;
}

static inline Byte ZPY(uint32_t* cycles, Mem* mem, CPU* cpu) {
    Byte ZPAddress = fetchByte(cycles, mem, cpu);
    ZPAddress += cpu->Y;
    (*cycles)--;
    return ZPAddress;
}

static inline Word ABSX(uint32_t* cycles, Mem* mem, CPU* cpu) {
    Word Address = fetchWord(cycles, mem, cpu);
    Word AbsAddress = Address + cpu->X;
    // refer to [http://archive.6502.org/datasheets/synertek_hardware_manual.pdf] (pg. 168) as to why there is not cycle decrease after addition
    /*pageCrossedAddCycle(cycles, Address, AbsAddress);
    if ((Address >> 8) != (AbsAddress >> 8)) {
        (*cycles)--; // to offset for the fact the 6502 adder is only 8-bit
    }*/
    return AbsAddress;
}

static inline Word ABSY(uint32_t* cycles, Mem* mem, CPU* cpu) {
    Word Address = fetchWord(cycles, mem, cpu);
    Word AbsAddress = Address + cpu->Y;
    // refer to [http://archive.6502.org/datasheets/synertek_hardware_manual.pdf] (pg. 168) as to why there is not cycle decrease after addition
    /*pageCrossedAddCycle(cycles, Address, AbsAddress);
    if ((Address >> 8) != (AbsAddress >> 8)) {
        (*cycles)--; // to offset for the fact the 6502 proessor is only 8-bit
    }*/
    return AbsAddress;
}

static inline Word INDX(uint32_t* cycles, Mem* mem, CPU* cpu) {
    Byte baseAddress = fetchByte(cycles, mem, cpu);
    baseAddress += cpu->X;
    Word Address = readWord(cycles, mem, cpu, baseAddress);
    return Address;
}

static inline Word INDY(uint32_t* cycles, Mem* mem, CPU* cpu) {
    Byte baseAddress = fetchByte(cycles, mem, cpu);
    Word Address = readWord(cycles, mem, cpu, baseAddress);
    Address += cpu->Y;
    return Address;
}


void execute(uint32_t* cycles, struct CPU* cpu, struct Mem* mem) {
    while (*cycles > 0) {
        Byte Instruction = fetchByte(cycles, mem, cpu);
        switch (Instruction) {

            // data from [http://www.obelisk.me.uk/6502/instructions.html]

        /* Loading */

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

        case INS_LDA_ZPX: {
            Byte ZPAddress = ZPX(cycles, mem, cpu);
            cpu->A = readByte(cycles, mem, cpu, ZPAddress);
            setLoadFlags(cpu, &cpu->A);
        } break;

        case INS_LDY_ZPX: {
            Byte ZPAddress = ZPX(cycles, mem, cpu);
            cpu->Y = readByte(cycles, mem, cpu, ZPAddress);
            setLoadFlags(cpu, &cpu->Y);
        } break;

        case INS_LDX_ZPY: {
            Byte ZPAddress = ZPX(cycles, mem, cpu);
            cpu->X = readByte(cycles, mem, cpu, ZPAddress);
            setLoadFlags(cpu, &cpu->X);
        } break;

        case INS_LDA_ABS: {
            Word Address = fetchWord(cycles, mem, cpu);
            cpu->A = readByte(cycles, mem, cpu, Address);
            setLoadFlags(cpu, &cpu->A);
        } break;

        case INS_LDX_ABS: {
            Word Address = fetchWord(cycles, mem, cpu);
            cpu->X = readByte(cycles, mem, cpu, Address);
            setLoadFlags(cpu, &cpu->X);
        } break;

        case INS_LDY_ABS: {
            Word Address = fetchWord(cycles, mem, cpu);
            cpu->Y = readByte(cycles, mem, cpu, Address);
            setLoadFlags(cpu, &cpu->Y);
        } break;

        case INS_LDA_ABSX: {
            Word AbsAddress = ABSX(cycles, mem, cpu);
            cpu->A = readByte(cycles, mem, cpu, AbsAddress);
            setLoadFlags(cpu, &cpu->A);
        } break;

        case INS_LDY_ABSX: {
            Word AbsAddress = ABSX(cycles, mem, cpu);
            cpu->Y = readByte(cycles, mem, cpu, AbsAddress);
            setLoadFlags(cpu, &cpu->Y);
        } break;

        case INS_LDA_ABSY: {
            Word AbsAddress = ABSY(cycles, mem, cpu);
            cpu->A = readByte(cycles, mem, cpu, AbsAddress);
            setLoadFlags(cpu, &cpu->A);
        } break;

        case INS_LDX_ABSY: {
            Word AbsAddress = ABSY(cycles, mem, cpu);
            cpu->X = readByte(cycles, mem, cpu, AbsAddress);
            setLoadFlags(cpu, &cpu->X);
        } break;

        case INS_LDA_INDX: {
            Word Address = INDX(cycles, mem, cpu);
            cpu->A = readWord(cycles, mem, cpu, Address);
            setLoadFlags(cpu, &cpu->A);
        } break;

        case INS_LDA_INDY: {
            Word Address = INDY(cycles, mem, cpu);
            cpu->A = readByte(cycles, mem, cpu, Address);
            setLoadFlags(cpu, &cpu->A);
        } break;

            /* Storing */

        case INS_STA_ZP: {
            Byte Address = fetchByte(cycles, mem, cpu);
            mem->Data[Address] = cpu->A;
            (*cycles)--;
        } break;

        case INS_STX_ZP: {
            Byte Address = fetchByte(cycles, mem, cpu);
            mem->Data[Address] = cpu->X;
            (*cycles)--;
        } break;

        case INS_STY_ZP: {
            Byte Address = fetchByte(cycles, mem, cpu);
            mem->Data[Address] = cpu->Y;
            (*cycles)--;
        } break;

        case INS_STA_ABS: {
            Word Address = fetchWord(cycles, mem, cpu);
            mem->Data[Address] = cpu->A;
            (*cycles)--;
        } break;

        case INS_STX_ABS: {
            Word Address = fetchWord(cycles, mem, cpu);
            mem->Data[Address] = cpu->X;
            (*cycles)--;
        } break;

        case INS_STY_ABS: {
            Word Address = fetchWord(cycles, mem, cpu);
            mem->Data[Address] = cpu->Y;
            (*cycles)--;
        } break;

        case INS_STA_ZPX: {
            Byte Address = ZPX(cycles, mem, cpu);
            mem->Data[Address] = cpu->A;
            (*cycles)--;
        } break;

        case INS_STY_ZPX: {
            Byte Address = ZPX(cycles, mem, cpu);
            mem->Data[Address] = cpu->Y;
            (*cycles)--;
        } break;

        case INS_STX_ZPY: {
            Byte Address = ZPY(cycles, mem, cpu);
            mem->Data[Address] = cpu->X;
            (*cycles)--;
        } break;

        case INS_STA_ABSX: {
            Word Address = ABSX(cycles, mem, cpu);
            (*cycles)--;
            mem->Data[Address] = cpu->A;
            (*cycles)--;
        } break;

        case INS_STA_ABSY: {
            Word Address = ABSY(cycles, mem, cpu);
            (*cycles)--;
            mem->Data[Address] = cpu->A;
            (*cycles)--;
        } break;

        case INS_STA_INDX: {
            Word Address = INDX(cycles, mem, cpu);
            (*cycles)--;
            mem->Data[Address] = cpu->A;
            (*cycles)--;
        } break;

        case INS_STA_INDY: {
            Word Address = INDY(cycles, mem, cpu);
            (*cycles)--;
            mem->Data[Address] = cpu->A;
            (*cycles)--;
        } break;

        case INS_TAX_IMP: {
            cpu->X = cpu->A;
            (*cycles)--;
            setLoadFlags(cpu, &cpu->X);
            (*cycles)--;
        } break;

        case INS_TAY_IMP: {
            cpu->Y = cpu->A;
            (*cycles)--;
            setLoadFlags(cpu, &cpu->Y);
            (*cycles)--;
        } break;

        case INS_TXA_IMP: {
            cpu->A = cpu->X;
            (*cycles)--;
            setLoadFlags(cpu, &cpu->A);
            (*cycles)--;
        } break;

        case INS_TYA_IMP: {
            cpu->A = cpu->Y;
            (*cycles)--;
            setLoadFlags(cpu, &cpu->A);
            (*cycles)--;
        } break;

        default: {
            printf("[ERROR]: Instruction Not Handled: %d\n\n", Instruction);
            *cycles = 0;
        } break;
        }
    }
}