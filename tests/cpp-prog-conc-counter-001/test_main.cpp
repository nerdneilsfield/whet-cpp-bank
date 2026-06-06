#include "../skeleton/solution.hpp"
#include <cassert>
#include <thread>
#include <vector>
int main(){
    {
        Counter c;
        assert(c.get() == 0);
        c.inc();
        assert(c.get() == 1);
    }
    {
        Counter c;
        const int T = 8;
        const int N = 10000;
        std::vector<std::thread> ths;
        for (int i = 0; i < T; ++i)
            ths.emplace_back([&]{ for (int j = 0; j < N; ++j) c.inc(); });
        for (auto& t : ths) t.join();
        assert(c.get() == T * N);
    }
    return 0;
}
