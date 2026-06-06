#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    assert(gcd_all({12,18,24}) == 6);
    assert(gcd_all({7}) == 7);
    assert(gcd_all({5,5,5}) == 5);
    assert(gcd_all({100,200,300,400}) == 100);
    assert(gcd_all({2,3,5}) == 1);
    assert(gcd_all({1000000000, 500000000}) == 500000000);
    return 0;
}