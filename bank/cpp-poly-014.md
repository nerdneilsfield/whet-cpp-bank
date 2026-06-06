---
qid: cpp-poly-014
type: single
kp: [cpp-polymorphism]
difficulty: easy
answer_key: B
---

# 以下代码有什么问题？

```cpp
struct Base {
    ~Base() { }         // 非 virtual 析构函数
};
struct Derived : Base {
    int* data;
    Derived() { data = new int[100]; }
    ~Derived() { delete[] data; }
};
int main() {
    Base* p = new Derived();
    delete p;           // 通过基类指针 delete
}
```

A. 代码完全正确，析构链会自动调用  
B. 未定义行为：`~Derived()` 不会被调用，`data` 内存泄漏  
C. 编译错误：基类析构函数必须是 `virtual`  
D. 运行时会调用 `~Derived()`，因为 C++ 析构链是自动的
