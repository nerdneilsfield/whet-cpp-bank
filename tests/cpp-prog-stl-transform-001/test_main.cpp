#include "../skeleton/solution.hpp"
#include <cassert>
#include <stdexcept>
int main(){
    {
        auto r = elem_add({1,2,3},{4,5,6});
        assert(r.size()==3);
        assert(r[0]==5 && r[1]==7 && r[2]==9);
    }
    {
        auto r = elem_add({},{});
        assert(r.empty());
    }
    {
        auto r = elem_add({-1,-2},{1,2});
        assert(r[0]==0 && r[1]==0);
    }
    {
        bool threw = false;
        try { elem_add({1,2},{1}); } catch (const std::invalid_argument&) { threw = true; }
        assert(threw);
    }
    return 0;
}
