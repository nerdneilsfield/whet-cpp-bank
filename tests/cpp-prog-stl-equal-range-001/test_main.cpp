#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    assert((find_all_equal({1,2,2,2,3}, 2) == std::vector<int>{2,2,2}));
    assert((find_all_equal({1,2,3}, 5) == std::vector<int>{}));
    assert((find_all_equal({}, 1) == std::vector<int>{}));
    assert((find_all_equal({5,5,5,5}, 5) == std::vector<int>{5,5,5,5}));
    assert((find_all_equal({1,2,3,4}, 3) == std::vector<int>{3}));
    assert((find_all_equal({-2,-2,-1,0,1}, -2) == std::vector<int>{-2,-2}));
    return 0;
}