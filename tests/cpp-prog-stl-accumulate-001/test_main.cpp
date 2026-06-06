#include "../skeleton/solution.hpp"
#include <cassert>
#include <cmath>
int main(){
    auto near=[](double a,double b){ return std::abs(a-b)<1e-9; };
    {
        auto r = mean_var({1,2,3,4,5});
        assert(near(r.first,3.0));
        assert(near(r.second,2.0));
    }
    {
        auto r = mean_var({});
        assert(r.first==0 && r.second==0);
    }
    {
        auto r = mean_var({5});
        assert(near(r.first,5.0));
        assert(near(r.second,0.0));
    }
    {
        auto r = mean_var({2,2,2,2});
        assert(near(r.first,2.0));
        assert(near(r.second,0.0));
    }
    return 0;
}
