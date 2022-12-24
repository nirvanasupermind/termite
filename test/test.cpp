#include <iostream>
#include "../src/tryte.h"
#include "../src/word.h"
#include "../src/vm.h"

int main() {
    termite::VM vm;

    // Assembly:
    // int 0n004;
    // int 0n000;

    vm.mem.data[0] = termite::Tryte::from_int(31);
    vm.mem.data[1] = termite::Tryte::from_int(4);
    vm.mem.data[2] = termite::Tryte::from_int(31);
    vm.mem.data[3] = termite::Tryte::from_int(0);
    vm.run();

    return 0;
}