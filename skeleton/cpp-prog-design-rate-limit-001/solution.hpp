#pragma once
#include <chrono>
#include <algorithm>

class TokenBucket {
    int rate_, burst_, tokens_;
    std::chrono::steady_clock::time_point last_refill_;
public:
    TokenBucket(int rate, int burst)
        : rate_(rate), burst_(burst), tokens_(burst),
          last_refill_(std::chrono::steady_clock::now()) {}
    bool allow() {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            now - last_refill_).count();
        if (elapsed > 0) {
            int add = static_cast<int>(elapsed * rate_ / 1000);
            tokens_ = std::min(burst_, tokens_ + add);
            last_refill_ = now;
        }
        if (tokens_ > 0) {
            --tokens_;
            return true;
        }
        return false;
    }
};
