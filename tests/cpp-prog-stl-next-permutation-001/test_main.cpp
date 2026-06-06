#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    {
        std::vector<int> v{1,2,3};
        bool ok = next_perm(v);
        assert(ok == true);
        assert((v == std::vector<int>{1,3,2}));
    }
    {
        std::vector<int> v{3,2,1};
        bool ok = next_perm(v);
        assert(ok == false);
        assert((v == std::vector<int>{1,2,3}));
    }
    {
        std::vector<int> v{};
        bool ok = next_perm(v);
        assert(ok == false);
        assert(v.empty());
    }
    {
        std::vector<int> v{1};
        bool ok = next_perm(v);
        assert(ok == false);
        assert((v == std::vector<int>{1}));
    }
    {
        std::vector<int> v{1,1,2};
        bool ok = next_perm(v);
        assert(ok == true);
        assert((v == std::vector<int>{1,2,1}));
    }
    return 0;
}