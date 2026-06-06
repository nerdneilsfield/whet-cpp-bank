#include "../skeleton/solution.hpp"
#include <cassert>
#include <string>
int main(){
    {
        MyTuple<int, double, char> t(1, 2.5, 'x');
        assert(get<0>(t) == 1);
        assert(get<1>(t) == 2.5);
        assert(get<2>(t) == 'x');
    }
    {
        MyTuple<int> t(42);
        assert(get<0>(t) == 42);
        get<0>(t) = 100;
        assert(get<0>(t) == 100);
    }
    {
        MyTuple<std::string, int> t(std::string("hi"), 5);
        assert(get<0>(t) == "hi");
        assert(get<1>(t) == 5);
    }
    return 0;
}
