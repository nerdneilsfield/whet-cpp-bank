#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    {
        std::vector<int> v{3,1,4,1,5,9,2,6,5,3,5};
        int p = partition_last(v);
        for (int i=0;i<p;++i) assert(v[i]<=v[p]);
        for (int i=p+1;i<(int)v.size();++i) assert(v[i]>v[p]);
    }
    {
        std::vector<int> v{1};
        int p = partition_last(v);
        assert(p==0 && v[0]==1);
    }
    {
        std::vector<int> v{5,5,5,5};
        int p = partition_last(v);
        for (int i=0;i<p;++i) assert(v[i]<=5);
    }
    {
        std::vector<int> v{1,2,3,4};
        int p = partition_last(v);
        assert(v[p]==4 && p==3);
    }
    return 0;
}
