#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    {
        auto m = char_freq("aabbc");
        assert(m['a']==2);
        assert(m['b']==2);
        assert(m['c']==1);
    }
    {
        auto m = char_freq("");
        assert(m.empty());
    }
    {
        auto m = char_freq("aaaa");
        assert(m.size()==1);
        assert(m['a']==4);
    }
    {
        auto m = char_freq("hello world");
        assert(m['l']==3);
        assert(m['o']==2);
        assert(m[' ']==1);
    }
    return 0;
}
