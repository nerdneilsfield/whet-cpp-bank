#include "../skeleton/solution.hpp"
#include <cassert>
#include <string>
int main(){
    assert(replaceAll("hello world", "world", "C++") == "hello C++");
    assert(replaceAll("aaaa", "a", "bb") == "bbbbbbbb");
    assert(replaceAll("abcabc", "bc", "X") == "aXaX");
    assert(replaceAll("xyz", "abc", "Q") == "xyz");
    assert(replaceAll("", "a", "b") == "");
    assert(replaceAll("hello", "", "X") == "hello");
    assert(replaceAll("aaa", "aa", "b") == "ba");
    return 0;
}
