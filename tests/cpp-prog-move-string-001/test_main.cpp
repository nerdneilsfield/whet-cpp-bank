#include "../skeleton/solution.hpp"
#include <cassert>
#include <cstring>
int main(){
    {
        String s("hello");
        assert(s.size() == 5);
        assert(std::strcmp(s.c_str(), "hello") == 0);
    }
    {
        String s("foo");
        String t(s);
        assert(std::strcmp(t.c_str(), "foo") == 0);
        assert(t.c_str() != s.c_str());
    }
    {
        String s("bar");
        String t(std::move(s));
        assert(std::strcmp(t.c_str(), "bar") == 0);
        assert(s.size() == 0);
    }
    {
        String s("a"), t("bb");
        s = t;
        assert(std::strcmp(s.c_str(), "bb") == 0);
        s = std::move(t);
        assert(std::strcmp(s.c_str(), "bb") == 0);
    }
    {
        String s;
        assert(s.size() == 0);
    }
    return 0;
}
