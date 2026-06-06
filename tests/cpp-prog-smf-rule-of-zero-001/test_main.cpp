#include "../skeleton/solution.hpp"
#include <cassert>
int main() {
    {
        RuleOfZero a;
        assert(a.vec.empty());
        assert(a.str.empty());
    }
    {
        RuleOfZero a;
        a.vec = {1,2,3};
        a.str = "hello";
        RuleOfZero b(a);
        assert(b.vec.size() == 3);
        assert(b.vec[0] == 1);
        assert(b.str == "hello");
        b.vec[0] = 99;
        assert(a.vec[0] == 1);
    }
    {
        RuleOfZero a;
        a.vec = {10,20};
        a.str = "world";
        RuleOfZero b(std::move(a));
        assert(b.vec.size() == 2);
        assert(b.str == "world");
    }
    {
        RuleOfZero a, b;
        a.vec = {1,2,3}; a.str = "foo";
        b.vec = {4,5}; b.str = "bar";
        b = a;
        assert(b.vec.size() == 3);
        assert(b.str == "foo");
        b.vec[0] = 99;
        assert(a.vec[0] == 1);
    }
    {
        RuleOfZero a, b;
        a.vec = {7,8,9}; a.str = "baz";
        b = std::move(a);
        assert(b.vec.size() == 3);
    }
    {
        RuleOfZero a;
        a.vec = {1,2,3,4,5};
        RuleOfZero b = a;
        RuleOfZero c = std::move(b);
        RuleOfZero d;
        d = c;
        RuleOfZero e;
        e = std::move(d);
        assert(e.vec.size() == 5);
        assert(e.vec[4] == 5);
    }
    return 0;
}
