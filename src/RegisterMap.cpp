#include "cpsys/RegisterMap.hpp"

namespace cpsys {

void RegisterMap::define_register(Offset offset, Value reset_value) {
    values_[offset] = reset_value;
    reset_values_[offset] = reset_value;
}

bool RegisterMap::contains(Offset offset) const {
    return values_.find(offset) != values_.end();
}

RegisterMap::Value RegisterMap::read32(Offset offset) const {
    const auto it = values_.find(offset);
    if (it == values_.end()) {
        throw std::out_of_range("read from undefined register offset");
    }
    return it->second;
}

void RegisterMap::write32(Offset offset, Value value) {
    const auto it = values_.find(offset);
    if (it == values_.end()) {
        throw std::out_of_range("write to undefined register offset");
    }
    it->second = value;
}

void RegisterMap::reset() {
    values_ = reset_values_;
}

} // namespace cpsys
