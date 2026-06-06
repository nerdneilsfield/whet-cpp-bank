#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    assert((filter_positive({-2,3,0,5,-1,8}) == std::vector<int>{3,5,8}));
    assert((filter_positive({}) == std::vector<int>{}));
    assert((filter_positive({-1,-2,-3}) == std::vector<int>{}));
    assert((filter_positive({1,2,3}) == std::vector<int>{1,2,3}));
    assert((filter_positive({0,0}) == std::vector<int>{}));
    assert((filter_positive({-1,0,1}) == std::vector<int>{1}));
    return 0;
}