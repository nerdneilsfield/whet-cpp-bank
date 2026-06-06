#include "../skeleton/solution.hpp"
#include <cassert>
#include <string>
int main(){
    assert(reverse_words("hello world foo") == "foo world hello");
    assert(reverse_words("abc") == "abc");
    assert(reverse_words("") == "");
    assert(reverse_words("a b") == "b a");
    assert(reverse_words("one two three four") == "four three two one");
    assert(reverse_words("x") == "x");
    return 0;
}