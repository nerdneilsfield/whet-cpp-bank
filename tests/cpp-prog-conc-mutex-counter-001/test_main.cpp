#include "../skeleton/solution.hpp"
#include <cassert>
#include <thread>
#include <vector>
int main() {
    {
        Counter c;
        assert(c.get() == 0);
        c.increment();
        assert(c.get() == 1);
    }
    {
        Counter c;
        std::vector<std::thread> threads;
        for (int t = 0; t < 4; ++t)
            threads.emplace_back([&c]() {
                for (int i = 0; i < 10000; ++i) c.increment();
            });
        for (auto& t : threads) t.join();
        assert(c.get() == 40000);
    }
    {
        Counter c;
        for (int i = 0; i < 1000; ++i) c.increment();
        assert(c.get() == 1000);
    }
    {
        Counter c;
        std::thread t1([&c]() { for (int i = 0; i < 5000; ++i) c.increment(); });
        std::thread t2([&c]() { for (int i = 0; i < 5000; ++i) c.increment(); });
        t1.join(); t2.join();
        assert(c.get() == 10000);
    }
    return 0;
}
