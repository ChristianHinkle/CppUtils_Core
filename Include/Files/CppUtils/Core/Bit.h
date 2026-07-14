// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <cstddef>
#include <limits>

namespace CppUtils
{
    /**
     * @brief Get the size of a type, in bits.
     */
    template <class T>
    consteval std::size_t BitSizeOf() noexcept;

    /**
     * @brief The number of bits per byte on this platform (typically eight).
     */
    constexpr std::size_t NumBitsPerByte = std::numeric_limits<unsigned char>::digits;
}

#include <CppUtils/Core/Bit.inl>
