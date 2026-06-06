#include "../skeleton/solution.hpp"
#include <cassert>
#include <string>
int main(){
    assert(first_mismatch("hello", "help") == 3);
    assert(first_mismatch("abc", "abc") == 3);
    assert(first_mismatch("abc", "ab") == 2);
    assert(first_mismatch("", "") == 0);
    assert(first_mismatch("a", "b") == 0);
    assert(first_mismatch("", "x") == 0);
    return 0;
}