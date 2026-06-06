#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    assert(romanToInt("III") == 3);
    assert(romanToInt("IV") == 4);
    assert(romanToInt("IX") == 9);
    assert(romanToInt("LVIII") == 58);
    assert(romanToInt("MCMXCIV") == 1994);
    assert(romanToInt("MMMCMXCIX") == 3999);
    assert(romanToInt("I") == 1);
    return 0;
}
