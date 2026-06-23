#include "cpsys/SimpleDevice.hpp"

#include <algorithm>

namespace cpsys {

SimpleDevice::SimpleDevice(std::size_t queue_capacity)
    : submissions_(queue_capacity),
      completions_(queue_capacity) {
    registers_.define_register(Control, 0);
    registers_.define_register(Status, 0);
    registers_.define_register(Doorbell, 0);
}

RegisterMap& SimpleDevice::registers() {
    return registers_;
}

const RegisterMap& SimpleDevice::registers() const {
    return registers_;
}

bool SimpleDevice::submit(const Descriptor& descriptor) {
    const bool accepted = submissions_.push(descriptor);
    if (accepted) {
        counters_.submitted++;
    }
    return accepted;
}

void SimpleDevice::ring() {
    registers_.write32(Doorbell, registers_.read32(Doorbell) + 1);

    while (auto descriptor = submissions_.pop()) {
        process_one(*descriptor);
    }
}

std::vector<Completion> SimpleDevice::drain_completions() {
    std::vector<Completion> result;
    while (auto completion = completions_.pop()) {
        result.push_back(*completion);
    }
    return result;
}

const PerfCounters& SimpleDevice::counters() const {
    return counters_;
}

void SimpleDevice::process_one(const Descriptor& descriptor) {
    Completion completion;
    completion.id = next_completion_id_++;
    completion.ok = true;
    completion.bytes_processed = descriptor.size;

    switch (descriptor.opcode) {
        case OpCode::Fill:
        case OpCode::Copy:
        case OpCode::Checksum:
            counters_.bytes_processed += descriptor.size;
            break;
        default:
            completion.ok = false;
            counters_.failed++;
            break;
    }

    if (completion.ok) {
        counters_.completed++;
    }

    const bool completion_accepted = completions_.push(completion);
    if (!completion_accepted) {
        counters_.failed++;
    }
}

} // namespace cpsys
