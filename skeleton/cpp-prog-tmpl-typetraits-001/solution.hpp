#pragma once

// TODO: implement my_is_same
template <class T, class U>
struct my_is_same {
    static constexpr bool value = false;
};

// TODO: implement my_remove_const
template <class T>
struct my_remove_const {
    using type = T;
};
