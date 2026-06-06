#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    assert(dedup_adjacent("aaabccdd")=="abcd");
    assert(dedup_adjacent("")=="");
    assert(dedup_adjacent("a")=="a");
    assert(dedup_adjacent("abcdef")=="abcdef");
    assert(dedup_adjacent("aabbaa")=="aba");
    return 0;
}
