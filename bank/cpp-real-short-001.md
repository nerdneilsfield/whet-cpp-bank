---
qid: cpp-real-short-001
type: short
kp: [cpp-memory-mgmt, cpp-cpp11]
primary_kp: cpp-memory-mgmt
difficulty: hard
tags: [interview-real, tencent]
rubric:
  - 引用计数用指针在堆上分配，所有 shared_ptr 实例共享同一计数（1 分）
  - 拷贝构造：拷贝 ptr 和 count，++(*count)（1 分）
  - 拷贝赋值：先检查自赋值，再 release()，再拷贝并 ++(*count)（1 分）
  - 析构：release() 中 --(*count)==0 时 delete ptr 和 count（1 分）
  - operator-> 和 operator* 正确实现（1 分）
---
手写一个简化的 `shared_ptr` 模板类，要求至少包含以下核心功能：

1. 指针存储 + 引用计数（整型指针）
2. 构造函数（接收原始指针）
3. 拷贝构造函数（增加引用计数）
4. 拷贝赋值运算符（先释放旧资源，再拷贝新资源）
5. 析构函数（减少引用计数，归零时释放对象和计数）
6. `operator->` 和 `operator*`

**rubric (5 分)：**
- [  ] 引用计数用指针在堆上分配，所有 shared_ptr 实例共享同一计数（1 分）
- [  ] 拷贝构造：拷贝 ptr 和 count，++(*count)（1 分）
- [  ] 拷贝赋值：先检查自赋值，再 release()，再拷贝并 ++(*count)（1 分）
- [  ] 析构：release() 中 --(*count)==0 时 delete ptr 和 count（1 分）
- [  ] operator-> 和 operator* 正确实现（1 分）

**期望答案：**
```cpp
template<typename T>
class SharedPtr {
    T* ptr_;
    int* count_;
    
    void release() {
        if (count_ && --(*count_) == 0) {
            delete ptr_;
            delete count_;
        }
    }
public:
    explicit SharedPtr(T* p = nullptr) : ptr_(p), count_(p ? new int(1) : nullptr) {}
    
    SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), count_(other.count_) {
        if (count_) ++(*count_);
    }
    
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            count_ = other.count_;
            if (count_) ++(*count_);
        }
        return *this;
    }
    
    ~SharedPtr() { release(); }
    
    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
    int use_count() const { return count_ ? *count_ : 0; }
};
```

**加分扩展：**
- 为什么不用 `count_` 做原子加减？（面试追问：多线程场景需要 atomic）
- `make_shared` 怎么做一次分配？（把对象和 control block 放在同一块内存）
- weak_ptr 如何实现？（增加 weak_count，lock() 时 check ref_count）

**来源：** 腾讯/字节智能指针手写题

## Explanation

本题评分重点是资源所有权、共享引用计数和拷贝控制：计数必须在堆上由所有副本共享，拷贝构造和拷贝赋值要正确递增计数。赋值运算符必须处理自赋值并先 release 旧资源，析构时在计数减到 0 后同时释放对象和计数。operator* 与 operator-> 只需提供底层指针语义。常见误区是把引用计数做成普通成员导致每个副本各算各的，或浅拷贝后重复 delete。
