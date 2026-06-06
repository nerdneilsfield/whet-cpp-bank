#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    assert((sequence(5) == std::vector<int>{1,2,3,4,5}));
    assert((sequence(1) == std::vector<int>{1}));
    assert((sequence(3) == std::vector<int>{1,2,3}));
    {
        auto r = sequence(100);
        assert((int)r.size() == 100);
        assert(r.front()==1 && r.back()==100);
        for(int i=0;i<100;i++) assert(r[i]==i+1);
    }
    return 0;
}