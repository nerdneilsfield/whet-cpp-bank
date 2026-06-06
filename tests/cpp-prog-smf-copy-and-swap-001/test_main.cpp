#include "../skeleton/solution.hpp"
#include <cassert>
#include <cstring>
int main() {
    {
        CopyAndSwap a("hello");
        assert(std::strcmp(a.c_str(), "hello") == 0);
        assert(a.size() == 5);
    }
    {
        CopyAndSwap a("abc"), b("xyz");
        a = b;
        assert(std::strcmp(a.c_str(), "xyz") == 0);
    }
    {
        CopyAndSwap a("foo");
        CopyAndSwap b(std::move(a));
        assert(std::strcmp(b.c_str(), "foo") == 0);
        assert(a.c_str() == nullptr || a.size() == 0);
    }
    {
        CopyAndSwap a("longer_string"), b("short");
        a = b;
        assert(std::strcmp(a.c_str(), "short") == 0);
    }
    {
        CopyAndSwap a("data"), b("more");
        a = std::move(b);
        assert(std::strcmp(a.c_str(), "more") == 0);
    }
    {
        CopyAndSwap a;
        CopyAndSwap b("test");
        a = b;
        assert(std::strcmp(a.c_str(), "test") == 0);
    }
    return 0;
}
