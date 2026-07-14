// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CppUtils/Core/Bit.h>

template <class T>
consteval std::size_t CppUtils::BitSizeOf() noexcept
{
    return sizeof(T) * NumBitsPerByte;
}
