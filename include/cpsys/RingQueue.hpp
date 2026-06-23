#pragma once

#include <cstddef>
#include <optional>
#include <stdexcept>
#include <vector>

namespace cpsys {

template <typename T>
class RingQueue {
public:
    explicit RingQueue(std::size_t capacity)
        : buffer_(capacity + 1) {
        if (capacity == 0) {
            throw std::invalid_argument("capacity must be non-zero");
        }
    }

    [[nodiscard]] bool empty() const {
        return head_ == tail_;
    }

    [[nodiscard]] bool full() const {
        return next(tail_) == head_;
    }

    [[nodiscard]] std::size_t capacity() const {
        return buffer_.size() - 1;
    }

    [[nodiscard]] std::size_t size() const {
        if (tail_ >= head_) {
            return tail_ - head_;
        }
        return buffer_.size() - head_ + tail_;
    }

    bool push(const T& value) {
        if (full()) {
            return false;
        }
        buffer_[tail_] = value;
        tail_ = next(tail_);
        return true;
    }

    std::optional<T> pop() {
        if (empty()) {
            return std::nullopt;
        }
        T value = buffer_[head_];
        head_ = next(head_);
        return value;
    }

private:
    [[nodiscard]] std::size_t next(std::size_t index) const {
        return (index + 1) % buffer_.size();
    }

    std::vector<T> buffer_;
    std::size_t head_ = 0;
    std::size_t tail_ = 0;
};

} // namespace cpsys
