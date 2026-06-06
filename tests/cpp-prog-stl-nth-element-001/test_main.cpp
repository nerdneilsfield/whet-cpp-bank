#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    assert(find_median({3,1,2,4,5}) == 3);
    assert(find_median({1,2}) == 2);
    assert(find_median({7}) == 7);
    assert(find_median({5,5,5,5}) == 5);
    assert(find_median({-3,-1,-2,-4,-5}) == -3);
    assert(find_median({10,20,30,40,50,60,70}) == 40);
    return 0;
}
