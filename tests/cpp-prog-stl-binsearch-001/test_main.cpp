#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    {
        std::vector<int> v{1,2,3,1};
        int i = find_peak(v);
        assert(i==2);
    }
    {
        std::vector<int> v{1,2,1,3,5,6,4};
        int i = find_peak(v);
        assert(i==1 || i==5);
    }
    {
        std::vector<int> v{1};
        assert(find_peak(v)==0);
    }
    {
        std::vector<int> v{5,4,3,2,1};
        assert(find_peak(v)==0);
    }
    {
        std::vector<int> v{1,2,3,4,5};
        assert(find_peak(v)==4);
    }
    return 0;
}
