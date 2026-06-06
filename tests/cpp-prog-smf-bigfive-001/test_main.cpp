#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    {
        IntArray a(5, 7);
        assert(a.size() == 5);
        for (std::size_t i = 0; i < 5; ++i) assert(a.at(i) == 7);
    }
    {
        IntArray a(3, 1);
        IntArray b(a);
        assert(b.size() == 3);
        assert(b.at(0) == 1);
    }
    {
        IntArray a(2, 9);
        IntArray b(std::move(a));
        assert(b.size() == 2);
        assert(b.at(0) == 9);
        assert(a.size() == 0);
    }
    {
        IntArray a(1, 0);
        IntArray b(4, 5);
        a = b;
        assert(a.size() == 4);
        assert(a.at(3) == 5);
        a = std::move(b);
        assert(a.size() == 4);
    }
    return 0;
}
