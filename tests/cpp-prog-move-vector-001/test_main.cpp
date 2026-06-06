#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    {
        Vector v;
        for (int i = 0; i < 10; ++i) v.push_back(i);
        assert(v.size() == 10);
        for (int i = 0; i < 10; ++i) assert(v[i] == i);
    }
    {
        Vector v;
        v.push_back(1); v.push_back(2);
        Vector w(v);
        assert(w.size() == 2);
        assert(w[0] == 1 && w[1] == 2);
        w[0] = 99;
        assert(v[0] == 1);
    }
    {
        Vector v;
        v.push_back(7);
        Vector w(std::move(v));
        assert(w.size() == 1);
        assert(w[0] == 7);
        assert(v.size() == 0);
    }
    {
        Vector v; v.push_back(1);
        Vector w; w.push_back(2); w.push_back(3);
        v = w;
        assert(v.size() == 2);
        v = std::move(w);
        assert(v.size() == 2);
    }
    return 0;
}
