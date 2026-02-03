// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

namespace CppUtils
{
    /**
     * @brief An alternative to `std::conditional_t` that avoids instantiating both of
     *        the true and false result types.
     * @todo Add constraints for the lambda template parameter.
     * @todo Document.
     */
    template <bool cond, auto lambda>
    using ConditionalShortCircuited = decltype(lambda.operator()<cond>());
}
