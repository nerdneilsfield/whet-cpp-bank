#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    assert(lengthOfLongestSubstring("abcabcbb") == 3);
    assert(lengthOfLongestSubstring("bbbbb") == 1);
    assert(lengthOfLongestSubstring("pwwkew") == 3);
    assert(lengthOfLongestSubstring("") == 0);
    assert(lengthOfLongestSubstring("dvdf") == 3);
    assert(lengthOfLongestSubstring("abcdef") == 6);
    return 0;
}
