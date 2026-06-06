#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    RangeCounter rc;
    for (int v : {5, 1, 9, 3, 7, 2}) rc.insert(v);
    assert(rc.countInRange(2, 7) == 4);
    assert(rc.countInRange(0, 10) == 6);
    assert(rc.countInRange(8, 8) == 0);
    assert(rc.countInRange(9, 9) == 1);
    assert(rc.countInRange(-5, 0) == 0);
    RangeCounter empty;
    assert(empty.countInRange(0, 100) == 0);
    return 0;
}
