#include "npu.h"

RAM::RAM() {
    reset();
}

void RAM::reset(size_t size) {
    for (int i = 0; i < size; i++) {
        data.push_back(0);
    }
}

void RAM::reset() {
    for (int i = 0; i < MAX_RAM_SIZE; i++) {
        data.push_back(0);
    }
}

Byte RAM::fetchByte(uint32_t &cycles, uint32_t &programCounter) {
    Byte value = data.at(programCounter);
    cycles--;
    programCounter++;
    return value;
}

Byte RAM::readByte(uint32_t &cycles, uint32_t address) {
    if (address > MAX_RAM_SIZE) {
        std::cerr << "Invalid memory address\n";
        return 0;
    }
    cycles--;
    return data.at(address);
}

void RAM::writeByte(uint32_t &cycles, uint32_t address, Byte value) {
    data.at(address) = value;
    cycles--;
}

NPU::NPU(uint32_t cycles, RAM &ram) : cycles(cycles), ram(ram) {
    sram.reset(MAX_SRAM_SIZE);
    
}

void NPU::execute(Operation op) {
    if (cycles == 0) return;
    switch(op) {
        case Operation::NOP: {
            cycles--;
            break;
        }
        case Operation::LOAD: {
            uint64_t matrixElementCount = MATRIX_ROWS * MATRIX_COLUMNS;
            if (matrixElementCount < MAX_SRAM_SIZE) {
                for (int i = 0; i < matrixElementCount; i++) {
                    sram.writeByte(cycles, i, ram.readByte(cycles, i));
                }
                break;
            }
            else {
                regA = ram.fetchByte(cycles, programCounter);
                break;
            }
        }
        case Operation::STORE: {
            ram.writeByte(cycles, 0, 0);
            break;
        }
        case Operation::MATMUL: {
            break;
        }
        case Operation::ACT: {
            break;
        }
        case Operation::HALT: {
            std::exit(EXIT_SUCCESS);
        }
    }
}