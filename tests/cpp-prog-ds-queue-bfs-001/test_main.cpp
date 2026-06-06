#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    assert(shortestPath({{0,0,0},{1,1,0},{0,0,0}}) == 4);
    assert(shortestPath({{0}}) == 0);
    assert(shortestPath({{0,1},{1,0}}) == -1);
    assert(shortestPath({{1,0},{0,0}}) == -1);
    assert(shortestPath({{0,0,0,0},{1,1,1,0},{0,0,0,0},{0,1,1,1},{0,0,0,0}}) == 10);
    assert(shortestPath({{0,0},{0,0}}) == 2);
    return 0;
}
