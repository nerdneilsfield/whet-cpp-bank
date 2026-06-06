#include "../skeleton/solution.hpp"
#include <cassert>
#include <thread>
#include <vector>
int main() {
    {
        Spinlock s;
        int shared = 0;
        {
            s.lock();
            shared = 42;
            s.unlock();
        }
        assert(shared == 42);
    }
    {
        Spinlock s;
        int shared = 0;
        std::thread t1([&]() {
            for (int i = 0; i < 5000; ++i) {
                s.lock();
                ++shared;
                s.unlock();
            }
        });
        std::thread t2([&]() {
            for (int i = 0; i < 5000; ++i) {
                s.lock();
                ++shared;
                s.unlock();
            }
        });
        t1.join(); t2.join();
        assert(shared == 10000);
    }
    {
        Spinlock s;
        int shared = 0;
        std::vector<std::thread> thr;
        for (int t = 0; t < 4; ++t)
            thr.emplace_back([&]() {
                for (int i = 0; i < 2500; ++i) {
                    s.lock();
                    ++shared;
                    s.unlock();
                }
            });
        for (auto& t : thr) t.join();
        assert(shared == 10000);
    }
    return 0;
}
