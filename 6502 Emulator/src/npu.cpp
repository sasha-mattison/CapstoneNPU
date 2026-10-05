#include <npu.h>

void RAM::initialize() {
    for (uint32_t i = 0; i < RAM_SIZE; i++) {
        data[i] = 0;
    }
}

void NPU::reset(RAM &ram) {
    programCounter = 0xFFFC;
    stackPointer = 0x0100;
    C = Z = I = D = B = V = N = 0;
    regA = regX = regY = 0;
    ram.initialize();
}

void NPU::setFlags(Byte &reg) {
    Z = (reg == 0);
    N = (regA & 0b10000000 > 0); // some negative bs
}

void NPU::execute(uint32_t cycles, RAM &ram) {
    while (cycles > 0) {
        Byte instruction = fetchByte(cycles, ram);

        switch (instruction) {
            case INS_LDA_IM: {
                regA = fetchByte(cycles, ram);
                setFlags(regA);
                std::cout << int(regA) << std::endl;
                break;
            }
            case INS_LDA_ZP: {
                Byte zeroPageAddress = fetchByte(cycles, ram);
                regA = readByte(zeroPageAddress, cycles, ram);
                setFlags(regA);
                break;
            }
            case INS_LDA_ZPX: {
                Byte zeroPageAddress = fetchByte(cycles, ram);
                zeroPageAddress += regX;
                cycles--;
                regA = readByte(zeroPageAddress, cycles, ram);
                setFlags(regA);
            }   
            default: {
                std::cout << "Instruction not valid\n";
                break;
            }
        }
    }
}

Byte NPU::fetchByte(uint32_t &cycles, RAM &ram) {
    Byte data = ram.data[programCounter];
    programCounter++;
    cycles--;
    return data;
}

Byte NPU::readByte(Byte address, uint32_t &cycles, RAM &ram) {
    Byte data = ram.data[address];
    cycles--;
    return data;
}
