// Copyright (c) 2023-2025 Christian Hinkle, BriFilesysteman Hinkle.

#include <CppUtils/Core/Filesystem.h>

#include <filesystem>
#include <string>
#include <utility>
#include <cassert>
#include <CppUtils/Core/Lifetime.h>

namespace
{
    template <bool shouldUseEc>
    std::filesystem::path Internal_MakeAbsoluteUsingBase_BoostLogic(
        const std::filesystem::path& p,
        const std::filesystem::path& base,
        std::error_code& ec);
}

CppUtils::ExpectedResult<std::filesystem::path, CppUtils::ErrorCode_MakeAbsolute> CppUtils::MakeAbsolute(
    const std::filesystem::path& p)
{
    CppUtils::ExpectedResult relativePathValidation = ValidateRelativePathCanBeMadeAbsolute(p);
    if (relativePathValidation.IsError())
    {
        switch (relativePathValidation.GetError())
        {
        case CppUtils::ErrorCode_ValidateRelativePathCanBeMadeAbsolute::PathNotRelative:
            return CppUtils::ErrorCode_MakeAbsolute::PathNotRelative;
        case CppUtils::ErrorCode_ValidateRelativePathCanBeMadeAbsolute::RelativePathHasRootName:
            return CppUtils::ErrorCode_MakeAbsolute::RelativePathHasRootName;
        case CppUtils::ErrorCode_ValidateRelativePathCanBeMadeAbsolute::RelativePathHasRootDirectory:
            return CppUtils::ErrorCode_MakeAbsolute::RelativePathHasRootDirectory;
        }

        assert(false); // Unhandled enum case!
        std::abort();
    }

    return std::filesystem::absolute(p);
}

CppUtils::ExpectedResult<std::filesystem::path, CppUtils::ErrorCode_MakeAbsoluteWithEc> CppUtils::MakeAbsolute(
    const std::filesystem::path& p,
    std::error_code& ec)
{
    ec.clear();

    CppUtils::ExpectedResult relativePathValidation = ValidateRelativePathCanBeMadeAbsolute(p);
    if (relativePathValidation.IsError())
    {
        switch (relativePathValidation.GetError())
        {
        case CppUtils::ErrorCode_ValidateRelativePathCanBeMadeAbsolute::PathNotRelative:
            return CppUtils::ErrorCode_MakeAbsoluteWithEc::PathNotRelative;
        case CppUtils::ErrorCode_ValidateRelativePathCanBeMadeAbsolute::RelativePathHasRootName:
            return CppUtils::ErrorCode_MakeAbsoluteWithEc::RelativePathHasRootName;
        case CppUtils::ErrorCode_ValidateRelativePathCanBeMadeAbsolute::RelativePathHasRootDirectory:
            return CppUtils::ErrorCode_MakeAbsoluteWithEc::RelativePathHasRootDirectory;
        }

        assert(false); // Unhandled enum case!
        std::abort();
    }

    auto result = std::filesystem::absolute(p, ec);

    if (ec)
    {
        return CppUtils::ErrorCode_MakeAbsoluteWithEc::StdErrorCode;
    }

    return result;
}

CppUtils::ExpectedResult<std::filesystem::path, CppUtils::ErrorCode_MakeAbsoluteUsingBase> CppUtils::MakeAbsoluteUsingBase(
    const std::filesystem::path& p,
    const std::filesystem::path& base)
{
    CppUtils::ExpectedResult relativePathValidation = ValidateRelativePathCanBeMadeAbsolute(p);
    if (relativePathValidation.IsError())
    {
        switch (relativePathValidation.GetError())
        {
        case ErrorCode_ValidateRelativePathCanBeMadeAbsolute::PathNotRelative:
            return ErrorCode_MakeAbsoluteUsingBase::PathNotRelative;
        case ErrorCode_ValidateRelativePathCanBeMadeAbsolute::RelativePathHasRootName:
            return ErrorCode_MakeAbsoluteUsingBase::RelativePathHasRootName;
        case ErrorCode_ValidateRelativePathCanBeMadeAbsolute::RelativePathHasRootDirectory:
            return ErrorCode_MakeAbsoluteUsingBase::RelativePathHasRootDirectory;
        }

        assert(false); // Unhandled enum case!
        std::abort();
    }

    if (!base.is_absolute())
    {
        return ErrorCode_MakeAbsoluteUsingBase::BaseIsNotAbsolute;
    }

    return base / p;
}

