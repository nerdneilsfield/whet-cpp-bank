#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    {
        auto r = find_min_max({3,1,4,1,5,9,2,6});
        assert(r.first==1 && r.second==9);
    }
    {
        auto r = find_min_max({7});
        assert(r.first==7 && r.second==7);
    }
    {
        auto r = find_min_max({5,5,5,5});
        assert(r.first==5 && r.second==5);
    }
    {
        auto r = find_min_max({-3,-1,-5,-2});
        assert(r.first==-5 && r.second==-1);
    }
    {
        auto r = find_min_max({1,2});
        assert(r.first==1 && r.second==2);
    }
    return 0;
}