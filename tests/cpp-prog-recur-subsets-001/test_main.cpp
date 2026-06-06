#include "../skeleton/solution.hpp"
#include <cassert>
#include <algorithm>
static std::vector<std::vector<int>> norm(std::vector<std::vector<int>> v){
    for (auto& s : v) std::sort(s.begin(), s.end());
    std::sort(v.begin(), v.end());
    return v;
}
int main(){
    {
        auto r = norm(subsets({1,2,3}));
        std::vector<std::vector<int>> exp = {{},{1},{1,2},{1,2,3},{1,3},{2},{2,3},{3}};
        std::sort(exp.begin(), exp.end());
        assert(r == exp);
    }
    {
        auto r = norm(subsets({}));
        assert(r == (std::vector<std::vector<int>>{{}}));
    }
    {
        auto r = norm(subsets({7}));
        assert(r == (std::vector<std::vector<int>>{{},{7}}));
    }
    {
        auto r = subsets({1,2,3,4});
        assert(r.size() == 16);
    }
    return 0;
}
