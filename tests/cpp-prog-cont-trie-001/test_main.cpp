#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    Trie t;
    t.insert("apple");
    assert(t.search("apple"));
    assert(!t.search("app"));
    assert(t.starts_with("app"));
    t.insert("app");
    assert(t.search("app"));
    assert(!t.search("apricot"));
    assert(!t.starts_with("z"));
    Trie t2;
    assert(!t2.search(""));
    t2.insert("a");
    assert(t2.search("a"));
    assert(t2.starts_with("a"));
    return 0;
}
