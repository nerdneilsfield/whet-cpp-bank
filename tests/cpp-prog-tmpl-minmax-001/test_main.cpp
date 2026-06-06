#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    assert(vmin(1) == 1);
    assert(vmin(3, 1, 4, 1, 5, 9, 2, 6) == 1);
    assert(vmin(-1, -2, -3) == -3);
    assert(vmin(5, 5, 5) == 5);
    assert(vmin(2, 1) == 1);
    return 0;
}
