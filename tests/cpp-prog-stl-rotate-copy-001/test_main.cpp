#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    assert((rotate_right({1,2,3,4,5}, 2) == std::vector<int>{4,5,1,2,3}));
    assert((rotate_right({1,2,3}, 0) == std::vector<int>{1,2,3}));
    assert((rotate_right({}, 3) == std::vector<int>{}));
    assert((rotate_right({1,2}, 5) == std::vector<int>{2,1}));
    assert((rotate_right({1}, 100) == std::vector<int>{1}));
    assert((rotate_right({1,2,3,4}, 4) == std::vector<int>{1,2,3,4}));
    return 0;
}