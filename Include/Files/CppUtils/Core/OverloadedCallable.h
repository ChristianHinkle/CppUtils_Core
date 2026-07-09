// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

namespace CppUtils
{
    /**
     * @brief A callable type holding multiple overloads of other callables. For convenient usage of `std::visit` with `std::variant` so that
     *        you can pass in several callbacks which are chosen automatically based on overload resolution of the variant's stored type.
     * @see https://cppreference.com/cpp/utility/variant/visit2
     */
    template <class... TCallables>
    struct OverloadedCallable : TCallables...
    {
        using TCallables::operator()...;
    };
}
