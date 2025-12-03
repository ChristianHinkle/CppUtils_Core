// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#include <CppUtils_Core.h>

#include <limits>
#include <cmath>
#include <CppUtils_Concepts/Std.h>

namespace
{
    template <CppUtils::Concepts::Std::floating_point TFloat>
    TFloat IeeeDivideInternal(TFloat dividend, TFloat divisor);
}

float CppUtils::Core::IeeeDivide(float dividend, float divisor)
{
    return IeeeDivideInternal(dividend, divisor);
}

double CppUtils::Core::IeeeDivide(double dividend, double divisor)
{
    return IeeeDivideInternal(dividend, divisor);
}

long double CppUtils::Core::IeeeDivide(long double dividend, long double divisor)
{
    return IeeeDivideInternal(dividend, divisor);
}

namespace
{
    template <CppUtils::Concepts::Std::floating_point TFloat>
    TFloat IeeeDivideInternal(TFloat dividend, TFloat divisor)
    {
        // Note: Although we don't explicitly check for NaNs, we are correctly abiding by
        // the NaNs-always-propagate rule, as each of the following return cases will naturally
        // propagate potential NaN values from our parameters.

        static_assert(-0.f == 0.f, "I believe equality of opposite-signed zeroes is standardized, but let's make sure.");

        if (divisor == 0)
        {
            // If both the divisor and dividend are zero values, return a NaN.
            if (dividend == 0)
            {
                return std::numeric_limits<TFloat>::quiet_NaN();
            }

            // If the divisor is +0, return inf with the original sign of the dividend.
            // If the divisor is -0, return inf with the opposite sign of the dividend.
            return std::copysign(
                std::numeric_limits<TFloat>::infinity(),
                dividend * std::copysign(1, divisor));
        }

        if (std::isinf(divisor))
        {
            // If both the divisor and dividend are inf values, return a NaN.
            if (std::isinf(dividend))
            {
                return std::numeric_limits<TFloat>::quiet_NaN();
            }

            // If the divisor is +inf, return 0 with the original sign of the dividend.
            // If the divisor is -inf, return 0 with the opposite sign of the dividend.
            return std::copysign(
                static_cast<TFloat>(0),
                dividend * std::copysign(1, divisor));
        }

        return dividend / divisor;
    }
}
