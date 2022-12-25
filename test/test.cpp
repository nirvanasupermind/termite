#include <iostream>
#include <chrono>
#include <ctime>
#include "../src/tryte.h"
#include "../src/word.h"
#include "../src/vm.h"

int main() {
    termite::VM vm;
    auto start = std::chrono::system_clock::now();

    // assembly:
    // main:
    //  nop;
    //  ldi r0, 5;
    //  addi r0, 3;
    //  ldi r1, 13;
    //  mul r0, r1;
    //  syscall 0n004;

    int addr = 511758;
    vm.mem.data[++addr] = termite::Tryte::from_int(2);
    vm.mem.data[++addr] = termite::Tryte::from_int(5);
    vm.mem.data[++addr] = termite::Tryte::from_int(7);
    vm.mem.data[++addr] = termite::Tryte::from_int(3);
    vm.mem.data[++addr] = termite::Tryte::from_int(2);
    vm.mem.data[++addr] = termite::Tryte::from_int(81 + 13);
    vm.mem.data[++addr] = termite::Tryte::from_int(10);
    vm.mem.data[++addr] = termite::Tryte::from_int(9);
    vm.mem.data[++addr] = termite::Tryte::from_int(31);
    vm.mem.data[++addr] = termite::Tryte::from_int(4);
    vm.mem.data[++addr] = termite::Tryte::from_int(31);
    vm.mem.data[++addr] = termite::Tryte::from_int(0);
    vm.run();
    
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "[finished in " << elapsed_seconds.count() << "s]\n";
    return 0;
}