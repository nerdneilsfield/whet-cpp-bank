#include "../skeleton/solution.hpp"
#include <cassert>
#include <string>
struct EventA { int x; };
struct EventB { std::string s; };
struct EventC { double d; };

int main() {
    {
        EventBus bus;
        int result = 0;
        bus.subscribe<EventA>([&](const EventA& e) { result = e.x; });
        bus.publish(EventA{42});
        assert(result == 42);
    }
    {
        EventBus bus;
        std::string collected;
        bus.subscribe<EventB>([&](const EventB& e) { collected += e.s; });
        bus.publish(EventB{"hello "});
        bus.publish(EventB{"world"});
        assert(collected == "hello world");
    }
    {
        EventBus bus;
        int sum = 0;
        double dsum = 0.0;
        bus.subscribe<EventA>([&](const EventA& e) { sum += e.x; });
        bus.subscribe<EventC>([&](const EventC& e) { dsum += e.d; });
        bus.publish(EventA{10});
        bus.publish(EventC{3.5});
        bus.publish(EventA{5});
        assert(sum == 15);
        assert(dsum > 3.49 && dsum < 3.51);
    }
    {
        EventBus bus;
        int calls = 0;
        bus.subscribe<EventA>([&](const EventA&) { ++calls; });
        bus.subscribe<EventA>([&](const EventA&) { ++calls; });
        bus.publish(EventA{0});
        assert(calls == 2);
    }
    return 0;
}
