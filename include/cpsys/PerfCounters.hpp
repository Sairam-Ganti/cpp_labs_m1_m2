#pragma once

#include <cstdint>
#include <iostream>

namespace cpsys {

struct PerfCounters {
    std::uint64_t submitted = 0;
    std::uint64_t completed = 0;
    std::uint64_t failed = 0;
    std::uint64_t bytes_processed = 0;

    void print(std::ostream& os) const {
        os << "submitted: " << submitted << '\n'
           << "completed: " << completed << '\n'
           << "failed: " << failed << '\n'
           << "bytes_processed: " << bytes_processed << '\n';
    }
};

} // namespace cpsys
