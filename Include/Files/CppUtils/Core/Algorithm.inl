// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CppUtils/Core/Algorithm.h>

#include <algorithm>
#include <utility>
#include <ranges>

template <class R, class T>
constexpr std::size_t CppUtils::index_find(R&& r, const T& value)
{
    return index_find(
        std::ranges::begin(r),
        std::ranges::end(r),
        value
    );
}

template <class R, class Pred>
constexpr std::size_t CppUtils::index_find_if(R&& r, Pred pred)
{
    return index_find_if(
        std::ranges::begin(r),
        std::ranges::end(r),
        std::move(pred)
    );
}

template <class R, class Pred>
constexpr std::size_t CppUtils::index_find_if_not(R&& r, Pred pred)
{
    return index_find_if_not(
        std::ranges::begin(r),
        std::ranges::end(r),
        std::move(pred)
    );
}

template <class InputIt, class T>
constexpr std::size_t CppUtils::index_find(InputIt first, InputIt last, const T& value)
{
    InputIt foundIt = std::find(first, last, value);
    if (foundIt == last)
    {
        return CppUtils::npos;
    }

    return std::distance(first, foundIt);
}

template <class InputIt, class UnaryPred>
constexpr std::size_t CppUtils::index_find_if(InputIt first, InputIt last, UnaryPred p)
{
    InputIt foundIt = std::find_if(first, last, std::move(p));
    if (foundIt == last)
    {
        return CppUtils::npos;
    }

    return std::distance(first, foundIt);
}

template <class InputIt, class UnaryPred>
constexpr std::size_t CppUtils::index_find_if_not(InputIt first, InputIt last, UnaryPred q)
{
    InputIt foundIt = std::find_if_not(first, last, std::move(q));
    if (foundIt == last)
    {
        return CppUtils::npos;
    }

    return std::distance(first, foundIt);
}

template <class R, class T>
constexpr std::ptrdiff_t CppUtils::distance_find(R&& r, const T& value)
{
    return distance_find(
        std::ranges::begin(r),
        std::ranges::end(r),
        value
    );
}

template <class R, class Pred>
constexpr std::ptrdiff_t CppUtils::distance_find_if(R&& r, Pred pred)
{
    return distance_find_if(
        std::ranges::begin(r),
        std::ranges::end(r),
        std::move(pred)
    );
}

template <class R, class Pred>
constexpr std::ptrdiff_t CppUtils::distance_find_if_not(R&& r, Pred pred)
{
    return distance_find_if_not(
        std::ranges::begin(r),
        std::ranges::end(r),
        std::move(pred)
    );
}

template <class InputIt, class T>
constexpr std::ptrdiff_t CppUtils::distance_find(InputIt first, InputIt last, const T& value)
{
    return std::distance(
        first,
        std::find(first, last, value)
    );
}

template <class InputIt, class UnaryPred>
constexpr std::ptrdiff_t CppUtils::distance_find_if(InputIt first, InputIt last, UnaryPred p)
{
    return std::distance(
        first,
        std::find_if(first, last, std::move(p))
    );
}

template <class InputIt, class UnaryPred>
constexpr std::ptrdiff_t CppUtils::distance_find_if_not(InputIt first, InputIt last, UnaryPred q)
{
    return std::distance(
        first,
        std::find_if_not(first, last, std::move(q))
    );
}
