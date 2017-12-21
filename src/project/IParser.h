#pragma once

namespace Arcade
{
    /// \brief Defines a common interface for objects that parse data of
    /// some type and return the result in another.
    template<typename TSource, typename TTarget>
    struct IParser
    {
        /// \brief Parses the given argument and returns the result.
        virtual TTarget Parse(TSource Arg) const = 0;
    };
}