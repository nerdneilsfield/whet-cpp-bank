#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    assert(firstUniqChar("leetcode") == 0);
    assert(firstUniqChar("loveleetcode") == 2);
    assert(firstUniqChar("aabb") == -1);
    assert(firstUniqChar("") == -1);
    assert(firstUniqChar("z") == 0);
    assert(firstUniqChar("aabbc") == 4);
    return 0;
}
