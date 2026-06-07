// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CppUtils_Core_Export.h>
#include <variant>
#include <utility>

namespace CppUtils
{
    /**
     * @brief A poor man's C++23 `std::expected` alternative.
     */
    template <class T, class TError>
    struct ExpectedResult
    {
    public:
        ExpectedResult(const T& value)
            : ValueOrErrorVariant{value}
        {
        }
        ExpectedResult(T&& value)
            : ValueOrErrorVariant{std::move(value)}
        {
        }
        ExpectedResult(const TError& error)
            : ValueOrErrorVariant{error}
        {
        }
        ExpectedResult(TError&& error)
            : ValueOrErrorVariant{std::move(error)}
        {
        }

    public:
        bool IsError() const
        {
            return ValueOrErrorVariant.index() != 0u;
        }

        const TError& GetError() const &
        {
            assert(IsError());
            return std::get<TError>(ValueOrErrorVariant);
        }
        TError&& GetError() &&
        {
            TError& result = const_cast<TError&>(
                const_cast<const ExpectedResult&>(*this).GetError()
            );

            return std::move(result);
        }

        const T& GetValue() const &
        {
            assert(!IsError());
            return std::get<T>(ValueOrErrorVariant);
        }
        T&& GetValue() &&
        {
            T& result = const_cast<T&>(
                const_cast<const ExpectedResult&>(*this).GetValue()
            );

            return std::move(result);
        }

    private:
        std::variant<T, TError> ValueOrErrorVariant;
    };
}
