#include "../skeleton/solution.hpp"
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>

class TestObserver : public Observer {
public:
    std::vector<std::string> messages;
    void update(const std::string& msg) override {
        messages.push_back(msg);
    }
};

int main() {
    {
        Subject s;
        TestObserver o1, o2;
        s.attach(&o1);
        s.attach(&o2);
        s.notify("hello");
        assert(o1.messages.size() == 1);
        assert(o1.messages[0] == "hello");
        assert(o2.messages.size() == 1);
        s.notify("world");
        assert(o1.messages.size() == 2);
        assert(o1.messages[1] == "world");
    }
    {
        Subject s;
        TestObserver o1, o2;
        s.attach(&o1);
        s.attach(&o2);
        s.detach(&o1);
        s.notify("test");
        assert(o1.messages.empty());
        assert(o2.messages.size() == 1);
    }
    {
        Subject s;
        TestObserver o;
        s.attach(&o);
        s.detach(&o);
        s.detach(&o);
        s.notify("x");
        assert(o.messages.empty());
    }
    return 0;
}
