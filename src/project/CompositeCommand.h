#pragma once
#include <memory>
#include "ArraySlice.h"
#include "ICommand.h"

namespace Arcade
{
    /// \brief Defines a sequence of commands that can be used as a
    /// single command.
    template<typename T>
    class CompositeCommand : public virtual ICommand<T>
    {
    public:
        /// \brief Creates a new composite command.
        CompositeCommand(stdx::ArraySlice<std::shared_ptr<ICommand<T>>> Commands);

        /// \brief Executes the command and returns a boolean that tells if
        /// the operation has completed successfully.
        bool Execute(T Target) override;

        /// \brief Gets an array of commands that will be executed in
        /// sequence.
        stdx::ArraySlice<std::shared_ptr<ICommand<T>>> GetCommands() const;
    private:
        /// \brief Sets an array of commands that will be executed in
        /// sequence.
        void SetCommands(stdx::ArraySlice<std::shared_ptr<ICommand<T>>> value);

        stdx::ArraySlice<std::shared_ptr<ICommand<T>>> Commands_value;
    };
}

#include "CompositeCommand.hxx"