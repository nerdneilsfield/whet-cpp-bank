#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    {
        UniquePtr<int> p(new int(7));
        assert(*p == 7);
        assert(p.get() != nullptr);
    }
    {
        UniquePtr<int> p(new int(1));
        UniquePtr<int> q(std::move(p));
        assert(!p);
        assert(*q == 1);
    }
    {
        UniquePtr<int> p(new int(2));
        UniquePtr<int> q;
        q = std::move(p);
        assert(!p);
        assert(*q == 2);
    }
    {
        UniquePtr<int> p(new int(5));
        int* raw = p.release();
        assert(!p);
        assert(*raw == 5);
        delete raw;
    }
    {
        UniquePtr<int> p(new int(3));
        p.reset(new int(9));
        assert(*p == 9);
        p.reset();
        assert(!p);
    }
    return 0;
}
