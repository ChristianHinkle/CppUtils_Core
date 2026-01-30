// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CppUtils/StdReimpl/Concepts.h>
#include <utility>
#include <type_traits>
#include <string>
#include <span>
#include <iterator>

namespace CppUtils
{
    /**
     * @note Constructor and assignment rules mirror `std::basic_string_view`. See https://eel.is/c++draft/string.view.cons and https://en.cppreference.com/w/cpp/string/basic_string_view/basic_string_view.html.
     */
    template <class TChar, class TTraits = std::char_traits<TChar>>
    struct StringSpan
    {
    public:

        using SpanType = std::span<TChar>;
        using StringViewType = std::basic_string_view<TChar, TTraits>;

    public:

        constexpr StringSpan() noexcept = default;
        constexpr StringSpan(const StringSpan& other) noexcept = default;
        constexpr StringSpan& operator=(const StringSpan& other) noexcept = default;

        constexpr StringSpan(TChar* data)
            : CharSpan(data, TTraits::length(data))
        {
        }

        constexpr StringSpan(TChar* data, std::size_t len)
            : CharSpan(data, len)
        {
        }

        template <class It, class End>
        constexpr StringSpan(It begin, End end)
            : CharSpan(begin, end)
        {
        }

    public:

        SpanType& GetSpan()
        {
            return CharSpan;
        }

        StringViewType ToStringView() const
        {
            return {CharSpan.data(), CharSpan.size()};
        }

    private:

        SpanType CharSpan;
    };

    /**
     * @brief Deduction guide that mirrors behavior of `std::basic_string_view`. See https://eel.is/c++draft/string.view.deduct.
     * @todo @Christian: TODO: [todo][techdebt] Use concepts to constrain the template parameters here. We would have to use
     *       concepts from the StdReimpl library that reimplement the iterator concepts. See https://eel.is/c++draft/iterator.concepts.
     */
    template <class _Iter, class _Sent>
    StringSpan(_Iter, _Sent) -> StringSpan<std::iter_value_t<_Iter>>;
}
