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

## 解析

正确答案是 B，因为该选项对应 `未定义行为：`~Derived()` 不会被调用，`data` 内存泄漏`，符合题中代码或概念的 C++ 语义。多态题的关键是区分静态类型与动态类型：只有通过基类指针或引用调用虚函数时，才会发生运行期动态分派。常见误区是把普通成员函数、对象切片、构造/析构期调用也当成完整的虚调用场景。 A 项、C 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
