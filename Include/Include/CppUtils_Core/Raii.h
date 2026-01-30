// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CppUtils_StdReimpl/Concepts.h>
#include <utility>
#include <type_traits>

namespace CppUtils
{
    /**
     * @brief @Christian: TODO: [todo][tests] No tests are written for this utility, and it's not currently used anywhere.
     */
    template <StdReimpl::invocable TFunctor>
    struct OnScopeExitStruct final
    {
        OnScopeExitStruct(const OnScopeExitStruct&) = delete;
        OnScopeExitStruct(OnScopeExitStruct&&) noexcept = delete;

        OnScopeExitStruct& operator=(const OnScopeExitStruct&) = delete;
        OnScopeExitStruct& operator=(OnScopeExitStruct&&) noexcept = delete;

        // Construct from rvalue callback.
        OnScopeExitStruct(TFunctor&& callback)
            : Callback(std::move(callback))
        {
        }
        // Construct from lvalue callback.
        OnScopeExitStruct(const TFunctor& callback)
            : Callback(callback)
        {
        }

        // Destructor, which invokes the callback.
        ~OnScopeExitStruct()
        {
            std::move(Callback)();
        }

    private:

        TFunctor Callback;
    };

    /**
     * @brief @Christian: TODO: [todo][tests] No tests are written for this utility, and it's not currently used anywhere.
     */
    template <StdReimpl::invocable TFunctor>
    decltype(auto) OnScopeExit(TFunctor&& callback)
    {
        return OnScopeExitStruct<std::decay_t<TFunctor>>(std::forward<TFunctor>(callback));
    }
}
