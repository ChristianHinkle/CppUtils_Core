// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CppUtils_Core_Export.h>
#include <filesystem>
#include <string_view>
#include <string>
#include <CppUtils/Core/Concepts.h>
#include <CppUtils/Core/ExpectedResult.h>

/**
 * @brief String literal alternative to `CppUtils::GenericPathSeparator`.
 */
#define CPPUTILS_GENERIC_PATH_SEPARATOR '/'

/**
 * @brief Filesystem utilities to extend the default std::filesystem tools.
 */
namespace CppUtils
{
    using FilesystemCharType = std::filesystem::path::value_type;
    using StdPathStringView = std::basic_string_view<FilesystemCharType>;

    enum class ErrorCode_MakeAbsolute
    {
        PathNotRelative,
        RelativePathHasRootName,
        RelativePathHasRootDirectory,
    };

    enum class ErrorCode_MakeAbsoluteWithEc
    {
        PathNotRelative,
        RelativePathHasRootName,
        RelativePathHasRootDirectory,
        StdErrorCode,
    };

    /**
     * @brief Makes an absolute path from a relative path, erroring if the given path is not valid for this operation.
     *
     * Required invariants:
     * - p.is_relative()
     * - !p.has_root_name()
     * - !p.has_root_directory()
     */
    CPPUTILS_CORE_EXPORT CppUtils::ExpectedResult<std::filesystem::path, ErrorCode_MakeAbsolute> MakeAbsolute(
        const std::filesystem::path& p);

    /**
     * @brief Overload of `MakeAbsolute` which uses std error code.
     */
    CPPUTILS_CORE_EXPORT CppUtils::ExpectedResult<std::filesystem::path, ErrorCode_MakeAbsoluteWithEc> MakeAbsolute(
        const std::filesystem::path& p,
        std::error_code& ec);

    enum class ErrorCode_MakeAbsoluteUsingBase
    {
        PathNotRelative,
        RelativePathHasRootName,
        RelativePathHasRootDirectory,
        BaseIsNotAbsolute,
    };

    /**
     * @brief Given a relative path and a base absolute path, return a combined absolute path.
     *
     * Required invariants:
     * - p.is_relative()
     * - !p.has_root_name()
     * - !p.has_root_directory()
     * - base.is_absolute()
     */
    CPPUTILS_CORE_EXPORT CppUtils::ExpectedResult<std::filesystem::path, ErrorCode_MakeAbsoluteUsingBase> MakeAbsoluteUsingBase(
        const std::filesystem::path& p,
        const std::filesystem::path& base);

    enum class ErrorCode_ValidateRelativePathCanBeMadeAbsolute
    {
        PathNotRelative,
        RelativePathHasRootName,
        RelativePathHasRootDirectory,
    };

    /**
     * @brief Test whether a path can successfully be made absolute.
     */
    CPPUTILS_CORE_EXPORT CppUtils::ExpectedResult<void, ErrorCode_ValidateRelativePathCanBeMadeAbsolute> ValidateRelativePathCanBeMadeAbsolute(
        const std::filesystem::path& p);

    /**
     * @brief Mirrors the overall logic of Boost.Filesystem's `boost::filesystem::absolute` function, according to their
     *        documentation: https://boost.org/doc/libs/latest/libs/filesystem/doc/reference.html#absolute.
     */
    CPPUTILS_CORE_EXPORT std::filesystem::path MakeAbsoluteUsingBase_BoostLogic(
        const std::filesystem::path& p,
        const std::filesystem::path& base);

    /**
     * @brief Overload of `MakeAbsoluteUsingBase_BoostLogic` which uses std error code.
     */
    CPPUTILS_CORE_EXPORT std::filesystem::path MakeAbsoluteUsingBase_BoostLogic(
        const std::filesystem::path& p,
        const std::filesystem::path& base,
        std::error_code& ec);

    /**
     * @brief Returns true for any path is a root path (not necessarily an absolute path). E.g., on Windows, the
     *        paths "/" and "C:/" are both "root paths" even though only the one specifying a root name is an absolute path.
     */
    CPPUTILS_CORE_EXPORT bool IsRootPath(const std::filesystem::path& p);

    /**
     * @brief A character that represents the most widely-accepted path separator across all platforms.
     */
    template <CppUtils::CharLike TChar = FilesystemCharType>
    constexpr TChar GenericPathSeparator = CPPUTILS_GENERIC_PATH_SEPARATOR;

    CPPUTILS_CORE_EXPORT StdPathStringView GetStringViewFromPath(const std::filesystem::path& path);

    template <class TFwdIt, CppUtils::CharLike TChar = char>
    void ConvertPathStringToGenericFormat(TFwdIt begin, TFwdIt end);

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
