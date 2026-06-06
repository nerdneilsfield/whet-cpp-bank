#pragma once
#include <utility>
#include <type_traits>

template <std::size_t I, typename T>
struct TupleLeaf {
    T value;
    TupleLeaf() = default;
    TupleLeaf(const T& v) : value(v) {}
    TupleLeaf(T&& v) : value(std::move(v)) {}
};

template <std::size_t I, typename... Types>
struct TupleImpl;

template <std::size_t I, typename T, typename... Rest>
struct TupleImpl<I, T, Rest...> : TupleLeaf<I, T>, TupleImpl<I+1, Rest...> {
    TupleImpl() = default;
    TupleImpl(const T& v, const Rest&... rest)
        : TupleLeaf<I, T>(v), TupleImpl<I+1, Rest...>(rest...) {}
};

template <std::size_t I>
struct TupleImpl<I> {};

template <typename... Types>
class Tuple : public TupleImpl<0, Types...> {
public:
    Tuple() = default;
    Tuple(const Types&... args) : TupleImpl<0, Types...>(args...) {}
};

template <std::size_t I, typename T>
T& get(TupleLeaf<I, T>& leaf) { return leaf.value; }

template <std::size_t I, typename T>
const T& get(const TupleLeaf<I, T>& leaf) { return leaf.value; }

template <std::size_t I, typename T>
T&& get(TupleLeaf<I, T>&& leaf) { return std::move(leaf.value); }
