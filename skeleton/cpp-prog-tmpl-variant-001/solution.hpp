#pragma once
#include <cstddef>
#include <new>
#include <type_traits>
#include <utility>

template <typename T1, typename T2>
class Variant {
    static constexpr std::size_t SZ = sizeof(T1) > sizeof(T2) ? sizeof(T1) : sizeof(T2);
    static constexpr std::size_t AL = alignof(T1) > alignof(T2) ? alignof(T1) : alignof(T2);
    alignas(AL) unsigned char storage_[SZ];
    int tag_;
public:
    Variant() : tag_(0) { ::new (storage_) T1(); }
    Variant(const T1& v) : tag_(0) { ::new (storage_) T1(v); }
    Variant(const T2& v) : tag_(1) { ::new (storage_) T2(v); }
    Variant(T1&& v) : tag_(0) { ::new (storage_) T1(std::move(v)); }
    Variant(T2&& v) : tag_(1) { ::new (storage_) T2(std::move(v)); }
    ~Variant() {
        if (tag_ == 0) reinterpret_cast<T1*>(storage_)->~T1();
        else reinterpret_cast<T2*>(storage_)->~T2();
    }
    Variant(const Variant& o) : tag_(o.tag_) {
        if (tag_ == 0) ::new (storage_) T1(*reinterpret_cast<const T1*>(o.storage_));
        else ::new (storage_) T2(*reinterpret_cast<const T2*>(o.storage_));
    }
    Variant(Variant&& o) noexcept : tag_(o.tag_) {
        if (tag_ == 0) ::new (storage_) T1(std::move(*reinterpret_cast<T1*>(o.storage_)));
        else ::new (storage_) T2(std::move(*reinterpret_cast<T2*>(o.storage_)));
    }
    int type_tag() const noexcept { return tag_; }
    template <typename Visitor>
    decltype(auto) visit(Visitor&& vis) {
        if (tag_ == 0) return std::forward<Visitor>(vis)(*reinterpret_cast<T1*>(storage_));
        return std::forward<Visitor>(vis)(*reinterpret_cast<T2*>(storage_));
    }
    template <typename Visitor>
    decltype(auto) visit(Visitor&& vis) const {
        if (tag_ == 0) return std::forward<Visitor>(vis)(*reinterpret_cast<const T1*>(storage_));
        return std::forward<Visitor>(vis)(*reinterpret_cast<const T2*>(storage_));
    }
};
