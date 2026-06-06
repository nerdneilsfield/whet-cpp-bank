#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    {
        auto r = two_sum({2,7,11,15}, 9);
        assert(r.first==0 && r.second==1);
    }
    {
        auto r = two_sum({3,2,4}, 6);
        assert(r.first==1 && r.second==2);
    }
    {
        auto r = two_sum({3,3}, 6);
        assert(r.first==0 && r.second==1);
    }
    {
        auto r = two_sum({1,2,3}, 10);
        assert(r.first==-1 && r.second==-1);
    }
    {
        auto r = two_sum({}, 5);
        assert(r.first==-1);
    }
    return 0;
}
