#pragma once

#include "cpsys/Descriptor.hpp"
#include "cpsys/PerfCounters.hpp"
#include "cpsys/RegisterMap.hpp"
#include "cpsys/RingQueue.hpp"

#include <cstdint>
#include <vector>

namespace cpsys {

class SimpleDevice {
public:
    static constexpr RegisterMap::Offset Control = 0x00;
    static constexpr RegisterMap::Offset Status = 0x04;
    static constexpr RegisterMap::Offset Doorbell = 0x08;

    explicit SimpleDevice(std::size_t queue_capacity);

    [[nodiscard]] RegisterMap& registers();
    [[nodiscard]] const RegisterMap& registers() const;

    bool submit(const Descriptor& descriptor);
    void ring();
    [[nodiscard]] std::vector<Completion> drain_completions();

    [[nodiscard]] const PerfCounters& counters() const;

private:
    void process_one(const Descriptor& descriptor);

    RegisterMap registers_;
    RingQueue<Descriptor> submissions_;
    RingQueue<Completion> completions_;
    PerfCounters counters_;
    std::uint64_t next_completion_id_ = 1;
};

} // namespace cpsys
