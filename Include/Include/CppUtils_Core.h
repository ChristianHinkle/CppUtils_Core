// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CppUtils/Core/Concepts.h>
#include <CppUtils/StdReimpl/Concepts.h>

namespace CppUtils
{
    /**
     * @brief Materialize a prvalue to a temporary and get an lvalue reference to it.
     * @tparam T Type of temporary to materialize. Automatically deduced but may be specified
     *         manually in order to implicitly convert the prvalue to another type.
     * @param inTemporary The caller's prvalue argument materialized to temporary.
     * @return Lvalue reference to the temporary.
     */
    template <CppUtils::NonLvalueReference T>
    constexpr T& Materialize(T&& inTemporary);

    /**
     * @brief A software implementation of the IEEE 754 standard's divide operation to support special
     *        cases like NaN and inf values.
     * @todo @Christian TODO: [todo][cpp] Convert this to a constexpr function, as it is basic arithmetic. There are
     *       two options for this: either (1) make our own `constexpr` versions of the `std` functions that aren't
     *       constexpr yet, or (2) wait for C++23 which will make many of the `std` functions `constexpr`. I'm just going
     *       to wait for C++23 support, unless we really need to have this for some reason.
     */
    template <StdReimpl::floating_point TFloat>
    TFloat IeeeDivide(TFloat dividend, TFloat divisor);
}

#include <CppUtils_Core.inl>
