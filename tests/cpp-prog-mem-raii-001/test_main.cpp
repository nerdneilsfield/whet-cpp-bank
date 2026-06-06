#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    {
        int x = 0;
        { ScopeExit g([&]{ x = 42; }); }
        assert(x==42);
    }
    {
        int x = 0;
        { ScopeExit g([&]{ x = 1; }); g.dismiss(); }
        assert(x==0);
    }
    {
        int counter = 0;
        for (int i = 0; i < 3; ++i) {
            ScopeExit g([&]{ ++counter; });
        }
        assert(counter==3);
    }
    return 0;
}
