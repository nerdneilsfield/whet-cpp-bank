#pragma once
#include <mutex>

class LazyInit {
    std::once_flag once_;
    int init_cnt_ = 0;
public:
    void ensure_init() {
        std::call_once(once_, [this]() {
            ++init_cnt_;
        });
    }
    bool is_initialized() const {
        return init_cnt_ > 0;
    }
    int init_count() const { return init_cnt_; }
};
