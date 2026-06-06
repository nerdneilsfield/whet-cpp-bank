#include "../skeleton/solution.hpp"
#include <cassert>
#include <string>
int main() {
    {
        Tuple<int, double, char> t(1, 2.5, 'c');
        assert(get<0>(t) == 1);
        assert(get<1>(t) > 2.49 && get<1>(t) < 2.51);
        assert(get<2>(t) == 'c');
    }
    {
        Tuple<std::string, int> t("hello", 42);
        get<0>(t) += " world";
        assert(get<0>(t) == "hello world");
        assert(get<1>(t) == 42);
    }
    {
        Tuple<int> t(99);
        assert(get<0>(t) == 99);
    }
    {
        Tuple<double, double, double> t(1.1, 2.2, 3.3);
        assert(get<0>(t) > 1.09);
        assert(get<2>(t) > 3.29);
    }
    {
        Tuple<int, char, long, float> t(1, 'a', 10L, 1.5f);
        assert(get<0>(t) == 1);
        assert(get<1>(t) == 'a');
        assert(get<2>(t) == 10L);
        assert(get<3>(t) > 1.49f);
    }
    return 0;
}
