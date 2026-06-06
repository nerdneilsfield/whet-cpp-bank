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
