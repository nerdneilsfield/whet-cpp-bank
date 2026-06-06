#pragma once
#include <cstdio>

inline bool g_closed = false;

class FileGuard {
public:
    explicit FileGuard(std::FILE* f) noexcept : f_(f) {}
    ~FileGuard() {
        // TODO: implement (close f_ if not null, set g_closed=true)
    }
    FileGuard(FileGuard&& other) noexcept : f_(nullptr) {
        (void)other;
        // TODO: implement
    }
    FileGuard& operator=(FileGuard&& other) noexcept {
        (void)other;
        // TODO: implement
        return *this;
    }
    FileGuard(const FileGuard&) = delete;
    FileGuard& operator=(const FileGuard&) = delete;
    std::FILE* get() const noexcept { return f_; }
private:
    std::FILE* f_;
};
