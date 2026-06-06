#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    {
        auto r = sorted_intersection({1,2,2,3,4},{2,2,4,5});
        std::vector<int> e{2,2,4};
        assert(r==e);
    }
    {
        auto r = sorted_intersection({},{1,2,3});
        assert(r.empty());
    }
    {
        auto r = sorted_intersection({1,2,3},{4,5,6});
        assert(r.empty());
    }
    {
        auto r = sorted_intersection({1,2,3},{1,2,3});
        std::vector<int> e{1,2,3};
        assert(r==e);
    }
    return 0;
}
