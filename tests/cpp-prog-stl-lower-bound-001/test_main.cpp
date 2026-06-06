#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    assert((insert_sorted({1,3,5,7}, 4) == std::vector<int>{1,3,4,5,7}));
    assert((insert_sorted({1,2,2,3}, 2) == std::vector<int>{1,2,2,2,3}));
    assert((insert_sorted({}, 5) == std::vector<int>{5}));
    assert((insert_sorted({2,4,6}, 1) == std::vector<int>{1,2,4,6}));
    assert((insert_sorted({2,4,6}, 9) == std::vector<int>{2,4,6,9}));
    assert((insert_sorted({-5,-3,-1}, -4) == std::vector<int>{-5,-4,-3,-1}));
    return 0;
}
