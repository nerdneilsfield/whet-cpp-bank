---
qid: cpp-cross-tc-002
type: single
kp: [cpp-templates, cpp-containers]
difficulty: easy
answer_key: C
---

以下代码输出是什么？

```cpp
#include <iostream>
#include <stack>

template<typename T>
class Stack {
    std::stack<T> s_;
public:
    void push(T val) { s_.push(val); }
    T top() const   { return s_.top(); }
    bool empty() const { return s_.empty(); }
};

int main() {
    Stack<int> si;
    si.push(10);
    si.push(20);
    si.push(30);
    std::cout << si.top() << "\n";

    Stack<std::string> ss;
    ss.push("hello");
    ss.push("world");
    std::cout << ss.top() << "\n";
    return 0;
}
```

A. `10\nhello\n`  
B. `10\nworld\n`  
C. `30\nworld\n`  
D. `30\nhello\n`

<!--
std::stack 是 LIFO，top() 返回最后压入的元素。
Stack<int>：依次 push 10、20、30，top 为 30。
Stack<std::string>：依次 push "hello"、"world"，top 为 "world"。
-->
