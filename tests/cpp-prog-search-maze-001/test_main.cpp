#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    assert(hasPath({{0,0,0},{1,1,0},{0,0,0}}, 0,0, 2,2) == true);
    assert(hasPath({{0,1},{1,0}}, 0,0, 1,1) == false);
    assert(hasPath({{0}}, 0,0, 0,0) == true);
    assert(hasPath({{1}}, 0,0, 0,0) == false);
    assert(hasPath({{0,0,0,0},{1,1,1,0},{0,0,0,0},{0,1,1,1},{0,0,0,0}}, 0,0, 4,3) == true);
    assert(hasPath({{0,1,0},{0,1,0},{0,1,0}}, 0,0, 0,2) == false);
    return 0;
}
