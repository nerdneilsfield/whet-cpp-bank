#pragma once
#include <vector>
#include <functional>

class SortContext {
public:
    void sort(std::vector<int>& v, std::function<bool(int,int)> cmp) {
        for (std::size_t i = 0; i + 1 < v.size(); ++i)
            for (std::size_t j = 0; j + 1 < v.size() - i; ++j)
                if (!cmp(v[j], v[j+1]))
                    std::swap(v[j], v[j+1]);
    }
};
