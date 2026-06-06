#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    LRUCache c(2);
    c.put(1,1);
    c.put(2,2);
    assert(c.get(1)==1);
    c.put(3,3); // evict 2
    assert(c.get(2)==-1);
    c.put(4,4); // evict 1
    assert(c.get(1)==-1);
    assert(c.get(3)==3);
    assert(c.get(4)==4);
    LRUCache c2(1);
    c2.put(1,10);
    c2.put(1,20);
    assert(c2.get(1)==20);
    return 0;
}
