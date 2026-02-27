// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <type_traits>
#include <CppUtils/StdReimpl/concepts.h>

namespace CppUtils
{
    template <class T>
    concept Pointer = std::is_pointer_v<T>;

    template <class T>
    concept Reference = std::is_reference_v<T>;

    template <class T>
    concept LvalueReference = std::is_lvalue_reference_v<T>;

    template <class T>
    concept RvalueReference = std::is_rvalue_reference_v<T>;

    /**
     * @brief Concept satisfied by types that are not lvalue references. This is a useful constraint for
     *        being able to have an rvalue-reference function parameter to a template-argument type
     *        without the possibility of an lvalue reference being used in that forwarding reference.
     */
    template <class T>
    concept NonLvalueReference = !LvalueReference<T>;

    template <class T, class TBase>
    concept PointerToDerivedFrom = Pointer<T> && StdReimpl::derived_from<std::remove_pointer_t<T>, TBase>;

    template <class T, class TBase>
    concept ReferenceToDerivedFrom = Reference<T> && StdReimpl::derived_from<std::remove_reference_t<T>, TBase>;

    /**
     * @brief A concept implementing the standard's definition of what "char-like types" are. Currently based on
     *        the C++26 standard.
     * @see https://eel.is/c++draft/strings#general-1
     * @see https://cppreference.com/w/cpp/string.html#Characters
     * @see https://cppevo.dev/diffs/cpp23-to-trunk/strings.general
     */
    template <class T>
    concept CharLike =
        // "non-array trivially copyable standard-layout type T"
        !std::is_array_v<T>
        && std::is_trivially_copyable_v<T>
        && std::is_standard_layout_v<T>
        // "where is_trivially_default_constructible_v<T> is true"
        && std::is_trivially_default_constructible_v<T>;

    template <class T>
    concept Enum = std::is_enum_v<T>;
}
