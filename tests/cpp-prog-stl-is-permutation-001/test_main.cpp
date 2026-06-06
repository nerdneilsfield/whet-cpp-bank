#include "../skeleton/solution.hpp"
#include <cassert>
#include <string>
int main(){
    assert(is_anagram("listen", "silent") == true);
    assert(is_anagram("abc", "abd") == false);
    assert(is_anagram("", "") == true);
    assert(is_anagram("a", "a") == true);
    assert(is_anagram("aabb", "abab") == true);
    assert(is_anagram("abc", "ab") == false);
    return 0;
}