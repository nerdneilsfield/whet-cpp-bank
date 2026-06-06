#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    assert(longestCommonPrefix({"flower","flow","flight"}) == "fl");
    assert(longestCommonPrefix({"dog","racecar","car"}) == "");
    assert(longestCommonPrefix({}) == "");
    assert(longestCommonPrefix({"single"}) == "single");
    assert(longestCommonPrefix({"","abc"}) == "");
    assert(longestCommonPrefix({"abc","abc","abc"}) == "abc");
    return 0;
}
