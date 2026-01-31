// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#include <CppUtils/Core/Concepts.h>

static_assert(CppUtils::CharLike<char>);
static_assert(CppUtils::CharLike<wchar_t>);
static_assert(CppUtils::CharLike<char8_t>);
static_assert(CppUtils::CharLike<char16_t>);
static_assert(CppUtils::CharLike<char32_t>);
