#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    assert(first_adjacent_dup({1,2,3,3,4}) == 2);
    assert(first_adjacent_dup({1,2,3,4}) == -1);
    assert(first_adjacent_dup({}) == -1);
    assert(first_adjacent_dup({5}) == -1);
    assert(first_adjacent_dup({7,7}) == 0);
    assert(first_adjacent_dup({1,1,2,2}) == 0);
    return 0;
}