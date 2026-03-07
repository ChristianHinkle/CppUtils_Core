// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CppUtils/Core/AssertiveCode.h>

#include <utility>
#include <cassert> // @Christian: TODO: [todo][assert] After we make a general assertion macro, we should eliminate this include in this file.

// @Christian: TODO: [todo][assert] Make an assertion macro that can be manually defined by external users of our library. Also, this
// should be defined in a generally usable header file anyway.
#define CPPUTILS_ASSERT(cond, message) assert((cond) && (message))

template <CppUtils::Dereferenceable T>
constexpr decltype(auto) CppUtils::DerefAsserted(T&& param)
{
    CPPUTILS_ASSERT(static_cast<bool>(param), "Expected to be valid before dereferencing!");
    return *std::forward<T>(param);
}

// Undef this, as it is not intended to be generally used yet. [todo]
#undef CPPUTILS_ASSERT
