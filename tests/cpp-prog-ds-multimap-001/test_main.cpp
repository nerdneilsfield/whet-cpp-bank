#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    {
        auto r = groupBy({{"a",1},{"b",2},{"a",3}});
        assert(r["a"] == (std::vector<int>{1,3}));
        assert(r["b"] == (std::vector<int>{2}));
    }
    {
        auto r = groupBy({});
        assert(r.empty());
    }
    {
        auto r = groupBy({{"x",5}});
        assert(r["x"] == (std::vector<int>{5}));
    }
    {
        auto r = groupBy({{"k",1},{"k",2},{"k",3},{"k",4}});
        assert(r["k"] == (std::vector<int>{1,2,3,4}));
    }
    return 0;
}
