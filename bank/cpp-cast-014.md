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

## Explanation

答案是抛出 `std::bad_cast` 异常。引用类型没有 `nullptr` 这样的失败返回值，因此 `dynamic_cast<Other&>(b)` 在运行时发现对象实际不是 `Other` 时只能抛异常。对指针版本才是返回 `nullptr`。
