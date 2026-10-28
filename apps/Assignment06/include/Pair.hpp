#pragma once
#include <compare>
#include <utility>

template <typename Key, typename Value>
struct Pair
{
    Key first;
    Value second;

    // C++20 generates the normal comparison operators.
    auto operator<=>(const Pair& rhs) const = default;
};
