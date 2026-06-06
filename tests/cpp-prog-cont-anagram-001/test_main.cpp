#include "../skeleton/solution.hpp"
#include <cassert>
#include <algorithm>
int main(){
    {
        auto r = group_anagrams({"eat","tea","tan","ate","nat","bat"});
        int total = 0;
        for (auto& g : r) total += g.size();
        assert(total == 6);
        assert(r.size()==3);
    }
    {
        auto r = group_anagrams({});
        assert(r.empty());
    }
    {
        auto r = group_anagrams({"a"});
        assert(r.size()==1 && r[0].size()==1 && r[0][0]=="a");
    }
    {
        auto r = group_anagrams({"abc","bca","xyz"});
        assert(r.size()==2);
    }
    return 0;
}
