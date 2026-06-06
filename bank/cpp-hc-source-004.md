---
qid: cpp-hc-source-004
type: single
kp: [cpp-concurrency, cpp-memory-mgmt]
primary_kp: cpp-concurrency
difficulty: hard
answer_key: A
tags: [interview-real, handcrafted, source-reading]
---
查看 libstdc++ 在 GCC 13 的 `std::shared_ptr` 复制构造路径（核心两行）：

```cpp
template<typename _Tp1>
__shared_ptr(const __shared_ptr<_Tp1>& __r) noexcept
: _M_ptr(__r._M_ptr), _M_refcount(__r._M_refcount)  // 这一行
{ }

// __shared_count 构造函数
__shared_count(const __shared_count& __r) noexcept
: _M_pi(__r._M_pi)
{
    if (_M_pi != 0)
        _M_pi->_M_add_ref_copy();   // ← 这里
}

void _M_add_ref_copy() {
    __gnu_cxx::__atomic_add_dispatch(&_M_use_count, 1);
}
```

注意 `_M_add_ref_copy` 用的是普通的 atomic add，使用 **memory_order_relaxed**（在内部实现）。为什么**复制 shared_ptr 时引用计数 +1 可以用 relaxed**，而**销毁 shared_ptr 时引用计数 -1 必须用 acquire+release（或 acq_rel）**？

A. 拷贝时调用方已持有源 shared_ptr，对源的 happens-before 保证已存在；只需保证原子性。销毁时必须确保最后一个释放者看到所有先前线程对对象的修改（acquire），且自己对对象的修改对析构线程可见（release）
B. 拷贝是创建动作不涉及对象访问；销毁会调用析构函数，析构函数本身需要同步
C. relaxed 比 acq_rel 快 10 倍以上，编译器要尽可能用 relaxed
D. 标准规定的，没有特别原因

---

**解析：**

选 A。这是 boost::shared_ptr 的作者 Peter Dimov 在 2008 年的经典论证，后来被所有主流实现采用。

**拷贝（+1）只需 relaxed**：

调用 `shared_ptr<T> b = a;` 时，调用方**已经持有 `a`**。要持有 a 必然之前已经通过某种同步（构造、赋值、参数传递）建立了 happens-before 关系。这意味着对象本身的状态对当前线程已经可见，**不需要再用 acquire**。当前线程也不会修改对象，所以**也不需要 release**。引用计数 +1 只需保证原子性（relaxed 即可）。

**销毁（-1）必须 acq_rel**：

调用 `~shared_ptr()` 时：

```
线程 A (持有最后引用):          线程 B (之前持有的引用已释放):
write to *p                     write to *p
~shared_ptr (refcount -1)      ~shared_ptr (refcount -1)
                                if counter == 0:
                                    delete p   ← 析构访问对象
```

- 线程 B 在调用析构函数前，需要**看见 A 对对象的所有修改**——需要 **acquire** 才能读到最新值
- 线程 A 在 -1 之前对对象的修改，需要**对 B 的析构可见**——需要 **release**

合起来就是 acq_rel。

实际 libstdc++ 用了一个轻微的优化：递减用 `release`，归零后再用一次 `acquire` 屏障再调析构。逻辑上等价于 acq_rel，但避免每次都付 acquire 代价（多数次 -1 时计数都没归零）。

```cpp
// 简化版
if (atomic_dec(&count, memory_order_release) == 1) {
    atomic_thread_fence(memory_order_acquire);
    delete ptr;
}
```

这个优化把多数路径降为 release-only。性能差异在高并发的 shared_ptr 上能实测出来。

B 不准确——拷贝时确实不访问对象，但论证不完整；析构需要同步是因为 happens-before 链，不是"析构函数本身"需要。C 是流言——relaxed 比 acq_rel 在 x86 上完全一样（都是 mov），在 ARM 上 acquire 只多一个 dmb ish 指令，差别远没 10x。D 是回避问题。

**来源：** 手写题，源参考 libstdc++ `bits/shared_ptr_base.h::_M_add_ref_copy` 与 `_M_release`；Peter Dimov 在 boost mailing list 的论证（2008）和 Hans Boehm 的 paper "Atomic Operations Library"。

## Explanation

正确答案是 A。这是 boost::shared_ptr 的作者 Peter Dimov 在 2008 年的经典论证，后来被所有主流实现采用。
要持有 a 必然之前已经通过某种同步（构造、赋值、参数传递）建立了 happens-before 关系。
B 不准确——拷贝时确实不访问对象，但论证不完整；析构需要同步是因为 happens-before 链，不是"析构函数本身"需要。
