---
qid: cpp-cast-014
type: fill
kp: [cpp-casting]
difficulty: easy
answer_key: "抛出 std::bad_cast 异常"
---

# dynamic_cast 引用失败

```cpp
struct Base { virtual ~Base() {} };
struct Derived : Base {};
struct Other   : Base {};

int main() {
    Derived d;
    Base& b = d;
    Other& o = dynamic_cast<Other&>(b);  // 此行
}
```

"此行" 会发生什么？___
