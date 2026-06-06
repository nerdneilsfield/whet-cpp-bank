#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    {
        std::vector<int> v{1,1,1,2,2,3};
        auto r = top_k_frequent(v, 2);
        assert(r.size()==2);
        assert(r[0]==1 && r[1]==2);
    }
    {
        std::vector<int> v{1};
        auto r = top_k_frequent(v, 1);
        assert(r.size()==1 && r[0]==1);
    }
    {
        std::vector<int> v{4,4,5,5,6};
        auto r = top_k_frequent(v, 2);
        assert(r.size()==2);
        assert(r[0]==4 && r[1]==5);
    }
    {
        std::vector<int> v{-1,-1,-2,-2,-3};
        auto r = top_k_frequent(v, 1);
        assert(r.size()==1 && r[0]==-1);
    }
    return 0;
}