CppUtils::ExpectedResult<void, CppUtils::ErrorCode_ValidateRelativePathCanBeMadeAbsolute> CppUtils::ValidateRelativePathCanBeMadeAbsolute(
    const std::filesystem::path& p)
{
    // Note: This check is a bit redundant considering the additional checks that follow it since, on the
    // usual operating systems (POSIX-based and Windows), `!p.has_root_name() && !p.has_root_directory()` already
    // implies `p.is_relative()`. But there could technically be a platform that defines path semantics differently so
    // we explicitly enforce our requirement here.
    if (!p.is_relative())
    {
        return ErrorCode_ValidateRelativePathCanBeMadeAbsolute::PathNotRelative;
    }

    if (p.has_root_name())
    {
        return ErrorCode_ValidateRelativePathCanBeMadeAbsolute::RelativePathHasRootName;
    }

    if (p.has_root_directory())
    {
        return ErrorCode_ValidateRelativePathCanBeMadeAbsolute::RelativePathHasRootDirectory;
    }

    return {};
}

std::filesystem::path CppUtils::MakeAbsoluteUsingBase_BoostLogic(
    const std::filesystem::path& p,
    const std::filesystem::path& base)
{
    constexpr bool shouldUseEc = false;
    return Internal_MakeAbsoluteUsingBase_BoostLogic<shouldUseEc>(p, base, CppUtils::Materialize(std::error_code{}));
}

std::filesystem::path CppUtils::MakeAbsoluteUsingBase_BoostLogic(
    const std::filesystem::path& p,
    const std::filesystem::path& base,
    std::error_code& ec)
{
    constexpr bool shouldUseEc = true;
    return Internal_MakeAbsoluteUsingBase_BoostLogic<shouldUseEc>(p, base, ec);
}

bool CppUtils::IsRootPath(const std::filesystem::path& p)
{
    const bool isRootPath = p.has_root_directory() && !p.has_relative_path();

#ifndef NDEBUG
    if (isRootPath)
    {
        // Ensure our logic is consistent.
        assert(p == p.root_path());
    }
#endif

    return isRootPath;
}

std::filesystem::path CppUtils::StripTrailingSeparator(const std::filesystem::path& p)
{
    return StripTrailingSeparator(std::filesystem::path{p});
}
std::filesystem::path CppUtils::StripTrailingSeparator(std::filesystem::path&& p)
{
    if (p.has_relative_path() && !p.has_filename())
    {
        // TODO: [todo] We should make a version of `parent_path` that supports in-place modification and move semantics. Because
        // right now this move isn't doing anything since they don't have an rvalue overload.
        return std::move(p).parent_path();
    }

    return p;
}

std::filesystem::path CppUtils::WithTrailingSeparator(const std::filesystem::path& p)
{
    return WithTrailingSeparator(std::filesystem::path{p});
}
std::filesystem::path CppUtils::WithTrailingSeparator(std::filesystem::path&& p)
{
    if (p.has_relative_path() && p.has_filename())
    {
        return std::move(p.operator/=(std::filesystem::path{}));
    }

    return p;
}

CppUtils::StdPathStringView CppUtils::GetStringViewFromPath(const std::filesystem::path& path)
{
    return StdPathStringView(path.native().c_str(), path.native().length());
}

bool CppUtils::TouchNewFile(const StdPathStringView path)
{
    return TouchNewFile<>(path);
}

namespace
{
    template <bool shouldUseEc>
    std::filesystem::path Internal_MakeAbsoluteUsingBase_BoostLogic(
        const std::filesystem::path& p,
        const std::filesystem::path& base,
        std::error_code& ec)
    {
        if constexpr (shouldUseEc)
        {
            ec.clear();
        }

        if (p.is_absolute())
        {
            return p;
        }

        std::filesystem::path baseAbsolute;
        if constexpr (shouldUseEc)
        {
            baseAbsolute = std::filesystem::absolute(base, ec);

            // If it errored then do not proceed to further logic.
            if (ec)
            {
                return {};
            }
        }
        else
        {
            baseAbsolute = std::filesystem::absolute(base);
        }

        if (p.has_root_name())
        {
            if (p.has_root_directory())
            {
                return p;
            }

            auto pRootName = p.root_name();
            auto baseAbsoluteRootDirectory = baseAbsolute.root_directory();
            auto baseAsRelative = baseAbsolute.relative_path();
            auto pRelative = p.relative_path();

            return std::move(pRootName.operator/=(baseAbsoluteRootDirectory).operator/=(baseAsRelative).operator/=(pRelative));
        }

        if (p.has_root_directory())
        {
            return std::move(baseAbsolute.root_name().operator/=(p));
        }

        return std::move(baseAbsolute.operator/=(p));
    }
}
