// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#include <CppUtils/Core/Filesystem.h>
#include <iostream>

void PrintCaseData(
    int errorCase,
    const std::filesystem::path& inputPath,
    const std::filesystem::path& resultPath)
{
    std::cout << "case " << errorCase << ":" << '\n';
    std::cout << "  input:  " << inputPath << '\n';
    std::cout << "  result: " << resultPath << '\n';
}

int main(int argc, char** argv)
{
    int errorCase = 0;

    // Note: Currently, we only implement test cases which safely pass on every platform. Ideally, we could verify
    // the intended behavior specifically for POSIX-based and Windows platforms. That would allow us to write more cases.

    {
        std::filesystem::path inputPath = "/MyDir";
        assert(inputPath == "/MyDir"); // Quick sanity check before proceeding.

        std::filesystem::path resultPath = CppUtils::WithTrailingSep(inputPath);

        ++errorCase;
        PrintCaseData(errorCase, inputPath, resultPath);
        if (resultPath != "/MyDir/")
        {
            return errorCase;
        }
    }

    std::cout << '\n';

    {
        std::filesystem::path inputPath = "/MyDir/";
        assert(inputPath == "/MyDir/"); // Quick sanity check before proceeding.

        std::filesystem::path resultPath = CppUtils::WithTrailingSep(inputPath);

        ++errorCase;
        PrintCaseData(errorCase, inputPath, resultPath);
        if (resultPath != "/MyDir/")
        {
            return errorCase;
        }
    }

    std::cout << '\n';

    {
        std::filesystem::path inputPath = "";
        assert(inputPath == ""); // Quick sanity check before proceeding.

        std::filesystem::path resultPath = CppUtils::WithTrailingSep(inputPath);

        ++errorCase;
        PrintCaseData(errorCase, inputPath, resultPath);
        if (resultPath != "")
        {
            return errorCase;
        }
    }

    std::cout << '\n';

    {
        std::filesystem::path inputPath = "/";
        assert(inputPath == "/"); // Quick sanity check before proceeding.

        std::filesystem::path resultPath = CppUtils::WithTrailingSep(inputPath);

        ++errorCase;
        PrintCaseData(errorCase, inputPath, resultPath);
        if (resultPath != "/")
        {
            return errorCase;
        }
    }

    std::cout << '\n';

    {
        std::filesystem::path inputPath = "MyDir";
        assert(inputPath == "MyDir"); // Quick sanity check before proceeding.

        std::filesystem::path resultPath = CppUtils::WithTrailingSep(inputPath);

        ++errorCase;
        PrintCaseData(errorCase, inputPath, resultPath);
        if (resultPath != "MyDir/")
        {
            return errorCase;
        }
    }

    std::cout << '\n';

    {
        std::filesystem::path inputPath = "MyDir/";
        assert(inputPath == "MyDir/"); // Quick sanity check before proceeding.

        std::filesystem::path resultPath = CppUtils::WithTrailingSep(inputPath);

        ++errorCase;
        PrintCaseData(errorCase, inputPath, resultPath);
        if (resultPath != "MyDir/")
        {
            return errorCase;
        }
    }

    std::cout << '\n';

    {
        std::filesystem::path inputPath = std::filesystem::absolute("/MyDir");

        std::filesystem::path resultPath = CppUtils::WithTrailingSep(inputPath);

        ++errorCase;
        PrintCaseData(errorCase, inputPath, resultPath);
        if (resultPath != std::filesystem::absolute("/MyDir/"))
        {
            return errorCase;
        }
    }

    std::cout << '\n';

    {
        std::filesystem::path inputPath = std::filesystem::absolute("/MyDir/");

        std::filesystem::path resultPath = CppUtils::WithTrailingSep(inputPath);

        ++errorCase;
        PrintCaseData(errorCase, inputPath, resultPath);
        if (resultPath != std::filesystem::absolute("/MyDir/"))
        {
            return errorCase;
        }
    }

    return 0;
}

