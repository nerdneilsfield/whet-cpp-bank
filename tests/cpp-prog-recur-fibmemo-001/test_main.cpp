#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    assert(fib(0) == 0);
    assert(fib(1) == 1);
    assert(fib(2) == 1);
    assert(fib(10) == 55);
    assert(fib(20) == 6765);
    assert(fib(50) == 12586269025LL);
    assert(fib(60) == 1548008755920LL);
    return 0;
}
