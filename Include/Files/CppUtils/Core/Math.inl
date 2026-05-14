// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CppUtils/Core/Math.h>

#include <CppUtils/StdReimpl/cstdlib.h>
#include <type_traits>

template <StdReimpl::signed_integral TInteger>
constexpr unsigned int CppUtils::CountNumDigits(TInteger number, unsigned int base)
{
    return CountNumDigits(
        static_cast<std::make_unsigned_t<TInteger>>(StdReimpl::abs(number)),
        base);
}

template <StdReimpl::unsigned_integral TInteger>
constexpr unsigned int CppUtils::CountNumDigits(TInteger number, unsigned int base)
{
    unsigned int count = 0u;

    for (TInteger testNum = number; testNum > 0; testNum /= base)
    {
        ++count;
    }

    return count;
}
