#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    assert(isPalindrome("A man, a plan, a canal: Panama") == true);
    assert(isPalindrome("race a car") == false);
    assert(isPalindrome("") == true);
    assert(isPalindrome(".,") == true);
    assert(isPalindrome("0P") == false);
    assert(isPalindrome("ab_a") == true);
    return 0;
}
