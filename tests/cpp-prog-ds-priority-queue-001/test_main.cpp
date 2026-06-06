#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    {
        KthLargest k(3, {4,5,8,2});
        assert(k.add(3) == 4);
        assert(k.add(5) == 5);
        assert(k.add(10) == 5);
        assert(k.add(9) == 8);
        assert(k.add(4) == 8);
    }
    {
        KthLargest k(1, {});
        assert(k.add(7) == 7);
        assert(k.add(3) == 7);
        assert(k.add(10) == 10);
    }
    return 0;
}
