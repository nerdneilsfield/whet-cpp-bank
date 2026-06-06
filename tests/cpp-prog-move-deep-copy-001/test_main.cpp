#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main() {
    DeepCopy::reset_counters();
    {
        DeepCopy a(100, 42);
        assert(DeepCopy::alive() == 1);
        assert(DeepCopy::copy_count() == 0);
        DeepCopy b(a);
        assert(DeepCopy::alive() == 2);
        assert(DeepCopy::copy_count() == 1);
        assert(b.data()[0] == 42 && b.data()[99] == 42);
        assert(a.data()[0] == 42);
    }
    assert(DeepCopy::alive() == 0);
    {
        DeepCopy a(10, 7);
        DeepCopy b(10, 0);
        DeepCopy::reset_counters();
        b = a;
        assert(DeepCopy::copy_count() == 1);
        assert(b.data()[0] == 7);
    }
    {
        DeepCopy a(5, 99);
        DeepCopy::reset_counters();
        DeepCopy b(std::move(a));
        assert(DeepCopy::move_count() == 1);
        assert(b.data()[0] == 99);
        assert(a.data() == nullptr);
    }
    {
        DeepCopy a(3, 1), b(3, 2);
        DeepCopy::reset_counters();
        a = std::move(b);
        assert(DeepCopy::move_count() == 1);
        assert(a.data()[0] == 2);
    }
    return 0;
}
