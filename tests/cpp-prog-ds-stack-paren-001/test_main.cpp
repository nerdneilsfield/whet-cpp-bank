#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    assert(isBalanced("()") == true);
    assert(isBalanced("()[]{}") == true);
    assert(isBalanced("(]") == false);
    assert(isBalanced("([{}])") == true);
    assert(isBalanced("(((") == false);
    assert(isBalanced("") == true);
    assert(isBalanced("){") == false);
    return 0;
}
