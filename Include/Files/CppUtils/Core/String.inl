// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CppUtils/Core/String.h>

#include <locale>
#include <CppUtils/Core/Math.h>

template <CppUtils::CharLike TChar, class TTraits>
bool CppUtils::HasLeadingWhitespace(std::basic_string_view<TChar, TTraits> sourceString)
{
    return !sourceString.empty() && std::isspace(sourceString.front());
}

template <CppUtils::CharLike TChar, class TTraits>
bool CppUtils::HasTrailingWhitespace(std::basic_string_view<TChar, TTraits> sourceString)
{
    return !sourceString.empty() && std::isspace(sourceString.back());
}

template <CppUtils::CharLike TChar, class TTraits>
std::basic_string_view<TChar, TTraits> CppUtils::TrimLeadingWhitespace(std::basic_string_view<TChar, TTraits> sourceString)
{
    return TrimLeadingWhitespace(std::span{sourceString.data(), sourceString.size()});
}

template <CppUtils::CharLike TChar, class TTraits>
std::basic_string_view<TChar, TTraits> CppUtils::TrimTrailingWhitespace(std::basic_string_view<TChar, TTraits> sourceString)
{
    return TrimTrailingWhitespace(std::span{sourceString.data(), sourceString.size()});
}

template <CppUtils::CharLike TChar>
std::span<TChar> CppUtils::TrimLeadingWhitespace(std::span<TChar> sourceString)
{
    return sourceString.subspan(GetTrimmedLeadingWhitespaceStartPos(sourceString));
}

template <CppUtils::CharLike TChar>
std::span<TChar> CppUtils::TrimTrailingWhitespace(std::span<TChar> sourceString)
{
    return sourceString.subspan(0u, GetTrimmedTrailingWhitespaceSize(sourceString));
}

template <CppUtils::CharLike TChar, class TTraits>
std::size_t CppUtils::GetTrimmedLeadingWhitespaceStartPos(std::basic_string_view<TChar, TTraits> sourceString)
{
    return GetTrimmedLeadingWhitespaceStartPos(std::span{sourceString.data(), sourceString.size()});
}

template <CppUtils::CharLike TChar, class TTraits>
std::size_t CppUtils::GetTrimmedTrailingWhitespaceSize(std::basic_string_view<TChar, TTraits> sourceString)
{
    return GetTrimmedTrailingWhitespaceSize(std::span{sourceString.data(), sourceString.size()});
}

template <CppUtils::CharLike TChar>
std::size_t CppUtils::GetTrimmedLeadingWhitespaceStartPos(std::span<TChar> sourceString)
{
    for (std::size_t pos = 0u; pos < sourceString.size(); ++pos)
    {
        if (!std::isspace(sourceString[pos]))
        {
            return pos;
        }
    }

    return sourceString.size();
}

template <CppUtils::CharLike TChar>
std::size_t CppUtils::GetTrimmedTrailingWhitespaceSize(std::span<TChar> sourceString)
{
    for (std::size_t pos = sourceString.size() - 1; pos >= 0u; --pos)
    {
        if (!std::isspace(sourceString[pos]))
        {
            return pos;
        }
    }

    return 0u;
}

template <CppUtils::CharLike TChar, class TTraits>
std::span<const TChar> CppUtils::MakeSpanFromStringView(const std::basic_string_view<TChar, TTraits>& stringView)
{
    return std::span<const TChar>(stringView.data(), stringView.length());
}

template <CppUtils::CharLike TChar, class TTraits>
std::basic_string_view<TChar, TTraits> CppUtils::MakeStringViewFromSpan(const std::span<TChar>& charSpan)
{
    return std::basic_string_view<TChar, TTraits>(charSpan.data(), charSpan.size());
}

template <CppUtils::CharLike TChar, class TTraits, class TAllocator>
std::basic_string_view<TChar, TTraits> CppUtils::MakeStringView(const std::basic_string<TChar, TTraits, TAllocator>& fromString)
{
    return std::basic_string_view<TChar, TTraits>(fromString);
}

template <StdReimpl::integral TInteger>
consteval std::size_t CppUtils::GetIntegerStringMaxSizeDec(TInteger)
{
    std::size_t numDigitsOfMaxValue = CppUtils::CountNumDigitsDec(std::numeric_limits<TInteger>::max());

    if constexpr (std::is_signed_v<TInteger>)
    {
        // In a special case of signed integers, make room for the sign as a character.
        return numDigitsOfMaxValue + 1u;
    }
    else
    {
        return numDigitsOfMaxValue;
    }
}
