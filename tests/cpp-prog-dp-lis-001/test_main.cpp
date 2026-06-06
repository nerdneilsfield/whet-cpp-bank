#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    assert(lengthOfLIS({10,9,2,5,3,7,101,18}) == 4);
    assert(lengthOfLIS({0,1,0,3,2,3}) == 4);
    assert(lengthOfLIS({7,7,7,7,7,7}) == 1);
    assert(lengthOfLIS({}) == 0);
    assert(lengthOfLIS({1}) == 1);
    assert(lengthOfLIS({1,2,3,4,5}) == 5);
    assert(lengthOfLIS({5,4,3,2,1}) == 1);
    return 0;
}
