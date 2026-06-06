#include "../skeleton/solution.hpp"
#include <cassert>
#include <cmath>
#include <climits>
int main(){
    auto close = [](double a, double b){ return std::fabs(a-b) < 1e-9; };
    assert(close(myPow(2.0, 10), 1024.0));
    assert(close(myPow(2.0, -2), 0.25));
    assert(close(myPow(2.1, 3), 9.261));
    assert(close(myPow(1.0, INT_MIN), 1.0));
    assert(close(myPow(0.0, 5), 0.0));
    assert(close(myPow(5.0, 0), 1.0));
    assert(close(myPow(-2.0, 3), -8.0));
    return 0;
}
