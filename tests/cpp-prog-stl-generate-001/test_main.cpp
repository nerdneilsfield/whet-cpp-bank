#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    assert((fib_n(1) == std::vector<long long>{0}));
    assert((fib_n(2) == std::vector<long long>{0,1}));
    assert((fib_n(6) == std::vector<long long>{0,1,1,2,3,5}));
    assert((fib_n(8) == std::vector<long long>{0,1,1,2,3,5,8,13}));
    {
        auto r = fib_n(10);
        assert(r.size() == 10);
        assert(r[9] == 34);
    }
    return 0;
}