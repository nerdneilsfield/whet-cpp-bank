#include "../skeleton/solution.hpp"
#include <cassert>
int main() {
    {
        LFUCache c(2);
        c.put(1, 10);
        c.put(2, 20);
        assert(c.get(1) == 10);
        c.put(3, 30);
        assert(c.get(2) == -1);
        assert(c.get(3) == 30);
    }
    {
        LFUCache c(3);
        c.put(1, 1); c.put(2, 2); c.put(3, 3);
        c.get(1); c.get(1);
        c.get(2);
        c.put(4, 4);
        assert(c.get(3) == -1);
        assert(c.get(1) == 1);
        assert(c.get(4) == 4);
    }
    {
        LFUCache c(1);
        c.put(1, 10);
        assert(c.get(1) == 10);
        c.put(2, 20);
        assert(c.get(1) == -1);
        assert(c.get(2) == 20);
    }
    {
        LFUCache c(2);
        c.put(1, 1); c.put(2, 2);
        assert(c.get(1) == 1);
        c.put(3, 3);
        assert(c.get(2) == -1);
        assert(c.get(3) == 3);
    }
    return 0;
}
