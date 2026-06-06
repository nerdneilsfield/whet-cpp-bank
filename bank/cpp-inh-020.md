---
qid: cpp-inh-020
type: multi
kp: [cpp-inheritance]
difficulty: easy
answer_key: [B, C]
---

以下代码中，哪些语句能编译通过？

```cpp
struct Animal {
protected:
    int age = 3;
public:
    int id = 1;
};
struct Dog : public Animal {
    void show() {
        std::cout << age;  // (X)
        std::cout << id;   // (Y)
    }
};

int main() {
    Dog d;
    std::cout << d.id;    // (A)
    std::cout << d.age;   // (B)  外部访问 protected
}
```

A. main 中 `d.age` 编译通过
B. `Dog::show()` 中访问 `age` 编译通过
C. `Dog::show()` 中访问 `id` 编译通过
D. main 中 `d.age` 和 `d.id` 都编译通过

## Explanation

本题正确答案是 B, C。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。A 项错误：“main 中 d.age 编译通过”与题干要求或 C++ 规则不符；B 项正确：“Dog::show() 中访问 age 编译通过”符合题干要求；C 项正确：“Dog::show() 中访问 id 编译通过”符合题干要求；D 项错误：“main 中 d.age 和 d.id 都编译通过”与题干要求或 C++ 规则不符。多选题常见误区是漏选同时成立的规则，或把只在特定上下文成立的说法当成普遍规则。
