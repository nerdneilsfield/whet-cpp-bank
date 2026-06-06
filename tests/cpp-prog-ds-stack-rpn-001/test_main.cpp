#include "../skeleton/solution.hpp"
#include <cassert>
int main(){
    assert(evalRPN({"2","1","+","3","*"}) == 9);
    assert(evalRPN({"4","13","5","/","+"}) == 6);
    assert(evalRPN({"10","6","9","3","+","-11","*","/","*","17","+","5","+"}) == 22);
    assert(evalRPN({"3","-4","+"}) == -1);
    assert(evalRPN({"5"}) == 5);
    return 0;
}
