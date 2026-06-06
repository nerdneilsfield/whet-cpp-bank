#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    assert(countDistinct({}) == 0);
    assert(countDistinct({1,2,3}) == 3);
    assert(countDistinct({1,1,1,1}) == 1);
    assert(countDistinct({1,2,2,3,3,3,4}) == 4);
    assert(countDistinct({-1,0,1,-1,0}) == 3);
    return 0;
}
