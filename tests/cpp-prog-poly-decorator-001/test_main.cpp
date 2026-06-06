#include "../skeleton/solution.hpp"
#include <cassert>
int main() {
    {
        auto b = std::make_unique<Espresso>();
        assert(b->cost() > 0.99 && b->cost() < 1.01);
    }
    {
        auto b = std::make_unique<MilkDecorator>(std::make_unique<Espresso>());
        assert(b->cost() > 1.49 && b->cost() < 1.51);
        assert(b->description().find("Milk") != std::string::npos);
    }
    {
        auto b = std::make_unique<SugarDecorator>(
                    std::make_unique<MilkDecorator>(
                        std::make_unique<Espresso>()));
        assert(b->cost() > 1.69 && b->cost() < 1.71);
        assert(b->description().find("Sugar") != std::string::npos);
    }
    {
        auto b = std::make_unique<SugarDecorator>(
                    std::make_unique<SugarDecorator>(
                        std::make_unique<Espresso>()));
        assert(b->cost() > 1.39 && b->cost() < 1.41);
    }
    return 0;
}
