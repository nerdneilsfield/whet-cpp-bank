#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    {
        auto r = top_k_smallest({7,2,5,1,3,9,4}, 3);
        assert((r == std::vector<int>{1,2,3}));
    }
    {
        auto r = top_k_smallest({5}, 1);
        assert((r == std::vector<int>{5}));
    }
    {
        auto r = top_k_smallest({3,3,3,3}, 2);
        assert((r == std::vector<int>{3,3}));
    }
    {
        auto r = top_k_smallest({-1,-5,2,0,-3}, 3);
        assert((r == std::vector<int>{-5,-3,-1}));
    }
    {
        auto r = top_k_smallest({1,2,3,4,5}, 5);
        assert((r == std::vector<int>{1,2,3,4,5}));
    }
    return 0;
}
