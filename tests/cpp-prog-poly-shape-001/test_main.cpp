#include "../skeleton/solution.hpp"
#include <cassert>
#include <cmath>
int main(){
    auto near = [](double a, double b){ return std::abs(a - b) < 1e-6; };
    {
        Circle c(1.0);
        assert(near(c.area(), 3.14159265358979));
    }
    {
        Rectangle r(3.0, 4.0);
        assert(near(r.area(), 12.0));
    }
    {
        std::vector<std::unique_ptr<Shape>> v;
        v.emplace_back(new Circle(1.0));
        v.emplace_back(new Rectangle(2.0, 3.0));
        assert(near(total_area(v), 3.14159265358979 + 6.0));
    }
    {
        std::vector<std::unique_ptr<Shape>> v;
        assert(near(total_area(v), 0.0));
    }
    return 0;
}
