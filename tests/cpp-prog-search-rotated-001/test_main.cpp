#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    assert(searchRotated({4,5,6,7,0,1,2}, 0) == 4);
    assert(searchRotated({4,5,6,7,0,1,2}, 3) == -1);
    assert(searchRotated({1}, 0) == -1);
    assert(searchRotated({1}, 1) == 0);
    assert(searchRotated({}, 5) == -1);
    assert(searchRotated({1,3}, 3) == 1);
    assert(searchRotated({5,1,3}, 5) == 0);
    assert(searchRotated({4,5,6,7,0,1,2}, 6) == 2);
    return 0;
}
