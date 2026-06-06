#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    assert((prefix_sum({1,2,3,4}) == std::vector<long long>{1,3,6,10}));
    assert((prefix_sum({}) == std::vector<long long>{}));
    assert((prefix_sum({5}) == std::vector<long long>{5}));
    assert((prefix_sum({0,0,0}) == std::vector<long long>{0,0,0}));
    assert((prefix_sum({-1,2,-3}) == std::vector<long long>{-1,1,-2}));
    assert((prefix_sum({1000000000,1000000000,1000000000}) == std::vector<long long>{1000000000LL,2000000000LL,3000000000LL}));
    return 0;
}