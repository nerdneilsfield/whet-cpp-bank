#pragma once
#include <vector>
#include <future>
#include <numeric>

long long parallel_sum(const std::vector<int>& v, std::size_t lo, std::size_t hi) {
    if (hi - lo < 1000) {
        return std::accumulate(v.begin() + lo, v.begin() + hi, 0LL);
    }
    std::size_t mid = lo + (hi - lo) / 2;
    auto fut = std::async(std::launch::async, parallel_sum, std::cref(v), lo, mid);
    long long right = parallel_sum(v, mid, hi);
    return fut.get() + right;
}
