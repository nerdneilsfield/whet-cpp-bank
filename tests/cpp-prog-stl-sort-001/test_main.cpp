#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    {
        auto r = merge_intervals({{1,3},{2,6},{8,10},{15,18}});
        assert(r.size()==3);
        assert(r[0]==std::make_pair(1,6));
        assert(r[1]==std::make_pair(8,10));
        assert(r[2]==std::make_pair(15,18));
    }
    {
        auto r = merge_intervals({{1,4},{4,5}});
        assert(r.size()==1);
        assert(r[0]==std::make_pair(1,5));
    }
    {
        auto r = merge_intervals({});
        assert(r.empty());
    }
    {
        auto r = merge_intervals({{1,10},{2,3},{4,5}});
        assert(r.size()==1);
        assert(r[0]==std::make_pair(1,10));
    }
    return 0;
}
