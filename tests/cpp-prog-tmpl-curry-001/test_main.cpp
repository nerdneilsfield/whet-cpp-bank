#include "../skeleton/solution.hpp"
#include <cassert>
#include <string>
int main() {
    {
        auto sum = [](int a, int b, int c) { return a + b + c; };
        auto c = curry(sum);
        assert(c(1)(2)(3) == 6);
    }
    {
        auto mul = [](int a, int b, int c) { return a * b * c; };
        assert(curry(mul)(2)(3)(4) == 24);
    }
    {
        auto r = curry([](int a, int b, int c) { return a + b + c; })(10)(20)(30);
        assert(r == 60);
    }
    {
        int factor = 10;
        auto f = [factor](int a, int b, int c) { return (a + b + c) * factor; };
        assert(curry(f)(1)(2)(3) == 60);
    }
    {
        auto r = curry([](int a, int b, int c) { return a * b + c; })(2)(3)(4);
        assert(r == 10);
    }
    return 0;
}