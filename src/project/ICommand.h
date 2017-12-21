#pragma once

namespace Arcade
{
    /// \brief Defines common functionality for generic commands, i.e.
    /// actions that can be applied to a given target.
    template<typename T>
    struct ICommand
    {
        /// \brief Executes the command and returns a boolean that tells if
        /// the operation has completed successfully.
        virtual bool Execute(T Target) = 0;
    };
}