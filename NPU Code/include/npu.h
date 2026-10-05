#pragma once

#include <cstdint>
#include <cstddef>
#include <iostream>
#include <vector>

using Byte = uint8_t;
using Word = uint16_t;

static constexpr size_t MATRIX_ROWS = 4;
static constexpr size_t MATRIX_COLUMNS = MATRIX_ROWS;


enum class Operation : uint8_t {
    NOP,
    LOAD,
    STORE,
    MATMUL,
    ACT,
    HALT
};

class Matrix {
    private:
        std::vector<Byte> rows;
        std::vector<Byte> columns;

    public:

};

class RAM {
    private:
        static constexpr size_t MAX_RAM_SIZE = 2 << 22;
        std::vector<Byte> data;

    public:
        RAM();
        void reset(size_t size);
        void reset();
        Byte fetchByte(uint32_t &cycles, uint32_t &programCounter);
        Byte readByte(uint32_t &cycles, uint32_t address);
        void writeByte(uint32_t &cycles, uint32_t address, Byte value);
};

class NPU {
    private:
        static constexpr size_t MAX_SRAM_SIZE = 2 << 18;
        RAM ram;
        RAM sram;
        Byte regA, regB, regC;

        uint32_t cycles;
        uint32_t programCounter = 0;
    public:
        NPU(uint32_t cycles, RAM &ram);
        void execute(Operation op);
};