---
qid: cpp-smf-r-002
type: single
kp: [cpp-special-members]
difficulty: easy
answer_key: "D"
---

## 题目

以下代码能否通过编译？

```cpp
struct NoCopy {
    NoCopy() = default;
    NoCopy(const NoCopy&) = delete;
};

void process(NoCopy nc) { }

int main() {
    NoCopy obj;
    process(obj);   // (1)
}
```

A. 能编译，正常运行
B. 能编译，但运行时崩溃
C. 能编译，触发移动构造
D. 编译错误，拷贝构造被删除

## 解析

`process` 按值接受参数，调用处 `process(obj)` 需要将 `obj` 拷贝构造为形参。`NoCopy` 的拷贝构造被 `= delete`，编译器报错：`use of deleted function 'NoCopy::NoCopy(const NoCopy&)'`。若想传递 `NoCopy`，必须改为引用传参或使用 `std::move`（前提是存在移动构造）。
