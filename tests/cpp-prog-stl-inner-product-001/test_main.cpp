#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    assert(dot_product({1,2,3}, {4,5,6}) == 32);
    assert(dot_product({}, {}) == 0);
    assert(dot_product({0,0}, {1,2}) == 0);
    assert(dot_product({-1,2}, {3,-4}) == -11);
    assert(dot_product({1}, {1}) == 1);
    assert(dot_product({100000,100000}, {100000,100000}) == 20000000000LL);
    return 0;
}