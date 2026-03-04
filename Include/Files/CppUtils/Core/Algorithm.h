// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <algorithm>
#include <cstddef>

namespace CppUtils
{
    /**
     * @brief An index that represents a not-found result in an algorithm.
     * @note This can also be written as `std::numeric_limits<std::size_t>::max()`.
     */
    constexpr std::size_t npos = static_cast<std::size_t>(-1);

    // @Christian: TODO: [todo][std][concepts] Add constraints to the iterater type template parameters. We'd have to
    // reimplement the iterator concepts in StdReimpl to do this.

    /**
     * @brief Uses the `find` algorithms along with `distance` to return the index of the found value. Returns npos if not found.
     */
    template <class InputIt, class T>
    constexpr std::size_t index_find(InputIt first, InputIt last, const T& value);

    template <class InputIt, class UnaryPred>
    constexpr std::size_t index_find_if(InputIt first, InputIt last, UnaryPred p);

    template <class InputIt, class UnaryPred>
    constexpr std::size_t index_find_if_not(InputIt first, InputIt last, UnaryPred q);

    /**
     * @brief Uses the `find` algorithms along with `distance` to return the distance to the found value.
     */
    template <class InputIt, class T>
    constexpr std::ptrdiff_t distance_find(InputIt first, InputIt last, const T& value);

    template <class InputIt, class UnaryPred>
    constexpr std::ptrdiff_t distance_find_if(InputIt first, InputIt last, UnaryPred p);

    template <class InputIt, class UnaryPred>
    constexpr std::ptrdiff_t distance_find_if_not(InputIt first, InputIt last, UnaryPred q);
}

#include <CppUtils/Core/Algorithm.inl>
