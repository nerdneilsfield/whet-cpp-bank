#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    assert(count_occurrences({1,2,2,2,3}, 2) == 3);
    assert(count_occurrences({1,2,3,4}, 5) == 0);
    assert(count_occurrences({7,7,7,7}, 7) == 4);
    assert(count_occurrences({1}, 1) == 1);
    assert(count_occurrences({1}, 0) == 0);
    assert(count_occurrences({-3,-3,-1,0,0,2}, -3) == 2);
    return 0;
}