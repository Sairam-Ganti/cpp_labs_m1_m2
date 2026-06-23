#include "cpsys/SimpleDevice.hpp"

#include <iostream>

int main() {
    cpsys::SimpleDevice device{16};

    cpsys::Descriptor descriptor;
    descriptor.src = 0x1000;
    descriptor.dst = 0x2000;
    descriptor.size = 4096;
    descriptor.opcode = cpsys::OpCode::Copy;

    if (!device.submit(descriptor)) {
        std::cerr << "submission queue is full\n";
        return 1;
    }

    device.ring();

    const auto completions = device.drain_completions();
    std::cout << "completions: " << completions.size() << "\n";

    device.counters().print(std::cout);
    return 0;
}
