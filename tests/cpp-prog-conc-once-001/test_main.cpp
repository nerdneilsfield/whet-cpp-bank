#include "../skeleton/solution.hpp"
#include <cassert>
#include <thread>
#include <vector>

// 用 call_once 的版本：solution 需要自己定义 std::once_flag
int main() {
    {
        LazyInit li;
        assert(!li.is_initialized());
        li.ensure_init();
        assert(li.is_initialized());
        assert(li.init_count() == 1);
    }
    {
        LazyInit li;
        std::vector<std::thread> threads;
        for (int t = 0; t < 10; ++t)
            threads.emplace_back([&li]() { li.ensure_init(); });
        for (auto& t : threads) t.join();
        assert(li.is_initialized());
        assert(li.init_count() == 1);
    }
    {
        LazyInit li;
        li.ensure_init();
        li.ensure_init();
        li.ensure_init();
        assert(li.init_count() == 1);
    }
    return 0;
}
