#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    assert((merge_sorted({1,3,5}, {2,4,6}) == std::vector<int>{1,2,3,4,5,6}));
    assert((merge_sorted({1,1,2}, {1,3}) == std::vector<int>{1,1,1,2,3}));
    assert((merge_sorted({}, {1,2,3}) == std::vector<int>{1,2,3}));
    assert((merge_sorted({1,2,3}, {}) == std::vector<int>{1,2,3}));
    assert((merge_sorted({}, {}) == std::vector<int>{}));
    assert((merge_sorted({-3,-1}, {-2,0}) == std::vector<int>{-3,-2,-1,0}));
    return 0;
}