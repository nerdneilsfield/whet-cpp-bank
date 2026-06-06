#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    assert((my_is_same<int,int>::value));
    assert(!(my_is_same<int,long>::value));
    assert(!(my_is_same<int,const int>::value));
    assert((my_is_same<my_remove_const<const int>::type, int>::value));
    assert((my_is_same<my_remove_const<int>::type, int>::value));
    assert(!(my_is_same<my_remove_const<const int*>::type, int*>::value));
    return 0;
}
