// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#include <CppUtils/Core/Filesystem.h>
#include <iostream>

int main(int argc, char** argv)
{
    int errorCase = 0;

    // Note: Currently, we only implement test cases which safely pass on every platform. Ideally, we could verify
    // the intended behavior specifically for POSIX-based and Windows platforms. That would allow us to write more cases.

    ++errorCase;
    if (!CppUtils::IsRootPath("/"))
    {
        return errorCase;
    }

    ++errorCase;
    if (!CppUtils::IsRootPath(std::filesystem::absolute("/")))
    {
        return errorCase;
    }

    // A root name path alone should not be considered a "root path". E.g., on Windows, the relative path "C:" is not a "root path".
    ++errorCase;
    if (CppUtils::IsRootPath(std::filesystem::current_path().root_name()))
    {
        return errorCase;
    }

    // Empty path should not be considered a "root path".
    ++errorCase;
    if (CppUtils::IsRootPath(""))
    {
        return errorCase;
    }

    // A relative path should not be considered a "root path".
    ++errorCase;
    if (CppUtils::IsRootPath("MyDir/MyFile.txt"))
    {
        return errorCase;
    }

    // Make sure relative paths with a trailing separators do not get by either.
    ++errorCase;
    if (CppUtils::IsRootPath("MyDir/"))
    {
        return errorCase;
    }

    return 0;
}
