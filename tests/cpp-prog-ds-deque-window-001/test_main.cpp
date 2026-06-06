#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    assert(maxSlidingWindow({1,3,-1,-3,5,3,6,7}, 3) == (std::vector<int>{3,3,5,5,6,7}));
    assert(maxSlidingWindow({1}, 1) == (std::vector<int>{1}));
    assert(maxSlidingWindow({9,8,7,6,5}, 2) == (std::vector<int>{9,8,7,6}));
    assert(maxSlidingWindow({1,2,3,4,5}, 5) == (std::vector<int>{5}));
    assert(maxSlidingWindow({4,4,4,4}, 2) == (std::vector<int>{4,4,4}));
    return 0;
}
