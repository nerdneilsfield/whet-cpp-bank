#include "../skeleton/solution.hpp"
#include <cassert>
#include <numeric>
int main() {
    {
        std::vector<int> v = {1,2,3,4,5};
        auto r = parallel_sum(v, 0, v.size());
        assert(r == 15);
    }
    {
        std::vector<int> v(10000, 1);
        auto r = parallel_sum(v, 0, v.size());
        assert(r == 10000);
    }
    {
        std::vector<int> v(2001, 0);
        v[0] = 42;
        auto r = parallel_sum(v, 0, v.size());
        assert(r == 42);
    }
    {
        std::vector<int> v;
        auto r = parallel_sum(v, 0, 0);
        assert(r == 0);
    }
    {
        std::vector<int> v(50000, 2);
        auto r = parallel_sum(v, 0, v.size());
        assert(r == 100000);
    }
    return 0;
}
