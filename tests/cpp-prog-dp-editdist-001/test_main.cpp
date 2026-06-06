#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    assert(minDistance("horse", "ros") == 3);
    assert(minDistance("intention", "execution") == 5);
    assert(minDistance("", "") == 0);
    assert(minDistance("abc", "") == 3);
    assert(minDistance("", "xyz") == 3);
    assert(minDistance("same", "same") == 0);
    assert(minDistance("kitten", "sitting") == 3);
    return 0;
}
