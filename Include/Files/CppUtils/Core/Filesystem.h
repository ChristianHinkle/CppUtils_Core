// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CppUtils_Core_Export.h>
#include <filesystem>
#include <string_view>
#include <string>
#include <CppUtils/Core/Concepts.h>

/**
 * @brief String literal alternative to `CppUtils::PrettyPathSeparator`.
 */
#define CPPUTILS_PRETTY_PATH_SEPARATOR '/'

/**
 * @brief Filesystem utilities to extend the default std::filesystem tools.
 */
namespace CppUtils
{
    using FilesystemCharType = std::filesystem::path::value_type;
    using StdPathStringView = std::basic_string_view<FilesystemCharType>;

    /**
     * @brief A character that represents the most widely-accepted path separator across all platforms.
     */
    template <CppUtils::CharLike TChar = FilesystemCharType>
    constexpr TChar PrettyPathSeparator = CPPUTILS_PRETTY_PATH_SEPARATOR;

    CPPUTILS_CORE_EXPORT StdPathStringView GetStringViewFromPath(const std::filesystem::path& path);

    template <class TFwdIt, CppUtils::CharLike TChar = char>
    void ConvertPathStringToPrettyFormat(TFwdIt begin, TFwdIt end);

    /**
     * @brief Create an empty file.
     * @remark Easy overload for the typical use case to allow implicit conversions to the string view.
     */
    CPPUTILS_CORE_EXPORT bool TouchNewFile(const StdPathStringView path);

    /**
     * @brief Create an empty file.
     * @remark Template function to support all types of strings.
     */
    template <CppUtils::CharLike TChar = FilesystemCharType, class TCharTraits = std::char_traits<TChar>>
    bool TouchNewFile(const std::basic_string_view<TChar, TCharTraits> path);
}

#include <CppUtils/Core/Filesystem.inl>
