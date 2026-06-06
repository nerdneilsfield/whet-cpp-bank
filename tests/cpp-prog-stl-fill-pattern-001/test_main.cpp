#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    assert((make_filled(4, 7) == std::vector<int>{7,7,7,7}));
    assert((make_filled(0, 9) == std::vector<int>{}));
    assert((make_filled(1, -1) == std::vector<int>{-1}));
    assert((make_filled(3, 0) == std::vector<int>{0,0,0}));
    {
        auto r = make_filled(100, 42);
        assert((int)r.size() == 100);
        for(int x : r) assert(x == 42);
    }
    return 0;
}