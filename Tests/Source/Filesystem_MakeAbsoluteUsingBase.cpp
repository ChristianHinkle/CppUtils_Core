// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#include <CppUtils/Core/Filesystem.h>
#include <iostream>
#include <CppUtils/StdReimpl/utility.h>

//
// Example cases to consider (note: assume Windows OS since its path semantics are the most complex):
//
// ---
//
// Simple cases/examples:
//
// ---
//
// p = "Scenes/0001/Cuts/0001/Timesheet.xdts"
// base = "Q:/Projects/MyAnimation"
//
// Result: "Q:/Projects/MyAnimation/Scenes/0001/Cuts/0001/Timesheet.xdts"
//
// ---
//
// p = "Q:/Projects/MyAnimation/Scenes/0001/Cuts/0001/Timesheet.xdts"
// base = "Q:/Projects/MyAnimation"
//
// Result: ERROR! `p` must be relative.
//
// ---
//
// p = "Scenes/0001/Cuts/0001/Timesheet.xdts"
// base = "Projects/MyAnimation"
//
// Result: ERROR! `base` must be absolute.
//
// ---
//
// Root directory paths without root name cases/examples:
//
// ---
//
// p = "Scenes/0001/Cuts/0001/Timesheet.xdts"
// base = "/Projects/MyAnimation"
//
// Result: ERROR! `base` must be absolute.
//
// ---
//
// p = "/Scenes/0001/Cuts/0001/Timesheet.xdts"
// base = "Q:/Projects/MyAnimation"
//
// Result: ERROR! `p` must not have a root directory.
//
// ---
//
// p = "/Scenes/0001/Cuts/0001/Timesheet.xdts"
// base = "/Projects/MyAnimation"
//
// Result: ERROR! `p` must not have a root directory. `base` must be absolute.
//
// ---
//
// Root name edge cases/examples:
//
// ---
//
// p = "Q:Scenes/0001/Cuts/0001/Timesheet.xdts"
// base = "Q:/Projects/MyAnimation"
//
// Result: ERROR! `p` must not specify a root name.
//
// ---
//
// p = "P:Scenes/0001/Cuts/0001/Timesheet.xdts"
// base = "Q:/Projects/MyAnimation"
//
// Result: ERROR! `p` must not specify a root name. In this case the root names differ, which is why we avoid relative paths with root names in the first place.
//
// ---
//
// Network cases/examples:
//
// ---
//
// p = "Scenes/0001/Cuts/0001/Timesheet.xdts"
// base = "//server/Projects/MyAnimation"
//
// base.is_absolute(): true
// base.root_name(): "//server"
// base.has_root_directory(): true
//
// Result: "//server/Projects/MyAnimation/Scenes/0001/Cuts/0001/Timesheet.xdts"
//
// ---
//
// p = "//server/Scenes/0001/Cuts/0001/Timesheet.xdts"
// base = "Q:/Projects/MyAnimation"
//
// Result: ERROR! `p` must be relative.
//
// ---
//
// p = "//server/Scenes/0001/Cuts/0001/Timesheet.xdts"
// base = "//server/Projects/MyAnimation"
//
// Result: ERROR! `p` must be relative.
//
// ---
//
// p = "MyFolder/MyFile.txt"
// base = "//server/"
//
// base.is_absolute(): true
// base.root_name(): "//server"
// base.has_root_directory(): true
//
// Result: "//server/MyFolder/MyFile.txt"
//
// ---
//
// p = "MyFolder/MyFile.txt"
// base = "//server"
//
// base.is_absolute(): false
// base.root_name(): "//server"
// base.has_root_directory(): false
//
// Result: ERROR! `base` must be absolute.
//
// ---
//
// Empty path cases/examples:
//
// ---
//
// p = ""
// base = "Q:/Projects/MyAnimation"
//
// Result: "Q:/Projects/MyAnimation/"
//
// ---
//
// p = "Scenes/0001/Cuts/0001/Timesheet.xdts"
// base = ""
//
// Result: ERROR! `base` must be absolute.
//
// ---
//
// p = ""
// base = ""
//
// Result: ERROR! `base` must be absolute.
//
int main(int argc, char** argv)
{
    int errorCase = 0;

    // Note: Currently, we only implement test cases which safely pass on every platform. Ideally, we could verify
    // the intended behavior specifically for POSIX-based and Windows platforms. That would allow us to write more cases.

    // p = "Scenes/0001/Cuts/0001/Timesheet.xdts"
    // base = std::filesystem::absolute("/Projects/MyAnimation")
    //
    // Result: std::filesystem::absolute("/Projects/MyAnimation/Scenes/0001/Cuts/0001/Timesheet.xdts")
    {
        CppUtils::ExpectedResult result =
            CppUtils::MakeAbsoluteUsingBase(
                "Scenes/0001/Cuts/0001/Timesheet.xdts",
                std::filesystem::absolute("/Projects/MyAnimation")
            );

        ++errorCase;
        if (result.IsError())
        {
            return errorCase;
        }

        std::filesystem::path value = std::move(result).GetValue();

        ++errorCase;
        std::cout << "case " << errorCase << ": result: " << value << '\n';
        if (value != std::filesystem::absolute("/Projects/MyAnimation/Scenes/0001/Cuts/0001/Timesheet.xdts"))
        {
            return errorCase;
        }
    }

#if 0 // Disabled for now because trailing separator behavior may not be consistent across all platforms.
    // p = ""
    // base = std::filesystem::absolute("/Projects/MyAnimation")
    //
    // Result: std::filesystem::absolute("/Projects/MyAnimation/")
    {
        CppUtils::ExpectedResult result =
            CppUtils::MakeAbsoluteUsingBase(
                "",
                std::filesystem::absolute("/Projects/MyAnimation")
            );

        ++errorCase;
        if (result.IsError())
        {
            return errorCase;
        }

        std::filesystem::path value = std::move(result).GetValue();

        ++errorCase;
        std::cout << "case " << errorCase << ": result: " << value << '\n';
        if (value != std::filesystem::absolute("/Projects/MyAnimation/"))
        {
            return errorCase;
        }
    }
#endif

    // p = std::filesystem::absolute("/Projects/MyAnimation/Scenes/0001/Cuts/0001/Timesheet.xdts")
    // base = std::filesystem::absolute("/Projects/MyAnimation")
    //
    // Result: ERROR! `p` must be relative.
    {
        CppUtils::ExpectedResult result =
            CppUtils::MakeAbsoluteUsingBase(
                std::filesystem::absolute("/Projects/MyAnimation/Scenes/0001/Cuts/0001/Timesheet.xdts"),
                std::filesystem::absolute("/Projects/MyAnimation")
            );

        ++errorCase;
        if (!result.IsError())
        {
            return errorCase;
        }

        CppUtils::ErrorCode_MakeAbsoluteUsingBase error = std::move(result).GetError();

        ++errorCase;
        std::cout << "case " << errorCase << ": result: " << StdReimpl::to_underlying(error) << '\n';
        if (error != CppUtils::ErrorCode_MakeAbsoluteUsingBase::PathNotRelative)
        {
            return errorCase;
        }
    }

    // p = "Scenes/0001/Cuts/0001/Timesheet.xdts"
    // base = "Projects/MyAnimation"
    //
    // Result: ERROR! `base` must be absolute.
    {
        CppUtils::ExpectedResult result =
            CppUtils::MakeAbsoluteUsingBase(
                "Scenes/0001/Cuts/0001/Timesheet.xdts",
                "Projects/MyAnimation"
            );

        ++errorCase;
        if (!result.IsError())
        {
            return errorCase;
        }

        CppUtils::ErrorCode_MakeAbsoluteUsingBase error = std::move(result).GetError();

        ++errorCase;
        std::cout << "case " << errorCase << ": result: " << StdReimpl::to_underlying(error) << '\n';
        if (error != CppUtils::ErrorCode_MakeAbsoluteUsingBase::BaseIsNotAbsolute)
        {
            return errorCase;
        }
    }

    return 0;
}
