#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    assert((set_intersect({1,2,3}, {2,3,4}) == std::vector<int>{2,3}));
    assert((set_intersect({1,1,2,3}, {1,1,1,2}) == std::vector<int>{1,1,2}));
    assert((set_intersect({}, {1,2}) == std::vector<int>{}));
    assert((set_intersect({1,2}, {}) == std::vector<int>{}));
    assert((set_intersect({1,2,3}, {4,5,6}) == std::vector<int>{}));
    assert((set_intersect({5,5,5}, {5,5}) == std::vector<int>{5,5}));
    return 0;
}