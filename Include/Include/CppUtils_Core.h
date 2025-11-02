// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CppUtils_Concepts.h>

namespace CppUtils::Core
{
    /**
     * @brief Materialize a prvalue to a temporary and get an lvalue reference to it.
     * @tparam T Type of temporary to materialize. Automatically deduced but may be specified
     *         manually in order to implicitly convert the prvalue to another type.
     * @param inTemporary The caller's prvalue argument materialized to temporary.
     * @return Lvalue reference to the temporary.
     */
    template <CppUtils::Concepts::NonLvalueReference T>
    T& Materialize(T&& inTemporary);
}

template <CppUtils::Concepts::NonLvalueReference T>
T& CppUtils::Core::Materialize(T&& inTemporary)
{
    // Note that the temporary gets promoted to an lvalue for the scope of this function. It
    // will revert to its original lifetime of temporary when this function is exited.
    return static_cast<T&>(inTemporary);
}
