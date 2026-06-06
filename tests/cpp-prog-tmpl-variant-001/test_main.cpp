#include "../skeleton/solution.hpp"
#include <cassert>
#include <string>
int main() {
    {
        Variant<int, double> v(42);
        assert(v.type_tag() == 0);
        auto r1 = v.visit([](auto x) { return static_cast<int>(x); });
        assert(r1 == 42);
    }
    {
        Variant<int, double> v(3.14);
        assert(v.type_tag() == 1);
        auto r = v.visit([](auto x) -> double { return x * 2; });
        assert(r > 6.27 && r < 6.29);
    }
    {
        Variant<std::string, int> v(std::string("hello"));
        assert(v.type_tag() == 0);
        v.visit([](auto& x) {
            using T = std::decay_t<decltype(x)>;
            if constexpr (std::is_same_v<T, std::string>)
                x += " world";
        });
        auto s = v.visit([](const auto& x) -> std::string {
            using T = std::decay_t<decltype(x)>;
            if constexpr (std::is_same_v<T, std::string>) return x;
            return "";
        });
        assert(s == "hello world");
    }
    {
        Variant<int, double> a(10);
        Variant<int, double> b(a);
        assert(b.type_tag() == 0);
        assert(b.visit([](auto x) { return static_cast<int>(x); }) == 10);
    }
    {
        Variant<int, double> a(99);
        Variant<int, double> b(std::move(a));
        assert(b.type_tag() == 0);
    }
    {
        Variant<int, double> v;
        assert(v.type_tag() == 0);
    }
    return 0;
}
