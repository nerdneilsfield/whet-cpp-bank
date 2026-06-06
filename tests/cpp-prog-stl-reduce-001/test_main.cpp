#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    assert(sum_with_reduce({1,2,3,4}) == 10);
    assert(sum_with_reduce({}) == 0);
    assert(sum_with_reduce({-5}) == -5);
    assert(sum_with_reduce({1000000000,1000000000}) == 2000000000LL);
    assert(sum_with_reduce({-1,-2,-3}) == -6);
    assert(sum_with_reduce({0,0,0}) == 0);
    return 0;
}