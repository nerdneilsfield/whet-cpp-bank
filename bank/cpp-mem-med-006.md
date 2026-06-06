---
qid: cpp-mem-med-006
type: single
kp: [cpp-memory-mgmt]
difficulty: medium
answer_key: C
---

下列代码使用 `weak_ptr` 检测对象是否仍存活，正确的访问方式是？

```cpp
std::weak_ptr<Widget> wp = /* 来自某 shared_ptr */;

// 想安全访问 wp 指向的对象
```

A. 直接判断 `if (wp) wp->foo();`，`weak_ptr` 重载了 `operator bool`
B. 先 `if (!wp.expired()) wp.lock()->foo();`，先检查再解引用
C. `if (auto sp = wp.lock()) sp->foo();`，用 `lock()` 拿临时强引用并判空
D. 用 `*wp` 直接解引用，`weak_ptr` 会自动延长对象寿命

---

**解析：**

`weak_ptr` 不支持 `operator->`、`operator*`、`operator bool`（A、D 错），它只是观察者，不能直接访问对象。要访问对象必须先用 `lock()` 把它升级成临时 `shared_ptr`：

- 若对象还活着，`lock()` 返回非空 `shared_ptr`，访问期间引用计数 +1，对象不会在访问中途被销毁；
- 若对象已被销毁（强引用计数归零），`lock()` 返回空 `shared_ptr`。

B 的写法 `expired()` + `lock()` 看似合理，但**两步之间存在 TOCTOU 竞态**：多线程下另一线程可能在 `expired()` 返回 false 后立刻销毁对象，导致后续 `lock()->foo()` 解引用空指针。正确做法（C）是直接 `lock()` 然后判断结果——原子地拿到强引用或拿到空指针。`expired()` 只适合做近似统计或不需要后续访问的场景。

## 解析

正确答案是 C，`weak_ptr` 不能直接解引用，必须用 `lock()` 尝试获取临时 `shared_ptr`。`if (auto sp = wp.lock())` 同时完成检查和延长生命周期，访问期间对象不会被销毁。先 `expired()` 再 `lock()` 有竞态窗口，多线程下检查后对象可能马上被释放。
