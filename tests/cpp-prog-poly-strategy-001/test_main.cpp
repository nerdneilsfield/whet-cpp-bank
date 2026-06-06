#include "../skeleton/solution.hpp"
#include <cassert>
int main() {
    {
        SortContext ctx;
        std::vector<int> v = {3,1,4,1,5,9};
        ctx.sort(v, [](int a, int b) { return a < b; });
        assert(v == (std::vector<int>{1,1,3,4,5,9}));
    }
    {
        SortContext ctx;
        std::vector<int> v = {1,2,3,4,5};
        ctx.sort(v, [](int a, int b) { return a > b; });
        assert(v == (std::vector<int>{5,4,3,2,1}));
    }
    {
        SortContext ctx;
        std::vector<int> v = {};
        ctx.sort(v, [](int a, int b) { return a < b; });
        assert(v.empty());
    }
    {
        SortContext ctx;
        std::vector<int> v = {7};
        ctx.sort(v, [](int, int) { return false; });
        assert(v.size() == 1 && v[0] == 7);
    }
    {
        SortContext ctx;
        std::vector<int> v = {5,5,5,5};
        ctx.sort(v, [](int a, int b) { return a < b; });
        assert(v == (std::vector<int>{5,5,5,5}));
    }
    return 0;
}
