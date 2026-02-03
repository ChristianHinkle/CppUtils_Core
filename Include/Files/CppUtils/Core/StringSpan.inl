// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CppUtils/Core/StringSpan.h>

namespace CppUtils::Detail
{
    template <class T>
    struct StringSpanTrait
    {
        // This is the primary template with value defaulted to false.
        enum
        {
            value = false
        };
    };

    template <CppUtils::CharLike TChar, class TTraits>
    struct StringSpanTrait<CppUtils::StringSpan<TChar, TTraits>>
    {
        // This is a partial specialization for the true case.
        enum
        {
            value = true
        };
    };
}

template <class T>
consteval bool CppUtils::IsStringSpan()
{
    return CppUtils::Detail::StringSpanTrait<T>::value;
}
