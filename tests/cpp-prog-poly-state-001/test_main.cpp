#include "../skeleton/solution.hpp"
#include <cassert>
int main() {
    {
        TrafficLight tl;
        assert(tl.current_color() == "Red");
        assert(tl.current_duration() == 30);
    }
    {
        TrafficLight tl;
        tl.advance();
        assert(tl.current_color() == "Green");
        assert(tl.current_duration() == 25);
    }
    {
        TrafficLight tl;
        tl.advance(); tl.advance();
        assert(tl.current_color() == "Yellow");
        assert(tl.current_duration() == 5);
    }
    {
        TrafficLight tl;
        tl.advance(); tl.advance(); tl.advance();
        assert(tl.current_color() == "Red");
    }
    {
        TrafficLight tl;
        for (int i = 0; i < 6; ++i) tl.advance();
        assert(tl.current_color() == "Red");
    }
    return 0;
}
