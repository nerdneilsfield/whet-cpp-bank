#include "../skeleton/solution.hpp"
#include <cassert>
#include <sstream>
int main() {
    {
        auto s = ShapeFactory::create("circle", 5.0);
        assert(s);
        assert(s->draw().find("Circle") != std::string::npos);
        assert(s->draw().find("5") != std::string::npos);
    }
    {
        auto s = ShapeFactory::create("square", 3.0);
        assert(s);
        assert(s->draw().find("Square") != std::string::npos);
        assert(s->draw().find("3") != std::string::npos);
    }
    {
        auto s = ShapeFactory::create("unknown", 0);
        assert(!s);
    }
    {
        auto c = ShapeFactory::create("circle", 2.5);
        auto q = ShapeFactory::create("square", 10.0);
        assert(c->draw() != q->draw());
    }
    return 0;
}
