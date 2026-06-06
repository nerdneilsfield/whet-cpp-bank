#include "../skeleton/solution.hpp"
#include <cassert>
#include <string>
int main() {
    {
        Function<int(int,int)> f;
        assert(!f);
    }
    {
        Function<int(int,int)> f = [](int a, int b) { return a + b; };
        assert(f);
        assert(f(3, 4) == 7);
    }
    {
        Function<int(int,int)> f = [](int a, int b) { return a * b; };
        auto g = f;
        assert(g(5, 6) == 30);
    }
    {
        Function<int(int)> f = [](int x) { return x * x; };
        auto g = std::move(f);
        assert(g(7) == 49);
    }
    {
        Function<std::string(std::string)> f = [](std::string s) { return s + s; };
        assert(f("a") == "aa");
    }
    {
        int calls = 0;
        Function<void()> f = [&calls]() { ++calls; };
        f(); f(); f();
        assert(calls == 3);
    }
    {
        Function<int(int,int)> a = [](int x, int y) { return x - y; };
        Function<int(int,int)> b = [](int x, int y) { return x + y; };
        a = b;
        assert(a(10, 5) == 15);
    }
    return 0;
}
