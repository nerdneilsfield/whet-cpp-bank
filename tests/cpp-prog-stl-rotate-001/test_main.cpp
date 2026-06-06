#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    {
        std::vector<int> v{1,2,3,4,5};
        rotate_left(v, 2);
        std::vector<int> e{3,4,5,1,2};
        assert(v==e);
    }
    {
        std::vector<int> v{1,2,3};
        rotate_left(v, 0);
        std::vector<int> e{1,2,3};
        assert(v==e);
    }
    {
        std::vector<int> v{1,2,3};
        rotate_left(v, 5);
        std::vector<int> e{3,1,2};
        assert(v==e);
    }
    {
        std::vector<int> v;
        rotate_left(v, 3);
        assert(v.empty());
    }
    return 0;
}
