#pragma once

#include <cstdint>
#include <stdexcept>
#include <unordered_map>

namespace cpsys {

class RegisterMap {
public:
    using Offset = std::uint64_t;
    using Value = std::uint32_t;

    RegisterMap() = default;

    void define_register(Offset offset, Value reset_value = 0);
    [[nodiscard]] bool contains(Offset offset) const;

    [[nodiscard]] Value read32(Offset offset) const;
    void write32(Offset offset, Value value);

    void reset();

private:
    std::unordered_map<Offset, Value> values_;
    std::unordered_map<Offset, Value> reset_values_;
};

} // namespace cpsys
