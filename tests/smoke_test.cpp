#include "cpsys/RegisterMap.hpp"
#include "cpsys/RingQueue.hpp"
#include "cpsys/SimpleDevice.hpp"

#include <cassert>
#include <iostream>

int main() {
    {
        cpsys::RegisterMap regs;
        regs.define_register(0x00, 7);
        assert(regs.read32(0x00) == 7);
        regs.write32(0x00, 42);
        assert(regs.read32(0x00) == 42);
        regs.reset();
        assert(regs.read32(0x00) == 7);
    }

    {
        cpsys::RingQueue<int> queue{2};
        assert(queue.empty());
        assert(queue.push(1));
        assert(queue.push(2));
        assert(queue.full());
        assert(!queue.push(3));
        assert(queue.pop().value() == 1);
        assert(queue.pop().value() == 2);
        assert(queue.empty());
    }

    {
        cpsys::SimpleDevice device{4};
        cpsys::Descriptor d;
        d.size = 128;
        d.opcode = cpsys::OpCode::Fill;

        assert(device.submit(d));
        device.ring();

        const auto completions = device.drain_completions();
        assert(completions.size() == 1);
        assert(completions[0].ok);
        assert(completions[0].bytes_processed == 128);
        assert(device.counters().submitted == 1);
        assert(device.counters().completed == 1);
    }

    std::cout << "smoke_test passed\n";
    return 0;
}
