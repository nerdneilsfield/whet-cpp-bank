#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    assert(describe(Value(42)) == "int:42");
    assert(describe(Value(-7)) == "int:-7");
    {
        std::string s = describe(Value(3.5));
        assert(s.substr(0, 7) == "double:");
    }
    assert(describe(Value(std::string("hi"))) == "str:hi");
    assert(describe(Value(std::string(""))) == "str:");
    return 0;
}
