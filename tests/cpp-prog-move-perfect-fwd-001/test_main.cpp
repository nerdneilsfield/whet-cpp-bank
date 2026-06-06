#include "../skeleton/solution.hpp"
#include <cassert>
#include <string>
#include <vector>

struct Cat {
    static int lv; static int rv; static int clv;
    int val;
    Cat(int v) : val(v) {}
    Cat(const Cat& o) : val(o.val) { ++lv; }
    Cat(Cat&& o) noexcept : val(o.val) { o.val = -1; ++rv; }
};
int Cat::lv = 0; int Cat::rv = 0; int Cat::clv = 0;

int take_cref(const int& x) { return x; }
int take_rref(int&& x) { return x; }
Cat build_cat(int v) { return Cat(v); }

int main() {
    auto add = [](int a, int b) { return a + b; };
    assert(wrapper(add, 3, 4) == 7);

    int x = 10;
    assert(wrapper(take_cref, x) == 10);

    auto identity = [](auto&& v) -> decltype(auto) { return std::forward<decltype(v)>(v); };
    Cat a(5);
    Cat& ref = wrapper(identity, a);
    assert(ref.val == 5);

    Cat::lv = Cat::rv = 0;
    Cat b = wrapper(identity, Cat(99));
    assert(Cat::rv >= 1);

    auto cb = [](std::vector<int> v) { return v.size(); };
    std::vector<int> vec = {1,2,3};
    assert(wrapper(cb, vec) == 3);
    assert(wrapper(cb, std::vector<int>{4,5,6,7}) == 4);

    return 0;
}
