#pragma once
#include <cstddef>

template <class... Ts>
struct MyTuple;

template <>
struct MyTuple<> {};

template <class Head, class... Tail>
struct MyTuple<Head, Tail...> {
    Head head;
    MyTuple<Tail...> tail;
    MyTuple() = default;
    MyTuple(Head h, Tail... t) : head(h), tail(t...) {}
};

// TODO: implement get<I>
template <std::size_t I, class Head, class... Tail>
struct TupleGetter {
    static auto& apply(MyTuple<Head, Tail...>& t) {
        return TupleGetter<I-1, Tail...>::apply(t.tail);
    }
};

template <class Head, class... Tail>
struct TupleGetter<0, Head, Tail...> {
    static auto& apply(MyTuple<Head, Tail...>& t) {
        return t.head;
    }
};

template <std::size_t I, class... Ts>
inline auto& get(MyTuple<Ts...>& t) {
    return TupleGetter<I, Ts...>::apply(t);
}
