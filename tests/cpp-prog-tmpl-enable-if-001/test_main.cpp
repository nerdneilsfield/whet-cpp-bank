#include "../skeleton/solution.hpp"
#include <cassert>
int main() {
    {
        auto r = process(10);
        assert(r == 20);
        static_assert(std::is_same<decltype(r), int>::value, "");
    }
    {
        auto r = process(3.14);
        assert(r > 1.56 && r < 1.58);
        static_assert(std::is_same<decltype(r), double>::value, "");
    }
    {
        auto r = process(short(5));
        assert(r == 10);
    }
    {
        auto r = process(2.0f);
        assert(r > 0.99 && r < 1.01);
    }
    {
        auto r = process(0L);
        assert(r == 0);
    }
    {
        auto r = process(1.5);
        assert(r > 0.74 && r < 0.76);
    }
    return 0;
}
