#include "../skeleton/solution.hpp"
#include <cassert>
#include <string>
#include <vector>
int main(){
    {
        int a = 1, b = 2;
        my_swap(a, b);
        assert(a == 2 && b == 1);
    }
    {
        std::string a = "foo", b = "bar";
        my_swap(a, b);
        assert(a == "bar" && b == "foo");
    }
    {
        std::vector<int> a{1,2,3}, b{4,5};
        my_swap(a, b);
        assert(a.size() == 2 && b.size() == 3);
    }
    {
        int x = 7;
        my_swap(x, x);
        assert(x == 7);
    }
    return 0;
}
