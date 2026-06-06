#include "../skeleton/solution.hpp"
#include <cassert>
#include <string>
#include <vector>
struct Tracker {
    static int constructed;
    static int copied;
    static int moved;
    int id;
    Tracker(int i) : id(i) { ++constructed; }
    Tracker(const Tracker& o) : id(o.id) { ++copied; }
    Tracker(Tracker&& o) noexcept : id(o.id) { o.id = -1; ++moved; }
    ~Tracker() = default;
};
int Tracker::constructed = 0;
int Tracker::copied = 0;
int Tracker::moved = 0;

int main() {
    {
        Container<int> c;
        c.emplace_back(10);
        c.emplace_back(20);
        assert(c.size() == 2);
        assert(c[0] == 10);
        assert(c[1] == 20);
    }
    {
        Container<std::string> c;
        c.emplace_back(3, char(65));
        c.emplace_back("hello");
        assert(c.size() == 2);
        assert(c[0] == "AAA");
        assert(c[1] == "hello");
    }
    {
        Tracker::constructed = Tracker::copied = Tracker::moved = 0;
        Container<Tracker> c;
        c.emplace_back(42);
        assert(Tracker::constructed == 1);
        assert(Tracker::copied == 0);
        assert(c[0].id == 42);
    }
    {
        Container<int> c;
        for (int i = 0; i < 256; ++i) c.emplace_back(i);
        assert(c.size() == 256);
        for (int i = 0; i < 256; ++i) assert(c[i] == i);
    }
    return 0;
}
