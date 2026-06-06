#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    {
        auto r = k_largest({3,1,4,1,5,9,2,6}, 3);
        assert(r.size()==3);
        assert(r[0]==9 && r[1]==6 && r[2]==5);
    }
    {
        auto r = k_largest({1,2}, 5);
        assert(r.size()==2);
        assert(r[0]==2 && r[1]==1);
    }
    {
        auto r = k_largest({}, 3);
        assert(r.empty());
    }
    {
        auto r = k_largest({-1,-2,-3}, 2);
        assert(r[0]==-1 && r[1]==-2);
    }
    return 0;
}
