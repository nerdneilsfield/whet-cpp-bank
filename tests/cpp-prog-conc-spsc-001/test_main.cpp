#include "../skeleton/solution.hpp"
#include <cassert>
#include <thread>
int main(){
    {
        SPSCQueue<int, 4> q;
        int x;
        assert(!q.pop(x));
        assert(q.push(1));
        assert(q.push(2));
        assert(q.push(3));
        assert(!q.push(4)); // full (capacity N-1 = 3)
        assert(q.pop(x) && x == 1);
        assert(q.push(4));
        assert(q.pop(x) && x == 2);
        assert(q.pop(x) && x == 3);
        assert(q.pop(x) && x == 4);
        assert(!q.pop(x));
    }
    {
        SPSCQueue<int, 1024> q;
        const int N = 5000;
        std::thread prod([&]{ for (int i = 0; i < N; ++i) while (!q.push(i)); });
        int sum = 0, got = 0, v;
        while (got < N) { if (q.pop(v)) { sum += v; ++got; } }
        prod.join();
        long long expected = (long long)N * (N - 1) / 2;
        assert(sum == expected);
    }
    return 0;
}
