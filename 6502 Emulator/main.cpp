#include <iostream>
#include <npu.h>

int main(){
    NPU npu;
    RAM ram;
    npu.reset(ram);
    // start program 
    ram.data[0xFFFC] = INS_LDA_ZP;
    ram.data[0xFFFD] = 0x42;
    ram.data[0x0042] = 0x84;
    // end program
    npu.execute(3, ram);

}
