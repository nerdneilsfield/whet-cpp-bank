#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    assert(contains_all({1,2,2,3,4}, {2,2,4}) == true);
    assert(contains_all({1,2,3}, {2,4}) == false);
    assert(contains_all({1,2,3}, {}) == true);
    assert(contains_all({}, {1}) == false);
    assert(contains_all({1,2,3,4,5}, {1,5}) == true);
    assert(contains_all({1,2,3}, {1,2,2}) == false);
    return 0;
}