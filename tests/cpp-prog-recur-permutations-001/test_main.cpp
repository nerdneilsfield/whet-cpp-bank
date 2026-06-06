#include "../skeleton/solution.hpp"
#include <cassert>
#include <algorithm>
int main(){
    {
        auto r = permute({1,2,3});
        std::sort(r.begin(), r.end());
        std::vector<std::vector<int>> exp = {{1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,1,2},{3,2,1}};
        std::sort(exp.begin(), exp.end());
        assert(r == exp);
    }
    {
        auto r = permute({1});
        assert(r == (std::vector<std::vector<int>>{{1}}));
    }
    {
        auto r = permute({});
        assert(r.size() == 1);
        assert(r[0].empty());
    }
    {
        auto r = permute({1,2});
        std::sort(r.begin(), r.end());
        assert(r == (std::vector<std::vector<int>>{{1,2},{2,1}}));
    }
    {
        auto r = permute({1,2,3,4});
        assert(r.size() == 24);
    }
    return 0;
}
