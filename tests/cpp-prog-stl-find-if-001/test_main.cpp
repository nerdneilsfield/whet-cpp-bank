#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    assert(first_negative_index({3,5,-1,7,-2}) == 2);
    assert(first_negative_index({1,2,3}) == -1);
    assert(first_negative_index({}) == -1);
    assert(first_negative_index({-5}) == 0);
    assert(first_negative_index({0,0,-1}) == 2);
    assert(first_negative_index({-1,-2,-3}) == 0);
    return 0;
}