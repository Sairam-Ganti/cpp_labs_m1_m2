#pragma once

#include <cstdint>

namespace cpsys {

enum class OpCode : std::uint32_t {
    Fill = 1,
    Copy = 2,
    Checksum = 3,
};

struct Descriptor {
    std::uint64_t src = 0;
    std::uint64_t dst = 0;
    std::uint32_t size = 0;
    OpCode opcode = OpCode::Fill;
};

struct Completion {
    std::uint64_t id = 0;
    bool ok = true;
    std::uint32_t bytes_processed = 0;
};

} // namespace cpsys
