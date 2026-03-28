// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CppUtils/Core/Filesystem.h>

#include <fstream>

template <CppUtils::CharLike TChar, class TCharTraits>
bool CppUtils::TouchNewFile(const std::basic_string_view<TChar, TCharTraits> path)
{
    std::ofstream fileStream = std::ofstream(path.data());
    fileStream.flush();
    fileStream.close();

    return !fileStream.fail();
}
