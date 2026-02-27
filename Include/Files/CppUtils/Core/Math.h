// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CppUtils/StdReimpl/concepts.h>

namespace CppUtils
{
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
