#include "../skeleton/solution.hpp"
#include <cassert>
#include <thread>
int main() {
    {
        TokenBucket tb(100, 10);
        int allowed = 0;
        for (int i = 0; i < 15; ++i) {
            if (tb.allow()) ++allowed;
        }
        assert(allowed == 10);
    }
    {
        TokenBucket tb(10, 5);
        int cnt = 0;
        for (int i = 0; i < 10; ++i)
            if (tb.allow()) ++cnt;
        assert(cnt == 5);
    }
    {
        TokenBucket tb(1000, 3);
        int cnt = 0;
        for (int i = 0; i < 5; ++i) if (tb.allow()) ++cnt;
        assert(cnt == 3);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        for (int i = 0; i < 5; ++i) if (tb.allow()) ++cnt;
        assert(cnt >= 4);
    }
    return 0;
}
