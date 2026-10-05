
#pragma once
#include <cstdint>
#include <iostream>

using Byte = uint8_t;
using Word = uint16_t;

struct RAM {
    static constexpr uint32_t RAM_SIZE = 1024 * 64;
    Byte data[RAM_SIZE];

    void initialize();

};

static constexpr Byte INS_LDA_IM = 0xA9;
static constexpr Byte INS_LDA_ZP = 0xA5;



struct NPU {
    
    Word programCounter;
    Word stackPointer;

    //Registers
    Byte regA, regX, regY;

    // Flags
    Byte C : 1;
    Byte Z : 1;
    Byte I : 1;
    Byte D : 1;
    Byte B : 1;
    Byte V : 1;
    Byte N : 1;

    void reset(RAM &ram);

    Byte fetchByte(uint32_t &cycles, RAM &ram);
    Byte readByte(Byte address, uint32_t &cycles, RAM &ram);

    void setFlags(Byte &reg);
    void execute(uint32_t cycles, RAM &ram);

};