#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    assert(split("a,b,c", ',') == (std::vector<std::string>{"a","b","c"}));
    assert(split("", ',') == (std::vector<std::string>{""}));
    assert(split(",a,", ',') == (std::vector<std::string>{"","a",""}));
    assert(split("a,,b", ',') == (std::vector<std::string>{"a","","b"}));
    assert(split("hello", ',') == (std::vector<std::string>{"hello"}));
    assert(split("a b c d", ' ') == (std::vector<std::string>{"a","b","c","d"}));
    return 0;
}
