#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    ObjectPool<int, 3> pool;
    int* a = pool.acquire();
    int* b = pool.acquire();
    int* c = pool.acquire();
    assert(a && b && c);
    *a = 1; *b = 2; *c = 3;
    assert(*a == 1 && *b == 2 && *c == 3);
    int* d = pool.acquire();
    assert(d == nullptr);
    pool.release(b);
    int* e = pool.acquire();
    assert(e != nullptr);
    pool.release(a);
    pool.release(c);
    pool.release(e);
    return 0;
}
