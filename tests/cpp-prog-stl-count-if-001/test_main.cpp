#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    assert(count_even({1,2,3,4,5,6}) == 3);
    assert(count_even({1,3,5}) == 0);
    assert(count_even({}) == 0);
    assert(count_even({0}) == 1);
    assert(count_even({-2,-1,0,1,2}) == 3);
    assert(count_even({2,4,6,8}) == 4);
    return 0;
}