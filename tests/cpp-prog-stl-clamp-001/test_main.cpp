#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    assert((clamp_all({1,5,8,12,-3}, 0, 10) == std::vector<int>{1,5,8,10,0}));
    assert((clamp_all({}, 0, 1) == std::vector<int>{}));
    assert((clamp_all({5,5,5}, 5, 5) == std::vector<int>{5,5,5}));
    assert((clamp_all({-10,-5,0,5,10}, -3, 3) == std::vector<int>{-3,-3,0,3,3}));
    assert((clamp_all({100}, 0, 50) == std::vector<int>{50}));
    assert((clamp_all({-100,200}, -1, 1) == std::vector<int>{-1,1}));
    return 0;
}