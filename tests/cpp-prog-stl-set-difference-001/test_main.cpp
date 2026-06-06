#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    assert((set_diff({1,2,3,4}, {2,4}) == std::vector<int>{1,3}));
    assert((set_diff({1,1,1,2}, {1,2}) == std::vector<int>{1,1}));
    assert((set_diff({}, {1,2}) == std::vector<int>{}));
    assert((set_diff({1,2,3}, {}) == std::vector<int>{1,2,3}));
    assert((set_diff({1,2,3}, {1,2,3}) == std::vector<int>{}));
    assert((set_diff({-2,-1,0,1}, {-1,1}) == std::vector<int>{-2,0}));
    return 0;
}