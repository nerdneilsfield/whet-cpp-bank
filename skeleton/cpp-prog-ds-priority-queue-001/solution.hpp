#pragma once
#include <vector>
#include <queue>
#include <functional>

class KthLargest {
public:
    KthLargest(int k, const std::vector<int>& nums) : k_(k) {
        // TODO: implement
        (void)nums;
    }
    int add(int val) {
        // TODO: implement
        (void)val;
        return 0;
    }
private:
    int k_;
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq_;
};
