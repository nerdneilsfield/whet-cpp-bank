#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    assert(coinChange({1,2,5}, 11) == 3);
    assert(coinChange({2}, 3) == -1);
    assert(coinChange({1}, 0) == 0);
    assert(coinChange({1}, 1) == 1);
    assert(coinChange({1}, 2) == 2);
    assert(coinChange({186,419,83,408}, 6249) == 20);
    assert(coinChange({2,5,10,1}, 27) == 4);
    return 0;
}
