#include "../skeleton/solution.hpp"
#include <cassert>
#include <cstdio>
#include <utility>
int main(){
    {
        g_closed = false;
        std::FILE* f = std::tmpfile();
        assert(f);
        {
            FileGuard g(f);
            assert(g.get() == f);
        }
        assert(g_closed == true);
    }
    {
        g_closed = false;
        std::FILE* f = std::tmpfile();
        FileGuard g(f);
        FileGuard g2(std::move(g));
        assert(g.get() == nullptr);
        assert(g2.get() == f);
    }
    {
        g_closed = false;
        FileGuard g(nullptr);
    }
    return 0;
}
