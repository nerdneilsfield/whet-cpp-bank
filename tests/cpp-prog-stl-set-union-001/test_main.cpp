#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    assert((set_union({1,2,3}, {2,3,4}) == std::vector<int>{1,2,3,4}));
    assert((set_union({1,1,2}, {1,3}) == std::vector<int>{1,1,2,3}));
    assert((set_union({}, {1,2}) == std::vector<int>{1,2}));
    assert((set_union({1,2}, {}) == std::vector<int>{1,2}));
    assert((set_union({}, {}) == std::vector<int>{}));
    assert((set_union({1,1,1}, {1,1}) == std::vector<int>{1,1,1}));
    return 0;
}