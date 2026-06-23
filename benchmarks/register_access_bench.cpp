#include "cpsys/RegisterMap.hpp"

#include <chrono>
#include <cstdint>
#include <iostream>
#include <vector>

namespace {

template <typename F>
std::uint64_t time_ns(F&& f) {
    const auto start = std::chrono::steady_clock::now();
    f();
    const auto end = std::chrono::steady_clock::now();
    return static_cast<std::uint64_t>(
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
    );
}

} // namespace

int main() {
    constexpr std::uint64_t iterations = 5'000'000;

    cpsys::RegisterMap regs;
    regs.define_register(0x00, 0);

    std::uint32_t direct_value = 0;

    const auto direct_ns = time_ns([&] {
        for (std::uint64_t i = 0; i < iterations; ++i) {
            direct_value += 1;
        }
    });

    const auto register_ns = time_ns([&] {
        for (std::uint64_t i = 0; i < iterations; ++i) {
            const auto value = regs.read32(0x00);
            regs.write32(0x00, value + 1);
        }
    });

    std::cout << "iterations: " << iterations << '\n';
    std::cout << "direct_ns: " << direct_ns << '\n';
    std::cout << "register_ns: " << register_ns << '\n';
    std::cout << "direct_value: " << direct_value << '\n';
    std::cout << "register_value: " << regs.read32(0x00) << '\n';

    return 0;
}
