// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CppUtils/StdReimpl/concepts.h>

namespace CppUtils
{
    template <StdReimpl::signed_integral TInteger>
    constexpr unsigned int CountNumDigits(TInteger number, unsigned int base);

    template <StdReimpl::unsigned_integral TInteger>
    constexpr unsigned int CountNumDigits(TInteger number, unsigned int base);

    namespace NumberSystemBases
    {
        constexpr unsigned int Decimal = 10u;
        constexpr unsigned int Hexadecimal = 16u;
        constexpr unsigned int Binary = 2u;
    }

    template <StdReimpl::integral TInteger>
    constexpr unsigned int CountNumDigitsDec(TInteger number)
    {
        return CountNumDigits(number, NumberSystemBases::Decimal);
    }

    template <StdReimpl::integral TInteger>
    constexpr unsigned int CountNumDigitsHex(TInteger number)
    {
        return CountNumDigits(number, NumberSystemBases::Hexadecimal);
    }

    template <StdReimpl::integral TInteger>
    constexpr unsigned int CountNumDigitsBin(TInteger number)
    {
        return CountNumDigits(number, NumberSystemBases::Binary);
    }
}

#include <CppUtils/Core/Math.inl>
