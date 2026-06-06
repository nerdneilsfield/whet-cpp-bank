#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    assert(find_subsequence({1,2,3,4,5}, {3,4}) == 2);
    assert(find_subsequence({1,2,3}, {4}) == -1);
    assert(find_subsequence({1,2,3}, {}) == 0);
    assert(find_subsequence({}, {1}) == -1);
    assert(find_subsequence({1,2,1,2,3}, {1,2,3}) == 2);
    assert(find_subsequence({5}, {5}) == 0);
    return 0;
}