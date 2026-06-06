#include "../skeleton/solution.hpp"
#include <cassert>
#include <thread>
#include <vector>
#include <set>
int main() {
    {
        BoundedBuffer buf(5);
        assert(buf.size() == 0);
        buf.push(10);
        assert(buf.size() == 1);
        assert(buf.pop() == 10);
        assert(buf.size() == 0);
    }
    {
        BoundedBuffer buf(3);
        buf.push(1); buf.push(2); buf.push(3);
        assert(buf.size() == 3);
        assert(buf.pop() == 1);
        assert(buf.pop() == 2);
        buf.push(4);
        assert(buf.pop() == 3);
        assert(buf.pop() == 4);
    }
    {
        BoundedBuffer buf(10);
        std::vector<int> produced, consumed;
        std::thread prod([&]() {
            for (int i = 0; i < 100; ++i) {
                buf.push(i);
                produced.push_back(i);
            }
        });
        std::thread cons([&]() {
            for (int i = 0; i < 100; ++i) {
                consumed.push_back(buf.pop());
            }
        });
        prod.join(); cons.join();
        assert(produced.size() == 100);
        assert(consumed.size() == 100);
        assert(consumed == produced);
    }
    return 0;
}
