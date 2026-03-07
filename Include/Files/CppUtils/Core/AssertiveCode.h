// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CppUtils/Core/Concepts.h>

namespace CppUtils
{
    /**
     * @brief Dereferences with an assertion that it can convert to a true boolean before doing so.
     * @todo @Christian: [todo][assert] Maybe make the assertion message customizable by the caller via a default argument.
     */
    template <CppUtils::Dereferenceable T>
    constexpr decltype(auto) DerefAsserted(T&& param);
}

#include <CppUtils/Core/AssertiveCode.inl>
